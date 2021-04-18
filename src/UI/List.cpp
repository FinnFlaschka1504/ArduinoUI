#include <Helper/IncludeAll.h>

List::List(int x, int y, byte *selectedItemIndex)
    : Component(x, y), selectedItemIndex(selectedItemIndex){};

List::List(int x, int y, byte *selectedItemIndex,
           OnSeletLitem *onSelectListItem)
    : Component(x, y), selectedItemIndex(selectedItemIndex),
      onSelectListItem(onSelectListItem){};

ListItem List::*items[10] = {nullptr, nullptr, nullptr, nullptr, nullptr,
                             nullptr, nullptr, nullptr, nullptr, nullptr};

void List::addItem(ListItem *item) {
  items[itemCount] = item;
  itemCount++;
};

void List::addItem(const char *text) {
  items[itemCount] = new ListItem(x, text);
  itemCount++;
}

void List::draw() {
  //   for (int i = 0; i < visibleRows; i++) {
  //     lcd.drawFrame(x, y + rowHeight * i, listWidth, rowHeight + 1);
  //   }

  // if (focused)
  //   lcd.drawFrame(x, y, listWidth, rowHeight * visibleRows);
  // Serial1.println("Render List");

  // if (true)
  //   return;

  int first;
  if (*selectedItemIndex < 2)
    first = 0;
  else if (*selectedItemIndex == itemCount - 1 && itemCount >= 3)
    first = *selectedItemIndex - 2;
  else
    first = *selectedItemIndex - 1;

  for (int row = 0; row < 6 && row < visibleRows && row < itemCount; row++) {
    ListItem item = *items[first + row];
    // ListItem item("Text");
    item.y = y + rowHeight * (row + 1) - 3;
    item.selected = focused && first + row == *selectedItemIndex;
    item.draw();
  }

  lcd.setFont(u8g2_font_unifont_t_symbols);
  if (first != 0)
    lcd.drawGlyph((x + listWidth) / 2 - 2, y + 5, 9652);
  if (first + visibleRows < itemCount)
    lcd.drawGlyph((x + listWidth) / 2 - 2, y + rowHeight * visibleRows + 4,
                  9662);
};

void List::focus() {
  Component::focus();

  InputManager::focusOnInput = [](byte pin, bool longPress, int change) {
    List *list = (List *)getCurrentFocus();
    switch (pin) {
    case ROTARY_LCD_LEFT:
    case BUTTON_U:
      list->navUp();
      break;
    case ROTARY_LCD_RIGHT:
    case BUTTON_D:
      list->navDown();
      break;
    // case BUTTON_L:
    //   UI::router.back();
    //   break;
    case BUTTON_R:
      if (longPress)
        return false;
    case BUTTON_LCD_ROTARY:
      if (!list->onSelectListItem)
        return false;
      list->navSelect();
      break;

    default:
      return false;
      break;
    }
    return true;
  };

  // auto onRotate = [](RotaryHelper *rotaryHelper, int value, int change) {
  //   // Serial.println("List Rotary Change");
  //   List *list = (List *)rotaryHelper->component;

  //   // Serial.println(list->test);
  //   // Serial.println(rotaryHelper->test);

  //   Serial.print("Cast List: ");
  //   Serial.println(list->instance);

  //   if (change > 0)
  //   {
  //     list->navDown();
  //   }
  //   else
  //   {
  //     list->navUp();
  //   }
  // };
}

void List::navUp() {
  // Serial1.println("Up");
  if (*selectedItemIndex == 0)
    *selectedItemIndex = itemCount - 1;
  else
    *selectedItemIndex = *selectedItemIndex - 1;
};

void List::navDown() {
  // Serial1.println("Down");
  if (*selectedItemIndex == itemCount - 1)
    *selectedItemIndex = 0;
  else
    *selectedItemIndex = *selectedItemIndex + 1;
};

void List::navSelect() {
  if (onSelectListItem)
    onSelectListItem(this, items[*selectedItemIndex], *selectedItemIndex);
}

// ---------------------------------------

ListItem::ListItem(byte x, const char *text) : Component(x, 0), text(text){};

void ListItem::draw() {
  lcd.setFont(u8g2_font_unifont_t_symbols);
  lcd.drawGlyph(x, y + (selected ? 3 : 1), selected ? 8594 : 9702);
  Label::drawSimple(x + 10, y, text);
};
