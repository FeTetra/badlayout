#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "layout.h"

void RenderLayout(LayoutItem *layout);

Color U32ToRaylibColor(uint32_t color) {
    return *(Color *)&color;
}

uint32_t RaylibColorToU32(Color color) {
    return *(uint32_t *)&color;
}

void RenderLayout(LayoutItem *layout) {
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
            Vector2 rect_pos = {glyph->x, glyph->y};
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

int main() {
    const int SCREEN_WITDH = 800;
    const int SCREEN_HEIGHT = 450;
    const int FRAMERATE = 60;

    InitWindow(SCREEN_WITDH, SCREEN_HEIGHT, "Layout Test");
    SetTargetFPS(FRAMERATE);

    Font font = GetFontDefault();

    LayoutItem form = {
        .x = 0,
        .y = 0,
        .w = SCREEN_WITDH,
        .h = SCREEN_HEIGHT,
        .pad = 5,
        .gap = 5,
        .type = LAYOUT_ROW,
        .color = RaylibColorToU32(BLACK),
        .text = NULL,
    };

    LayoutItem children[3] = {
        {.weight = 1, .spacer = 1,},
        {.color = RaylibColorToU32(GREEN), .weight = 1, .pad = 5},
        {.color = RaylibColorToU32(BLUE), .pad = 5, .gap = 5, .type = LAYOUT_COL, .weight = 2,},
    };
    form.children = children;
    form.child_count = 3;

    LayoutItem spacer_children[2] = {
        {.spacer = 1, .weight = 1,},
        {.type = LAYOUT_ROW, .color = RaylibColorToU32(RED), .weight = 1,},
    };
    form.children[0].children = spacer_children;
    form.children[0].child_count = 2;
    form.children[0].type = LAYOUT_COL;

    LayoutItem sub_children[3] = {
        {.color = RaylibColorToU32(VIOLET), .weight = 1,},
        {.color = RaylibColorToU32(ORANGE), .weight = 1,},
        {.color = RaylibColorToU32(LIME), .weight = 1,},
    };
    form.children[2].children = sub_children;
    form.children[2].child_count = 3;

    char *message = "this is an example of word wrapping with badlayout";
    size_t len = strlen(message);
    LayoutGlyph glyphs[len];
    LayoutText text = {
        .str = message,
        .glyphs = glyphs,
        .len = len,
        .font = font,
        .size = 24,
        .color = RaylibColorToU32(BLACK),
        .align = RIGHT,
        .wrap = WORD,
        .spacing = 2,
    };
    form.children[1].text = &text;

    Layout(&form);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderLayout(&form);
        EndDrawing();
    }

    CloseWindow();
}
