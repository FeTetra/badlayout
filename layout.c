#include "layout.h"

#include <stdio.h>

void Layout(LayoutItem *item) {
    if (item->type == LAYOUT_ROW) {
        LayoutRow(item);
    } else if (item->type == LAYOUT_COL) {
        LayoutCol(item);
    }
}

void LayoutRow(LayoutItem *item) {
    float cur = item->x + item->pad;
    for (int i = 0; i < item->child_count; i++) {
        LayoutItem *child = &item->children[i];
        child->x = cur;
        child->w = (item->w - (item->pad * 2) - (child->gap * 2)) / item->child_count;
        child->y = item->y + item->pad;
        child->h = item->h - (item->pad * 2);
        cur += child->w + child->gap;
        if (child->child_count > 0) {
            Layout(child);
        }
    }
}

void LayoutCol(LayoutItem *item) {
    float cur = item->y + item->pad;
    for (int i = 0; i < item->child_count; i++) {
        LayoutItem *child = &item->children[i];
        child->y = cur;
        child->h = (item->h - (item->pad * 2) - (child->gap * 2)) / item->child_count;
        child->x = item->x + item->pad;
        child->w = item->w - (item->pad * 2);
        cur += child->h + child->gap;
        if (child->child_count > 0) {
            Layout(child);
        }
    }
}
