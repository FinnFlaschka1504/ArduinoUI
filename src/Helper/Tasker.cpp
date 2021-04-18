#include "IncludeAll.h"

byte Tasker::taskCount = 0;
RunTask Tasker::tasks[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};

void Tasker::addTask(RunTask task) {
  if (taskCount >= sizeof(tasks) / 2) {
    Serial1.println("!!WARNUNG!!::TaskArray Voll");
    return;
  }

  tasks[taskCount] = task;
  taskCount++;
};

void Tasker::bindPageTask(Page *page) {
  addTask(page->pageTask);
  page->beforeDestroy = [](Page *page) { Tasker::removeTask(page->pageTask); };
};

void Tasker::removeTask(RunTask task) {
  //   byte size = sizeof(tasks) / 2;
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i] == task) {
      for (byte k = i; k < taskCount - 1; k++) {
        tasks[k] = tasks[k + 1];
      }
      tasks[taskCount - 1] = nullptr;
      return;
    }
  }
}

void Tasker::runTasks() {
  for (byte i = 0; i < taskCount; i++) {
    if (tasks[i]) {
      tasks[i]();
    }
  }
}