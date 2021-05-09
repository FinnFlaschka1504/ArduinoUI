class MultiPager;

typedef void (AddPages)(MultiPager *multiPager);

class MultiPager : public PageHolder {
  // generate Page austauschbar
  // in render statusanzeige hinzufügen
public:
  byte currentPageIndex = 0;
  byte generatePageCount = 0;
  byte currentPageIndicatorX = 0;
  byte currentPageIndicatorY = 64;
  GeneratePage *generatePageArr[5] = {nullptr, nullptr, nullptr, nullptr,
                                      nullptr};
  int focusArr[5] = {-1, -1, -1, -1, -1};
  MultiPager(PageId pageId, AddPages *addPages, PageState *state);
  void render() override;
  void addPage(GeneratePage *generatePage);
  void nextPage();
  void previousPage();
};