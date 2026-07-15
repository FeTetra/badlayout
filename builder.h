#include <stdlib.h>

#include "layout.h"

LayoutItem *NewLayoutChildren(LayoutItem *children, int count);

int AddLayoutChildren(LayoutItem *parent, LayoutItem *children, int count);
int AddLayoutChild(LayoutItem *parent, LayoutItem *child);

LayoutText *NewLayoutText(
    char *str,
    uint32_t color,
    float spacing,
    float size,
    TextAlign align,
    Anchor anchor,
    TextWrap wrap,
    Font font
);

void LayoutItem_dtor(LayoutItem *parent);
void LayoutText_dtor(LayoutText *text);
void Layout_dtor(LayoutItem *item);
