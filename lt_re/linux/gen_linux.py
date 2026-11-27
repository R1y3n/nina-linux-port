#!/usr/bin/env python3
"""Generate the data the native-Linux build needs. Run from lt_re/linux/ after lift_all.py + gen_image.py."""
import re,glob,subprocess,pefile,os
exe=os.environ.get('LT_EXE','../lithtechreal.exe')
pe=pefile.PE(exe); raw=open(exe,'rb').read()
# 1. export table of implemented shim functions
names=[]
for f in sorted(glob.glob('*.c')):
    if f.startswith('lt_'): continue
    names+=re.findall(r'\bW_(\w+)\s*\(',open(f).read())
names=sorted(set(names))
o=['struct exp{const char*name;void*fn;};']+['extern char W_%s[];'%n for n in names]+['struct exp lt_exports[]={']+[' {"%s",(void*)W_%s},'%(n,n) for n in names]+['};','int lt_exports_n=%d;'%len(names)]
open('lt_exports.c','w').write('\n'.join(o)+'\n')
# 2. arity table from mingw import libs (name -> bytes of stdcall args)
ar={}
for lib in glob.glob('/usr/i686-w64-mingw32/lib/lib*.a'):
    out=subprocess.run(['nm','-g',lib],capture_output=True,text=True).stdout
    for m in re.finditer(r'^[0-9a-f]* T _(\w+)@(\d+)$',out,re.M): ar.setdefault(m.group(1),int(m.group(2)))
o=['struct ar{const char*name;int n;};','struct ar lt_arity[]={']+[' {"%s",%d},'%(k,ar[k]) for k in sorted(ar)]+['};','int lt_arity_n=%d;'%len(ar)]
open('lt_arity.c','w').write('\n'.join(o)+'\n')
# 3. IAT slots
imps=[]
for d in pe.DIRECTORY_ENTRY_IMPORT:
    for i in d.imports: imps.append((i.address,d.dll.decode(),i.name.decode() if i.name else None,i.ordinal or 0))
o=['struct iat{unsigned slot;const char*dll;const char*name;unsigned ord;};','struct iat lt_iat_tab[]={']+[' {0x%08x,"%s",%s,%d},'%(s,d,'"%s"'%n if n else '0',oo) for s,d,n,oo in imps]+['};','int lt_iat_n=%d;'%len(imps)]
open('lt_iat_tab.c','w').write('\n'.join(o)+'\n')
# 4. original images embedded as blobs (written by ../build_images.py)
import shutil; shutil.copy('../lttext.bin','lttext.bin'); shutil.copy('../ltdata.bin','ltdata.bin')
blob='.section .rodata\n'+''.join('.globl lt_blob_%s\nlt_blob_%s:\n.incbin "%s.bin"\n.globl lt_blob_%s_end\nlt_blob_%s_end:\n'%(a,a,b,a,a) for a,b in [('hdr','hdr'),('text','lttext'),('data','ltdata'),('rsrc','rsrc')])
open('blobs.S','w').write(blob)
# 5. translated code, ELF flavour (no leading underscores)
s=open('../lifted_all.s').read().replace('_lt_','lt_')
vas=re.findall(r'^\.Llt_([0-9a-f]{8}):',s,re.M)
s+='.section .ltmap,"a"\n.globl lt_map_start\nlt_map_start:\n'+''.join('.long .Llt_%s, 0x%s\n'%(v,v) for v in vas)+'.globl lt_map_end\nlt_map_end:\n'
open('lifted_all_elf.s','w').write(s)
print('exports',len(names),'arity',len(ar),'iat',len(imps))
