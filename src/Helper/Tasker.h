typedef void (*RunTask)();

class Tasker {
public:
    static byte taskCount;
    static RunTask tasks[5];
    static void addTask(RunTask task);
    static void bindPageTask(Page *page);
    static void removeTask(RunTask task);
    static void runTasks();
};