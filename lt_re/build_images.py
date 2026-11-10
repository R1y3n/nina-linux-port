#!/usr/bin/env python3
"""Derive the memory layout from the PE and write the blobs mapped at the ORIGINAL addresses + linux/layout.h."""
import sys, pefile, os
exe = os.environ.get('LT_EXE', '/mnt/user-data/uploads/lithtechreal.exe')
pe = pefile.PE(exe); base = pe.OPTIONAL_HEADER.ImageBase; raw = open(exe, 'rb').read()
S = {s.Name.rstrip(b'\0').decode(): s for s in pe.sections}
text, rdata, data, rsrc = S['.text'], S['.rdata'], S['.data'], S['.rsrc']
al = lambda v: (v + 0xfff) & ~0xfff
tva = base + text.VirtualAddress; tsz = al(max(text.SizeOfRawData, text.Misc_VirtualSize))
dva = base + rdata.VirtualAddress
dend = base + al(data.VirtualAddress + max(data.Misc_VirtualSize, data.SizeOfRawData))   # .data incl. .bss
assert dend <= base + rsrc.VirtualAddress
rva = base + rsrc.VirtualAddress; rsz = al(max(rsrc.SizeOfRawData, rsrc.Misc_VirtualSize))
open('lttext.bin', 'wb').write(raw[text.PointerToRawData:text.PointerToRawData + text.SizeOfRawData].ljust(tsz, b'\0'))
img = bytearray(dend - dva)
for s in (rdata, data):
    a = base + s.VirtualAddress
    d = raw[s.PointerToRawData:s.PointerToRawData + min(s.SizeOfRawData, s.Misc_VirtualSize)]
    img[a - dva:a - dva + len(d)] = d
open('ltdata.bin', 'wb').write(img)
open('linux/hdr.bin', 'wb').write(raw[:0x1000].ljust(0x1000, b'\0'))
open('linux/rsrc.bin', 'wb').write(raw[rsrc.PointerToRawData:rsrc.PointerToRawData + rsrc.SizeOfRawData].ljust(rsz, b'\0'))
open('linux/layout.h', 'w').write('#define LT_TEXT_VA 0x%x\n#define LT_TEXT_SZ 0x%x\n#define LT_DATA_VA 0x%x\n#define LT_DATA_SZ 0x%x\n#define LT_RSRC_VA 0x%x\n#define LT_RSRC_SZ 0x%x\n#define LT_IMAGE_END 0x%x\n' % (tva, tsz, dva, dend - dva, rva, rsz, rva + rsz))
open('layout.json', 'w').write('{"text":%d,"tsz":%d,"data":%d,"dend":%d,"rsrc":%d,"rsz":%d}' % (tva, tsz, dva, dend, rva, rsz))
print('text %x+%x data %x..%x rsrc %x+%x' % (tva, tsz, dva, dend, rva, rsz))
