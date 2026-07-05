#ifndef LAYOUT_H
#define LAYOUT_H

#include <stddef.h>
#include <stdint.h>

typedef enum LayoutItemType {
    LAYOUT_ROW,
    LAYOUT_COL,
} LayoutItemType;

typedef struct LayoutItem {
    float x, y;
    float w, h;
    float pad, gap;
    uint32_t color;

    LayoutItemType type;
    struct LayoutItem *children;
    int child_count;
} LayoutItem;

void Layout(LayoutItem *item);
void LayoutRow(LayoutItem *item);
void LayoutCol(LayoutItem *item);

#endif // LAYOUT_H