#include <FastLED.h>
#include "effects.h"

class Cylon : public Effect
{
public:
    Cylon(CRGBSet& leds);
    virtual void vloop();
private:
    bool up;
    int i;
    void fadeall();
};
