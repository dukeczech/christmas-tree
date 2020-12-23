#include <typeinfo>
#include "effects.h"

Effect::Effect(CRGBSet& leds) : leds(leds), len(leds.len)
{
    this->delayTime = 0;
    this->start = 0;
    this->elapsed = 0;
    this->active = false;
}

void Effect::setup(CRGBSet& leds)
{
    this->leds = leds;
    this->len = leds.len;
}

void Effect::loop()
{
    const uint32_t st = millis();
    this->vloop();
    const uint32_t t = millis() - st;
    if(this->delayTime < t)
    {
        this->delayTime = t;
    }
}

uint32_t Effect::getSize() const
{
    return this->len;
}

String Effect::getName() const
{
#define quote(x) #x
    return String(typeid(*this).name()).substring(1);
}

uint32_t Effect::getDelay() const
{
    return this->delayTime;
}

uint32_t Effect::getElapsed() const
{
    return this->elapsed;
}

void Effect::activate()
{
    this->start = millis();
    this->active = true;
}

void Effect::deactivate()
{
    this->elapsed += millis() - this->start;
    this->active = false;
}

bool Effect::isActive() const
{
    return this->active;
}
