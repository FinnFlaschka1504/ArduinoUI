#include <Helper/IncludeAll.h>

// U8G2_ST7920_128X64_1_SW_SPI UI::lcd(U8G2_R0, 23 /*clock*/, 17 /*data*/,
// 16/*cs*/);
U8G2_KS0108_128X64_1 UI::lcd(U8G2_R0, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
                             40, 41, 42, 43);

// InputManager UI::inputManager;

Router UI::router;

InterlacedInRender UI::interlacedInRender = nullptr;

bool UI::pendingRender = true;
bool UI::suspendRender = false;
bool UI::permanentRender = false;

void UI::render() { router.render(); }

Component *UI::getCurrentFocus() {
  return router.currentPageHolder->page->currentFocus;
}

Page *UI::getCurrentPage() { return router.currentPageHolder->page; }

Page *UI::getOldPage() { return router.oldPageHolder->page; }

PageState *UI::getOldState() { return router.oldPageHolder->state; }

PageState *UI::getCurrentState() { return router.currentPageHolder->state; }

PageHolder *UI::getOldPageHolder() { return router.oldPageHolder; }

PageHolder *UI::getCurrentPageHolder() { return router.currentPageHolder; }

PageId UI::getOldPageId() { return router.oldPageHolder->pageId; };

PageId UI::getCurrentPageId() { return router.currentPageHolder->pageId; };

bool UI::shouldRender() { return pendingRender || permanentRender; }

void UI::reRender() {
  if (!suspendRender)
    pendingRender = true;
};
