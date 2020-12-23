#include "Arduino.h"

class Memory
{
public:
    enum Param
    {
        LED_BRIGHTNESS = 1
    };

    static bool bStarted;

    Memory();
    ~Memory();

    static void begin();
    static void end();

    static int32_t readInt(Param p);
    static String readString(Param p);

    static void saveInt(Param p, int32_t i);
    static void saveString(Param p, String& str);
};
