#ifndef INCLUDE_ALL
#define INCLUDE_ALL DONE

#include <Arduino.h>
// #include "avr8-stub.h"
#include <KeyboardManager.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <IoAbstraction.h>
#include <TaskManagerIO.h>
#include <AccelStepper.h>
#include <MultiStepper.h>


class UI;
class Page;
class PageHolder;
class Router;
class Component;
struct PageState;
struct VarTestState;
struct ProgressTestState;

#include <Helper/MemoryFree.h>
#include "Helper/InputManager.h"
#include "Helper/Tasker.h"
#include "Helper/Global.h"
#include "Helper/Router.h"
#include "Helper/MotorHelper.h"
#include "UI/UI.h"
#include "UI/Component.h"
#include "UI/Page.h"
#include "UI/Label.h"
#include "UI/List.h"
#include "UI/NumberSelect.h"
#include "UI/Button.h"
#include "UI/ProgressBar.h"
#include "UI/MultiPager.h"
#include "UI/Dialog.h"


#define BUTTON_EVENT 12
#define BUTTON_SECOND 11
#define BUTTON_THIRD 9
// #define BUTTON_U 7
#define BUTTON_U A9
// #define BUTTON_R 6
#define BUTTON_R A11
// #define BUTTON_D 5
#define BUTTON_D A12
// #define BUTTON_L 4
#define BUTTON_L A5
// #define BUTTON_LCD_ROTARY 8
#define BUTTON_LCD_ROTARY 35
#define BEEPER_LCD 35
#define ROTARY_LCD_RIGHT 2
#define ROTARY_LCD_LEFT 3
#define BUTTON_LCD_STOP 41
#define JOYSTICK_HORIZONTAL A3
#define JOYSTICK_VERTICAL A4

#define STEPPER_SLIDE_STEP 46 // !!PIN ÜBERPRÜFEN!!
#define STEPPER_SLIDE_DIR 48 // !!PIN ÜBERPRÜFEN!!
#define STEPPER_SLIDE_ENABLE A8
#define STEPPER_PAN_STEP 36 // !!PIN ÜBERPRÜFEN!!
#define STEPPER_PAN_DIR 34 // !!PIN ÜBERPRÜFEN!!
#define STEPPER_PAN_ENABLE 30 // E1
#define STEPPER_TILT_STEP 26
#define STEPPER_TILT_DIR 28
#define STEPPER_TILT_ENABLE 24 // E0

#endif 


/*
Simulation vs. RL:
    • In UI lcd tauschen
    • Pinbelegung überprüfen
    • Sind Motoren irgendwie am laufen? 
*/