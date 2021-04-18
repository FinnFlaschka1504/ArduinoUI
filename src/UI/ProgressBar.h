class ProgressBar : public Component {
public:
  void draw() override;
  void focus() override;
  static void drawSimple(byte x, byte y, byte width, int progress, int maxProgress = 100, bool showDetail = false);
};