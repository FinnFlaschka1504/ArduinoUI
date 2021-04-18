#include <Helper/IncludeAll.h>

UI ui;

MultiPager multiPagerTestHolder(
    MultiPagerTestId,
    [](MultiPager *multiPager) {
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 13, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c1));

        page->addComponent(
            new Button(70, 18, "Weiter", 38, 14, [](Button *button) {
              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            }));

        return page;
      });
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 13, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c2));

        page->addComponent(
            new Button(0, 18, "Zurueck", 44, 14, [](Button *button) {
              ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
            }));

        page->addComponent(
            new Button(70, 18, "Weiter", 38, 14, [](Button *button) {
              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            }));
        return page;
      });
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 13, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c3));

        page->addComponent(
            new Button(0, 18, "Zurueck", 44, 14, [](Button *button) {
              ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
            }));

        page->addComponent(
            new Button(70, 18, "Weiter", 38, 14, [](Button *button) {
              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            }));

        return page;
      });
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 13, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c4));

        page->addComponent(
            new Button(0, 18, "Zurueck", 44, 14, [](Button *button) {
              ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
            }));

        return page;
      });
    },
    new MultiPageTestState());

PageHolder ProgressTestPageHolder(
    ProgressTestId,
    []() -> Page * {
      ProgressTestPage *page = new ProgressTestPage([](Page *page) {
        Caption::drawSimple(0, 13, "Progress Test");
        ProgressBar::drawSimple(
            0, 28, 64, ((ProgressTestState *)UI::getCurrentState())->progress,
            10, true);
        Label::drawSimple(
            0, 60, ((ProgressTestState *)UI::getCurrentState())->progress - 5,
            "Speed: ", " rpm", 2, " ");
      });

      NumberSelect *numberSelect = new NumberSelect(
          0, 45, &((ProgressTestState *)UI::getCurrentState())->progress);
      // numberSelect->stepSize = 10;
      numberSelect->setBounds(0, 10);
      numberSelect->loop = true;
      page->addComponent(numberSelect);

      return (Page *)page;
    },
    new ProgressTestState());

PageHolder buttonTestPageHolder(
    ButtonTestId,
    []() -> Page * {
      Page *page = new Page(
          [](Page *page) { Caption::drawSimple(0, 13, "Button Test"); });

      Button *button1 = new Button(0, 18, 26, 14, [](Button *button) {
        Serial1.println("Button 1 Click");
      });
      button1->label = "Test";

      Button *button2 = new Button(50, 18, 32, 14, [](Button *button) {
        Serial1.println("Button 2 Click");
      });
      button2->label = "Test2";

      Button *button3 = new Button(0, 35, 32, 14, [](Button *button) {
        Serial1.println("Button 3 Click");
      });
      button3->label = "Test3";

      page->addComponent(button1);
      page->addComponent(button2);
      page->addComponent(button3);

      return page;
    },
    new PageState());

PageHolder varTestPageHolder(
    VarTestId,
    []() -> Page * {
      Page *page = new Page([](Page *page) {
        Caption::drawSimple(0, 13, "Variablen Test");
        Label::drawSimple(0, 25, "Variable:");
      });

      VarTestState *state = (VarTestState *)UI::getCurrentState();

      NumberSelect *numberSelect1 = new NumberSelect(55, 25, &state->var1);
      NumberSelect *numberSelect2 = new NumberSelect(76, 25, &state->var2);
      numberSelect1->allowNegative = true;
      numberSelect2->allowNegative = true;
      page->addComponent(numberSelect1);
      page->addComponent(numberSelect2);

      List *list =
          new List(0, 30, &((VarTestState *)UI::getCurrentState())->listIndex,
                   [](List *list, ListItem *listItem, int index) {
                     Serial1.print("List Item: ");
                     Serial1.println(index);
                   });
      list->addItem("Item 1");
      list->addItem("Item 2");

      page->addComponent(list);

      printFreeMemory("In generate VarTestPage: ");

      return page;
    },
    new VarTestState());

PageHolder listTestPageHolder(
    ListTestId,
    []() -> Page * {
      Page *page = new Page(
          [](Page *page) { Caption::drawSimple(0, 13, "Listen Test"); });
      List *list =
          new List(0, 18, &((ListTestState *)UI::getCurrentState())->listIndex,
                   [](List *list, ListItem *listItem, int index) {
                     switch (index) {
                     case 0:
                       ui.router.navigate(&multiPagerTestHolder);
                       break;
                     case 1:
                       ui.router.navigate(&buttonTestPageHolder);
                       break;
                     case 2:
                       ui.router.navigate(&varTestPageHolder);
                       break;
                     case 3:
                       ui.router.navigate(&ProgressTestPageHolder);
                       break;
                     }
                   });
      list->addItem("Multi Pager");
      list->addItem("Button Test");
      list->addItem("Variablen Test");
      list->addItem("Progress Test");
      list->addItem("Item 5");
      list->addItem("Item 6");

      page->addComponent(list);

      PageState *pageState = ui.getOldState();
      if (pageState) {
        switch (ui.getOldPageId()) {
        case VarTestId:
          Serial1.print("VarTestPage1: ");
          Serial1.println(((VarTestState *)pageState)->var1);
          Serial1.print("VarTestPage2: ");
          Serial1.println(((VarTestState *)pageState)->var2);
          break;
        case ProgressTestId:
          Serial1.print("Progress: ");
          Serial1.println(((ProgressTestState *)pageState)->progress);
          break;
        default:
          Serial1.println("Keine Daten");
        }
      } else
        Serial1.println("Keine AltePage");

      return page;
    },
    new ListTestState());

// ------------------------------------------------

void onInterrupt(){
    // Serial1.print("Pin A: ");
    // Serial1.println(digitalRead(INTERRUPT_PIN_A) == LOW ? "LOW" : "HIGH");
    // Serial1.print("Pin B: ");
    // Serial1.println(digitalRead(INTERRUPT_PIN_B) == LOW ? "LOW" : "HIGH");
};

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  printFreeMemory("Before Setup: ");

  // if (true)
  //   return;

  switches.initialise(ioUsingArduino(), true);
  ui.lcd.begin();

  // InputManager::addButton(BUTTON_U);
  InputManager::addAnalogButton(BUTTON_U);
  InputManager::addButton(BUTTON_R);
  InputManager::addButton(BUTTON_D);
  InputManager::addButton(BUTTON_L);
  InputManager::addButton(BUTTON_LCD_ROTARY);
  RotaryHelper::attach(ROTARY_LCD_RIGHT, ROTARY_LCD_LEFT);

  InputManager::defaultOnInput = [](byte pin, bool longPress, int change) {
    switch (pin) {
    case ROTARY_LCD_LEFT:
    case BUTTON_L:
      if (longPress || !ui.getCurrentPage()->canChangeFocus()) {
        Serial1.println("Navigate Back");
        ui.router.back();
      } else
        ui.getCurrentPage()->focusPrevious();
      break;
    case ROTARY_LCD_RIGHT:
    case BUTTON_R:
      ui.getCurrentPage()->focusNext();
      break;
    default:
      return false;
      break;
    }
    return true;
  };

  ui.router.init(&listTestPageHolder);
  // ui.router.init(&multiPagerTestHolder);

  // StepperControl.addStepper(stepperSlide);

  Tasker::addTask([]() {
    G::stepperSlide.setMaxSpeed(2000);
    G::stepperSlide.setSpeed(10);
    G::stepperSlide.runSpeed();
    G::stepperPan.setMaxSpeed(2000);
    G::stepperPan.setSpeed(-10);
    G::stepperPan.runSpeed();
    // stepperTilt.setMaxSpeed(2000);
    // stepperTilt.setSpeed(20);
    // stepperTilt.runSpeed();
    // Serial1.println("Task");
  });

  printFreeMemory("After Setup: ");
}

void loop() {
  // if (counter != lastCounter) {
  //   lastCounter = counter;
  //   Serial1.println(lastCounter);
  // }

  // if (true)
  //   return;
  InputManager::checkButtons();

  taskManager.runLoop();
  Tasker::runTasks();

  if (ui.shouldRender()) {
    ui.lcd.firstPage();
    do {
      // rotaryHelper.check();
      ui.render();
    } while (ui.lcd.nextPage());
    ui.pendingRender = false;
  }
}