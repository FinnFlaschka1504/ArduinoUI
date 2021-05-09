class NumberSelect : public Component {
public:
  int *value = nullptr;
  byte digits = 3;
  byte stepSize = 1;
  byte bigStepSize = 5;
  uint8_t taskId = -1;
  bool loop = true;
  bool allowNegative = false;
  const char *prefix = nullptr;
  const char *suffix = nullptr;
  NumberSelect(int x, int y, int *value, const char *prefix = nullptr, const char *suffix = nullptr) : Component(x, y), value(value), prefix(prefix), suffix(suffix) {};
  NumberSelect(int x, int y, int *value, int minValue, int maxValue, const char *prefix = nullptr, const char *suffix = nullptr) : Component(x, y), value(value), prefix(prefix), suffix(suffix) {
    setBounds(minValue, maxValue);
  };
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