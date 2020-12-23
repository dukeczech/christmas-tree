#include <Arduino.h>
#include "memory.h"

#define BRIGHTNESS  255

class Config
{
public:
    Config();

    static int32_t getBrigthness();
    static void setBrigthness(uint32_t b);
};