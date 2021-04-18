class Label : public Component
{
public:
    const char* text = nullptr;
    const uint8_t* font = nullptr;
    Label(byte x, byte y, const char* text);
    Label(byte x, byte y, const char* text, const uint8_t* font);
    void draw() override;
    void focus() override;
    static void drawSimple(byte x, byte y, const char* text, const uint8_t *font = u8g2_font_t0_11_tf);
    static void drawSimple(byte x, byte y, int value, const char *prefix = "", const char *suffix = "", byte digits = 1, const char *filler = "0", const uint8_t *font = u8g2_font_t0_11_tf);
};

class Caption : public Label {
    public:
        Caption(byte x, byte y, const char *text);
        static void drawSimple(byte x, byte y, const char* text, const uint8_t *font = u8g2_font_7x14B_tf);
};