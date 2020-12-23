#include <FastLED.h>
#include "effects.h"

class Pacific : public Effect
{
public:
    Pacific(CRGBSet& leds);

    // Increment the four "color index start" counters, one for each wave layer.
    // Each is incremented at a different speed, and the speeds vary over time.
    virtual void vloop();
    // Add one layer of waves into the led array
    void one_layer(CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff);
    // Add extra 'white' to areas where the four layers of light have lined up brightly
    void add_whitecaps();
    // Deepen the blues and greens
    void deepen_colors();
};
