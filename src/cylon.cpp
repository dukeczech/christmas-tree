#include "cylon.h"

Cylon::Cylon(CRGBSet& leds) : Effect(leds)
{
    up = true;
    i = 0;
}

void Cylon::vloop()
{
    static uint8_t hue = 0;

    // First slide the led in one direction
    //for(int i = 0; i < this->len; i++)
    if(up)
    {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        this->fadeall();
        // Wait a little bit before we loop around and do it again
        delay(2);
        i++;
        if(i >= this->len)
        {
            up = false;
            i = this->len;
        }
    }

    // Now go in the other direction.
    //for(int i = (NUM_LEDS) - 1; i >= 0; i--)
    if(!up)
    {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        this->fadeall();
        // Wait a little bit before we loop around and do it again
        delay(2);
        i--;
        if(i < 0)
        {
            up = true;
            i = 0;
        }
    }
}

void Cylon::fadeall()
{
    for(int i = 0; i < this->len; i++)
    {
        leds[i].nscale8(250);
    }
}
