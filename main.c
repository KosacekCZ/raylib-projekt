 #include "raylib.h"
 #include <stdlib.h>


 #define border_sx 0
 #define border_sy 0
 #define border_ex 800
 #define border_ey 600
 #define moveStep 5



 int main() {

     struct Square {
         int x;
         int y;
         int w;
         int h;
         Vector2 vec;
         Color color;
     };

     struct Pad {
       int x;
       int y;
       int w;
       int h;
       Color color;
     };

     struct Square * s = (struct Square *)malloc(sizeof(struct Square));
     s->x = 200;
     s->y = 300;
     s->w = 50;
     s->h = 50;
     s->color = WHITE;
     s->vec = (Vector2){4.0f, -4.0f};

     struct Pad * p1 = (struct Pad *)malloc(sizeof(struct Pad));
     struct Pad * p2 = (struct Pad *)malloc(sizeof(struct Pad));
     p1->w = 20;
     p2->w = 20;
     p1->h = 100;
     p2->h = 100;
     p1->x = 50;
     p2->x = 800 - p2->w - 50;
     p1->y = GetScreenHeight() + p1->h / 2;
     p2->y = GetScreenHeight() + p2->h / 2;
     p1->color = WHITE;
     p2->color = WHITE;

     InitWindow(800,600,"Raylib");
     SetTargetFPS(60);

     while (!WindowShouldClose())
     {
         // Start drawing
         BeginDrawing();
         ClearBackground(BLACK);

         DrawRectangle(s->x, s->y, s->w, s->h, s->color);
         DrawRectangle(p1->x, p1->y, p1->w, p1->h, s->color);
         DrawRectangle(p2->x, p2->y, p2->w, p2->h, s->color);

         s->x += s->vec.x;
         s->y += s->vec.y;

         if (p1->y > 0 && IsKeyDown(KEY_W)) p1-> y-= moveStep;
         if (p1->y + p1->h < border_ey && IsKeyDown(KEY_S)) p1-> y+= moveStep;
         if (p2->y > 0 && IsKeyDown(KEY_UP)) p2-> y-= moveStep;
         if (p2->y + p2->h < border_ey && IsKeyDown(KEY_DOWN)) p2-> y+= moveStep;

         if (s->y <= border_sy) s->vec.y *= -1;
         //if ((s->x + s->w) >= border_ex) s->vec.x *= -1;
         if ((s->y + s->h) >= border_ey) s->vec.y *= -1;
         //if (s->x <= border_sx) s->vec.x *= -1;


         if (s->x <= border_sx) CloseWindow();
         if (s->x + s->w >= border_ex) CloseWindow();

         if ((s->y + s->h >= p1->y && s->y <= p1->y + p1->h) && s->x <= p1->x + p1->w) {
           s->vec.x *= -1;
           }

         if ((s->y + s->h >= p2->y && s->y <= p2->y + p2->h) && s->x + s->w >= p2->x) {
             s->vec.x *= -1;
         }





         // vykreslení textury
         EndDrawing();
     }

     CloseWindow();

     return 0;
 }
