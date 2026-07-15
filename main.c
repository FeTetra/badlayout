#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "layout.h"
#include "builder.h"
#include "renderer_raylib.h"

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
        .child_count = 3,
        .children = NewLayoutChildren((LayoutItem[]){
        {
            .weight = 1, 
            .spacer = 1,
            .child_count = 2,
            .type = LAYOUT_COL,
            .children = NewLayoutChildren((LayoutItem[]){
                {.spacer = 1, .weight = 1,},
                {.color = RaylibColorToU32(RED), .weight = 1,},
                }, 2)
            },
        {
            .color = RaylibColorToU32(GREEN), 
            .weight = 2, 
            .pad = 5,
            .text = NewLayoutText(
                "this is an example of word wrapping with badlayout", 
                RaylibColorToU32(BLACK), 
                2, 
                24, 
                AL_LEFT, 
                AN_TB | AN_LR, 
                WORD, 
                font)
            },
        {
            .color = RaylibColorToU32(BLUE), 
            .pad = 5, .gap = 5, 
            .type = LAYOUT_COL, 
            .weight = 1,
            .child_count = 3,
            .children = NewLayoutChildren((LayoutItem[]){
                    {.color = RaylibColorToU32(VIOLET), .weight = 1,},
                    {.color = RaylibColorToU32(ORANGE), .weight = 1,},
                    {.color = RaylibColorToU32(LIME), .weight = 1,},
                }, 3)
            },
        }, 3)
    };

    Layout(&form);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderLayout(&form);
        EndDrawing();
    }

    Layout_dtor(&form);

    CloseWindow();
}
