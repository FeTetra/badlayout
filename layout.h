#ifndef LAYOUT_H
#define LAYOUT_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <raylib.h>

typedef enum LayoutItemType {
    LAYOUT_ROW,
    LAYOUT_COL,
} LayoutItemType;

typedef struct LayoutGlyph {
    float x, y, w, h;
} LayoutGlyph;

typedef enum TextWrap {
    LETTER,
    WORD,
    NONE,
} TextWrap;

typedef enum TextAlign {
    AL_LEFT,
    AL_RIGHT,
    AL_CENTER,
} TextAlign;

static const float AnchorTable[] = {
    0.0, // none
    0.0, // left | top
    1.0, // right | bottom
    0.5, // center
};

typedef enum Anchor {
    AN_TOP = 1,
    AN_BOTTOM = 2,
    AN_LEFT = 4,
    AN_RIGHT = 8,
    AN_TB = 3,
    AN_LR = 12,
} Anchor;

typedef struct LayoutText {
    char *str;
    LayoutGlyph *glyphs;
    size_t len;
    uint32_t color;
    float spacing;
    float size;
    float offset_x;
    float offset_y;
    TextAlign align;
    Anchor anchor;
    TextWrap wrap;
    Font font; // To be changed per-platform
} LayoutText;

typedef struct LayoutItem {
    float x, y;
    float w, h;
    float pad, gap, weight;

    int spacer;
    uint32_t color;

    LayoutItemType type;
    struct LayoutItem *children;
    int child_count;

    LayoutText *text;
} LayoutItem;

void Layout(LayoutItem *item);
void LayoutRow(LayoutItem *item);
void LayoutCol(LayoutItem *item);

void LayoutItemGlyphs(LayoutItem *item);

#endif // LAYOUT_H