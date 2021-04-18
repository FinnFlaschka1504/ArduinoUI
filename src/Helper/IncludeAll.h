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
#include "UI/UI.h"
#include "UI/Component.h"
#include "UI/Page.h"
#include "UI/Label.h"
#include "UI/List.h"
#include "UI/NumberSelect.h"
#include "UI/Button.h"
#include "UI/ProgressBar.h"
#include "UI/MultiPager.h"


#define BUTTON_EVENT 12
#define BUTTON_SECOND 11
#define BUTTON_THIRD 9
// #define BUTTON_U 7
// #define BUTTON_U 3
#define BUTTON_U A13
#define BUTTON_R 6
#define BUTTON_D 5
// #define BUTTON_D 2
#define BUTTON_L 4
#define BUTTON_LCD_ROTARY 8
#define ROTARY_LCD_RIGHT 2
#define ROTARY_LCD_LEFT 3
#define BUTTON_STOP 41

#define STEPPER_SLIDE_STEP 22
#define STEPPER_SLIDE_DIR 23
#define STEPPER_PAN_STEP 24
#define STEPPER_PAN_DIR 25
#define STEPPER_TILT_STEP 26
#define STEPPER_TILT_DIR 27

#endif 
