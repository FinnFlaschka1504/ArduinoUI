
typedef void(PageCallback)(Page *page);

class Page : public UI {
public:
  byte componentCount = 0;
  Component *currentFocus = nullptr;
  Component *components[5];
  PageCallback *drawPageComponents = nullptr;
  PageCallback *beforeDestroy = nullptr;
  RunTask pageTask = nullptr;
  Page(){};
  Page(PageCallback *drawPageComponents)
      : drawPageComponents(drawPageComponents){};
  void render();
  void draw();
  void addComponent(Component *component, bool defaultFocus = false);
  void destroy();
  bool canChangeFocus();
  byte getCurrentFocusIndex(bool lazy = true);
  void focusNext();
  void focusPrevious();
};

// eventuell buildPage Callback implementieren

// -------------------------------------------------------

class ProgressTestPage : public Page {
public:
  ProgressTestPage(){};
  ProgressTestPage(PageCallback *drawPageComponents) : Page(drawPageComponents) {
    pageTask = []() {
      G::stepperTilt.setMaxSpeed(2000);
      G::stepperTilt.setSpeed((((ProgressTestState *)UI::getCurrentState())->progress - 5) * 2);
      G::stepperTilt.runSpeed();
    };
    Tasker::bindPageTask(this);
  };
};