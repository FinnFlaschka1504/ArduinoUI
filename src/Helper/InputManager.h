typedef bool (OnInput)(byte pin, bool longPress, int change);
typedef bool (RawInput)(byte pin, bool release, bool longPress, int change);
class AnalogButtonHelper;

class InputManager
{
public:
    static OnInput* defaultOnInput;
    static OnInput* focusOnInput;
    static OnInput* customOnInput;
    static RawInput* rawInput;
    static byte analogButtonCount;
    static AnalogButtonHelper *analogButtons[5];
    static void addAnalogButton(uint8_t pin);
    static void addButton(byte pin);
    static void checkButtons();
    static void dispatchOnInput(byte pin, bool longPress, int change);
};

// // ---------------------------------------
// 
// class ButtonListener : public SwitchListener {
// public:    
//     void onPressed(uint8_t /*pin*/, bool held) override {
//         // Called on key press
//     }
// 
//     void onReleased(uint8_t /*pin*/, bool held) override {
//         // Called on key release
//     }
//     ButtonListener(byte pin);
// };


// ---------------------------------

class RotaryHelper
{
    public:
    static byte pinA;
    static byte pinB;
    static int lastClicked;
    static void attach(byte pinA, byte pinB);
};

class AnalogButtonHelper {
public:
    uint8_t pin = 0;
    bool pressed = false;
    unsigned long lastClicked = 0;
    AnalogButtonHelper(uint8_t pin);
    void check();
};