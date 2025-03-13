#include <stdlib.h>
#include "raylib.h"

#define border_sx 0
#define border_sy 0
#define border_ey 1080
#define border_ex 1920

int main() {
    struct Squere {
        int x;
        int y;
        int w;
        int h;
        Color color;
        Vector2 vec;
    };

    // Cast the malloc return value to Squere*
    struct Squere *s = (struct Squere *) malloc(sizeof(struct Squere));
    s->x = 400;
    s->y = 300;
    s->w = 50;
    s->h = 50;
    s->color = ORANGE;
    s->vec = (Vector2){2.0f, -1.0f};

    InitWindow(border_ex, border_ey, "Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawRectangle(s->x, s->y, s->w, s->h, s->color);



        s->x += s->vec.x;
        s->y += s->vec.y;


        EndDrawing();
    }

    CloseWindow();
    free(s);
    return 0;
}
