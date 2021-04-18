#include "Helper/IncludeAll.h"

MultiPager::MultiPager(PageId pageId, AddPages *addPages, PageState *state)
    : PageHolder(pageId, nullptr, state) {
  //   va_list args;
  //   va_start(args, generatePage);
  //
  //   Serial.println("result init");
  //   String result = "";
  //
  //   for (GeneratePage *strArg = nullptr; strArg != NULL; strArg =
  //   va_arg(args, GeneratePage *)) {
  //
  //   }
  addPages(this);
  generatePage = generatePageArr[0];
}

void MultiPager::addPage(GeneratePage *generatePage) {
  generatePageArr[generatePageCount] = generatePage;
  // stateArr[generatePageCount] = state;
  generatePageCount++;
};

void MultiPager::nextPage() {
  Serial1.println("Next Page");
  if (currentPageIndex < generatePageCount - 1) {
    generatePage = generatePageArr[currentPageIndex + 1];
    focusArr[currentPageIndex] = state->focusIndex;
    state->focusIndex = focusArr[currentPageIndex + 1];
    // state = stateArr[currentPageIndex + 1];
    currentPageIndex++;
    UI::router.reloadPage();
  }
};

void MultiPager::previousPage() {
  Serial1.println("Previous Page");
  if (currentPageIndex > 0) {
    generatePage = generatePageArr[currentPageIndex - 1];
    // state = stateArr[currentPageIndex - 1];
    focusArr[currentPageIndex] = state->focusIndex;
    state->focusIndex = focusArr[currentPageIndex - 1];
    currentPageIndex--;
    UI::router.reloadPage();
  }
};

void MultiPager::render() {
  PageHolder::render();
  char buf[5];
  sprintf(buf, "%d", currentPageIndex + 1);
  Caption::drawSimple(0, 64, buf);
};
