#include <Helper/IncludeAll.h>

UI ui;

PageHolder manuelControlPageHolder(
    ManuelControlPageId,
    []() -> Page * {
      InputManager::rotated = false;
      ManuelControlState *state = (ManuelControlState *)ui.getCurrentState();

      state->reRenderTaskId = taskManager.scheduleFixedRate(500, []() {
        // ((ManuelControlState *)ui.getCurrentState())->analogHorizontal =
        //     analogRead(JOYSTICK_HORIZONTAL);
        UI::reRender();
      });
      state->slideSpeed = 0;
      MH::resetSpeed();
      MH::resetMaxSpeed();
      MH::motorControlMode = SPEED;

      if (G::buildUp == HEAD_SHOULDERS) {
        InputManager::customRawInput = [](byte pin, bool release, bool longPress, int change) {
          ManuelControlState *state = (ManuelControlState *)ui.getCurrentState();
          switch (pin)
          {
          case ROTARY_LCD_LEFT:
            if (state->slideSpeed > -20)
              state->slideSpeed--;
            break;
          case ROTARY_LCD_RIGHT:
            if (state->slideSpeed < 20)
              state->slideSpeed++;
            break;
          case BUTTON_LCD_ROTARY:
            if (release)
            {
              state->slideSpeed = 0;
            }
            break;

          default:
            return false;
          }
          MH::stepperSlide.setSpeed(state->slideSpeed * 250);
          return true;
        };
      }

      Page *page = new Page([](Page *page) {
        Caption::drawSimple(-1, 10, "Manuell");
        Label::drawSimpleD(0, 45, MH::stepperTilt.currentPosition(), "T: ", "", 6);
        Label::drawSimpleD(69, 45, MH::stepperPan.currentPosition(), "P: ", "", 6);
        if (G::buildUp == HEAD_SHOULDERS) {
          Label::drawSimpleN(45, 25, ((ManuelControlState *)ui.getCurrentState())->slideSpeed, "S:", "", 2);
          Label::drawSimpleD(0, 60, MH::stepperSlide.currentPosition(), "S: ", "", 6);
        }
      });

      page->addComponent(new NumberSelect(0, 25, &((ManuelControlState *)ui.getCurrentState())->speed, 0, 20, "T/P:"));

      // page->addComponent(new Button(90, 15, "<", [](Button *button) {
      //   MH::motorControlMode = POSITION;
// 
      //   long rounds = ((ManuelControlState *)ui.getCurrentState())->rounds;
      //   long position[] = {MH::stepperTilt.currentPosition() - 3200 * rounds, 0,
      //                      0};
      //   MH::stepperControl.moveTo(position);
      //   // MH::stepperControl.runSpeedToPosition();
// 
      //   // MH::stepperTilt.setSpeed(0);
      //   // MH::motorControlMode = SPEED;
// 
      // }));
// 
      // page->addComponent(new NumberSelect(103, 25, &((ManuelControlState *)ui.getCurrentState())->rounds, 1, 50));
// 
      // page->addComponent(new Button(120, 15, ">", [](Button *button) {
      //                  MH::motorControlMode = POSITION;
      //                  // taskManager.scheduleOnce(5000, [](){
      //                  // });
      //                  long rounds =
      //                      ((ManuelControlState *)ui.getCurrentState())->rounds;
      //                  long position[] = {MH::stepperTilt.currentPosition() +
      //                                         3200 * rounds,
      //                                     0, 0};
      //                  MH::stepperControl.moveTo(position);
// 
      //                  //  MH::stepperControl.runSpeedToPosition();
// 
      //                  // MH::stepperTilt.setSpeed(0);
      //                  // MH::motorControlMode = SPEED;
      //                }),
      //     true);

      page->applyPageTask(
          []() {
            // MH::stepperTilt.setMaxSpeed(1000);
            // long position[] = {
            //     ((ManuelControlState *)ui.getCurrentState())->speed * 10, 0,
            //     0};
            // MH::stepperControl.moveTo(position);

            if (MH::motorControlMode == POSITION)
            {
              if (MH::stepperTilt.distanceToGo() == 0)
              {
                MH::resetSpeed();
                MH::motorControlMode = SPEED;
              } else
                 return;
            }
            
            // return;
            // if (((ManuelControlState *)ui.getCurrentState())->buttonPressed) {
              // MH::stepperTilt.setSpeed(
              //     ((ManuelControlState *)ui.getCurrentState())->speed * 500);
              // ((ManuelControlState *)ui.getCurrentState())->analogHorizontal =
              //     analogRead(JOYSTICK_HORIZONTAL);

              int speed = ((ManuelControlState *)ui.getCurrentState())->speed * 250;
              int analogH = analogRead(JOYSTICK_HORIZONTAL);
              int analogV = analogRead(JOYSTICK_VERTICAL);
              int deadMin = 493;
              int deadMax = 505;

              if (analogH >= deadMin && analogH <= deadMax) {
                MH::stepperPan.setSpeed(0);
              } else {
                int mapRes;
                if (analogH < deadMin)
                  mapRes = map(analogH, 4, deadMin - 1, -speed, 0);
                else if (analogH > deadMax)
                  mapRes = map(analogH, deadMax + 1, 1023, 0, speed);
                MH::stepperPan.setSpeed(mapRes);
              }

              if (analogV >= deadMin && analogV <= deadMax) {
                MH::stepperTilt.setSpeed(0);
              } else {
                int mapRes;
                if (analogV < deadMin)
                  mapRes = map(analogV, 4, deadMin - 1, -speed, 0);
                else if (analogV > deadMax)
                  mapRes = map(analogV, deadMax + 1, 1023, 0, speed);
                MH::stepperTilt.setSpeed(mapRes);
              }

            // } else
            //   MH::stepperTilt.setSpeed(0);
          },
          [](Page *page) {
            MH::resetSpeed();
            // taskManager.cancelTask(((ManuelControlState
            // *)ui.getCurrentState())->reRenderTaskId);
            InputManager::customRawInput = nullptr;
            Serial.println("Reset RawInput");
          });

      return page;
    },
    new ManuelControlState());

MultiPager keyFrameABMultiPageHolder(
    KeyFrameABId,
    [](MultiPager *multiPager) {
      multiPager->currentPageIndicatorX = 122;
      multiPager->currentPageIndicatorY = 10;

      multiPager->addPage([]() -> Page * {
        InputManager::rotated = false;
        MH::motorControlMode = MANUELL;
        Page *page = new Page([](Page *page) {
          Caption::drawSimple(-1, 10, "Keyframe A");
          Label::drawSimpleD(0, 38, MH::stepperTilt.currentPosition(), "T: ");
          Label::drawSimpleD(72, 38, ((KayFrameABState *)UI::getCurrentState())->keyFrameA[0], "(", ")");
          Label::drawSimpleD(0, 50, MH::stepperPan.currentPosition(), "P: ");
          Label::drawSimpleD(72, 50, ((KayFrameABState *)UI::getCurrentState())->keyFrameA[1], "(", ")");
          if (G::buildUp == HEAD_SHOULDERS)
          {            
            Label::drawSimpleD(0, 62, MH::stepperSlide.currentPosition(), "S: ");
            Label::drawSimpleD(72, 62, ((KayFrameABState *)UI::getCurrentState())->keyFrameA[2], "(", ")");
          }
          
        });

        page->addComponent(new Button(0, 13, "Auswählen", [](Button *button) {
          ui.router.navigate(&manuelControlPageHolder);
        }));

        page->addComponent(new Button(
            100, 13, ">",
            [](Button *button) {
              KayFrameABState *state =
                  ((KayFrameABState *)UI::getCurrentState());
              if (!state->keyFrameASet) {
                state->keyFrameASet = true;
                state->keyFrameA[0] = MH::stepperTilt.currentPosition();
                state->keyFrameA[1] = MH::stepperPan.currentPosition();
                state->keyFrameA[2] = MH::stepperSlide.currentPosition();
}

              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            },
            [](Button *button) {
              KayFrameABState *state =
                  ((KayFrameABState *)UI::getCurrentState());
              state->keyFrameASet = true;
              state->keyFrameA[0] = MH::stepperTilt.currentPosition();
              state->keyFrameA[1] = MH::stepperPan.currentPosition();
              state->keyFrameA[2] = MH::stepperSlide.currentPosition();

              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            }));

        return page;
      });

      multiPager->addPage([]() -> Page * {
        InputManager::rotated = false;
        MH::motorControlMode = MANUELL;
        Page *page = new Page([](Page *page) {
          Caption::drawSimple(-1, 10, "Keyframe B");
          Label::drawSimpleD(0, 38, MH::stepperTilt.currentPosition(), "T: ");
          Label::drawSimpleD(72, 38, ((KayFrameABState *)UI::getCurrentState())->keyFrameB[0], "(", ")");
          Label::drawSimpleD(0, 50, MH::stepperPan.currentPosition(), "P: ");
          Label::drawSimpleD(72, 50, ((KayFrameABState *)UI::getCurrentState())->keyFrameB[1], "(", ")");
          if (G::buildUp == HEAD_SHOULDERS)
          {
            Label::drawSimpleD(0, 62, MH::stepperSlide.currentPosition(), "S: ");
            Label::drawSimpleD(72, 62, ((KayFrameABState *)UI::getCurrentState())->keyFrameB[2], "(", ")");
          }
        });

        page->addComponent(new Button(0, 13, "Auswählen", [](Button *button) {
          ui.router.navigate(&manuelControlPageHolder);
        }));

        page->addComponent(new Button(80, 13, "<", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
        }));

        page->addComponent(new Button(
            100, 13, ">",
            [](Button *button) {
              KayFrameABState *state =
                  ((KayFrameABState *)UI::getCurrentState());
              if (!state->keyFrameBSet) {
                state->keyFrameBSet = true;
                state->keyFrameB[0] = MH::stepperTilt.currentPosition();
                state->keyFrameB[1] = MH::stepperPan.currentPosition();
                state->keyFrameB[2] = MH::stepperSlide.currentPosition();
              }

              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            },
            [](Button *button) {
              KayFrameABState *state = ((KayFrameABState *)UI::getCurrentState());
              state->keyFrameBSet = true;
              state->keyFrameB[0] = MH::stepperTilt.currentPosition();
              state->keyFrameB[1] = MH::stepperPan.currentPosition();
              state->keyFrameB[2] = MH::stepperSlide.currentPosition();

              ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
            }));

        return page;
      });

      multiPager->addPage([]() -> Page * {
        InputManager::rotated = false;
        MH::motorControlMode = MANUELL;
        Page *page = new Page([](Page *page) {
          Caption::drawSimple(-1, 10, "Zeit Auswählen");
          Label::drawSimple(35, 50, "H");
          Label::drawSimple(68, 50, "M");
          Label::drawSimple(100, 50, "S");
        });

        page->addComponent(new NumberSelect(26, 50, &((KayFrameABState *)ui.getCurrentState())->hour, 0, 9));
        page->addComponent(new NumberSelect(53, 50, &((KayFrameABState *)ui.getCurrentState())->minute, 0, 60));
        page->addComponent(new NumberSelect(85, 50, &((KayFrameABState *)ui.getCurrentState())->second, 0, 60), true);

        page->addComponent(new Button(80, 18, "<", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
        }));

        page->addComponent(new Button(100, 18, ">", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
        }));

        return page;
      });

      multiPager->addPage([]() -> Page * {
        InputManager::rotated = false;
        MH::motorControlMode = MANUELL;
        Page *page = new Page([](Page *page) {
          Caption::drawSimple(-1, 10, "Zusammenfassung");
          Label::drawSimpleN(0, 24, ((KayFrameABState *)UI::getCurrentState())->getDuration(), "Zeit: ", " Sek.");
          Label::drawSimpleD(0, 37, ((KayFrameABState *)UI::getCurrentState())->keyFrameA[0], "T: ");
          Label::drawSimple(68, 40, 8594);
          Label::drawSimpleD(84, 37, ((KayFrameABState *)UI::getCurrentState())->keyFrameB[0]);
          Label::drawSimpleD(0, 50, ((KayFrameABState *)UI::getCurrentState())->keyFrameA[1], "P: ");
          Label::drawSimple(68, 53, 8594);
          Label::drawSimpleD(84, 50, ((KayFrameABState *)UI::getCurrentState())->keyFrameB[1]);
          if (G::buildUp == HEAD_SHOULDERS) {
            Label::drawSimpleD(0, 63, ((KayFrameABState *)UI::getCurrentState())->keyFrameA[2], "S: ");
            Label::drawSimple(68, 66, 8594);
            Label::drawSimpleD(84, 63, ((KayFrameABState *)UI::getCurrentState())->keyFrameB[2]);
          }
        });

        page->addComponent(new Button(109, 13, "<", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
        }));

        page->addComponent(new Button(119, 13, ">", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
        }));

        return page;
      });

      multiPager->addPage([]() -> Page * {
        InputManager::rotated = false;
        MH::motorControlMode = MANUELL;
        Page *page = new Page([](Page *page) {
          KayFrameABState* state = (KayFrameABState *)UI::getCurrentState();
          Caption::drawSimple(-1, 10, "A  B / B  A");
          ProgressBar::drawSimple(0, 50, 128, state->getTimeElapsed(), state->getDuration(), true);
          Label::drawSimple(36, 12, 8594);
          Label::drawSimple(85, 12, 8594);
          Label::drawSimple(40, 33, 8594);
          Label::drawSimple(90, 33, 8594);

        });

        page->addComponent(new Button(5, 20, "<", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
        }));

        page->addComponent(new Button(30, 20, "A  B", [](Button *button) {
          // MH::motorControlMode = POSITION;
          // MH::stepperControl.moveTo(((KayFrameABState *)UI::getCurrentState())->keyFrameB);
          KayFrameABState* state = (KayFrameABState *)UI::getCurrentState();
          MH::moveToPosition(state->keyFrameB, state->getDuration());
          state->startTime = millis();
          // state->setUpdateTask();
          if (state->updateTimeTaskId == 0)
          {
            state->updateTimeTaskId = taskManager.scheduleFixedRate(1000, []() {
              UI::reRender();
            });
          }
        }));

        page->addComponent(new Button(80, 20, "B  A", [](Button *button) {
          // MH::motorControlMode = POSITION;
          // MH::stepperControl.moveTo(((KayFrameABState *)UI::getCurrentState())->keyFrameA);
          KayFrameABState* state = (KayFrameABState *)UI::getCurrentState();
          // unsigned long mill = millis();
          // Serial.print("Time: ");
          // Serial.println(mill - state->time);
          // state->time = mill;
          MH::moveToPosition(state->keyFrameA, state->getDuration());
          state->startTime = millis();
          // state->setUpdateTask();
          if (state->updateTimeTaskId == 0)
          {
            state->updateTimeTaskId = taskManager.scheduleFixedRate(1000, []() {
              UI::reRender();
            });
          }
       }), true);

       page->beforeDestroy = [](Page *page) {
          KayFrameABState* state = (KayFrameABState *)UI::getCurrentState();
          if (state->updateTimeTaskId != 0)
          {
            taskManager.cancelTask(state->updateTimeTaskId);
            state->updateTimeTaskId = 0;
            Serial.println("Task Beendet");
          }
       };

        return page;
      });
    },
    new KayFrameABState());

PageHolder homePageHolder(
    HomePageHolderId,
    []() -> Page * {
      InputManager::rotated = false;
      Page *page = new Page(
          [](Page *page) { Caption::drawSimple(-1, 10, "Homescreen"); });
      List *list = new List(
          0, 15, &((ListTestState *)UI::getCurrentState())->listIndex,
          [](List *list, ListItem *listItem, int index) {

            if (G::buildUp == HEAD && index > 0) {
              index++;
            }

            switch (index) {
            case 0:
              ui.router.navigate(&keyFrameABMultiPageHolder);
              break;
            case 1:
              UI::showDialog = []() {
                Dialog::showSimpleDialog(3, 10, "Work In Progress",
                                         "Noch nicht fertig!", 120, 45);
              };
              break;
            case 2:
              ui.router.navigate(&manuelControlPageHolder);
              break;
            case 3:
              break;
            case 4:
              break;
            }
          });

      list->addItem("Keyframes");
      if (G::buildUp == HEAD_SHOULDERS)
        list->addItem("Pivot Point"); // ToDo: Je nach BuildUp nicht anzeigen
      list->addItem("Manuell");
      list->addItem("Import");
      list->addItem("Einstellungen");

      page->addComponent(list);

      return page;
    },
    new HomeState());

PageHolder buildUpSelectPageHolder(
    BuildUpSelectPageId,
    []() -> Page * {
      InputManager::rotated = true;
      Page *page = new Page(
          [](Page *page) { Caption::drawSimple(-1, 10, "Mode Select"); });

      page->addComponent(new Button(50, 20, "Head", [](Button *button) {
        G::buildUp = HEAD;
        ui.router.navigate(&homePageHolder);
      }));
      page->addComponent(
          new Button(15, 40, "Head & Shoulders", [](Button *button) {
            G::buildUp = HEAD_SHOULDERS;
            ui.router.navigate(&homePageHolder);
          }));
      return page;
    },
    new PageState());

PageHolder bootScreenPageHolder(BootPageId,
                                []() -> Page * {
                                  taskManager.scheduleOnce(1000, []() {
                                    ui.router.navigate(
                                        &buildUpSelectPageHolder);
                                    UI::reRender();
                                    ui.router.resetStack();
                                  });

                                  Page *page = new Page([](Page *page) {
                                    Caption::drawSimple(40, 40, "slug.",
                                                        u8g2_font_lubBI14_tr);
                                  });

                                  // page->applyPageTask([]() {
                                  //   MH::stepperTilt.setMaxSpeed(5000);
                                  //   MH::stepperTilt.setSpeed(0);
                                  //   // MH::stepperTilt.runSpeed();
                                  // });

                                  return page;
                                },
                                new PageState());

// ----------------------------------

MultiPager multiPagerTestHolder(
    MultiPagerTestId,
    [](MultiPager *multiPager) {
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 10, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c1));

        page->addComponent(new Button(70, 18, "Weiter", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
        }));

        return page;
      });
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 10, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c2));

        page->addComponent(new Button(0, 18, "Zurück", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
        }));

        page->addComponent(new Button(70, 18, "Weiter", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
        }));
        return page;
      });
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 10, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c3));

        page->addComponent(new Button(0, 18, "Zurück", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->previousPage();
        }));

        page->addComponent(new Button(70, 18, "Weiter", [](Button *button) {
          ((MultiPager *)UI::getCurrentPageHolder())->nextPage();
        }));

        return page;
      });
      multiPager->addPage([]() -> Page * {
        Page *page = new Page(
            [](Page *page) { Caption::drawSimple(0, 10, "MultiPager Test"); });

        page->addComponent(new NumberSelect(
            50, 50, &((MultiPageTestState *)UI::getCurrentState())->c4));

        page->addComponent(new Button(0, 18, "Zurück", [](Button *button) {
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
        Caption::drawSimple(0, 10, "Progress Test");
        ProgressBar::drawSimple(
            0, 28, 64, ((ProgressTestState *)UI::getCurrentState())->progress,
            10, true);
        Label::drawSimpleN(
            0, 60, ((ProgressTestState *)UI::getCurrentState())->progress - 5,
            "Speed: ", " rpm", 2, " ");
      });

      NumberSelect *numberSelect = new NumberSelect(
          0, 45, &((ProgressTestState *)UI::getCurrentState())->progress);
      // numberSelect->stepSize = 10;
      numberSelect->setBounds(0, 10);
      page->addComponent(numberSelect);

      return (Page *)page;
    },
    new ProgressTestState());

PageHolder buttonTestPageHolder(
    ButtonTestId,
    []() -> Page * {
      Page *page = new Page(
          [](Page *page) { Caption::drawSimple(0, 10, "Button Test"); });

      page->addComponent(new Button(0, 18, "Test", [](Button *button) {
        Serial1.println("Button 1 Click");
      }));

      page->addComponent(new Button(50, 18, "Test2", [](Button *button) {
        Serial1.println("Button 2 Click");
      }));

      page->addComponent(new Button(0, 40, "Test3", [](Button *button) {
        Serial1.println("Button 3 Click");
      }));

      page->addComponent(new ToggleButton(
          50, 40, "AÄgöh3f1",
          &((ButtonTestState *)ui.getCurrentState())->toggled1,
          [](Button *button) { Serial1.println("Button 4 Click"); }));

      return page;
    },
    new ButtonTestState());

PageHolder varTestPageHolder(
    VarTestId,
    []() -> Page * {
      Page *page = new Page([](Page *page) {
        Caption::drawSimple(0, 10, "Variablen Test");
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
          [](Page *page) { Caption::drawSimple(0, 10, "Listen Test"); });
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
                     case 4:
                       UI::showDialog = []() {
                         Dialog::showSimpleDialog(10, 10, "Test Dialog 1",
                                                  "Nur ein Test", 100, 45);
                       };
                       break;
                     case 5:
                       //  UI::lcd.setPowerSave(1);
                       UI::showDialog = []() {
                         Dialog::showSimpleDialog(10, 10, "Test Dialog 2",
                                                  "Noch ein Test", 100, 45);
                       };
                       break;
                     }
                   });
      list->addItem("Multi Pager");
      list->addItem("Button Test");
      list->addItem("Variablen Test");
      list->addItem("Progress Test");
      list->addItem("Dialog Test 1");
      list->addItem("Dialog Test 2");

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

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  printFreeMemory("Before Setup: ");

  pinMode(JOYSTICK_HORIZONTAL, INPUT);
  pinMode(JOYSTICK_VERTICAL, INPUT);
  pinMode(STEPPER_TILT_ENABLE, OUTPUT);
  pinMode(STEPPER_SLIDE_ENABLE, OUTPUT);
  pinMode(STEPPER_PAN_ENABLE, OUTPUT);
  digitalWrite(STEPPER_TILT_ENABLE, LOW);
  digitalWrite(STEPPER_SLIDE_ENABLE, LOW);
  digitalWrite(STEPPER_PAN_ENABLE, LOW);

  // if (true)
  // return;

  switches.initialise(ioUsingArduino(), true);
  ui.lcd.begin();
  ui.lcd.enableUTF8Print();

  InputManager::addButton(BUTTON_U);
  InputManager::addButton(BUTTON_R);
  InputManager::addButton(BUTTON_D);
  InputManager::addButton(BUTTON_L);
  InputManager::addButton(BUTTON_LCD_ROTARY);
  InputManager::addButton(BUTTON_LCD_STOP);
  RotaryHelper::attach(ROTARY_LCD_RIGHT, ROTARY_LCD_LEFT);

  InputManager::defaultOnInput = [](byte pin, bool longPress, int change) {
    if (InputManager::rotated) {
      switch (pin) {
      case BUTTON_LCD_STOP:
        ui.router.back();
        break;
      case BUTTON_L:
        // if (longPress || !ui.getCurrentPage()->canChangeFocus())
        // {
        Serial1.println("Navigate Back");
        ui.router.back();
        // }
        break;
      case ROTARY_LCD_LEFT:
      case BUTTON_U:
        ui.getCurrentPage()->focusPrevious();
        break;
      case BUTTON_LCD_ROTARY:
      case ROTARY_LCD_RIGHT:
      case BUTTON_D:
        ui.getCurrentPage()->focusNext();
        break;
      default:
        return false;
        break;
      }
    } else {

      switch (pin) {
      case BUTTON_LCD_STOP:
        ui.router.back();
        break;
      case ROTARY_LCD_LEFT:
      case BUTTON_L:
        if (longPress || !ui.getCurrentPage()->canChangeFocus()) {
          Serial1.println("Navigate Back");
          ui.router.back();
        } else
          ui.getCurrentPage()->focusPrevious();
        break;
      case BUTTON_LCD_ROTARY:
      case ROTARY_LCD_RIGHT:
      case BUTTON_R:
        ui.getCurrentPage()->focusNext();
        break;
      default:
        return false;
        break;
      }
    }
    return true;
  };

  UI::interlacedInRender = [](Page *page) { taskManager.runLoop(); };

  MH::init();
  // MH::stepperTilt.setCurrentPosition(1234567);
  // MH::stepperPan.setCurrentPosition(1234567);
  // MH::stepperSlide.setCurrentPosition(1234567);
  digitalWrite(STEPPER_TILT_STEP, LOW);
  digitalWrite(STEPPER_PAN_STEP, LOW);
  digitalWrite(STEPPER_SLIDE_STEP, LOW);
  ui.router.init(&bootScreenPageHolder);
  // ui.router.init(&manuelControlPageHolder);

  printFreeMemory("After Setup: ");
}

/*
  • Voll: 32°
  • Max: 9°
  • PS4: 21°
*/

void loop() {
  // if (counter != lastCounter) {
  //   lastCounter = counter;
  //   Serial1.println(lastCounter);
  // }

  // Serial.println(analogRead(BUTTON_U));
  // Serial.println(analogRead(BUTTON_R));
  // Serial.println(analogRead(BUTTON_D));
  // Serial.println(analogRead(BUTTON_L));
  // Serial.println();
  // delay(200);
  // Serial.print("H:");
  // Serial.println(analogRead(JOYSTICK_HORIZONTAL));
  // Serial.print("V:");
  // Serial.println(analogRead(JOYSTICK_VERTICAL));
  // Serial.println();
  // delay(200);
  // return;

  // InputManager::checkButtons();

  // Serial.println();
  // delay(500);
  // if (true)
  //   return;

  taskManager.runLoop();
  Tasker::runTasks();

  if (ui.shouldRender()) {
    // renderInline = !renderInline;
    // Serial.println(renderInline);
    ui.pendingRender = false;
    ui.lcd.firstPage();
    do {
      // if (renderInline)
      // Tasker::runTasks();
      ui.render();
      taskManager.runLoop();
    } while (ui.lcd.nextPage());
  }
}