class Dialog;

typedef void (DrawDialogContent)(Dialog *dialog);

class Dialog : public Component {
public:
    static void showSimpleDialog(byte x, byte y, const char *title, const char *text, byte width, byte height);
    // static void initShowSimpleDialog(byte x, byte y, const char *title, const char *text, byte width, byte height);
};