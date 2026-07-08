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

        if (child->text) {
            LayoutText(child);
        }

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

        if (child->text) {
            LayoutText(child);
        }

        if (child->child_count > 0) {
            Layout(child);
        }
    }
}

// This function should be modified for whatever text renderer you use, this is for raylib
LayoutGlyph MeasureGlyph(char c, Font font, float font_size) {
    Rectangle size = GetGlyphAtlasRec(font, c);
    float scale = font_size / font.baseSize;
    return (LayoutGlyph){.w = size.width * scale, .h = size.height * scale};
}

// This function expects `item->text` to be an array the size of the string length of `str`
// This may need to be modified to change how it handles fonts per platform
void LayoutText(LayoutItem *item) {
    float cur_x = item->x + item->pad;
    float cur_y = item->y + item->pad;
    for (size_t i = 0; i < item->text_len; i++) {
        LayoutGlyph *glyph = &item->glyphs[i];
        *glyph = MeasureGlyph(item->text[i], item->font, item->font_size);

        if (glyph->w > (item->w - (item->pad * 2)) - (cur_x - item->x)) {
            cur_x = item->x + item->pad;
            cur_y += item->font_size;
        }

        glyph->x = cur_x;
        glyph->y = cur_y;
        cur_x += glyph->w + item->text_spacing;
    }
}
