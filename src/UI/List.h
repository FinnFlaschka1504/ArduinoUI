class ListItem;
class List;

typedef void (OnSeletLitem)(List* list, ListItem* listItem, int index);

class List : public Component {
public:
  byte itemCount = 0;
  byte visibleRows = 3;
  byte rowHeight = 15;
  byte listWidth = 128;
  byte *selectedItemIndex = nullptr;
  OnSeletLitem* onSelectListItem = nullptr;
  ListItem *items[10];
  List(int x, int y, byte *selectedItemIndex);
  List(int x, int y, byte *selectedItemIndex, OnSeletLitem* onSelectListItem);
  void addItem(ListItem *item);
  void addItem(const char *text);
  void draw() override;
  void focus() override;
  void navUp();
  void navDown();
  void navSelect();
};

class ListItem : public Component {
public:
  const char* text;
  bool selected;
  // bool showMoreUp;
  // bool showMoreDown;
  ListItem(byte x, const char *text);
  void draw() override;
};