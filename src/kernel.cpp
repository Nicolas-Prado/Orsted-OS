//Helpful stuff
#include "../include/types.h"
#include "../include/utils.h"

//Important stuff
#include "../include/gdt.h"
#include "../include/interrupts.h"

//Drivers
#include "../include/driver.h"
#include "../include/keyboard.h"
#include "../include/mouse.h"

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Welcome to Orsted OS\n");
    printf("This is a simple OS made by Worcnaz Prado, one of the most trustful follower of Orsted in Earth(aka Real World)\n");
    printf("Status: Very beginning, we just maded the GDT, IDT and implemented a very simple and incomplete Keyboard driver\n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    printf("Initializing Hardware, Stage 1\n");
    DriverManager driverManager;

        KeyboardDriver keyboard(&interrupts);
        driverManager.addDriver(&keyboard);

        MouseDriver mouse(&interrupts);
        driverManager.addDriver(&mouse);

    printf("Initializing Hardware, Stage 2\n");
    driverManager.activateAll();

    printf("Initializing Hardware, Stage 3\n");
    interrupts.Activate();

    while(1);
}