#include <math.h>

#include "raylib.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

struct Entity {
    Vector2 pos;
    Vector2 vel;
    float angle;
    float acceleration;
    int health;
    void draw();
    void update();
};

struct Player {
    struct Entity entity;
    void draw() {
        DrawPolyLines(entity.pos, 3, 30, entity.angle + 270.0f, RAYWHITE);
    }

    void update() {
        if (entity.vel.x > 0 && entity.pos.x < 800) entity.pos.x += entity.vel.x;
        if (entity.vel.x < 0 && entity.pos.x > 0) entity.pos.x += entity.vel.x;
        if (entity.vel.y > 0 && entity.pos.y < 800) entity.pos.y += entity.vel.y;
        if (entity.vel.y < 0 && entity.pos.y > 0) entity.pos.y += entity.vel.y;

        if (!IsKeyDown(KEY_S)) {
            // Deaccelerate
            if (entity.vel.x > 0.0) {entity.vel.x = (entity.vel.x < 0.1 ? 0.0f : (entity.vel.x -= 0.05f));}
            if (entity.vel.x < 0.0) {entity.vel.x = (entity.vel.x > -0.1 ? 0.0f : (entity.vel.x += 0.05f));}
            if (entity.vel.y > 0.0) {entity.vel.y = (entity.vel.y < 0.1 ? 0.0f : (entity.vel.y -= 0.05f));}
            if (entity.vel.y < 0.0) {entity.vel.y = (entity.vel.y > -0.1 ? 0.0f : (entity.vel.y += 0.05f));}
        }
    }
};

int main() {printf("stop");
    bool running = true;

    InitWindow(800, 800, "Snek");
    SetTargetFPS(60);
    srand(time(NULL));

    struct Player player = {
        {
            400,
            400,
            0,
            0,
            0.0f,
            0.1f,
            10 }};


    while (running) {
        BeginDrawing();
        ClearBackground(BLACK);

        player.update();
        player.draw();

        EndDrawing();
        if (IsKeyDown(KEY_W)) {
            //shoot
        }

        if (IsKeyDown(KEY_S)) {
            float angleInRadians = player.entity.angle * (M_PI / 180.0f); // Convert angle from degrees to radians
            if (abs(player.entity.vel.x) < 10.0f)
                player.entity.vel.x += cos(angleInRadians - M_PI_2) * player.entity.acceleration; // Moving backwards in angle direction
            if (abs(player.entity.vel.y) < 10.0f)
                player.entity.vel.y += sin(angleInRadians - M_PI_2) * player.entity.acceleration; // Moving backwards in angle direction
        }

        if (IsKeyDown(KEY_A)) {
            player.entity.angle -= 5;
        }
        if (IsKeyDown(KEY_D)) {
            player.entity.angle += 5;
        }

        if (IsKeyPressed(KEY_ESCAPE)) running = false;
    }


}