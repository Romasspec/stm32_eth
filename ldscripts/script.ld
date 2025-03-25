/* Highest address of the user mode stack */
_estack = 0x20005000;    /* end of RAM */

/* Memories definition */
MEMORY
{
  RAM (xrw)		: ORIGIN = 0x20000000, LENGTH = 20K
  ROM (rx)		: ORIGIN = 0x8000000, LENGTH = 128K
}

/* Sections */
SECTIONS
{
  /* The program code and other data into ROM memory */
  .text :
  {
    . = ALIGN(4); 
    *(.vectors)
    KEEP(*(.vectors))
    *(.text)           /* .text sections (code) */
  } >ROM

  /* Constant data into ROM memory*/
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
  } >ROM

	_sidata = LOADADDR(.data);
	
  /* Initialized data sections into RAM memory */
  .data : 
  {
	_sdata = . ;        	/* STM specific definition */
    . = ALIGN(4);
    *(.data)           /* .data sections */
    _edata = . ;        	/* STM specific definition */
  } >RAM AT> ROM

  
  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss :
  {
	_sbss = .;              /* STM specific definition */
    *(.bss)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
    end = __bss_end__;
  } >RAM
  
  
   /* This can remove the debugging information from the standard libraries */    
    /* 
    DISCARD :
    {
     libc.a ( * )
     libm.a ( * )
     libgcc.a ( * )
     }
     */
  
    /* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /*
     * DWARF debug sections.
     * Symbols in the DWARF debugging sections are relative to the beginning
     * of the section so we begin them at 0.  
     */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }  

}
