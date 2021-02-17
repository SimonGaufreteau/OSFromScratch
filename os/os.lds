ENTRY(main);

PHDRS
{
  headers PT_PHDR PHDRS;
  code PT_LOAD FILEHDR PHDRS;
}

SECTIONS
{
  
  .text 0x1000: { *(.text)  } :code
  .data :  { *(.data)  }
  .bss :  { *(.bss) }
  /DISCARD/ : { *(.eh_frame) }
}