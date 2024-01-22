#include "../include/gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0, 0, 0),
unusedSegmentSelector(0, 0, 0),
codeSegmentSelector(0,64*1024*1024, 0x9A),
dataSegmentSelector(0,64*1024*1024, 0x92) {
    uint32_t i[2];
	i[0] = sizeof(GlobalDescriptorTable) << 16; // BRO! THAT IS A BURNAHOLE! I MEAN... That is the right version... i thing, for some reason the guide is was following define base address before the size, and that not make sense! Size should come first https://en.wikibooks.org/wiki/X86_Assembly/Global_Descriptor_Table
	i[1] = (uint32_t)this;

    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i)+2)); // +2 jumping the empty 0 made by << 16 shift. REMEMBER!Endian Little Order!!! So the first bytes are the least important, so the 0000 0000 are there!
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16_t GlobalDescriptorTable::DataSegmentSelector(){
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector(){
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags){
    uint8_t* target = (uint8_t*)this;

    if(limit <= 65536){
        target[6] = 0x40; //16-bit mode
    }
    else {
        // That limit address needs to be compatible to 8086 first x86 processor, that have just 20 bits bus address. To do that, we cut the 12 last bits and replace by 12 positive bit(1). But, if we do that, we need to decrement the value to not increase the limit, that would cause problems, so it is decressed
        if((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;
        
        target[6] = 0xC0; //32-bit mode
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = flags;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base() {
    uint8_t* target = (uint8_t*) this;

    uint32_t result;

    result = target[7];
    result = (result << 8) | target[4];
    result = (result << 8) | target[3];
    result = (result << 8) | target[2];

    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit() {
    uint8_t* target = (uint8_t*) this;

    uint32_t result;

    result = target[6] & 0xF;
    result = (result << 8) | target[1];
    result = (result << 8) | target[0];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;   

    return result;
}