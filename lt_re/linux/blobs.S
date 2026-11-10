.section .rodata
.globl lt_blob_hdr
lt_blob_hdr:
.incbin "hdr.bin"
.globl lt_blob_hdr_end
lt_blob_hdr_end:
.globl lt_blob_text
lt_blob_text:
.incbin "lttext.bin"
.globl lt_blob_text_end
lt_blob_text_end:
.globl lt_blob_data
lt_blob_data:
.incbin "ltdata.bin"
.globl lt_blob_data_end
lt_blob_data_end:
.globl lt_blob_rsrc
lt_blob_rsrc:
.incbin "rsrc.bin"
.globl lt_blob_rsrc_end
lt_blob_rsrc_end:
