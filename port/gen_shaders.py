#!/usr/bin/env python3
"""Embed the GLSL RCDATA resources (opengl.rc.in) in the shared object: generates shader_table.cpp."""
import re, sys
src = sys.argv[1] if len(sys.argv) > 1 else 'src'
ids = dict((m.group(1), int(m.group(2))) for m in re.finditer(r'#define\s+(IDR_\w+)\s+(\d+)', open(src + '/resources/resource.h').read()))
out = ['#include <stddef.h>', 'struct WpRes { int id; const unsigned char *data; unsigned size; };']
ent = []
for m in re.finditer(r'(IDR_\w+)\s+RCDATA\s+"[^"]*?/(src/resources/shaders/[^"/]+)"', open(src + '/resources/opengl.rc.in').read()):
    name, path = m.group(1), m.group(2)
    d = open(src + '/../' + path, 'rb').read()
    out.append('static const unsigned char r_%s[] = {%s,0};' % (name, ','.join(map(str, d))))
    ent.append('{%d, r_%s, %d}' % (ids[name], name, len(d)))
out.append('extern const WpRes g_wp_resources[] = {%s};' % ','.join(ent))
out.append('extern const unsigned g_wp_resource_count = %d;' % len(ent))
open(src + '/shader_table.cpp', 'w').write('\n'.join(out) + '\n')
print(len(ent), 'shader resources embedded')
