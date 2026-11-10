#!/usr/bin/env python3
"""Code discovery for lithtech.exe (VC6) without Ghidra.
Recursive descent from: entry point, code pointers stored in .rdata/.data, immediates that point into .text,
call/jmp targets, jump tables (jmp [r*4+table]) and, last, function prologues in still-uncovered gaps.
Writes data/code_units.txt  ("<hex va> <len>" per instruction, same format as the Ghidra export)."""
import sys, struct, collections, json
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG

exe = sys.argv[1] if len(sys.argv) > 1 else '/mnt/user-data/uploads/lithtechreal.exe'
out = sys.argv[2] if len(sys.argv) > 2 else 'data/code_units.txt'
pe = pefile.PE(exe)
base = pe.OPTIONAL_HEADER.ImageBase
raw = open(exe, 'rb').read()
text = next(s for s in pe.sections if s.Name.startswith(b'.text'))
T0 = base + text.VirtualAddress
TLEN = text.SizeOfRawData
T1 = T0 + TLEN
tb = raw[text.PointerToRawData:text.PointerToRawData + TLEN]
# whole mapped image for reading tables
img = {}
for s in pe.sections:
    a = base + s.VirtualAddress
    d = raw[s.PointerToRawData:s.PointerToRawData + min(s.SizeOfRawData, max(s.Misc_VirtualSize, 0))]
    img[a] = d

def rd32(va):
    for a, d in img.items():
        if a <= va and va + 4 <= a + len(d):
            return struct.unpack_from('<I', d, va - a)[0]
    return None

def in_text(v): return T0 <= v < T1

md = Cs(CS_ARCH_X86, CS_MODE_32); md.detail = True
insn = {}            # va -> (len)
datarange = []       # (start,end) jump tables / data inside text
work = collections.deque()
seeds = set()
stats = collections.Counter()
deferred = []
rej = []
why = ['']
tx = None
def known(pc): return pc in insn or (tx is not None and pc in tx)

def add_seed(v, why):
    if in_text(v) and not known(v):
        work.append(v); seeds.add(v)

add_seed(base + pe.OPTIONAL_HEADER.AddressOfEntryPoint, 'entry')

# 1. code pointers in data sections (vtables, callbacks, SEH scope tables, jump tables in .rdata)
for s in pe.sections:
    if s.Name.startswith((b'.rdata', b'.data')):
        a = base + s.VirtualAddress
        d = raw[s.PointerToRawData:s.PointerToRawData + min(s.SizeOfRawData, s.Misc_VirtualSize)]
        for k in range(0, len(d) - 3, 4):
            v = struct.unpack_from('<I', d, k)[0]
            if in_text(v):
                deferred.append(v); stats['data ptr seeds'] += 1

def jt_entries(site_insn, table, count_hint):
    ents = []
    n = 0
    while True:
        if count_hint is not None and n >= count_hint: break
        v = rd32(table + 4 * n)
        if v is None:
            v = struct.unpack_from('<I', tb, table + 4 * n - T0)[0] if T0 <= table + 4 * n < T1 - 3 else None
        if v is None or not in_text(v): break
        if abs(v - site_insn) > (0x20000 if (count_hint is not None and n < count_hint) else 0x2000): break
        ents.append(v); n += 1
        if n > 1024: break
    return ents

recent = collections.deque(maxlen=8)

cov = bytearray(TLEN)     # 1 = first byte of committed insn, 2 = continuation byte
tx = None                 # speculative transaction: dict of new insns, or None
txbad = [False]
tseeds = []
def known(pc): return pc in insn or (tx is not None and pc in tx)
def commit(pc, size):
    if tx is not None: tx[pc] = size
    else:
        insn[pc] = size
        cov[pc - T0] = 1
        for q in range(pc - T0 + 1, pc - T0 + size): cov[q] = 2
def overlaps(pc, size):
    o = pc - T0
    for q in range(o, o + size):
        if cov[q] and not (q == o and cov[q] == 1): return True
        if tx is not None:
            pass
    if tx is not None:
        for a, l in tx.items():
            if a != pc and a < pc + size and pc < a + l: return True
    return False
def run(start):
    pc = start
    recent.clear()
    while True:
        if known(pc): return
        if not in_text(pc): return
        off = pc - T0
        ins = next(md.disasm(tb[off:off + 16], pc, 1), None)
        if ins is None:
            stats['invalid'] += 1; txbad[0] = True; why[0]='invalid@%x'%pc; return
        if overlaps(pc, ins.size):
            stats['overlap'] += 1; txbad[0] = True; why[0]='overlap@%x vs %s'%(pc,[hex(a) for a in range(pc-3,pc+ins.size) if a in insn][:2]); return
        commit(pc, ins.size)
        recent.append(ins)
        mn = ins.mnemonic
        nxt = pc + ins.size
        # immediates / displacements that look like code addresses -> seeds (callbacks, SEH handlers)
        for o in ins.operands:
            if o.type == X86_OP_IMM and mn not in ('call',) and not mn.startswith('j') and in_text(o.imm & 0xffffffff):
                deferred.append(o.imm & 0xffffffff)
        if mn == 'ret' or mn == 'retn' or mn == 'iretd' or mn == 'hlt':
            return
        if mn == 'int3' or mn == 'ud2':
            return
        if mn == 'jmp':
            o = ins.operands[0]
            if o.type == X86_OP_IMM:
                t = o.imm & 0xffffffff
                add_seed(t, 'jmp'); return
            if o.type == X86_OP_MEM and o.mem.index != 0 and o.mem.scale == 4 and o.mem.base == 0:
                table = o.mem.disp & 0xffffffff
                hint = None
                for p in reversed(list(recent)[:-1]):
                    if p.mnemonic == 'cmp' and len(p.operands) == 2 and p.operands[1].type == X86_OP_IMM:
                        hint = (p.operands[1].imm & 0xffffffff) + 1; break
                ents = jt_entries(pc, table, hint)
                if in_text(table):
                    datarange.append((table, table + 4 * len(ents)))
                for e in ents: add_seed(e, 'jt')
                stats['jump tables'] += 1; stats['jt entries'] += len(ents)
            return
        if mn.startswith('j') or mn.startswith('loop') or mn == 'jecxz':
            t = ins.operands[0].imm & 0xffffffff
            add_seed(t, 'jcc')
        elif mn == 'call':
            o = ins.operands[0]
            if o.type == X86_OP_IMM: add_seed(o.imm & 0xffffffff, 'call')
        pc = nxt

def drain():
    while work:
        s = work.popleft()
        if not known(s): run(s)
def spec(seed):
    """speculative closure: commit only if conflict-free"""
    global tx
    tx = {}; txbad[0] = False; work.clear(); work.append(seed)
    drain()
    ok = not txbad[0]; got = tx; tx = None
    if ok:
        for a, l in sorted(got.items()): commit(a, l)
        return len(got)
    stats['rejected speculative'] += 1
    rej.append((seed, why[0]))
    return 0

drain()
print('phase1 (entry closure):', len(insn))
done = set()
def plaus(v):
    p = tb[v - T0 - 1] if v > T0 else 0xcc
    q = tb[v - T0 - 3] if v - T0 >= 3 else 0
    return p in (0xcc, 0x90, 0xc3) or (q == 0xc2) or tb[v - T0:v - T0 + 3] in (b'\x55\x8b\xec', b'\x83\xec\x08')
while True:
    cand = [v for v in dict.fromkeys(deferred) if v not in done and in_text(v) and v not in insn]
    if not cand: break
    tier = [v for v in cand if plaus(v)] or cand
    del deferred[:]
    deferred.extend(v for v in cand if v not in tier)
    for v in tier:
        done.add(v)
        if v not in insn: spec(v)
n1 = len(insn)
# 2. prologue scan in uncovered gaps (unreferenced / indirectly-reached functions)
def covered_mask():
    m = bytearray(TLEN)
    for a, l in insn.items(): m[a - T0:a - T0 + l] = b'\x01' * l
    for a, b in datarange: m[a - T0:b - T0] = b'\x02' * (b - a)
    return m
PRO = (b'\x55\x8b\xec', b'\x55\x89\xe5', b'\x83\xec', b'\x81\xec', b'\x6a\xff\x68', b'\x56\x8b\xf1', b'\x51\x56', b'\x53\x56\x57', b'\x8b\x44\x24', b'\x8b\x4c\x24', b'\x56\x8b\x74\x24', b'\x56\x57\x8b', b'\xb8', b'\x33\xc0\xc3', b'\x55\x8b', b'\x53\x8b', b'\x56\x8b', b'\x57\x8b', b'\x8b\xff')
added = 0
for rounds in range(400):
    m = covered_mask()
    k = 0; new = 0
    while k < TLEN:
        if m[k]: k += 1; continue
        # gap start
        e = k
        while e < TLEN and not m[e]: e += 1
        # candidate starts: first non-padding byte of the gap and of every padding run inside it
        cands=[]
        q=k
        while q<e:
            if tb[q] in (0xcc,0x90): q+=1; continue
            cands.append(q)
            while q<e and tb[q] not in (0xcc,): q+=1
        for kk in range(k, e - 3):
            v = struct.unpack_from('<I', tb, kk)[0]
            if in_text(v) and v not in insn and T0 <= v < T0 + TLEN and tb[v-T0] not in (0xcc,) and kk % 4 == 0:
                if spec(v): new += 1; stats['gap table seeds'] += 1
        for q in cands:
            if tb[q:q+2]==b'\x00\x00' or tb[q]==0x00: continue
            pc = q+T0; ok = False; cnt = 0
            while pc < T0 + e and cnt < 6000:
                ins = next(md.disasm(tb[pc - T0:pc - T0 + 16], pc, 1), None)
                if ins is None: break
                cnt += 1
                if ins.mnemonic in ('ret', 'retn', 'jmp'): ok = True; break
                pc += ins.size
            if ok and cnt>=2 or (ok and tb[q]==0xc3):
                if spec(T0 + q): new += 1; stats['gap seeds'] += 1
        k = e
    added += new
    if not new: break

# 3. report
m = covered_mask()
unc = 0; runs = []
k = 0
while k < TLEN:
    if m[k] == 0:
        e = k
        while e < TLEN and m[e] == 0: e += 1
        seg = tb[k:e]
        if any(b not in (0xcc, 0x90, 0x00) for b in seg): runs.append((T0 + k, e - k)); unc += e - k
        k = e
    else: k += 1
open(out, 'w').write(''.join('%x %d\n' % (a, l) for a, l in sorted(insn.items())))
json.dump([(hex(a), l) for a, l in runs], open('data/uncovered_text.json', 'w'))
print('instructions', len(insn), 'after-static', n1, 'text bytes', TLEN, 'uncovered non-padding bytes', unc, 'in', len(runs), 'gaps', dict(stats))

import collections as C
print(C.Counter(w.split('@')[0] for _,w in rej)); print([ (hex(a),w) for a,w in rej if tb[a-T0:a-T0+3]==b'\x55\x8b\xec'][:15], sum(1 for a,w in rej if tb[a-T0:a-T0+3]==b'\x55\x8b\xec'))
for a,w in rej[:25]: print(hex(a), w, tb[a-T0:a-T0+10].hex())
