#include "layout.h"

void Layout(LayoutItem *item) {
    if (item->type == LAYOUT_ROW) {
        LayoutRow(item);
    } else if (item->type == LAYOUT_COL) {
        LayoutCol(item);
    }
}

void LayoutRow(LayoutItem *item) {
    float total_weight = 0;
    for (int i = 0; i < item->child_count; i++)
        total_weight += item->children[i].weight;
    float usable = item->w
        - item->pad * 2
        - item->gap * (item->child_count - 1);

    float cur = item->x + item->pad;

    for (int i = 0; i < item->child_count; i++) {
        LayoutItem *child = &item->children[i];
        
        child->x = cur;
        child->w = usable * (child->weight / total_weight);
        cur += child->w + item->gap;

        child->y = item->y + item->pad;
        child->h = item->h - (item->pad * 2);

        if (child->child_count > 0) {
            Layout(child);
        }
    }
}

void LayoutCol(LayoutItem *item) {
    float total_weight = 0;
    for (int i = 0; i < item->child_count; i++)
        total_weight += item->children[i].weight;
    float usable = item->h
        - item->pad * 2
        - item->gap * (item->child_count - 1);

    float cur = item->y + item->pad;

    for (int i = 0; i < item->child_count; i++) {
        LayoutItem *child = &item->children[i];
        
        child->y = cur;
        child->h = usable * (child->weight / total_weight);
        cur += child->h + item->gap;

        child->x = item->x + item->pad;
        child->w = item->w - (item->pad * 2);

        if (child->child_count > 0) {
            Layout(child);
        }
    }
}

