#include <FastLED.h>
#include "effects.h"

// Overall twinkle speed.
// 0 (VERY slow) to 8 (VERY fast).
// 4, 5, and 6 are recommended, default is 4.
#define TWINKLE_SPEED 4

// Overall twinkle density.
// 0 (NONE lit) to 8 (ALL lit at once).
// Default is 5.
#define TWINKLE_DENSITY 6

// How often to change color palettes.
#define SECONDS_PER_PALETTE  10
// Also: toward the bottom of the file is an array
// called "ActivePaletteList" which controls which color
// palettes are used; you can add or remove color palettes
// from there freely.

// Background color for 'unlit' pixels
// Can be set to CRGB::Black if desired.
static CRGB gBackgroundColor = CRGB::Black;
// Example of dim incandescent fairy light background color
// CRGB gBackgroundColor = CRGB(CRGB::FairyLight).nscale8_video(16);

// If AUTO_SELECT_BACKGROUND_COLOR is set to 1,
// then for any palette where the first two entries
// are the same, a dimmed version of that color will
// automatically be used as the background color.
#define AUTO_SELECT_BACKGROUND_COLOR 0

// If COOL_LIKE_INCANDESCENT is set to 1, colors will
// fade out slighted 'reddened', similar to how
// incandescent bulbs change color as they get dim down.
#define COOL_LIKE_INCANDESCENT 1

class Twinkle : public Effect
{
public:
    Twinkle(CRGBSet& leds);

    //  This function loops over each pixel, calculates the
    //  adjusted 'clock' that this pixel should use, and calls
    //  "CalculateOneTwinkle" on each pixel.  It then displays
    //  either the twinkle color of the background color,
    //  whichever is brighter.
    virtual void vloop();
    //  This function takes a time in pseudo-milliseconds,
    //  figures out brightness = f( time ), and also hue = f( time )
    //  The 'low digits' of the millisecond time are used as
    //  input to the brightness wave function.
    //  The 'high digits' are used to select a color, so that the color
    //  does not change over the course of the fade-in, fade-out
    //  of one cycle of the brightness wave function.
    //  The 'high digits' are also used to determine whether this pixel
    //  should light at all during this cycle, based on the TWINKLE_DENSITY.
    CRGB computeOneTwinkle(uint32_t ms, uint8_t salt);
    // This function is like 'triwave8', which produces a
    // symmetrical up-and-down triangle sawtooth waveform, except that this
    // function produces a triangle wave with a faster attack and a slower decay:
    //
    //     / \
    //    /     \
    //   /         \
    //  /             \
    //
    uint8_t attackDecayWave8(uint8_t i);
    // This function takes a pixel, and if its in the 'fading down'
    // part of the cycle, it adjusts the color a little bit like the
    // way that incandescent bulbs fade toward 'red' as they dim.
    void coolLikeIncandescent(CRGB& c, uint8_t phase);
    // Advance to the next color palette in the list (above).
    void chooseNextColorPalette(CRGBPalette16& pal);

};