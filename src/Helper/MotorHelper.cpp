#include "Helper/IncludeAll.h"

CustomStepper MH::stepperSlide(AccelStepper::DRIVER, STEPPER_SLIDE_STEP,
                              STEPPER_SLIDE_DIR); // (Type:driver, STEP, DIR)
CustomStepper MH::stepperPan(AccelStepper::DRIVER, STEPPER_PAN_STEP,
                            STEPPER_PAN_DIR); // (Type:driver, STEP, DIR)
CustomStepper MH::stepperTilt(AccelStepper::DRIVER, STEPPER_TILT_STEP,
                             STEPPER_TILT_DIR); // (Type:driver, STEP, DIR)
MultiStepper MH::stepperControl;                // Tilt, Pan, Slide

MOTOR_CONTROL_MODE MH::motorControlMode = POSITION;

void MH::init() {
  stepperTilt.setMaxSpeed(5000);
  stepperTilt.setSpeed(0);
  stepperPan.setMaxSpeed(5000);
  stepperPan.setSpeed(0);
  stepperSlide.setMaxSpeed(5000);
  stepperSlide.setSpeed(0);
  stepperControl.addStepper(stepperTilt);
  stepperControl.addStepper(stepperPan);
  stepperControl.addStepper(stepperSlide);
//   long position[] = {100000, 0, 0};
//   stepperControl.moveTo(position);

  initTimer();
  // stepperControl.runSpeedToPosition();
};

void MH::initTimer() {
  noInterrupts(); // Interrupts ausschalten
  TCCR3A = 0;     // Timer3 initialisieren
  TCCR3B = 0;
  TCNT3 = 0;
  OCR3A = 639;    // 319; // Vergleichsregister um die Zeit einzustellen 16MHz/256/2Hz
  TCCR3B |= (1 << WGM12);                            // CTC mode
  TCCR3B |= (0 << CS12) | (0 << CS11) | (1 << CS10); // 256 prescaler
  TIMSK3 |= (1 << OCIE1A); // enable timer compare interrupt
  interrupts();            // Interrups einschalten
}

ISR(TIMER3_COMPA_vect) { // timer interrupt service routine
  // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // LED umschalten
  // MH::stepperTilt.run();
  // MH::stepperControl.runSpeedToPosition();

  switch (MH::motorControlMode) {
  case SPEED:
    MH::stepperTilt.runSpeed();
    MH::stepperPan.runSpeed();
    MH::stepperSlide.runSpeed();
    break;

  case POSITION:
    MH::stepperControl.run();
    break;
  }

  // while (MH::stepperControl.run())
  // ;
  // Tasker::runTasks();
}

void MH::moveToPosition(long position[3], int time) {
  motorControlMode = MANUELL;
  stepperControl.moveTo(position);
  long tiltTteps = stepperTilt.distanceToGo();
  float maxSpeedTilt = tiltTteps / (float) time;
  // Serial.print("Max Speed: ");
  // Serial.println(maxSpeedTilt);
  resetMaxSpeed();
  stepperTilt.setMaxSpeed(maxSpeedTilt < 5000 ? maxSpeedTilt : 5000);
  stepperControl.moveTo(position);
  motorControlMode = POSITION;
}

void MH::resetSpeed() {
  stepperTilt.setSpeed(0);
  stepperPan.setSpeed(0);
  stepperSlide.setSpeed(0);
};

void MH::resetMaxSpeed() {
  stepperTilt.setMaxSpeed(5000);
  stepperPan.setMaxSpeed(5000);
  stepperSlide.setMaxSpeed(5000);
};


// ----------------------------

void CustomStepper::performStep() {

    long currentPos = currentPosition();

	// if (_direction == DIRECTION_CW)
	// {
	//     // Clockwise
	//     setCurrentPosition(++currentPos);
	// }
	// else
	// {
	//     // Anticlockwise  
	//     setCurrentPosition(--currentPos);

	// }
	step(currentPos);
};