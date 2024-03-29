#include "../include/interrupts.h"
#include "../include/utils.h"

InterruptHandler::InterruptHandler(uint8_t interruptNumber, InterruptManager* interruptManager){
    this->interruptNumber = interruptNumber;
    this->interruptManager = interruptManager;

    interruptManager->handlers[interruptNumber] = this;
}

InterruptHandler::~InterruptHandler(){
    if(interruptManager->handlers[interruptNumber] == this)
        interruptManager->handlers[interruptNumber] = 0;
}

uint32_t InterruptHandler::handleInterrupt(uint32_t esp){
    return esp;
}

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

InterruptManager* InterruptManager::ActiveInterruptManager = 0;

void InterruptManager::SetInterruptDescriptorTableEntry(
    uint8_t interruptNumber,
    uint16_t codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t DescriptorPrivilegeLevel,
    uint8_t DescriptorType
) {
    const uint8_t IDT_DESC_PRESENT = 0x80;

    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel & 0b11) << 5);
    interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
: picMasterCommand(0x20),
  picMasterData(0x21),
  picSlaveCommand(0xA0),
  picSlaveData(0xA1) {
    uint16_t codeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for(int16_t i = 0; i<256; i++){
        handlers[i] = 0;

        SetInterruptDescriptorTableEntry(i, codeSegment, &InterruptManager::ignoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
    }

    SetInterruptDescriptorTableEntry(0x20, codeSegment, &InterruptManager::handleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21, codeSegment, &InterruptManager::handleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x2C, codeSegment, &InterruptManager::handleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);

    //ICW1
    picMasterCommand.Write(0x11); 
    picSlaveCommand.Write(0x11);

    //ICW2
    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);

    //ICW3
    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    //ICW4
    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    //Clear data registers, finish the preparing to receive interrupts
    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

    interruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;

    asm volatile("lidt %0" : : "m" (idt));
}

InterruptManager::~InterruptManager() {

}

void InterruptManager::Activate() {
    if(ActiveInterruptManager != 0)
        ActiveInterruptManager->Deactivate();
    ActiveInterruptManager = this;
    asm("sti");
}

void InterruptManager::Deactivate() {
    if(ActiveInterruptManager == this){
        ActiveInterruptManager = 0;
        asm("cli");
    }
}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){
    if(ActiveInterruptManager != 0)
        return ActiveInterruptManager->doHandleInterrupt(interruptNumber, esp);
    return esp;
}

uint32_t InterruptManager::doHandleInterrupt(uint8_t interruptNumber, uint32_t esp){
    if(handlers[interruptNumber] != 0) {
        handlers[interruptNumber]->handleInterrupt(esp);
    } else if(interruptNumber != 0x20) {
        char* foo = "EPK: UNHANDLED INTERRUPT 0x00";
        char* hex = "0123456789ABCDEF";

        foo[27] = hex[(interruptNumber>>4) & 0x0F];
        foo[28] = hex[interruptNumber & 0x0F];
        printf(foo);
    }

    if(0x20 <= interruptNumber && interruptNumber < 0x30){
        picMasterCommand.Write(0x20);
        if(0x28 <= interruptNumber)
            picSlaveCommand.Write(0x20);
    }

    return esp;
}