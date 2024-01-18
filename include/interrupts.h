#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"

    class InterruptManager{
        protected:

            struct GateDescriptor{
                uint16_t handlerAddressLowBits;
                uint16_t han

            } __attribute__((packed));

        public:
            static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);

            static void handleInterruptRequest0x00(); //Timer interrupt?
            static void handleInterruptRequest0x01();
    };

#endif