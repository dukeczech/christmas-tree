#include <vector>
#include <FastLED.h>
#include "memory.h"
#include "leds.h"
#include "cylon.h"
#include "fire.h"
#include "pride.h"
#include "pacific.h"
#include "twinkle.h"
#include "tree.h"

#if defined(ARDUINO_HELTEC_WIFI_LORA_32)

#include "SSD1306.h"
#include "network.h"
#include "ota.h"
#include "webform.h"

#endif

#define DATA_PIN 5

// Define the array of leds
CRGBArray<NUM_LEDS> leds;
// Define a vector of effects
std::vector<Effect*> effects;


#if defined(ARDUINO_HELTEC_WIFI_LORA_32)
Network wifi;
SSD1306 display(0x3c, 4, 15);
WebForm form;
#endif

Cylon c(leds);
Fire f(leds);
Twinkle t(leds);
Pride p(leds);
Pacific pp(leds);

void setup()
{
    pinMode(16, OUTPUT);

    digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
    delay(50);
    digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high、

    Serial.begin(115200);
    Serial.println("Serial init");
    while(!Serial)
    {
        Serial.print(".");
    }
    Serial.println();
    Serial.println("ESP32 test board");

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

    // FastLED.setTemperature(OvercastSky);
    //FastLED.setCorrection(TypicalLEDStrip);
    //FastLED.setDither(BRIGHTNESS < 255);

    //FastLED.setBrightness(BRIGHTNESS);

    FastLED.clear();
    FastLED.delay(500);

#if defined(ARDUINO_HELTEC_WIFI_LORA_32)
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.clear();

    wifi.init("Palmova_21a", "31415926535");

    ota_setup();

    display.drawString(0, 15, "TEST");
    display.drawString(0, 26, "IP: " + wifi.getLocalIP());
    display.display();

    form.init();
#endif

#if defined(ARDUINO_AVR_NANO)
#endif

    // Effect initialization
    effects.push_back(&c);
    //effects.push_back(&f);
    effects.push_back(&t);
    effects.push_back(&p);
    effects.push_back(&pp);

    for(Effect* e : effects)
    {
        e->setup(leds);
    }

    FastLED.showColor(0xff0000);

    delay(1500);
    Serial.println("Init OK");
}

int a = 0;

void loop()
{
    effects[a]->loop();

    FastLED.show();
    yield();

    EVERY_N_SECONDS(8)
    {
        effects[a]->deactivate();
        a++;
        if(a > effects.size())
        {
            a = 0;
        }
        effects[a]->activate();
    }


#if defined(ARDUINO_HELTEC_WIFI_LORA_32)
    ota_loop();
    form.loop();
#endif
}
