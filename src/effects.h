#ifndef CHRISTMAS_TREE_EFFECTS_H
#define CHRISTMAS_TREE_EFFECTS_H

#include <FastLED.h>

class Effect
{
public:
    Effect(CRGBSet& leds);
    virtual void setup(CRGBSet& leds);
    virtual void vloop() = 0;
    void loop();

    uint32_t getSize() const;
    String getName() const;
    uint32_t getDelay() const;
    uint32_t getElapsed() const;

    void activate();
    void deactivate();
    bool isActive() const;
protected:
    CRGBSet& leds;
    union
    {
        uint32_t len;
        uint32_t size;
        //int NUM_LEDS;
    };
    uint32_t delayTime;
    uint32_t start;
    uint32_t elapsed;
    bool active;
};

#endif //CHRISTMAS_TREE_EFFECTS_H
