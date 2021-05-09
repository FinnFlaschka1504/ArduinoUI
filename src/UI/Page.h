
typedef void(PageCallback)(Page *page);

class Page : public UI {
public:
  byte componentCount = 0;
  Component *currentFocus = nullptr;
  Component *components[5];
  PageCallback *drawPageComponents = nullptr;
  PageCallback *beforeDestroy = nullptr;
  PageCallback *cleanup = nullptr;
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
  void applyPageTask(RunTask pageTask, PageCallback *cleanup = nullptr);
};

// eventuell buildPage Callback implementieren

// -------------------------------------------------------

class ProgressTestPage : public Page {
public:
  ProgressTestPage(){};
  ProgressTestPage(PageCallback *drawPageComponents) : Page(drawPageComponents) {
    pageTask = []() {
      // MH::stepperTilt.setMaxSpeed(5000);
      MH::stepperTilt.setSpeed((((ProgressTestState *)UI::getCurrentState())->progress - 5) * 1000);
      MH::stepperTilt.runSpeed();
    };
    Tasker::bindPageTask(this);
  };
};