class PageHolder;

typedef Page *(GeneratePage)();

class Router {
public:
  PageHolder *pageHolderStack[5];
  int pageHolderStackHeight = 0;
  PageHolder *oldPageHolder = nullptr;
  PageHolder *currentPageHolder = nullptr;
  void init(PageHolder *rootPageHolder);
  void navigate(PageHolder *newPageHolder);
  void resetStack();
  void reloadPage();
  void back();
  void render();
};

// --------------------------------------

enum PageId {
  ListTestId, VarTestId, ButtonTestId, ProgressTestId, MultiPagerTestId /**/, BootPageId, BuildUpSelectPageId, HomePageHolderId, ManuelControlPageId, KeyFrameABId
};

class PageHolder {
public:
  GeneratePage *generatePage;
  Page *page;
  PageState *state;
  PageId pageId;
  PageHolder(PageId pageId, GeneratePage *generatePage, PageState *state);
  virtual void render();
  void generate();
  void clear();
};

// -----

struct PageState {
    int focusIndex = -1;
};

struct KayFrameABState : public PageState {
  long keyFrameA[3] = {0, 0, 0};
  bool keyFrameASet = false;
  long keyFrameB[3] = {0, 0, 0};
  bool keyFrameBSet = false;
  bool aToB = false;
  int hour = 0;
  int minute = 0;
  int second = 0;
  int getDuration() {
    return ((hour * 60) + minute) * 60 + second;
  }
  unsigned long startTime = 0;
  int getTimeElapsed() {
    if (startTime == 0)
      return 0;
    unsigned long mill = millis();
    unsigned long diff = mill - startTime;
    int result = (int) (diff / 1000);
    int duration = getDuration();
    if (result >= duration && updateTimeTaskId != 0)
    {
      taskManager.cancelTask(updateTimeTaskId);
      updateTimeTaskId = 0;
      Serial.println("Auto Cancel Task");
    }
    
    return result < duration ? result : duration;
  }
  taskid_t updateTimeTaskId = 0;
  void setUpdateTask() {
    if (updateTimeTaskId == 0)
    {
      // updateTimeTaskId = taskManager.scheduleFixedRate(1000, []() {
      //   UI::reRender();
      // });
    }
  }
};

struct ManuelControlState : public PageState {
  // bool buttonPressed = true;
  int speed = 1;
  int slideSpeed = 0;
  int rounds = 1;
  taskid_t reRenderTaskId = 0;
  int analogHorizontal = 0;
};

struct HomeState : public PageState {
  byte selcctedIndex = 0;
};

struct ButtonTestState : public PageState {
  bool toggled1;
};

struct ListTestState : public PageState {
  byte listIndex;
};

struct VarTestState : public PageState {
  int var1 = 0;
  int var2 = 0;
  byte listIndex;
};

struct ProgressTestState : public PageState {
  int progress = 5;
};

struct MultiPageTestState : public PageState {
  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;
};