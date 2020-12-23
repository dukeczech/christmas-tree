#include <Arduino.h>
#include "fire.h"

Fire::Fire(CRGBSet& leds) : Effect(leds)
{
    this->heat = new byte[this->len];
}

Fire::~Fire()
{
    delete[] this->heat;
}

void Fire::vloop()
{
    // Step 1.  Cool down every cell a little
    for(int i = 0; i < this->len; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / this->len) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for(int k = this->len - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if(random8() < SPARKING)
    {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for(int j = 0; j < this->len; j++)
    {
        CRGB color = HeatColor(heat[j]);
        int pixelnumber;
        if(gReverseDirection)
        {
            pixelnumber = (this->len - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds[pixelnumber] = color;
    }

    FastLED.delay(1000 / FRAMES_PER_SECOND);
}
