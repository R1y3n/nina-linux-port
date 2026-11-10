#!/usr/bin/env python3
"""Place the original .rdata/.data/.bss at their ORIGINAL virtual addresses in the rebuilt exe.
Outputs: ltdata.bin/ltdata.o (image), lt_syms.ld (name=VA for every Ghidra global), c/lt_fixups.c (code-pointer fixups)."""
import re,glob,subprocess,pefile
exe='/mnt/user-data/uploads/lithtech.exe'
pe=pefile.PE(exe); base=pe.OPTIONAL_HEADER.ImageBase; raw=open(exe,'rb').read()
lo=base+0xcb000; hi=base+0xef000
img=bytearray(hi-lo)
for s in pe.sections:
    a=base+s.VirtualAddress
    if s.Name.startswith((b'.rdata',b'.data')):
        d=raw[s.PointerToRawData:s.PointerToRawData+min(s.SizeOfRawData,s.Misc_VirtualSize)]
        img[a-lo:a-lo+len(d)]=d
open('ltdata.bin','wb').write(img)
open('ltdata.S','w').write('.section .ltdata,"dw"\n.globl _ltdata_start\n_ltdata_start:\n.incbin "ltdata.bin"\n'); subprocess.run(['i686-w64-mingw32-gcc','-c','ltdata.S','-o','ltdata.o'],check=True)
# symbols
names=set()
for f in ['c/lt_globals.h']:
    for m in re.finditer(r'extern [\w ]+?\s*\*?\s*(\w+)(?:\[\d*\]|\(void\))?;',open(f).read()): names.add(m.group(1))
for f in glob.glob('c/unnamed*.c')+glob.glob('c/*.c'):
    pass
out=[]
for n in sorted(names):
    m=re.search(r'_([0-9a-f]{8})$',n)
    if not m or n.startswith(('LAB_','LOOP_','switchD_','caseD_')): continue
    va=int(m.group(1),16)
    if lo<=va<hi: out.append('_%s = 0x%08x;'%(n,va))
open('lt_syms.ld','w').write('\n'.join(out)+'\n'); print('data symbols',len(out))
# fixups: function VA -> C name
import json as _j
fm={int(k,16):v[0] for k,v in _j.load(open('funcmap.json')).items()}
o=['/* generated: translate original code VAs stored in the data image to rebuilt function addresses */','#include "ghidra_types.h"','#include <string.h>',
'struct fx{unsigned va;void*fn;};','static const struct fx fx_tab[]={']
import json,os
ext=json.load(open('lifted_labels.json')) if os.path.exists('lifted_labels.json') else {}
allf=dict(fm)
for va,n in sorted((int(k,16),v) for k,v in ext.items()): o.insert(4,'extern char %s[];'%n); allf[va]=n
for va,n in sorted(allf.items()): o.append(' {0x%08x,(void*)%s%s},'%(va,'' if n.startswith('lt_L_') else '&',n))
o+=['};','extern unsigned char lt_img[] __asm__("_ltdata_start");',
'void lt_fixup_init(void){',
' unsigned *p=(unsigned*)0x%08x; unsigned n=(0x%08x-0x%08x)/4;'%(lo,hi,lo),
' unsigned N=sizeof(fx_tab)/sizeof(fx_tab[0]);',
' for(unsigned i=0;i<n;i++){unsigned v=p[i]; if(v<0x401000||v>=0x4cb000) continue; unsigned a=0,b=N; while(a<b){unsigned m=(a+b)/2; if(fx_tab[m].va<v)a=m+1; else b=m;} if(a<N&&fx_tab[a].va==v) p[i]=(unsigned)fx_tab[a].fn;}',
'}']
open('c/lt_fixups.c','w').write('\n'.join(o)+'\n'); print('fixup targets',len(fm))

# IAT patching
imps=[]
for d in pe.DIRECTORY_ENTRY_IMPORT:
    for imp in d.imports:
        imps.append((imp.address,d.dll.decode(),imp.name.decode() if imp.name else None,imp.ordinal))
o=['/* generated: fill the original import address table slots (lives at its original VA) */','#include <windows.h>','struct iat{unsigned slot;const char*dll;const char*name;unsigned ord;};','static const struct iat tab[]={']
for slot,dll,name,ordn in imps: o.append(' {0x%08x,"%s",%s,%d},'%(slot,dll,'"%s"'%name if name else 'NULL',ordn or 0))
o+=['};','void lt_iat_init(void){',' for(unsigned i=0;i<sizeof(tab)/sizeof(tab[0]);i++){ HMODULE h=LoadLibraryA(tab[i].dll); void*p=h?(void*)GetProcAddress(h,tab[i].name?tab[i].name:(LPCSTR)(UINT_PTR)tab[i].ord):0; *(void**)tab[i].slot=p; }','}']
open('c/lt_iat.c','w').write('\n'.join(o)+'\n'); print('iat slots',len(imps))
