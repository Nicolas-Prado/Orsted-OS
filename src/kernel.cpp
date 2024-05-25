//Helpful stuff
#include "../include/types.h"
#include "../include/utils.h"

//Important stuff
#include "../include/gdt.h"
#include "../include/interrupts.h"

//Drivers
#include "../include/keyboard.h"
#include "../include/mouse.h"

// ebx, eax values... so the last value put in the stack will be the first parameter here, in the function
extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Welcome to Orsted OS\n");
    printf("This is a simple OS made by Worcnaz Prado, one of the most trustful follower of Orsted in Earth(aka Real World)\n");
    printf("Status: Very beginning, we just maded the GDT, IDT and implemented a very simple and incomplete Keyboard driver");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    KeyboardDriver keyboard(&interrupts);
    MouseDriver mouse(&interrupts);

    interrupts.Activate();

    while(1);
}