class Label : public Component
{
public:
    const char* text = nullptr;
    const uint8_t* font = nullptr;
    Label(byte x, byte y, const char* text);
    Label(byte x, byte y, const char* text, const uint8_t* font);
    void draw() override;
    void focus() override;
    static void drawSimple(byte x, byte y, const char* text, const uint8_t *font = u8g2_font_t0_11_me);
    static void drawSimple(byte x, byte y, int glyph, const uint8_t *font = u8g2_font_unifont_t_symbols);
    static void drawSimpleN(byte x, byte y, int value, const char *prefix = "", const char *suffix = "", byte digits = 1, const char *filler = "", const uint8_t *font = u8g2_font_t0_11_me);
    static void drawSimpleD(byte x, byte y, double value, const char *prefix = "", const char *suffix = "", byte digits = 1, byte prec = 0, const char *filler = "", const uint8_t *font = u8g2_font_t0_11_me);
};

class Caption : public Label {
    public:
        Caption(byte x, byte y, const char *text);
        static void drawSimple(byte x, byte y, const char* text, const uint8_t *font = u8g2_font_7x14B_tf);
};