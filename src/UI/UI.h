typedef void (*InterlacedInRender)(Page *page);

class UI {
public:
  static U8G2_KS0108_128X64_1 lcd;
  // static U8G2_ST7920_128X64_1_SW_SPI lcd;
  // static InputManager inputManager;
  static Router router;
  static InterlacedInRender interlacedInRender;
  static bool pendingRender;
  static bool suspendRender;
  static bool permanentRender;
  void render();
  static Component *getCurrentFocus();
  static PageHolder *getOldPageHolder();
  static PageHolder *getCurrentPageHolder();
  static Page *getOldPage();
  static Page *getCurrentPage();
  static PageId getOldPageId();
  static PageId getCurrentPageId();
  static PageState *getOldState();
  static PageState *getCurrentState();
  static bool shouldRender();
  static void reRender();
};