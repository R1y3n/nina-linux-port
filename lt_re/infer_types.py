import re,collections,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32,CS_OP_MEM
from capstone.x86 import X86_OP_MEM
pe=pefile.PE('/mnt/user-data/uploads/lithtech.exe'); base=pe.OPTIONAL_HEADER.ImageBase
data=open('/mnt/user-data/uploads/lithtech.exe','rb').read()
t=next(s for s in pe.sections if s.Name.startswith(b'.text'))
md=Cs(CS_ARCH_X86,CS_MODE_32); md.detail=True
acc=collections.defaultdict(set)
FP=('fld','fst','fadd','fsub','fmul','fdiv','fcom','fild','fist','fiadd','fisub','fimul','fidiv','ficom','fsubr','fdivr','fisubr','fidivr')
code=data[t.PointerToRawData:t.PointerToRawData+t.Misc_VirtualSize]
for i in md.disasm(code,base+t.VirtualAddress):
    for op in i.operands:
        if op.type==X86_OP_MEM and op.mem.base==0 and op.mem.index==0 and op.mem.disp>=base+0x80000:
            va=op.mem.disp&0xffffffff; m=i.mnemonic
            if m.startswith(FP):
                k='f32' if op.size==4 else 'f64' if op.size==8 else 'fx'
                if m.startswith(('fild','fist','fiadd','fisub','fimul','fidiv','ficom','fisubr','fidivr')): k='i%d'%(op.size*8)
                acc[va].add(k)
            elif m=='lea': acc[va].add('addr')
            else: acc[va].add('i%d'%(op.size*8))
res={}
for va,k in acc.items():
    if 'f32' in k and 'addr' in k and k<={'f32','addr','i32'}: res[va]='float[64]'
    elif 'f32' in k and k<={'f32','i32'}: res[va]='float'
    elif 'f64' in k and k<={'f64','i32'}: res[va]='double'
    elif k<= {'i8'}: res[va]='uint8_t'
    elif k<= {'i16'}: res[va]='uint16_t'
import json; json.dump({hex(k):v for k,v in res.items()},open('/tmp/gtypes.json','w'))
c=collections.Counter(res.values()); print(c)
