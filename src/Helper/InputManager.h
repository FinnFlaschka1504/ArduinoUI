typedef bool (OnInput)(byte pin, bool longPress, int change);
typedef bool (RawInput)(byte pin, bool release, bool longPress, int change);
class AnalogButtonHelper;

class InputManager
{
public:
    static bool rotated;
    static OnInput* defaultOnInput;
    static OnInput* focusOnInput;
    static OnInput* customOnInput;
    static RawInput* focusRawInput;
    static RawInput* customRawInput;
    static byte analogButtonCount;
    static AnalogButtonHelper *analogButtons[5];
    static void addAnalogButton(uint8_t pin);
    static void addButton(byte pin);
    static void checkButtons();
    static bool dispatchRawInput(byte pin, bool release, bool longPress, int change);
    static void dispatchOnInput(byte pin, bool longPress, int change);
};

// ---------------------------------

class RotaryHelper
{
    public:
    static byte pinA;
    static byte pinB;
    static unsigned long lastClicked;
    static void attach(byte pinA, byte pinB);
};

class AnalogButtonHelper {
public:
    uint8_t pin = 0;
    bool pressed = false;
    bool longPressed = false;
    static unsigned long lastChecked;
    unsigned long lastClicked = 0;
    AnalogButtonHelper(uint8_t pin);
    void check();
};