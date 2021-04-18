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
  void reloadPage();
  void back();
  void render();
};

// --------------------------------------

enum PageId {
  ListTestId, VarTestId, ButtonTestId, ProgressTestId, MultiPagerTestId
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