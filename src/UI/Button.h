class Button;

typedef void(OnClick)(Button *button);

class Button : public Component {
public:
  byte width = 0;
  byte height = 0;
  byte cornerRadius = 3;
  OnClick *onClick = nullptr;
  const char *label = nullptr;
  int icon = -1;
  Button(byte x, byte y, byte width, byte height, OnClick *onClick)
      : Component(x, y), width(width), height(height), onClick(onClick){};
  Button(byte x, byte y, const char *label, byte width, byte height, OnClick *onClick)
      : Component(x, y), label(label), width(width), height(height), onClick(onClick){};
  void draw() override;
  void focus() override;
  void fireOnClick();
};