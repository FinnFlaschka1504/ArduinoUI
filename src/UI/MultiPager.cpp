#include "Helper/IncludeAll.h"

MultiPager::MultiPager(PageId pageId, AddPages *addPages, PageState *state)
    : PageHolder(pageId, nullptr, state) {
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
  Caption::drawSimple(currentPageIndicatorX, currentPageIndicatorY, buf);
};
