#ifndef LAYOUT_H
#define LAYOUT_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <raylib.h>

typedef enum LayoutItemType {
    LAYOUT_ROW,
    LAYOUT_COL,
} LayoutItemType;

typedef struct LayoutGlyph {
    float x, y, w, h;
} LayoutGlyph;

typedef struct LayoutItem {
    float x, y;
    float w, h;
    float pad, gap, weight;

    int spacer;
    uint32_t color;

    LayoutItemType type;
    struct LayoutItem *children;
    int child_count;

    char *text;
    LayoutGlyph *glyphs;
    size_t text_len;
    uint32_t text_color;
    float text_spacing;
    float font_size;
    Font font; // To be changed per-platform
} LayoutItem;

void Layout(LayoutItem *item);
void LayoutRow(LayoutItem *item);
void LayoutCol(LayoutItem *item);

void LayoutText(LayoutItem *item);

#endif // LAYOUT_H