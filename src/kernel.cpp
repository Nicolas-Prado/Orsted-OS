#include "../include/types.h"
#include "../include/gdt.h"

void printf(int8_t* str){
    uint16_t* VideoMemory = (uint16_t*) 0xb8000;
    
    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("El Psy Kongroo!");

    GlobalDescriptorTable gdt;

    while(1);
}