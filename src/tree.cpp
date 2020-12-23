#include "tree.h"

#if 0
leds[0] = CRGB::Red;
leds[40] = CRGB::Red;
leds[74] = CRGB::Red;
leds[102] = CRGB::Red;
leds[123] = CRGB::Red;
leds[138] = CRGB::Red;
leds[148] = CRGB::Red;

leds[36] = CRGB::Green;
leds[71] = CRGB::Green;
leds[100] = CRGB::Green;
leds[121] = CRGB::Green;
leds[137] = CRGB::Green;
leds[147] = CRGB::Green;

leds[32] = CRGB::Blue;
leds[68] = CRGB::Blue;
leds[97] = CRGB::Blue;
leds[119] = CRGB::Blue;
leds[135] = CRGB::Blue;
leds[146] = CRGB::Blue;

leds[29] = CRGB::DarkKhaki;
leds[64] = CRGB::DarkKhaki;
leds[94] = CRGB::DarkKhaki;
leds[117] = CRGB::DarkKhaki;
leds[134] = CRGB::DarkKhaki;
leds[145] = CRGB::DarkKhaki;

leds[23] = CRGB::Teal;
leds[59] = CRGB::Teal;
leds[90] = CRGB::Teal;
leds[115] = CRGB::Teal;
leds[132] = CRGB::Teal;
leds[144] = CRGB::Teal;

leds[17] = CRGB::Orange;
leds[54] = CRGB::Orange;
leds[86] = CRGB::Orange;
leds[112] = CRGB::Orange;
leds[130] = CRGB::Orange;
leds[143] = CRGB::Orange;

leds[11] = CRGB::LawnGreen;
leds[49] = CRGB::LawnGreen;
leds[82] = CRGB::LawnGreen;
leds[109] = CRGB::LawnGreen;
leds[128] = CRGB::LawnGreen;
leds[142] = CRGB::LawnGreen;

leds[5] = CRGB::PowderBlue;
leds[44] = CRGB::PowderBlue;
leds[78] = CRGB::PowderBlue;
leds[106] = CRGB::PowderBlue;
leds[126] = CRGB::PowderBlue;
leds[140] = CRGB::PowderBlue;
leds[149] = CRGB::PowderBlue;
FastLED.show();
#endif

void lines(CRGBArray<NUM_LEDS>& leds)
{
    static int lines[][7] = {
            { 0,  40, 74,  102, 123, 138, 148 },
            { 36, 71, 100, 121, 137, 147, -1 },
            { 32, 68, 97,  119, 135, 146, -1 },
            { 29, 64, 94,  117, 134, 145, -1 },
            { 23, 59, 90,  115, 132, 144, -1 },
            { 17, 54, 86,  112, 130, 143, -1 },
            { 11, 49, 82,  109, 128, 142, -1 },
            { 5,  44, 78,  106, 126, 140, 149 }
    };

    FastLED.clear();
    for(int y = 0; y < (sizeof(lines) / sizeof(*lines)); ++y)
    {
        // Get random color
        CHSV color = CHSV(random8(), 255, 255);
        for(int x = 0; x < (sizeof(*lines) / sizeof(**lines)); ++x)
        {
            if(lines[y][x] >= 0)
            {
                leds[lines[y][x]] = color; // HSV(color, saturation, brightness);
            }
        }
    }

    for(int a = 0; a < 255; a += 5)
    {
        for(int y = 0; y < (sizeof(lines) / sizeof(*lines)); ++y)
        {
            // Get random color
            CHSV color = CHSV(random8(), 255, 255);
            for(int x = 0; x < (sizeof(*lines) / sizeof(**lines)); ++x)
            {
                if(lines[y][x] >= 0)
                {
                    leds[lines[y][x]].setHue(a); // HSV(color, saturation, brightness);
                }
            }
        }
        FastLED.show();
        FastLED.delay(10);
    }

    /*for(int a = 0; a < 255; a+=5)
    {
        for( CRGB& pixel: leds) {
            //pixel.fadeLightBy(a);
            //pixel.maximizeBrightness(a);
            //pixel.addToRGB(20);
            pixel.setHue(a);
        }
        FastLED.show();
        FastLED.delay(10);
    }*/
}