.set MAGIC, 0x1badb002 ##Magic number for the boot loader identify that program a operational system. Basicly to configure all the proccess by the bootloader
.set FLAGS, (1<<0 | 1<<1) ##This(<<) is a bit shift to the left! And the "|" operator is a bitwise OR, to use OR in all bits and concat the bits.
.set CHECKSUM, -(MAGIC + FLAGS) ##Used to verify the Multiboot header, if its a valid Multiboot header

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax
    push %ebx
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024;
kernel_stack: