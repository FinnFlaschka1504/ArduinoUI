class NumberSelect : public Component {
public:
  int *value = nullptr;
  byte digits = 3;
  byte stepSize = 1;
  byte bigStepSize = 5;
  uint8_t taskId = -1;
  bool loop = false;
  bool allowNegative = false;
  NumberSelect(int x, int y, int *value) : Component(x, y), value(value){};
  void draw() override;
  void focus() override;
  // void blur() {
  //   Component::blur();
  //   Serial1.println("Blur Number");
  // };
  void countUp(bool bigStep = false);
  void countDown(bool bigStep = false);
  void setBounds(int minValue, int maxValue);

private:
  bool hasBounds = false;
  int maxValue = 0;
  int minValue = 0;
};