#include <Helper/IncludeAll.h>

void Router::init(PageHolder *rootPageHolder) {
  this->pageHolderStack[0] = rootPageHolder;
  pageHolderStackHeight = 1;
  this->currentPageHolder = rootPageHolder;
  rootPageHolder->generate();
};

void Router::render() { currentPageHolder->render(); }

void Router::navigate(PageHolder *newPageHolder) {
  oldPageHolder = currentPageHolder;
  oldPageHolder->clear();
  currentPageHolder = newPageHolder;
  newPageHolder->generate();
  delete oldPageHolder->page;
  oldPageHolder->page = nullptr;

  // wo wird das neue auf den Stack geschrieben
  // auch verhindern können, dass stack erhöht wird
  pageHolderStackHeight++;
  oldPageHolder = nullptr;

  printFreeMemory("After Navigate: ");
};

void Router::reloadPage()
{
  currentPageHolder->clear();
  delete currentPageHolder->page;
  currentPageHolder->generate();
  printFreeMemory("After Reload: ");
};


void Router::back() {
  if (pageHolderStackHeight > 1) {
    PageHolder *newPageHolder = pageHolderStack[pageHolderStackHeight - 2];
    oldPageHolder = currentPageHolder;

    oldPageHolder->clear();
    currentPageHolder = newPageHolder;
    newPageHolder->generate();
    printFreeMemory();

    delete oldPageHolder->page;
    oldPageHolder->page = nullptr;

    pageHolderStackHeight--;
    oldPageHolder = nullptr;

    printFreeMemory("After Back: ");
  }
}

// --------------------------------

// PageHolder::PageHolder(GeneratePage generatePage)
//     : generatePage(generatePage) {}

PageHolder::PageHolder(PageId pageId, GeneratePage *generatePage, PageState *state)
    : pageId(pageId), generatePage(generatePage), state(state) {}

void PageHolder::generate() {
  page = generatePage();
  UI::getCurrentState()->focusIndex = page->getCurrentFocusIndex(false);
};

void PageHolder::clear() { page->destroy(); };

void PageHolder::render()
{
  page->render();
};
