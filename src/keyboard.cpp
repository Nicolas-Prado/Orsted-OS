#include "../include/keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(0x21, manager),
  dataPort(0x60),
  commandPort(0x64) {
    while (commandPort.Read() & 0x1)
        dataPort.Read();
    
    commandPort.Write(0xAE); // tells the keyboard to talk with the PIC... Is that?
    commandPort.Write(0x20); //get current state
    uint8_t status = (dataPort.Read() | 1) & ~0x10; //Set rightmost bit because this will be new state
    commandPort.Write(0x60); // set state
    dataPort.Write(status);

    dataPort.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver(){

}

void printf(char*);

uint32_t KeyboardDriver::handleInterrupt(uint32_t esp){
    uint8_t key = dataPort.Read();

    if(/key < 0x80){
        char* foo = "EPK: KEYBOARD 0x00";
        char* hex = "0123456789ABCDEF";

        foo[16] = hex[(key>>4) & 0x0F];
        foo[17] = hex[key & 0x0F];
        printf(foo);
        printf("\n");
    }

    return esp;
}