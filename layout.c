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
            LayoutItemGlyphs(child);
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
            LayoutItemGlyphs(child);
        }

        if (child->child_count > 0) {
            Layout(child);
        }
    }
}

typedef struct GlyphLine {
    int glyph_count;
    float length;
} GlyphLine;

// This function should be modified for whatever text renderer you use, this is for raylib
LayoutGlyph MeasureGlyph(LayoutText *text, char c) {
    Rectangle size = GetGlyphAtlasRec(text->font, c);
    float scale = text->size / text->font.baseSize;
    return (LayoutGlyph){.w = size.width * scale, .h = size.height * scale};
}

// TODO: Do a MeasureGlyph pass for word wrap so we don't remeasure glyphs when walking back
GlyphLine MeasureGlyphLine(LayoutItem *item, int *start_idx) {
    LayoutText *text = item->text;
    GlyphLine result;

    float remaining = (item->w - (item->pad * 2));
    float total_len = 0;

    int nonspace_count = 0;
    float word_len = 0;

    int i = *start_idx;
    while (i < text->len) {
        text->glyphs[i] = MeasureGlyph(text, text->str[i]);

        if (text->wrap == LETTER) {
            if (text->glyphs[i].w + text->spacing > remaining - total_len) {
                break;
            }
        }

        if (text->wrap == WORD) {
            if (!isspace(text->str[i])) {
                word_len += text->glyphs[i].w + text->spacing;
                nonspace_count++;
            } else {
                word_len = 0; 
                nonspace_count = 0;
            }

            if (word_len > remaining - (total_len - word_len)) {
                total_len -= word_len;
                
                if (word_len > remaining) {
                    break; // Word longer than all remaining space, just cut it
                }

                i -= nonspace_count - 1; // Jump back to beginning of word
                break;
            }
        }

        total_len += text->glyphs[i].w + text->spacing;

        i++;
    }

    result.glyph_count = i - *start_idx;
    result.length = total_len;
    *start_idx = i;

    return result;
}

void LayoutItemGlyphs(LayoutItem *item) {
    LayoutText *text = item->text;

    float cur_x = 0;
    float cur_y = item->y + item->pad;

    for (int i = 0; i < text->len;) {
        int start = i;
        GlyphLine line = MeasureGlyphLine(item, &i);

        if (text->align == LEFT) {
            cur_x = item->x + item->pad;
        } else if (text->align == RIGHT) {
            cur_x = (item->x + (item->w - line.length));
        } else if (text->align == CENTER) {
            cur_x = item->x + ((item->w - line.length) / 2);
        }

        for (int j = start; j - start < line.glyph_count; j++) {
            LayoutGlyph *glyph = &text->glyphs[j];

            glyph->x = cur_x;
            glyph->y = cur_y;

            cur_x += glyph->w + text->spacing;
        }

        cur_y += text->size;
    }
}
