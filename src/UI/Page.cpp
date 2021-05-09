#include <Helper/IncludeAll.h>

Component Page::*components[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};

void Page::render() {
  for (int i = 0; i < componentCount; i++) {
    if (UI::interlacedInRender)
      UI::interlacedInRender(this);

    components[i]->draw();
  }
  draw();
}

void Page::draw() {
  if (drawPageComponents)
    drawPageComponents(this);
}

void Page::addComponent(Component *component, bool defaultFocus = false) {
  if (getCurrentState()->focusIndex != -1) {
    if (getCurrentState()->focusIndex == componentCount) {
      component->focus();
      currentFocus = component;
    }
  } else if (!currentFocus || defaultFocus) {
    if (currentFocus)
    {
      currentFocus->blur();
    }
    
    component->focus();
    currentFocus = component;
  }

  components[componentCount] = component;
  componentCount++;
}

void Page::destroy() {
  if (beforeDestroy)
    beforeDestroy(this);

  InputManager::focusOnInput = nullptr;

  for (int i = 0; i < componentCount; i++) {
    components[i]->blur();
    delete components[i];
    components[i] = nullptr;
  }
  componentCount = 0;
}

bool Page::canChangeFocus() { return componentCount > 1; };

byte Page::getCurrentFocusIndex(bool lazy = true) {
  if (lazy && getCurrentState()->focusIndex != -1)
    return getCurrentState()->focusIndex;
  if (!currentFocus)
    return -1;
  for (byte i = 0; i < componentCount; i++) {
    if (components[i] == currentFocus)
      return i;
  }
};

void Page::focusNext() {
  byte current = getCurrentFocusIndex();

  if (current == -1)
    return;
  else if (current < componentCount - 1) {
    Component *newFocus = components[current + 1];
    currentFocus->blur();
    currentFocus = newFocus;
    getCurrentState()->focusIndex = current + 1;
    newFocus->focus();
  } else if (current == componentCount - 1) {
    Component *newFocus = components[0];
    currentFocus->blur();
    currentFocus = newFocus;
    getCurrentState()->focusIndex = 0;
    newFocus->focus();
  }
};

void Page::focusPrevious() {
  byte current = getCurrentFocusIndex();

  if (current == -1)
    return;
  else if (current > 0) {
    Component *newFocus = components[current - 1];
    currentFocus->blur();
    currentFocus = newFocus;
    getCurrentState()->focusIndex = current - 1;
    newFocus->focus();
  } else if (current == 0) {
    Component *newFocus = components[componentCount - 1];
    currentFocus->blur();
    currentFocus = newFocus;
    getCurrentState()->focusIndex = componentCount - 1;
    newFocus->focus();
  }
};

void Page::applyPageTask(RunTask pageTask, PageCallback *cleanup = nullptr){
  this->pageTask = pageTask;
  this->cleanup = cleanup;
  Tasker::bindPageTask(this);
};
