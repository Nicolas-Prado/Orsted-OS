.set IRQ_BASE, 0x20 # Exception take the first 32 interrupt index, so if i send interrupt 0x00 i mean the 0x20, because the offset of the exceptions

.section .text

.extern _ZN16InterruptManager15handleInterruptEhj

.global _ZN16InterruptManager22ignoreInterruptRequestEv

.macro HandleException num
.global _ZN16InterruptManager16handleException\num\()Ev
_ZN16InterruptManager16handleException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26handleInterruptRequest\num\()Ev
_ZN16InterruptManager26handleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm


HandleInterruptRequest 0x00
/*Example of the macro
.global _ZN16InterruptManager26handleInterruptRequest0x00\()Ev
_ZN16InterruptManager26handleInterruptRequest0x00\()Ev:
    movb $0x00(immediate value) + IRQ_BASE, (interruptnumber)
    jmb int_bottom
 */
HandleInterruptRequest 0x01


int_bottom:

    pusha  # General purpose registers
    pushl %ds # Data segment
    pushl %es # Extra segment
    pushl %fs # F segment... ?
    pushl %gs # G segment

    pushl %esp
    push (interruptnumber)
    call _ZN16InterruptManager15handleInterruptEhj # Call -> push return address
    # addl $5, %esp // This is genius!!! This will reset the stack poiter before the pushs(pushl %esp, push (interruptnumber)). This because we need to mantain the starting state of the stack. But how that little instruction do that? Simple! Add 5 to the esp register! if each 1 address refer 1 byte(8 bits) if i add 5 i will jump 5 bytes(40 bits), that is exactly the sum of the size of esp(4 bytes -> 32 bits) + interruptnumber(1 byte -> 8 bits), and you know, the stack are in reverse, on push it decrease its value to point the start to the stack, so add more value will refer old values!
    movl %eax, %esp # But we use that to reset the esp. In the eax we will have the return from the C function, who is the initial pointer pushed into the stack. So i just use that to set esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

_ZN16InterruptManager22ignoreInterruptRequestEv:

    iret # iret -> a special return for interrupt case, poping more values from stack that was saved there when the cpu gived the control to the interrupt handler. After the pops, return to the stopped process before the interrupt

.data
    interruptnumber: .byte 0