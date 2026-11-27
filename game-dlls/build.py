#!/usr/bin/env python3
"""Cross-compile AVP2 ObjectDLL / ClientShellDLL with MinGW-w64 (i686) on Linux.
usage: build.py <path to extracted si_avp2_sourcecode_v1/proj> [--link]
Produces Windows PE DLLs (run under Wine/with the Windows engine), NOT Linux ELF."""
import os,re,sys,shlex,subprocess
from concurrent.futures import ThreadPoolExecutor
HERE=os.path.dirname(os.path.abspath(__file__)); ROOT=os.path.abspath(sys.argv[1]); os.chdir(ROOT)
T='i686-w64-mingw32'; SH=os.path.join(HERE,'shim','compat'); OUT=os.path.join(HERE,'out'); os.makedirs(OUT,exist_ok=True)
inc=['AVP2/Shared','AVP2/ObjectDLL','AVP2/ClientShellDLL','LT2/lithshared/incs','LT2/sdk/inc','LT2/sdk/inc/compat','LT2/lithshared/stdlith','LT2/lithshared/butemgr','LT2/lithshared/ltguimgr','LT2/lithshared/lithfontmgr','LT2/lithshared/regmgr','LT2/lithshared/cryptmgr','LT2/lithshared/mfcstub','LT2/lithshared/lith','AVP2/ServerRes','AVP2/ClientRes','LT2/lithshared/wonapi']
COMMON=['-fpermissive','-w','-std=gnu++98','-Wno-write-strings','-fno-strict-aliasing','-I'+SH]+['-I'+i for i in inc]+['-DWIN32','-D_WINDOWS','-D_AVP2BUILD','-DLT15_COMPAT','-DNO_PRAGMA_LIBS','-DNDEBUG','-include','lt_debugnew.h']
FLAGS={'ObjectDLL':COMMON+['-D_OBJECTBUILD'],'ClientShellDLL':COMMON+['-D_CLIENTBUILD']}
DSP={'ObjectDLL':'Object','ClientShellDLL':'ClientShellDLL'}
# system headers referenced with non-MinGW spelling
MG='/usr/%s/include'%T
for n,t in (('IO.h','io.h'),('Direct.h','direct.h'),('sys\\stat.h','sys/stat.h'),('sys\\types.h','sys/types.h')):
    d=os.path.join(SH,n)
    if not os.path.lexists(d) and os.path.exists(os.path.join(MG,t)): os.symlink(os.path.join(MG,t),d)
def ci(base,path):
    cur=base
    for p in path.replace('\\','/').split('/'):
        if p in('.',''): continue
        if p=='..': cur=os.path.dirname(cur); continue
        try: m=[e for e in os.listdir(cur) if e.lower()==p.lower()]
        except OSError: return None
        if not m: return None
        cur=os.path.join(cur,m[0])
    return cur if os.path.isfile(cur) else None
def make_links():  # Linux is case-sensitive / MSVC accepts backslashes: add symlinks in MSVC search order
    pat=re.compile(rb'#\s*include\s*"([^"]+)"'); n=0
    for dp,_,fs in os.walk('.'):
        for f in fs:
            if not f.lower().endswith(('.cpp','.h','.c','.inl')) or os.path.islink(os.path.join(dp,f)): continue
            for m in pat.findall(open(os.path.join(dp,f),'rb').read()):
                nm=m.decode('latin1').strip(); norm=nm.replace('\\','/')
                cands=[dp]+inc
                if any(os.path.isfile(os.path.join(d,norm)) for d in cands) and '\\' not in nm: continue
                for d in cands:
                    h=ci(d,nm)
                    if h:
                        dst=os.path.join(d,nm)
                        if '/' in nm: os.makedirs(os.path.dirname(dst),exist_ok=True)
                        if not os.path.lexists(dst): os.symlink(os.path.abspath(h),dst); n+=1
                        break
    return n
def build(proj,extra):
    base='AVP2/'+proj; od=os.path.join(OUT,proj); os.makedirs(od,exist_ok=True)
    srcs=sorted({m.group(1).strip() for l in open('%s/%s.dsp'%(base,DSP[proj]),'rb').read().decode('latin1').splitlines() for m in [re.match(r'SOURCE=(.*\.(?:cpp|c))\s*$',l,re.I)] if m})
    def one(s):
        r=ci(base,s)
        if not r: return (s,False,'missing')
        o=os.path.join(od,r.replace('/','_')[:-4]+'.o')
        p=subprocess.run([T+'-g++']+FLAGS[proj]+['-x','c++','-c',r,'-o',o],capture_output=True,text=True,env={**os.environ,'LC_ALL':'C'})
        return (r,p.returncode==0,p.stderr)
    with ThreadPoolExecutor(os.cpu_count() or 4) as ex: res=list(ex.map(one,srcs))
    bad=[r for r in res if not r[1]]
    print('%s: %d/%d compiled'%(proj,len(res)-len(bad),len(res)))
    for r in bad: print('  FAIL',r[0])
    return od
print('include symlinks created:',make_links())
objs={p:build(p,[]) for p in FLAGS}
# libshim
subprocess.run([T+'-g++']+FLAGS['ObjectDLL']+['-c',os.path.join(HERE,'libshim','mfcstub.cpp'),'-o',os.path.join(OUT,'mfcstub.o')],check=True)
if '--link' in sys.argv:
    libs=['-lwsock32','-lws2_32','-lwinmm','-lole32','-luuid','-lgdi32','-luser32','-ladvapi32','-lshell32','-lcomctl32','-limm32','-lversion']
    for proj,name in (('ObjectDLL','object.lto'),('ClientShellDLL','cshell.dll')):
        ofs=[os.path.join(objs[proj],f) for f in sorted(os.listdir(objs[proj]))]+[os.path.join(OUT,'mfcstub.o')]
        extra=[os.path.join(OUT,f) for f in sorted(os.listdir(OUT)) if f.startswith('ext_') and f.endswith('.o')]  # drop your own library objects in out/ext_*.o
        p=subprocess.run([T+'-g++','-shared','-static-libgcc','-static-libstdc++','-o',os.path.join(OUT,name)]+ofs+extra+libs,capture_output=True,text=True)
        und=sorted(set(re.findall(r"undefined reference to `([^']+)'",p.stderr)))
        print('%s: %s (%d undefined symbols)'%(name,'LINKED' if p.returncode==0 else 'link failed',len(und)))
