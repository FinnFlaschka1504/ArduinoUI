#include "Helper/IncludeAll.h"

void Dialog::showSimpleDialog(byte x, byte y, const char *title, const char *text, byte width, byte height)
{
    UI::lcd.setDrawColor(0);
    UI::lcd.drawBox(x - 1, y - 1, width + 2, height + 2);
    // ui.lcd.drawBox(x, y, width, height);
    UI::lcd.setDrawColor(1);
    UI::lcd.drawFrame(x, y, width, height);
    Caption::drawSimple(x + 5, y + 15, title);
    Label::drawSimple(x + 5, y + 35, text);
};

// void Dialog::initShowSimpleDialog(byte x, byte y, const char *title, const char *text, byte width, byte height)
// {
//     UI::showDialog = []() {
//         Dialog::showSimpleDialog(10, 10, "Test Dialog", "Nur ein Test", 100, 45);
//     };
// }