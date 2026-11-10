import re,glob,subprocess,sys,json,os
CC=['i686-w64-mingw32-gcc','-c','-w','-fpermissive','-x','c','-fno-builtin','-include','ghidra_types.h']
def funcs(lines):
    out=[];i=0
    while i<len(lines):
        if lines[i]=='{' and i>0:
            j=i-1
            while j>=0 and lines[j].strip()=='' : j-=1
            s=j
            while s>0 and lines[s-1].strip()!='' and not lines[s-1].startswith('/*') and not lines[s-1].startswith('#'): s-=1
            k=i
            while k<len(lines) and lines[k]!='}': k+=1
            out.append((s,i,k)); i=k
        i+=1
    return out
stubbed={}
hdr_err=0
for f in sorted(glob.glob('*.c')):
    for rnd in range(6):
        r=subprocess.run(CC+[f,'-o','../obj/'+f[:-2]+'.o'],capture_output=True,text=True)
        errs=[int(m.group(1)) for m in re.finditer(r'^%s:(\d+):\d+: error'%re.escape(f),r.stderr,re.M)]
        other=len(re.findall(r'^(?!%s)[^\s:]+\.h:\d+:\d+: error'%re.escape(f),r.stderr,re.M))
        if not errs: 
            hdr_err+=other; break
        lines=open(f).read().split('\n'); fs=funcs(lines); hit=set()
        for e in errs:
            for (s,b,k) in fs:
                if s<=e-1<=k: hit.add((s,b,k)); break
        if not hit: print('unmapped errors in',f,errs[:3]); break
        for (s,b,k) in sorted(hit,reverse=True):
            name=re.search(r'(\w+)\(',' '.join(lines[s:b]))
            stubbed[name.group(1) if name else '?']=f
            lines[b+1:k]=['  __builtin_trap(); /* STUB: decompiled body did not compile */']
        open(f,'w').write('\n'.join(lines))
json.dump(stubbed,open('../stubbed_functions.json','w'),indent=0)
print('stubbed',len(stubbed),'header errors',hdr_err)
