#include <FastLED.h>
#include "effects.h"

class Pride : public Effect
{
public:
    Pride(CRGBSet& leds);

    // This function draws rainbows with an ever-changing,
    // widely-varying set of parameters.
    virtual void vloop();
};