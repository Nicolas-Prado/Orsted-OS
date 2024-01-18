#include "../include/interrupts.h"

void printf(char* str);

void InterruptManager::SetInterruptDescriptorTableEntry(
    uint8_t interruptNumber,
    uint16_t codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t DescriptorPrivilegeLevel,
    uint8_t DescriptorType
) {

}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt) {

}

InterruptManager::~InterruptManager() {

}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){

    printf(" INTERRUPT")

    return esp;
}

handleInterruptc