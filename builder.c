#include "builder.h"

int AddLayoutChildren(LayoutItem *parent, LayoutItem *children, int count) {
    int total = parent->child_count + count;
    size_t children_size = sizeof(LayoutItem) * total;
    void *tmp = realloc(parent->children, children_size);
    if (tmp) {
        parent->children = tmp;
        memcpy(&parent->children[parent->child_count], children, children_size);
        parent->child_count = total;
        return 1;
    }

    return 0;
}

int AddLayoutChild(LayoutItem *parent, LayoutItem *child) {
    return AddLayoutChildren(parent, child, 1);
}

LayoutItem *NewLayoutChildren(LayoutItem *children, int count) {
    size_t children_size = sizeof(LayoutItem) * count;
    LayoutItem *result = malloc(children_size);
    memcpy(result, children, children_size);
    return result;
}

// TODO: allow for removing children (requires adding a `child_capacity` to prevent memory leaking)

LayoutText *NewLayoutText(
    char *str,
    uint32_t color,
    float spacing,
    float size,
    TextAlign align,
    Anchor anchor,
    TextWrap wrap,
    Font font
) {
    LayoutText *text = malloc(sizeof(LayoutText));
    size_t len = strlen(str);
    LayoutGlyph *glyphs = malloc(sizeof(LayoutGlyph) * len);
    text->str = str;
    text->glyphs = glyphs;
    text->len = len;
    text->color = color;
    text->spacing = spacing;
    text->size = size;
    text->offset_x = 0;
    text->offset_y = 0;
    text->align = align;
    text->anchor = anchor;
    text->wrap = wrap;
    text->font = font;
    return text;
}

void LayoutItem_dtor(LayoutItem *parent) {
    free(parent->children);
    memset(parent, 0, sizeof(LayoutItem));
}

void LayoutText_dtor(LayoutText *text) {
    free(text->glyphs);
    memset(text, 0, sizeof(LayoutText));
}

void Layout_dtor(LayoutItem *item) {
    if (item == NULL) {
        return;
    }
    for (int i = 0; i < item->child_count; i++) {
        Layout_dtor(&item->children[i]);
    }

    if (item->text) {
        LayoutText_dtor(item->text);
    }

    LayoutItem_dtor(item);
}
