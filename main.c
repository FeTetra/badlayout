#include <raylib.h>

#include "layout.h"

void RenderLayout(LayoutItem *layout);

Color U32ToRaylibColor(uint32_t color) {
    return *(Color *)&color;
}

uint32_t RaylibColorToU32(Color color) {
    return *(uint32_t *)&color;
}

void RenderLayout(LayoutItem *layout) {
    Vector2 rect_pos = {layout->x, layout->y};
    Vector2 rect_size = {layout->w, layout->h};
    DrawRectangleV(rect_pos, rect_size, U32ToRaylibColor(layout->color));
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

    LayoutItem form = {
        .x = 0,
        .y = 0,
        .w = 200,
        .h = 100,
        .pad = 5,
        .type = LAYOUT_COL,
        .color = RaylibColorToU32(BLACK),
    };

    LayoutItem children[3] = {
        {.color = RaylibColorToU32(RED), .gap = 5},
        {.color = RaylibColorToU32(GREEN), .gap = 5},
        {.color = RaylibColorToU32(BLUE), .gap = 5, .pad = 5, .type = LAYOUT_ROW},
    };
    form.children = children;
    form.child_count = 3;

    LayoutItem sub_children[3] = {
        {.color = RaylibColorToU32(VIOLET), .gap = 5},
        {.color = RaylibColorToU32(ORANGE), .gap = 5},
        {.color = RaylibColorToU32(LIME), .gap = 5},
    };
    form.children[2].children = sub_children;
    form.children[2].child_count = 3;

    Layout(&form);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderLayout(&form);
        EndDrawing();
    }

    CloseWindow();
}
