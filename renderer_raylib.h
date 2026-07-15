#include <raylib.h>

#include "layout.h"

static Color U32ToRaylibColor(uint32_t color) {
    return *(Color *)&color;
}

static uint32_t RaylibColorToU32(Color color) {
    return *(uint32_t *)&color;
}

static void RenderLayout(LayoutItem *layout) {
    if (!layout->spacer) {
        Vector2 rect_pos = {layout->x, layout->y};
        Vector2 rect_size = {layout->w, layout->h};
        DrawRectangleV(
            rect_pos, 
            rect_size, 
            U32ToRaylibColor(layout->color)
        );
    }
    if (layout->text) {
        LayoutText *text = layout->text;
        for (size_t i = 0; i < text->len; i++) {
            LayoutGlyph *glyph = &text->glyphs[i];
            Vector2 rect_pos = {glyph->x + text->offset_x, glyph->y + text->offset_y};
            DrawTextCodepoint(
                text->font, 
                text->str[i], 
                rect_pos, 
                text->size, 
                U32ToRaylibColor(text->color)
            );
        }
    }
    for (int i = 0; i < layout->child_count; i++) {
        RenderLayout(&layout->children[i]);
    }
}