#include <EEPROM.h>
#include "memory.h"

bool Memory::bStarted = false;

Memory::Memory()
{
    Memory::begin();
}

Memory::~Memory()
{
    Memory::end();
}

void Memory::begin()
{
    if(!bStarted)
    {
        EEPROM.begin(512);
        bStarted = true;
    }
}

void Memory::end()
{
    if(bStarted)
    {
        EEPROM.end();
    }
}

int32_t Memory::readInt(Param p)
{
    Memory::begin();
    return EEPROM.readInt(static_cast<int>(p));
}

String Memory::readString(Param p)
{
    Memory::begin();
    return EEPROM.readString(static_cast<int>(p));
}

void Memory::saveInt(Param p, int32_t i)
{
    Memory::begin();
    EEPROM.writeInt(static_cast<int>(p), i);
    EEPROM.commit();
}

void Memory::saveString(Param p, String& str)
{
    Memory::begin();
    EEPROM.writeString(static_cast<int>(p), str);
    EEPROM.commit();
}