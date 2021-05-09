class CustomStepper;

enum MOTOR_CONTROL_MODE {
    SPEED, POSITION, MANUELL
};

class MH {
    public:
    static CustomStepper stepperSlide; // (Type:driver, STEP, DIR)
    static CustomStepper stepperPan; // (Type:driver, STEP, DIR)
    static CustomStepper stepperTilt; // (Type:driver, STEP, DIR)
    static MultiStepper stepperControl;
    static MOTOR_CONTROL_MODE motorControlMode; // mit methode setzen um max speed zurücksetzen
    static void init();
    static void initTimer();
    static void moveToPosition(long position[3], int time);
    static void resetSpeed();
    static void resetMaxSpeed();
};

// -----------------------

class CustomStepper : public AccelStepper {
public:
    CustomStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3) : AccelStepper(interface, pin1, pin2) {};
    void performStep();
};