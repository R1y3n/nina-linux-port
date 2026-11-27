	/* Miles Sound System (mss32.dll) SDL2 Audio backend for LithTech native Linux port */
#include "win.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_2D_SAMPLES  64
#define MAX_3D_SAMPLES  64
#define MAX_STREAMS      8
#define MIX_FREQ     44100

/* Miles status & format constants */
#define SMP_FREE       0x0001
#define SMP_DONE       0x0002
#define SMP_PLAYING    0x0004
#define SMP_STOPPED    0x0008

#define WAVE_FORMAT_PCM       1
#define WAVE_FORMAT_IMA_ADPCM 0x0011

#define DIG_F_MONO_8      0x0000
#define DIG_F_MONO_16     0x0001
#define DIG_F_STEREO_8    0x0002
#define DIG_F_STEREO_16   0x0003

#pragma pack(push, 1)
typedef struct {
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
} MSS_WAVEFORMATEX;
#pragma pack(pop)

typedef struct {
    int32_t  format;
    void    *data_ptr;
    uint32_t data_len;
    uint32_t rate;
    int32_t  channels;
    int32_t  bits;
    uint32_t block_size;
    void    *initial_ptr;
    uint32_t initial_len;
} AILSOUNDINFO;

typedef struct {
    int      allocated;
    uint32_t status;
    int16_t *pcm;          /* Interleaved or mono 16-bit PCM owned by slot */
    uint32_t frames;       /* Total sample frames */
    int      channels;     /* 1 or 2 */
    int      bits;         /* 8 or 16 */
    int      rate;         /* Hz */
    double   pos;          /* Current playback frame */
    int      volume;       /* 0..127 */
    int      pan;          /* 0..127 (64 = center) */
    int      loop_count;   /* 0 = infinite, 1 = once, N = N times */
    int      loops_done;
    uint8_t *raw_copy;     /* Raw buffer copy so set_sample_address + set_sample_type work in any order */
    uint32_t raw_len;
    int32_t  user_data[8];
} Sample2D;

typedef struct {
    int      allocated;
    uint32_t status;
    int16_t *pcm;
    uint32_t frames;
    int      channels;
    int      rate;
    double   pos;
    int      volume;       /* 0..127 */
    int      loop_count;   /* 0 = infinite */
    int      loops_done;
    float    x, y, z;
    float    vx, vy, vz;
    float    min_dist;
    float    max_dist;
    float    occlusion;
    float    obstruction;
    float    effects_level;
    int32_t  user_data[8];
} Sample3D;

typedef struct {
    int      allocated;
    uint32_t status;
    int16_t *pcm;
    uint32_t frames;
    int      channels;
    int      rate;
    double   pos;
    int      volume;       /* 0..127 */
    int      pan;          /* 0..127 */
    int      loop_count;   /* 0 = infinite */
    int      loops_done;
    int32_t  user_data[8];
} AudioStream;

static SDL_AudioDeviceID g_dev = 0;
static int               g_out_rate = MIX_FREQ;
static int               g_master_vol = 127;
static int               g_prefs[64];
static char              g_last_err[128] = "";

static Sample2D          g_smp2d[MAX_2D_SAMPLES];
static Sample3D          g_smp3d[MAX_3D_SAMPLES];
static AudioStream       g_streams[MAX_STREAMS];

/* 3D Listener state */
static float g_lis_x = 0.0f, g_lis_y = 0.0f, g_lis_z = 0.0f;
static float g_lis_fx = 0.0f, g_lis_fy = 0.0f, g_lis_fz = 1.0f;
static float g_lis_ux = 0.0f, g_lis_uy = 1.0f, g_lis_uz = 0.0f;
static float g_lis_vx = 0.0f, g_lis_vy = 0.0f, g_lis_vz = 0.0f;
static int   g_room_type = 0;
static int32_t g_lis_user_data[8];

/* Sentinel handles */
#define HANDLE_DRIVER   ((void*)0x4D535301u)
#define HANDLE_3DPROV   ((void*)0x4D535302u)
#define HANDLE_LISTENER ((void*)0x4D535303u)

static void audio_lock(void)   { if (g_dev) SDL_LockAudioDevice(g_dev); }
static void audio_unlock(void) { if (g_dev) SDL_UnlockAudioDevice(g_dev); }

/* ---- IMA ADPCM Decoder (Mono & Stereo) ---- */
static const int ima_index_table[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};

static const int ima_step_table[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31,
    34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143,
    157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658,
    724, 796, 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499,
    2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630,
    9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623,
    27086, 29794, 32767
};

static int16_t ima_decode_nibble(int nibble, int *predictor, int *step_idx) {
    int step = ima_step_table[*step_idx];
    int diff = step >> 3;
    if (nibble & 1) diff += step >> 2;
    if (nibble & 2) diff += step >> 1;
    if (nibble & 4) diff += step;
    if (nibble & 8) diff = -diff;

    *predictor += diff;
    if (*predictor > 32767)  *predictor = 32767;
    if (*predictor < -32768) *predictor = -32768;

    *step_idx += ima_index_table[nibble & 15];
    if (*step_idx < 0)  *step_idx = 0;
    if (*step_idx > 88) *step_idx = 88;

    return (int16_t)(*predictor);
}

static int16_t *decode_ima_adpcm(const uint8_t *src, uint32_t src_len, int channels, uint32_t block_align, uint32_t *out_frames) {
    if (!src || src_len < 4 || channels < 1 || channels > 2) return NULL;
    if (block_align < (uint32_t)(4 * channels)) block_align = (uint32_t)(4 * channels);

    uint32_t num_blocks = src_len / block_align;
    if (num_blocks == 0) return NULL;

    uint32_t data_bytes_per_block = block_align - (4 * channels);
    uint32_t samples_per_block = 1 + (data_bytes_per_block * 2) / (uint32_t)channels;
    uint32_t total_frames = num_blocks * samples_per_block;

    int16_t *out = (int16_t*)malloc(total_frames * channels * sizeof(int16_t));
    if (!out) return NULL;

    uint32_t out_pos = 0;
    for (uint32_t b = 0; b < num_blocks; b++) {
        const uint8_t *blk = src + b * block_align;
        if (channels == 1) {
            int pred = (int16_t)(blk[0] | (blk[1] << 8));
            int idx  = blk[2];
            if (idx < 0) idx = 0; else if (idx > 88) idx = 88;
            out[out_pos++] = (int16_t)pred;

            for (uint32_t i = 4; i < block_align; i++) {
                uint8_t byte = blk[i];
                out[out_pos++] = ima_decode_nibble(byte & 0x0F, &pred, &idx);
                out[out_pos++] = ima_decode_nibble((byte >> 4) & 0x0F, &pred, &idx);
            }
        } else {
            int pred_l = (int16_t)(blk[0] | (blk[1] << 8));
            int idx_l  = blk[2];
            int pred_r = (int16_t)(blk[4] | (blk[5] << 8));
            int idx_r  = blk[6];
            if (idx_l < 0) idx_l = 0; else if (idx_l > 88) idx_l = 88;
            if (idx_r < 0) idx_r = 0; else if (idx_r > 88) idx_r = 88;

            out[out_pos++] = (int16_t)pred_l;
            out[out_pos++] = (int16_t)pred_r;

            const uint8_t *p = blk + 8;
            uint32_t rem = block_align - 8;
            while (rem >= 8) {
                for (int w = 0; w < 4; w++) {
                    uint8_t bl = p[w];
                    uint8_t br = p[w + 4];
                    out[out_pos++] = ima_decode_nibble(bl & 0x0F, &pred_l, &idx_l);
                    out[out_pos++] = ima_decode_nibble(br & 0x0F, &pred_r, &idx_r);
                    out[out_pos++] = ima_decode_nibble((bl >> 4) & 0x0F, &pred_l, &idx_l);
                    out[out_pos++] = ima_decode_nibble((br >> 4) & 0x0F, &pred_r, &idx_r);
                }
                p += 8;
                rem -= 8;
            }
        }
    }

    *out_frames = out_pos / (uint32_t)channels;
    return out;
}

/* ---- WAV / AILSOUNDINFO Conversion to 16-bit PCM ---- */
static int16_t *decode_to_pcm16(int format, const uint8_t *data, uint32_t len, int channels, int bits, uint32_t block_align, uint32_t *out_frames) {
    if (!data || len == 0 || channels < 1 || channels > 2) return NULL;

    if (format == WAVE_FORMAT_IMA_ADPCM) {
        return decode_ima_adpcm(data, len, channels, block_align, out_frames);
    }

    if (format == WAVE_FORMAT_PCM) {
        if (bits == 8) {
            uint32_t frames = len / (uint32_t)channels;
            if (frames == 0) return NULL;
            int16_t *pcm = (int16_t*)malloc(frames * channels * sizeof(int16_t));
            if (!pcm) return NULL;
            for (uint32_t i = 0; i < frames * (uint32_t)channels; i++) {
                pcm[i] = (int16_t)(((int)data[i] - 128) << 8);
            }
            *out_frames = frames;
            return pcm;
        } else if (bits == 16) {
            uint32_t frames = len / (uint32_t)(2 * channels);
            if (frames == 0) return NULL;
            int16_t *pcm = (int16_t*)malloc(frames * channels * sizeof(int16_t));
            if (!pcm) return NULL;
            memcpy(pcm, data, frames * channels * sizeof(int16_t));
            *out_frames = frames;
            return pcm;
        }
    }
    return NULL;
}

static int16_t *parse_wav_memory(const uint8_t *buf, uint32_t max_len, int *out_rate, int *out_channels, uint32_t *out_frames) {
    if (!buf || max_len < 44) return NULL;
    if (memcmp(buf, "RIFF", 4) != 0 || memcmp(buf + 8, "WAVE", 4) != 0) return NULL;

    uint16_t fmt_tag = 0, channels = 0, block_align = 0, bits = 0;
    uint32_t rate = 0;
    const uint8_t *data_ptr = NULL;
    uint32_t data_len = 0;

    uint32_t pos = 12;
    while (pos + 8 <= max_len) {
        const uint8_t *ch = buf + pos;
        uint32_t ch_sz = *(const uint32_t*)(ch + 4);
        pos += 8;
        if (pos + ch_sz > max_len) ch_sz = max_len - pos;

        if (memcmp(ch, "fmt ", 4) == 0 && ch_sz >= 16) {
            fmt_tag     = *(const uint16_t*)(buf + pos + 0);
            channels    = *(const uint16_t*)(buf + pos + 2);
            rate        = *(const uint32_t*)(buf + pos + 4);
            block_align = *(const uint16_t*)(buf + pos + 12);
            bits        = *(const uint16_t*)(buf + pos + 14);
        } else if (memcmp(ch, "data", 4) == 0) {
            data_ptr = buf + pos;
            data_len = ch_sz;
        }
        pos += (ch_sz + 1) & ~1u;
    }

    if (!data_ptr || data_len == 0 || channels == 0 || rate == 0) return NULL;
    *out_rate = (int)rate;
    *out_channels = (int)channels;
    return decode_to_pcm16(fmt_tag, data_ptr, data_len, channels, bits, block_align, out_frames);
}

static void rebuild_sample2d_pcm(Sample2D *s) {
    if (!s || !s->raw_copy || s->raw_len == 0) return;
    uint32_t frames = 0;
    int16_t *pcm = decode_to_pcm16(WAVE_FORMAT_PCM, s->raw_copy, s->raw_len,
                                   s->channels, s->bits, 0, &frames);
    if (!pcm) return;

    audio_lock();
    free(s->pcm);
    s->pcm = pcm;
    s->frames = frames;
    s->pos = 0.0;
    s->loops_done = 0;
    audio_unlock();
}

/* ---- SDL2 Audio Mixer Callback ---- */
static void mix_source(int32_t *mix_l, int32_t *mix_r, int out_frames,
                       const int16_t *pcm, uint32_t total_frames, int channels, int rate,
                       double *p_pos, int loop_count, int *p_loops_done,
                       float gain_l, float gain_r, int *p_active) {
    if (!pcm || total_frames == 0 || !(*p_active)) return;

    double step = (double)rate / (double)g_out_rate;
    double pos = *p_pos;

    for (int i = 0; i < out_frames; i++) {
        uint32_t idx = (uint32_t)pos;
        if (idx >= total_frames) {
            (*p_loops_done)++;
            if (loop_count == 0 || *p_loops_done < loop_count) {
                pos = fmod(pos, (double)total_frames);
                idx = (uint32_t)pos;
            } else {
                *p_active = 0;
                break;
            }
        }

        uint32_t idx2 = (idx + 1 < total_frames) ? (idx + 1) : idx;
        float frac = (float)(pos - (double)idx);

        float sl, sr;
        if (channels == 1) {
            float s = (float)pcm[idx] * (1.0f - frac) + (float)pcm[idx2] * frac;
            sl = s;
            sr = s;
        } else {
            sl = (float)pcm[idx * 2]     * (1.0f - frac) + (float)pcm[idx2 * 2]     * frac;
            sr = (float)pcm[idx * 2 + 1] * (1.0f - frac) + (float)pcm[idx2 * 2 + 1] * frac;
        }

        mix_l[i] += (int32_t)(sl * gain_l);
        mix_r[i] += (int32_t)(sr * gain_r);
        pos += step;
    }

    *p_pos = pos;
}

static void SDLCALL sdl_audio_callback(void *userdata, Uint8 *stream, int len) {
    (void)userdata;
    int out_frames = len / 4; /* 16-bit stereo = 4 bytes/frame */
    int16_t *out = (int16_t*)stream;
    memset(out, 0, (size_t)len);

    if (out_frames <= 0) return;

    int32_t stack_l[2048];
    int32_t stack_r[2048];
    int32_t *mix_l = (out_frames <= 2048) ? stack_l : (int32_t*)calloc((size_t)out_frames, sizeof(int32_t));
    int32_t *mix_r = (out_frames <= 2048) ? stack_r : (int32_t*)calloc((size_t)out_frames, sizeof(int32_t));
    if (!mix_l || !mix_r) return;
    if (out_frames <= 2048) {
        memset(mix_l, 0, (size_t)out_frames * sizeof(int32_t));
        memset(mix_r, 0, (size_t)out_frames * sizeof(int32_t));
    }

    float master = (float)g_master_vol / 127.0f;

    /* 1. Mix 2D Samples */
    for (int i = 0; i < MAX_2D_SAMPLES; i++) {
        Sample2D *s = &g_smp2d[i];
        if (!s->allocated || s->status != SMP_PLAYING || !s->pcm) continue;

        float vol = master * ((float)s->volume / 127.0f);
        float pan = (float)s->pan / 127.0f; /* 0 = left, 0.5 = center, 1 = right */
        float gl = vol * (pan <= 0.5f ? 1.0f : (1.0f - pan) * 2.0f);
        float gr = vol * (pan >= 0.5f ? 1.0f : pan * 2.0f);

        int active = 1;
        mix_source(mix_l, mix_r, out_frames, s->pcm, s->frames, s->channels, s->rate,
                   &s->pos, s->loop_count, &s->loops_done, gl, gr, &active);
        if (!active) s->status = SMP_DONE;
    }

    /* 2. Mix 3D Samples */
    float rx = g_lis_uy * g_lis_fz - g_lis_uz * g_lis_fy;
    float ry = g_lis_uz * g_lis_fx - g_lis_ux * g_lis_fz;
    float rz = g_lis_ux * g_lis_fy - g_lis_uy * g_lis_fx;
    float rlen = sqrtf(rx*rx + ry*ry + rz*rz);
    if (rlen > 1e-5f) { rx /= rlen; ry /= rlen; rz /= rlen; }
    else { rx = 1.0f; ry = 0.0f; rz = 0.0f; }

    for (int i = 0; i < MAX_3D_SAMPLES; i++) {
        Sample3D *s = &g_smp3d[i];
        if (!s->allocated || s->status != SMP_PLAYING || !s->pcm) continue;

        float dx = s->x - g_lis_x;
        float dy = s->y - g_lis_y;
        float dz = s->z - g_lis_z;
        float dist = sqrtf(dx*dx + dy*dy + dz*dz);

        float atten = 1.0f;
        float min_d = (s->min_dist > 0.0f) ? s->min_dist : 100.0f;
        float max_d = (s->max_dist > min_d) ? s->max_dist : (min_d + 2000.0f);
        if (dist >= max_d) {
            atten = 0.0f;
        } else if (dist > min_d) {
            atten = 1.0f - (dist - min_d) / (max_d - min_d);
        }

        float pan = 0.5f;
        if (dist > 1e-4f) {
            float dot = (dx * rx + dy * ry + dz * rz) / dist;
            pan = 0.5f + 0.5f * dot;
            if (pan < 0.0f) pan = 0.0f;
            if (pan > 1.0f) pan = 1.0f;
        }

        float vol = master * ((float)s->volume / 127.0f) * atten;
        float gl = vol * (pan <= 0.5f ? 1.0f : (1.0f - pan) * 2.0f);
        float gr = vol * (pan >= 0.5f ? 1.0f : pan * 2.0f);

        int active = 1;
        mix_source(mix_l, mix_r, out_frames, s->pcm, s->frames, s->channels, s->rate,
                   &s->pos, s->loop_count, &s->loops_done, gl, gr, &active);
        if (!active) s->status = SMP_DONE;
    }

    /* 3. Mix Music / Ambient Streams */
    for (int i = 0; i < MAX_STREAMS; i++) {
        AudioStream *st = &g_streams[i];
        if (!st->allocated || st->status != SMP_PLAYING || !st->pcm) continue;

        float norm_vol = (st->volume > 0) ? sqrtf((float)st->volume / 127.0f) : 0.0f;
        /* Boost only MENULOOP.WAV (509953 frames) since cshell caps its stream volume at 8-9/127 */
        if (st->frames == 509953 && st->rate == 44100 && st->channels == 2 && st->volume > 0) {
            norm_vol *= 3.2f;
            if (norm_vol > 1.0f) norm_vol = 1.0f;
        }
        float vol = master * norm_vol;
        float pan = (float)st->pan / 127.0f;
        float gl = vol * (pan <= 0.5f ? 1.0f : (1.0f - pan) * 2.0f);
        float gr = vol * (pan >= 0.5f ? 1.0f : pan * 2.0f);

        int active = 1;
        mix_source(mix_l, mix_r, out_frames, st->pcm, st->frames, st->channels, st->rate,
                   &st->pos, st->loop_count, &st->loops_done, gl, gr, &active);
        if (!active) st->status = SMP_DONE;
    }

    for (int i = 0; i < out_frames; i++) {
        int32_t l = mix_l[i];
        int32_t r = mix_r[i];
        if (l > 32767) l = 32767; else if (l < -32768) l = -32768;
        if (r > 32767) r = 32767; else if (r < -32768) r = -32768;
        out[i * 2]     = (int16_t)l;
        out[i * 2 + 1] = (int16_t)r;
    }

    if (out_frames > 2048) {
        free(mix_l);
        free(mix_r);
    }
}

/* ---- Case-insensitive Windows -> Linux file resolver for Streams ---- */
static FILE *open_win_path_ci(const char *win_path) {
    if (!win_path || !*win_path) return NULL;

    char norm[1024];
    size_t j = 0;
    const char *p = win_path;
    if (p[0] && p[1] == ':') p += 2;
    while (*p && j < sizeof(norm) - 1) {
        norm[j++] = (*p == '\\') ? '/' : *p;
        p++;
    }
    norm[j] = '\0';

    FILE *f = fopen(norm, "rb");
    if (f) return f;

    char asset_path[1100];
    snprintf(asset_path, sizeof(asset_path), "assets/%s", norm);
    f = fopen(asset_path, "rb");
    if (f) return f;

    const char *roots[3] = { (norm[0] == '/') ? "/" : ".", "assets", "." };
    int num_roots = (norm[0] == '/') ? 1 : 2;
    for (int r = 0; r < num_roots; r++) {
        char cur[1024];
        snprintf(cur, sizeof(cur), "%s", roots[r]);
        char tmp[1024];
        snprintf(tmp, sizeof(tmp), "%s", norm[0] == '/' ? norm + 1 : norm);

        char *saveptr = NULL;
        char *tok = strtok_r(tmp, "/", &saveptr);
        int ok = 1;
        while (tok) {
            DIR *d = opendir(cur);
            if (!d) { ok = 0; break; }
            struct dirent *ent;
            int found = 0;
            while ((ent = readdir(d)) != NULL) {
                if (strcasecmp(ent->d_name, tok) == 0) {
                    size_t clen = strlen(cur);
                    if (clen > 0 && cur[clen - 1] == '/')
                        snprintf(cur + clen, sizeof(cur) - clen, "%s", ent->d_name);
                    else
                        snprintf(cur + clen, sizeof(cur) - clen, "/%s", ent->d_name);
                    found = 1;
                    break;
                }
            }
            closedir(d);
            if (!found) { ok = 0; break; }
            tok = strtok_r(NULL, "/", &saveptr);
        }
        if (ok) {
            f = fopen(cur, "rb");
            if (f) return f;
        }
    }
    return NULL;
}

/* ---- Core Miles Exports ---- */
void *WINAPI W_AIL_mem_alloc_lock(DWORD n) { return malloc(n ? n : 1); }
void WINAPI W_AIL_mem_free_lock(void *p) { free(p); }
void WINAPI W_AIL_lock(void) { audio_lock(); }
void WINAPI W_AIL_unlock(void) { audio_unlock(); }

int WINAPI W_AIL_startup(void) {
    memset(g_smp2d, 0, sizeof(g_smp2d));
    memset(g_smp3d, 0, sizeof(g_smp3d));
    memset(g_streams, 0, sizeof(g_streams));
    return 1;
}

void WINAPI W_AIL_shutdown(void) {
    if (g_dev) {
        SDL_CloseAudioDevice(g_dev);
        g_dev = 0;
    }
    for (int i = 0; i < MAX_2D_SAMPLES; i++) {
        free(g_smp2d[i].pcm); g_smp2d[i].pcm = NULL;
        free(g_smp2d[i].raw_copy); g_smp2d[i].raw_copy = NULL;
    }
    for (int i = 0; i < MAX_3D_SAMPLES; i++) { free(g_smp3d[i].pcm); g_smp3d[i].pcm = NULL; }
    for (int i = 0; i < MAX_STREAMS; i++)    { free(g_streams[i].pcm); g_streams[i].pcm = NULL; }
}

int WINAPI W_AIL_set_preference(DWORD idx, int val) {
    if (idx < 64) {
        int old = g_prefs[idx];
        g_prefs[idx] = val;
        return old;
    }
    return 0;
}

int WINAPI W_AIL_get_preference(DWORD idx) {
    return (idx < 64) ? g_prefs[idx] : 0;
}

const char *WINAPI W_AIL_last_error(void) {
    return g_last_err;
}

DWORD WINAPI W_AIL_ms_count(void) {
    extern DWORD WINAPI W_GetTickCount(void);
    return W_GetTickCount();
}

int WINAPI W_AIL_waveOutOpen(void *drv, void *lphWaveOut, DWORD wDeviceID, void *lpFormat) {
    (void)lphWaveOut; (void)wDeviceID;
    if (!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO)) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
            snprintf(g_last_err, sizeof(g_last_err), "SDL_InitSubSystem(AUDIO) failed: %s", SDL_GetError());
            return 1;
        }
    }

    int req_freq = MIX_FREQ;
    if (lpFormat) {
        const MSS_WAVEFORMATEX *wf = (const MSS_WAVEFORMATEX*)lpFormat;
        if (wf->nSamplesPerSec >= 8000 && wf->nSamplesPerSec <= 96000) {
            req_freq = (int)wf->nSamplesPerSec;
        }
    }

    if (g_dev) {
        SDL_CloseAudioDevice(g_dev);
        g_dev = 0;
    }

    SDL_AudioSpec want, have;
    memset(&want, 0, sizeof(want));
    want.freq     = req_freq;
    want.format   = AUDIO_S16LSB;
    want.channels = 2;
    want.samples  = 1024;
    want.callback = sdl_audio_callback;

    g_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (!g_dev) {
        snprintf(g_last_err, sizeof(g_last_err), "SDL_OpenAudioDevice failed: %s", SDL_GetError());
        return 1;
    }

    g_out_rate = have.freq;
    SDL_PauseAudioDevice(g_dev, 0);
    if (drv) *(void**)drv = HANDLE_DRIVER;
    fprintf(stderr, "[mss32] SDL2 audio opened: %d Hz stereo\n", g_out_rate);
    return 0; /* MMSYSERR_NOERROR */
}

void WINAPI W_AIL_waveOutClose(void *drv) {
    (void)drv;
    if (g_dev) {
        SDL_CloseAudioDevice(g_dev);
        g_dev = 0;
    }
}

void WINAPI W_AIL_digital_handle_release(void *drv) {
    (void)drv;
    if (g_dev) SDL_PauseAudioDevice(g_dev, 1);
}

void WINAPI W_AIL_digital_handle_reacquire(void *drv) {
    (void)drv;
    if (g_dev) SDL_PauseAudioDevice(g_dev, 0);
}

int WINAPI W_AIL_digital_master_volume(void *drv) {
    (void)drv;
    return g_master_vol;
}

void WINAPI W_AIL_set_digital_master_volume(void *drv, int vol) {
    (void)drv;
    if (vol < 0) vol = 0;
    if (vol > 127) vol = 127;
    g_master_vol = vol;
}

/* ---- Codecs (ADPCM / ASI) ---- */
int WINAPI W_AIL_decompress_ADPCM(void *info_ptr, void **outdata, DWORD *outsize) {
    if (!info_ptr || !outdata || !outsize) return 0;
    const AILSOUNDINFO *info = (const AILSOUNDINFO*)info_ptr;
    uint32_t frames = 0;
    int16_t *pcm = decode_ima_adpcm((const uint8_t*)info->data_ptr, info->data_len,
                                    info->channels, info->block_size, &frames);
    if (!pcm) return 0;
    uint32_t bytes = frames * (uint32_t)info->channels * sizeof(int16_t);
    void *locked = W_AIL_mem_alloc_lock(bytes);
    if (!locked) { free(pcm); return 0; }
    memcpy(locked, pcm, bytes);
    free(pcm);
    *outdata = locked;
    *outsize = bytes;
    return 1;
}

int WINAPI W_AIL_decompress_ASI(void *indata, DWORD insize, const char *ext, void **outdata, DWORD *outsize, void *info) {
    (void)indata; (void)insize; (void)ext; (void)outdata; (void)outsize; (void)info;
    return 0;
}

/* ---- 2D Samples ---- */
void *WINAPI W_AIL_allocate_sample_handle(void *drv) {
    (void)drv;
    audio_lock();
    for (int i = 0; i < MAX_2D_SAMPLES; i++) {
        if (!g_smp2d[i].allocated) {
            memset(&g_smp2d[i], 0, sizeof(Sample2D));
            g_smp2d[i].allocated = 1;
            g_smp2d[i].status = SMP_FREE;
            g_smp2d[i].volume = 127;
            g_smp2d[i].pan = 64;
            g_smp2d[i].loop_count = 1;
            g_smp2d[i].rate = 22050;
            g_smp2d[i].channels = 1;
            g_smp2d[i].bits = 16;
            audio_unlock();
            return &g_smp2d[i];
        }
    }
    audio_unlock();
    return NULL;
}

void WINAPI W_AIL_release_sample_handle(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    audio_lock();
    free(s->pcm);
    free(s->raw_copy);
    memset(s, 0, sizeof(Sample2D));
    audio_unlock();
}

void WINAPI W_AIL_init_sample(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    audio_lock();
    free(s->pcm);
    free(s->raw_copy);
    s->pcm = NULL;
    s->raw_copy = NULL;
    s->raw_len = 0;
    s->frames = 0;
    s->pos = 0.0;
    s->channels = 1;
    s->bits = 16;
    s->status = SMP_DONE;
    s->volume = 127;
    s->pan = 64;
    s->loop_count = 1;
    s->loops_done = 0;
    audio_unlock();
}

int WINAPI W_AIL_set_sample_file(void *s_ptr, void *file_image, int block) {
    (void)block;
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s || !file_image) return 0;

    const uint8_t *hdr = (const uint8_t*)file_image;
    uint32_t max_len = 64 * 1024 * 1024;
    if (memcmp(hdr, "RIFF", 4) == 0) {
        max_len = *(const uint32_t*)(hdr + 4) + 8;
    }

    int rate = 22050, channels = 1;
    uint32_t frames = 0;
    int16_t *pcm = parse_wav_memory(hdr, max_len, &rate, &channels, &frames);
    if (!pcm) {
        fprintf(stderr, "[mss32] set_sample_file failed to parse WAV\n");
        return 0;
    }

    audio_lock();
    free(s->pcm);
    free(s->raw_copy);
    s->raw_copy = NULL;
    s->raw_len = 0;
    s->pcm = pcm;
    s->rate = rate;
    s->channels = channels;
    s->bits = 16;
    s->frames = frames;
    s->pos = 0.0;
    s->loops_done = 0;
    s->status = SMP_DONE;
    audio_unlock();
    return 1;
}

int WINAPI W_AIL_set_named_sample_file(void *s_ptr, const char *suffix, void *file_image, int file_size, int block) {
    (void)suffix; (void)file_size;
    return W_AIL_set_sample_file(s_ptr, file_image, block);
}

void WINAPI W_AIL_set_sample_address(void *s_ptr, void *start, DWORD len) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s || !start || len == 0) return;

    uint8_t *copy = (uint8_t*)malloc(len);
    if (!copy) return;
    memcpy(copy, start, len);

    audio_lock();
    free(s->raw_copy);
    s->raw_copy = copy;
    s->raw_len = len;
    audio_unlock();

    rebuild_sample2d_pcm(s);
}

void WINAPI W_AIL_set_sample_type(void *s_ptr, int format, DWORD flags) {
    (void)flags;
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    s->channels = (format & DIG_F_STEREO_8) ? 2 : 1;
    s->bits = (format & DIG_F_MONO_16) ? 16 : 8;
    if (s->raw_copy && s->raw_len > 0) {
        rebuild_sample2d_pcm(s);
    }
}

void WINAPI W_AIL_set_sample_playback_rate(void *s_ptr, int rate) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (s && rate > 0) s->rate = rate;
}

void WINAPI W_AIL_set_sample_volume(void *s_ptr, int vol) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    if (vol < 0) vol = 0; else if (vol > 127) vol = 127;
    s->volume = vol;
}

int WINAPI W_AIL_sample_volume(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    return s ? s->volume : 0;
}

void WINAPI W_AIL_set_sample_pan(void *s_ptr, int pan) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    if (pan < 0) pan = 0; else if (pan > 127) pan = 127;
    s->pan = pan;
}

int WINAPI W_AIL_sample_pan(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    return s ? s->pan : 64;
}

void WINAPI W_AIL_set_sample_loop_count(void *s_ptr, int count) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (s) s->loop_count = count;
}

void WINAPI W_AIL_set_sample_loop_block(void *s_ptr, int start, int end) {
    (void)s_ptr; (void)start; (void)end;
}

void WINAPI W_AIL_set_sample_ms_position(void *s_ptr, int ms) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s || ms < 0) return;
    audio_lock();
    s->pos = ((double)ms / 1000.0) * (double)s->rate;
    audio_unlock();
}

void WINAPI W_AIL_sample_ms_position(void *s_ptr, int32_t *total_ms, int32_t *current_ms) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s || s->rate <= 0) {
        if (total_ms) *total_ms = 0;
        if (current_ms) *current_ms = 0;
        return;
    }
    if (total_ms) *total_ms = (int32_t)(((double)s->frames / (double)s->rate) * 1000.0);
    if (current_ms) *current_ms = (int32_t)((s->pos / (double)s->rate) * 1000.0);
}

void WINAPI W_AIL_start_sample(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    audio_lock();
    s->pos = 0.0;
    s->loops_done = 0;
    s->status = SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_resume_sample(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    audio_lock();
    if (s->status == SMP_DONE) {
        s->pos = 0.0;
        s->loops_done = 0;
    }
    s->status = SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_stop_sample(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (!s) return;
    audio_lock();
    s->status = SMP_STOPPED;
    audio_unlock();
}

DWORD WINAPI W_AIL_sample_status(void *s_ptr) {
    Sample2D *s = (Sample2D*)s_ptr;
    return s ? s->status : SMP_DONE;
}

void WINAPI W_AIL_set_sample_user_data(void *s_ptr, DWORD idx, int val) {
    Sample2D *s = (Sample2D*)s_ptr;
    if (s && idx < 8) s->user_data[idx] = val;
}

int WINAPI W_AIL_sample_user_data(void *s_ptr, DWORD idx) {
    Sample2D *s = (Sample2D*)s_ptr;
    return (s && idx < 8) ? s->user_data[idx] : 0;
}

void WINAPI W_AIL_set_sample_reverb(void *s_ptr, float mix, float time, float decay) {
    (void)s_ptr; (void)mix; (void)time; (void)decay;
}

void WINAPI W_AIL_set_sample_processor(void *s_ptr, DWORD stage, void *prov) {
    (void)s_ptr; (void)stage; (void)prov;
}

/* ---- 3D Audio Provider & Listener ---- */
int WINAPI W_AIL_enumerate_3D_providers(DWORD *next, void **dest, char **name) {
    if (!next || !dest || !name) return 0;
    if (*next == 0) {
        *next = 1;
        *dest = HANDLE_3DPROV;
        *name = "Miles Fast 2D Positional Audio";
        return 1;
    }
    return 0;
}

int WINAPI W_AIL_open_3D_provider(void *lib) {
    (void)lib;
    return 0; /* M3D_NOERR */
}

void WINAPI W_AIL_close_3D_provider(void *lib) { (void)lib; }

void WINAPI W_AIL_3D_provider_attribute(void *lib, const char *name, void *val) {
    (void)lib;
    if (name && val && strstr(name, "Max samples")) {
        *(int32_t*)val = MAX_3D_SAMPLES;
    }
}

void *WINAPI W_AIL_open_3D_listener(void *lib) {
    (void)lib;
    return HANDLE_LISTENER;
}

void WINAPI W_AIL_close_3D_listener(void *lis) { (void)lis; }

void WINAPI W_AIL_set_3D_room_type(void *lib, int type) { (void)lib; g_room_type = type; }
int WINAPI W_AIL_3D_room_type(void *lib) { (void)lib; return g_room_type; }

void WINAPI W_AIL_set_3D_position(void *obj, float x, float y, float z) {
    if (obj == HANDLE_LISTENER) {
        g_lis_x = x; g_lis_y = y; g_lis_z = z;
    } else if (obj) {
        Sample3D *s = (Sample3D*)obj;
        s->x = x; s->y = y; s->z = z;
    }
}

void WINAPI W_AIL_3D_position(void *obj, float *x, float *y, float *z) {
    if (obj == HANDLE_LISTENER) {
        if (x) *x = g_lis_x; if (y) *y = g_lis_y; if (z) *z = g_lis_z;
    } else if (obj) {
        Sample3D *s = (Sample3D*)obj;
        if (x) *x = s->x; if (y) *y = s->y; if (z) *z = s->z;
    }
}

void WINAPI W_AIL_set_3D_velocity_vector(void *obj, float dx, float dy, float dz) {
    if (obj == HANDLE_LISTENER) {
        g_lis_vx = dx; g_lis_vy = dy; g_lis_vz = dz;
    } else if (obj) {
        Sample3D *s = (Sample3D*)obj;
        s->vx = dx; s->vy = dy; s->vz = dz;
    }
}

void WINAPI W_AIL_3D_velocity(void *obj, float *dx, float *dy, float *dz) {
    if (obj == HANDLE_LISTENER) {
        if (dx) *dx = g_lis_vx; if (dy) *dy = g_lis_vy; if (dz) *dz = g_lis_vz;
    } else if (obj) {
        Sample3D *s = (Sample3D*)obj;
        if (dx) *dx = s->vx; if (dy) *dy = s->vy; if (dz) *dz = s->vz;
    }
}

void WINAPI W_AIL_set_3D_orientation(void *obj, float xf, float yf, float zf, float xu, float yu, float zu) {
    if (obj == HANDLE_LISTENER) {
        g_lis_fx = xf; g_lis_fy = yf; g_lis_fz = zf;
        g_lis_ux = xu; g_lis_uy = yu; g_lis_uz = zu;
    }
}

void WINAPI W_AIL_3D_orientation(void *obj, float *xf, float *yf, float *zf, float *xu, float *yu, float *zu) {
    if (obj == HANDLE_LISTENER) {
        if (xf) *xf = g_lis_fx; if (yf) *yf = g_lis_fy; if (zf) *zf = g_lis_fz;
        if (xu) *xu = g_lis_ux; if (yu) *yu = g_lis_uy; if (zu) *zu = g_lis_uz;
    }
}

void WINAPI W_AIL_set_3D_user_data(void *obj, DWORD idx, int val) {
    if (idx >= 8) return;
    if (obj == HANDLE_LISTENER) g_lis_user_data[idx] = val;
    else if (obj) ((Sample3D*)obj)->user_data[idx] = val;
}

int WINAPI W_AIL_3D_user_data(void *obj, DWORD idx) {
    if (idx >= 8) return 0;
    if (obj == HANDLE_LISTENER) return g_lis_user_data[idx];
    return obj ? ((Sample3D*)obj)->user_data[idx] : 0;
}

/* ---- 3D Samples ---- */
void *WINAPI W_AIL_allocate_3D_sample_handle(void *lib) {
    (void)lib;
    audio_lock();
    for (int i = 0; i < MAX_3D_SAMPLES; i++) {
        if (!g_smp3d[i].allocated) {
            memset(&g_smp3d[i], 0, sizeof(Sample3D));
            g_smp3d[i].allocated = 1;
            g_smp3d[i].status = SMP_FREE;
            g_smp3d[i].volume = 127;
            g_smp3d[i].loop_count = 1;
            g_smp3d[i].rate = 22050;
            g_smp3d[i].channels = 1;
            g_smp3d[i].min_dist = 100.0f;
            g_smp3d[i].max_dist = 2500.0f;
            audio_unlock();
            return &g_smp3d[i];
        }
    }
    audio_unlock();
    return NULL;
}

void WINAPI W_AIL_release_3D_sample_handle(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    audio_lock();
    free(s->pcm);
    memset(s, 0, sizeof(Sample3D));
    audio_unlock();
}

int WINAPI W_AIL_set_3D_sample_info(void *s_ptr, void *info_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    const AILSOUNDINFO *info = (const AILSOUNDINFO*)info_ptr;
    if (!s || !info) return 0;

    uint32_t frames = 0;
    int16_t *pcm = decode_to_pcm16(info->format, (const uint8_t*)info->data_ptr, info->data_len,
                                   info->channels, info->bits, info->block_size, &frames);
    if (!pcm && info->initial_ptr && info->initial_len >= 44) {
        int r = 0, ch = 0;
        pcm = parse_wav_memory((const uint8_t*)info->initial_ptr, info->initial_len, &r, &ch, &frames);
    }
    if (!pcm) return 0;

    audio_lock();
    free(s->pcm);
    s->pcm = pcm;
    s->rate = (info->rate > 0) ? (int)info->rate : 22050;
    s->channels = (info->channels > 0) ? info->channels : 1;
    s->frames = frames;
    s->pos = 0.0;
    s->loops_done = 0;
    s->status = SMP_DONE;
    audio_unlock();
    return 1;
}

void WINAPI W_AIL_start_3D_sample(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    audio_lock();
    s->pos = 0.0;
    s->loops_done = 0;
    s->status = SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_stop_3D_sample(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    audio_lock();
    s->status = SMP_STOPPED;
    audio_unlock();
}

void WINAPI W_AIL_resume_3D_sample(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    audio_lock();
    if (s->status == SMP_DONE) {
        s->pos = 0.0;
        s->loops_done = 0;
    }
    s->status = SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_end_3D_sample(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    audio_lock();
    s->status = SMP_DONE;
    audio_unlock();
}

DWORD WINAPI W_AIL_3D_sample_status(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    return s ? s->status : SMP_DONE;
}

void WINAPI W_AIL_set_3D_sample_volume(void *s_ptr, int vol) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    if (vol < 0) vol = 0; else if (vol > 127) vol = 127;
    s->volume = vol;
}

int WINAPI W_AIL_3D_sample_volume(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    return s ? s->volume : 0;
}

void WINAPI W_AIL_set_3D_sample_playback_rate(void *s_ptr, int rate) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (s && rate > 0) s->rate = rate;
}

void WINAPI W_AIL_set_3D_sample_offset(void *s_ptr, DWORD offset) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    audio_lock();
    s->pos = (double)(offset / 2);
    audio_unlock();
}

void WINAPI W_AIL_set_3D_sample_loop_count(void *s_ptr, int count) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (s) s->loop_count = count;
}

void WINAPI W_AIL_set_3D_sample_loop_block(void *s_ptr, int start, int end) {
    (void)s_ptr; (void)start; (void)end;
}

void WINAPI W_AIL_set_3D_sample_distances(void *s_ptr, float max_dist, float min_dist) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (!s) return;
    s->max_dist = max_dist;
    s->min_dist = min_dist;
}

void WINAPI W_AIL_set_3D_sample_occlusion(void *s_ptr, float occ) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (s) s->occlusion = occ;
}

void WINAPI W_AIL_set_3D_sample_obstruction(void *s_ptr, float obs) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (s) s->obstruction = obs;
}

float WINAPI W_AIL_3D_sample_obstruction(void *s_ptr) {
    Sample3D *s = (Sample3D*)s_ptr;
    return s ? s->obstruction : 0.0f;
}

void WINAPI W_AIL_set_3D_sample_effects_level(void *s_ptr, float lvl) {
    Sample3D *s = (Sample3D*)s_ptr;
    if (s) s->effects_level = lvl;
}

void WINAPI W_AIL_set_3D_sample_preference(void *s_ptr, const char *name, void *val) {
    (void)s_ptr; (void)name; (void)val;
}

/* ---- Streams (Music / Ambient Loops) ---- */
/*void *WINAPI W_AIL_open_stream(void *drv, const char *filename, int stream_mem) {
    (void)drv; (void)stream_mem;
    if (!filename) return NULL;

    FILE *f = open_win_path_ci(filename);
    if (!f) {
        fprintf(stderr, "[mss32] open_stream NOT FOUND: '%s'\n", filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz <= 44) { fclose(f); return NULL; }

    uint8_t *buf = (uint8_t*)malloc((size_t)sz);
    if (!buf) { fclose(f); return NULL; }
    fread(buf, 1, (size_t)sz, f);
    fclose(f);

    int rate = 22050, channels = 2;
    uint32_t frames = 0;
    int16_t *pcm = parse_wav_memory(buf, (uint32_t)sz, &rate, &channels, &frames);
    free(buf);
    if (!pcm) {
        fprintf(stderr, "[mss32] open_stream WAV parse failed: '%s'\n", filename);
        return NULL;
    }

    audio_lock();
    for (int i = 0; i < MAX_STREAMS; i++) {
        if (!g_streams[i].allocated) {
            memset(&g_streams[i], 0, sizeof(AudioStream));
            g_streams[i].allocated = 1;
            g_streams[i].status = SMP_STOPPED;
            g_streams[i].pcm = pcm;
            g_streams[i].frames = frames;
            g_streams[i].channels = channels;
            g_streams[i].rate = rate;
            g_streams[i].volume = 127;
            g_streams[i].pan = 64;
            g_streams[i].loop_count = 1;
            audio_unlock();
            fprintf(stderr, "[mss32] open_stream OK: '%s' (%d Hz, %d ch)\n", filename, rate, channels);
            return &g_streams[i];
        }
    }
    audio_unlock();
    free(pcm);
    return NULL;
}*/

extern BOOL WINAPI W_ReadFile(HANDLE hFile, void *lpBuffer, DWORD nNumberOfBytesToRead, DWORD *lpNumberOfBytesRead, void *lpOverlapped);
extern DWORD WINAPI W_SetFilePointer(HANDLE hFile, int32_t lDistanceToMove, int32_t *lpDistanceToMoveHigh, DWORD dwMoveMethod);

/* ---- Streams (Music / Ambient Loops) ---- */
void *WINAPI W_AIL_open_stream(void *drv, const char *filename, int stream_mem) {
    (void)drv; (void)stream_mem;
    if (!filename) return NULL;

    uint8_t *buf = NULL;
    uint32_t buf_sz = 0;

    /* Miles Sound System convention: "\\<decimal_HANDLE>" streams from an open Win32 HANDLE */
    
        /* Miles Sound System convention: "\\<HANDLE>" or "\\\\<HANDLE>" streams from an open Win32 HANDLE */
    if (filename[0] == '\\' && filename[1] == '\\') {
        const char *num_str = filename;
        while (*num_str == '\\') num_str++;
        char *endptr = NULL;
        unsigned long hval = (*num_str && isdigit((unsigned char)*num_str)) ? strtoul(num_str, &endptr, 10) : 0;
        if (hval > 0 && endptr && *endptr == '\0') {
            HANDLE h = (HANDLE)(uintptr_t)hval;
            DWORD start_pos = W_SetFilePointer(h, 0, NULL, 1 /* FILE_CURRENT */);
            if (start_pos == 0xFFFFFFFFu) {
                fprintf(stderr, "[mss32] open_stream invalid HANDLE: '%s'\n", filename);
                return NULL;
            }

            uint8_t hdr[12];
            DWORD br = 0;
            if (!W_ReadFile(h, hdr, 12, &br, NULL) || br != 12 ||
                memcmp(hdr, "RIFF", 4) != 0 || memcmp(hdr + 8, "WAVE", 4) != 0) {
                int32_t hi = 0;
                W_SetFilePointer(h, (int32_t)start_pos, &hi, 0 /* FILE_BEGIN */);
                fprintf(stderr, "[mss32] open_stream HANDLE '%s' not at RIFF/WAVE header\n", filename);
                return NULL;
            }

            uint32_t riff_sz = *(uint32_t*)(hdr + 4);
            buf_sz = riff_sz + 8;
            if (buf_sz < 44 || buf_sz > 128 * 1024 * 1024) {
                int32_t hi = 0;
                W_SetFilePointer(h, (int32_t)start_pos, &hi, 0);
                return NULL;
            }

            buf = (uint8_t*)malloc(buf_sz);
            if (!buf) {
                int32_t hi = 0;
                W_SetFilePointer(h, (int32_t)start_pos, &hi, 0);
                return NULL;
            }
            memcpy(buf, hdr, 12);

            DWORD rem = buf_sz - 12;
            DWORD got = 0;
            while (got < rem) {
                DWORD chunk = 0;
                if (!W_ReadFile(h, buf + 12 + got, rem - got, &chunk, NULL) || chunk == 0) break;
                got += chunk;
            }
            int32_t hi = 0;
            W_SetFilePointer(h, (int32_t)start_pos, &hi, 0 /* FILE_BEGIN */);
            buf_sz = 12 + got;
        }
    }

    if (!buf) {
        FILE *f = open_win_path_ci(filename);
        if (!f) {
            fprintf(stderr, "[mss32] open_stream NOT FOUND: '%s'\n", filename);
            return NULL;
        }

        fseek(f, 0, SEEK_END);
        long sz = ftell(f);
        fseek(f, 0, SEEK_SET);
        if (sz <= 44) { fclose(f); return NULL; }

        buf_sz = (uint32_t)sz;
        buf = (uint8_t*)malloc(buf_sz);
        if (!buf) { fclose(f); return NULL; }
        fread(buf, 1, buf_sz, f);
        fclose(f);
    }

    int rate = 22050, channels = 2;
    uint32_t frames = 0;
    int16_t *pcm = parse_wav_memory(buf, buf_sz, &rate, &channels, &frames);
    free(buf);
    if (!pcm) {
        fprintf(stderr, "[mss32] open_stream WAV parse failed: '%s'\n", filename);
        return NULL;
    }

    audio_lock();
    for (int i = 0; i < MAX_STREAMS; i++) {
        if (!g_streams[i].allocated) {
            memset(&g_streams[i], 0, sizeof(AudioStream));
            g_streams[i].allocated = 1;
            g_streams[i].status = SMP_STOPPED;
            g_streams[i].pcm = pcm;
            g_streams[i].frames = frames;
            g_streams[i].channels = channels;
            g_streams[i].rate = rate;
            g_streams[i].volume = 127;
            g_streams[i].pan = 64;
            g_streams[i].loop_count = 1;
            audio_unlock();
            fprintf(stderr, "[mss32] open_stream OK: '%s' (%d Hz, %d ch)\n", filename, rate, channels);
		fprintf(stderr, "[mss32] open_stream OK: '%s' (%d Hz, %d ch, %u frames)\n", filename, rate, channels, frames);
            return &g_streams[i];
        }
    }
    audio_unlock();
    free(pcm);
    return NULL;
}

/* In W_AIL_open_stream, update the OK log to include frames: */

/* In W_AIL_open_stream, update the OK log to include frames: */
//fprintf(stderr, "[mss32] open_stream OK: '%s' (%d Hz, %d ch, %u frames)\n", filename, rate, channels, frames);

/* Update the stream control functions right below W_AIL_close_stream: */
void WINAPI W_AIL_close_stream(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    fprintf(stderr, "[mss32] close_stream(%p) pos=%.0f/%u\n", st_ptr, st->pos, st->frames);
    audio_lock();
    free(st->pcm);
    memset(st, 0, sizeof(AudioStream));
    audio_unlock();
}

void WINAPI W_AIL_start_stream(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    fprintf(stderr, "[mss32] start_stream(%p) vol=%d pan=%d loop=%d frames=%u\n",
            st_ptr, st->volume, st->pan, st->loop_count, st->frames);
    audio_lock();
    st->pos = 0.0;
    st->loops_done = 0;
    st->status = SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_pause_stream(void *st_ptr, int onoff) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    fprintf(stderr, "[mss32] pause_stream(%p, %d) vol=%d\n", st_ptr, onoff, st->volume);
    audio_lock();
    st->status = onoff ? SMP_STOPPED : SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_set_stream_volume(void *st_ptr, int vol) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    fprintf(stderr, "[mss32] set_stream_volume(%p, %d)\n", st_ptr, vol);
    if (vol < 0) vol = 0; else if (vol > 127) vol = 127;
    st->volume = vol;
}

/*
void WINAPI W_AIL_close_stream(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    audio_lock();
    free(st->pcm);
    memset(st, 0, sizeof(AudioStream));
    audio_unlock();
}

void WINAPI W_AIL_start_stream(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    audio_lock();
    st->pos = 0.0;
    st->loops_done = 0;
    st->status = SMP_PLAYING;
    audio_unlock();
}

void WINAPI W_AIL_pause_stream(void *st_ptr, int onoff) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    audio_lock();
    st->status = onoff ? SMP_STOPPED : SMP_PLAYING;
    audio_unlock();
}*/

int WINAPI W_AIL_service_stream(void *st_ptr, int fillup) {
    (void)fillup;
    AudioStream *st = (AudioStream*)st_ptr;
    return (st && st->status == SMP_PLAYING) ? 1 : 0;
}

DWORD WINAPI W_AIL_stream_status(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    return st ? st->status : SMP_DONE;
}

void WINAPI W_AIL_set_stream_loop_count(void *st_ptr, int count) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (st) st->loop_count = count;
}

void WINAPI W_AIL_set_stream_ms_position(void *st_ptr, int ms) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st || ms < 0) return;
    audio_lock();
    st->pos = ((double)ms / 1000.0) * (double)st->rate;
    audio_unlock();
}

void WINAPI W_AIL_stream_ms_position(void *st_ptr, int32_t *total_ms, int32_t *current_ms) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st || st->rate <= 0) {
        if (total_ms) *total_ms = 0;
        if (current_ms) *current_ms = 0;
        return;
    }
    if (total_ms) *total_ms = (int32_t)(((double)st->frames / (double)st->rate) * 1000.0);
    if (current_ms) *current_ms = (int32_t)((st->pos / (double)st->rate) * 1000.0);
}

void WINAPI W_AIL_set_stream_playback_rate(void *st_ptr, int rate) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (st && rate > 0) st->rate = rate;
}
/*
void WINAPI W_AIL_set_stream_volume(void *st_ptr, int vol) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    if (vol < 0) vol = 0; else if (vol > 127) vol = 127;
    st->volume = vol;
}*/

int WINAPI W_AIL_stream_volume(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    return st ? st->volume : 0;
}

void WINAPI W_AIL_set_stream_pan(void *st_ptr, int pan) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (!st) return;
    if (pan < 0) pan = 0; else if (pan > 127) pan = 127;
    st->pan = pan;
}

int WINAPI W_AIL_stream_pan(void *st_ptr) {
    AudioStream *st = (AudioStream*)st_ptr;
    return st ? st->pan : 64;
}

void WINAPI W_AIL_set_stream_user_data(void *st_ptr, DWORD idx, int val) {
    AudioStream *st = (AudioStream*)st_ptr;
    if (st && idx < 8) st->user_data[idx] = val;
}

/* ---- Filters (unused in software mixer) ---- */
int WINAPI W_AIL_enumerate_filters(DWORD *next, void **dest, char **name) {
    (void)next; (void)dest; (void)name;
    return 0;
}
int WINAPI W_AIL_enumerate_filter_sample_attributes(void *h, DWORD *next, void *info) {
    (void)h; (void)next; (void)info;
    return 0;
}
void WINAPI W_AIL_filter_sample_attribute(void *h, const char *name, void *val) {
    (void)h; (void)name; (void)val;
}
void WINAPI W_AIL_set_filter_sample_preference(void *h, const char *name, void *val) {
    (void)h; (void)name; (void)val;
}
