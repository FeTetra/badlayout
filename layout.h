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
    LEFT,
    RIGHT,
    CENTER,
} TextAlign;

typedef struct LayoutText {
    char *str;
    LayoutGlyph *glyphs;
    size_t len;
    uint32_t color;
    float spacing;
    float size;
    TextAlign align;
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