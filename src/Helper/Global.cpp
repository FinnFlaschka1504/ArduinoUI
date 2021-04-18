#include "IncludeAll.h"

AccelStepper G::stepperSlide(1, STEPPER_SLIDE_STEP,
                         STEPPER_SLIDE_DIR); // (Type:driver, STEP, DIR)
AccelStepper G::stepperPan(1, STEPPER_PAN_STEP,
                                STEPPER_PAN_DIR); // (Type:driver, STEP, DIR)
AccelStepper G::stepperTilt(1, STEPPER_TILT_STEP,
                                 STEPPER_TILT_DIR); // (Type:driver, STEP, DIR)
