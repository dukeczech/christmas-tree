#include <FastLED.h>
#include "config.h"

Config::Config()
{

}

int32_t Config::getBrigthness()
{
    return Memory::readInt(Memory::LED_BRIGHTNESS);
}

void Config::setBrigthness(uint32_t b)
{
    if(b >= 0 && b <= 255)
    {
        Memory::saveInt(Memory::LED_BRIGHTNESS, b);
        FastLED.setBrightness(b);
    }
}