OUTPUT_FORMAT("elf32-z80", "elf32-z80", "elf32-z80")
OUTPUT_ARCH(z180)
ENTRY(_start)
PHDRS
{
  text PT_LOAD ;
  data PT_LOAD ;
  bss PT_DYNAMIC ;
}

SECTIONS
{
    .apl 0x5000 :
    {
     KEEP (*(SORT_NONE(.header)))
     /* set proper ELF flags for section */
     *(.apl .stub .apl.* .gnu.linkonce.t.*)
    } :text
    .text 0x5008 :
    {
        /* make fallback entry point address,
                _start from your code will override it */
        PROVIDE(_start = .);
        KEEP (*(SORT_NONE(_HEADER)))
        KEEP (*(SORT_NONE(_GSINIT)))
        KEEP (*(SORT_NONE(_GSFINAL)))
        *(_HOME)
        *(_CODE)
        /* set proper ELF flags for section */
        *(.text .stub .text.* .gnu.linkonce.t.*)
        s__INITIALIZER = .;
        KEEP(*(SORT_NONE(_INITIALIZER)))
        l__INITIALIZER = . - s__INITIALIZER;
        __text_end = .;
    } :text
    .data :
    {
        __data_start = .;
        s__INITIALIZED = .;
	s__HEAP = .;
        KEEP(*(SORT_NONE(_INITIALIZED)))
        /* set proper ELF flags for section */
        *(.data .data.* .gnu.linkonce.d.*)
        __data_end = .;
    } :data
    .bss :
    {
        __bss_start = .;
	s__DATA = .;
        *(_DATA)
        /* set proper ELF flags for section */
        *(.bss .bss.* .gnu.linkonce.b.*)
        __bss_end = .;
	l__DATA = . - s__DATA;
    } :data :bss
}
