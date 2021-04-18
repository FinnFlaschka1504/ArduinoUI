#include "Helper/IncludeAll.h"

void Component::focus() {
    // router.currentPageHolder->page->currentFocus = this;
    focused = true;
    if (onFocus)
        onFocus(this);
}

void Component::blur()
{
    InputManager::focusOnInput = nullptr;
    focused = false;
    if (onBlur)
        onBlur(this);
}