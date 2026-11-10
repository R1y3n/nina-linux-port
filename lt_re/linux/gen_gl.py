#!/usr/bin/env python3
"""Parse the Mesa GL headers for argument-byte sizes of every GL function (stdcall thunks need them)."""
import re
txt=open('/usr/include/GL/gl.h').read()+open('/usr/include/GL/glext.h').read()
ar={}
for m in re.finditer(r'GLAPI\s+[\w\s\*]+?\s*(?:GL)?APIENTRY\s+(gl\w+)\s*\(([^)]*)\)',txt):
    name,args=m.group(1),m.group(2).strip()
    n=0
    if args and args!='void':
        for a in args.split(','):
            n+=8 if (re.search(r'GLdouble|GLclampd|GLint64|GLuint64',a) and '*' not in a) else 4
    ar.setdefault(name,n)
o=['struct glar{const char*name;int n;};','struct glar lt_glarity[]={']+[' {"%s",%d},'%(k,ar[k]) for k in sorted(ar)]+['};','int lt_glarity_n=%d;'%len(ar)]
open('lt_glarity.c','w').write('\n'.join(o)+'\n'); print('GL functions',len(ar))
