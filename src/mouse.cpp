#include "../include/mouse.h"
#include "../include/types.h"

MouseDriver::MouseDriver(InterruptManager* manager)
: InterruptHandler(0x2C, manager),
  dataport(0x60),
  commandport(0x64) {
    offset = 0;
    buttons = 0;

    commandport.Write(0xA8); //activate interrupts...?
    commandport.Write(0x20); //get current state
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60); //set state
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}

MouseDriver::~MouseDriver(){

}

MouseDriver::handleInterrupt(uint32_t esp) {
    uint8_t status = commandport.Read();
    if(!(status & 0x20))
        return esp;

    static int8_t x=0, y=0;

    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;

    if(offset == 0){
        x += buffer[1];
        y -= buffer[2]; //why not += ??
    }

    return esp;
}