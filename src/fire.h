#include <FastLED.h>
#include "effects.h"

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING  60

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 160

#define FRAMES_PER_SECOND 60

static bool gReverseDirection = false;

class Fire : public Effect
{
public:
    Fire(CRGBSet& leds);
    ~Fire();

    virtual void vloop();

private:
    byte* heat;
};
