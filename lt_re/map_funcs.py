#!/usr/bin/env python3
"""Map lithtech.exe functions -> repo source files via string xrefs.
usage: map_funcs.py lithtech.exe <repo_root> <outdir>"""
import sys,re,os,json,bisect,collections
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
exe,repo,out=sys.argv[1:4]
os.makedirs(out,exist_ok=True)
pe=pefile.PE(exe); base=pe.OPTIONAL_HEADER.ImageBase
data=open(exe,'rb').read()
def sec(n): return next(s for s in pe.sections if s.Name.startswith(n))
text=sec(b'.text'); tva=base+text.VirtualAddress
tb=data[text.PointerToRawData:text.PointerToRawData+text.Misc_VirtualSize]
def va2off(va):
    for s in pe.sections:
        a=base+s.VirtualAddress
        if a<=va<a+max(s.Misc_VirtualSize,s.SizeOfRawData): return s.PointerToRawData+va-a
# 1. strings in .rdata/.data with VA
strs={}
for n in (b'.rdata',b'.data'):
    s=sec(n); raw=data[s.PointerToRawData:s.PointerToRawData+s.SizeOfRawData]
    for m in re.finditer(rb'[\x20-\x7e\t\r\n]{6,}(?=\x00)',raw):
        strs[base+s.VirtualAddress+m.start()]=m.group().decode('latin1')
# 2. repo corpus: string literal -> files
lit=collections.defaultdict(set)
for dp,_,fs in os.walk(repo):
    if '/.git' in dp: continue
    for f in fs:
        if f.lower().endswith(('.cpp','.c','.h','.inl')):
            p=os.path.join(dp,f)
            try: t=open(p,errors='ignore').read()
            except: continue
            for m in re.finditer(r'"((?:[^"\\\n]|\\.){6,})"',t):
                lit[m.group(1).replace('\\n','\n').replace('\\t','\t').replace('\\\\','\\')].add(os.path.relpath(p,repo))
# 3. disassemble, find function starts
md=Cs(CS_ARCH_X86,CS_MODE_32); md.detail=False
starts=set(); refs=[]  # (insn_va, target)
for i in md.disasm(tb,tva):
    if i.mnemonic=='call' and i.op_str.startswith('0x'):
        t=int(i.op_str,16)
        if tva<=t<tva+len(tb): starts.add(t)
    for m in re.finditer(r'0x[0-9a-f]{6,8}',i.op_str):
        v=int(m.group(),16)
        if v in strs: refs.append((i.address,v))
for m in re.finditer(rb'\x55\x8b\xec',tb): starts.add(tva+m.start())
fl=sorted(starts)
fmap=collections.defaultdict(list)
for a,v in refs:
    k=bisect.bisect_right(fl,a)-1
    if k>=0: fmap[fl[k]].append(v)
res=[];hits=0
for f,vs in sorted(fmap.items()):
    ss=[]; files=collections.Counter()
    for v in vs:
        s=strs[v]; fs=lit.get(s) or lit.get(s.rstrip('\r\n'))
        ss.append({'va':hex(v),'s':s[:100].replace('\\"', ''),'files':sorted(fs)[:4] if fs else []})
        for x in (fs or []): files[x]+=1
    if files: hits+=1
    res.append({'func':hex(f),'strings':ss,'best_files':files.most_common(3)})
json.dump(res,open(out+'/func_string_map.json','w'),indent=1)
with open(out+'/lithtech_rename.py','w') as g:   # Ghidra Jython script
    g.write("# @category LithTech\nfrom ghidra.program.model.symbol import SourceType\n")
    g.write("def go(a,n,c):\n    ad=toAddr(a); f=getFunctionAt(ad) or createFunction(ad,None)\n    if f:\n        setPlateComment(ad,c)\n        if f.getName().startswith('FUN_'): f.setName(n,SourceType.USER_DEFINED)\n")
    for r in res:
        if not r['best_files']: continue
        top=r['best_files'][0][0]; stem=re.sub(r'\W','_',os.path.splitext(os.path.basename(top))[0])
        c="repo: "+", ".join(f for f,_ in r['best_files'])
        g.write("go('%s','%s_%s','%s')\n"%(r['func'][2:],stem,r['func'][2:],c.replace("'","")))
print('functions found',len(fl),'| funcs with string refs',len(fmap),'| matched to repo',hits)
cnt=collections.Counter(r['best_files'][0][0].split('/')[0]+'/'+('/'.join(r['best_files'][0][0].split('/')[1:3])) for r in res if r['best_files'])
for k,v in cnt.most_common(15): print(v,k)
