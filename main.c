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
    bool is_destroyed;
    int type; // 0 = player, 1 = projectile, 2 = asteroid
};

struct Entities {
    int count;
    struct Entity *entities;
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

        if (IsKeyDown(KEY_S)) {
            float angleInRadians = entity.angle * (M_PI / 180.0f); // Convert angle from degrees to radians
            if (abs(entity.vel.x) < 10.0f)
               entity.vel.x += cos(angleInRadians - M_PI_2) * entity.acceleration; // Moving backwards in angle direction
            if (abs(entity.vel.y) < 10.0f)
                entity.vel.y += sin(angleInRadians - M_PI_2) * entity.acceleration; // Moving backwards in angle direction
        }

        if (IsKeyDown(KEY_A)) {
            entity.angle -= 5;
        }
        if (IsKeyDown(KEY_D)) {
            entity.angle += 5;
        }

        draw();
    }
};

struct Projectile {
    struct Entity entity;
};

// Initialize the entities list
void initEntities(struct Entities* es) {
    es->entities = (struct Entity*)malloc(sizeof(struct Entity) * 1);  // Initially allocate for one entity
    es->count = 0;
}

// Add an entity to the list
void putEntity(struct Entities* es, struct Entity* e) {
    // Try reallocating memory for the entities list
    struct Entity* newEntities = (struct Entity*)realloc(es->entities, (es->count + 1) * sizeof(struct Entity));

    if (newEntities == NULL) {
        // If realloc fails, keep the original memory and print an error
        printf("Memory allocation failed!\n");
        return;  // Don't proceed further
    }

    // If realloc is successful, update the pointer to the newly allocated memory
    es->entities = newEntities;

    // Copy the new entity into the array and update the count
    es->entities[es->count] = *e;
    es->count++;

    printf("Inserted entity. Total entities: %d\n", es->count);
}

// Remove an entity from the list
void removeEntity(struct Entities* es, int pos) {
    if (pos < 0 || pos >= es->count) {
        printf("Index out of bounds\n");
        return;
    }

    for (int i = pos; i < es->count - 1; i++) {
        es->entities[i] = es->entities[i + 1];
    }

    es->count--;
}

void updateEntity(struct Entity * entity) {
    entity->pos.x += entity->vel.x;
    entity->pos.y += entity->vel.y;
    if (entity->pos.x > 800 || entity->pos.x < 0 || entity->pos.y > 800 || entity->pos.y < 0) entity->is_destroyed = true;
}

void drawEntity(struct Entity * e) {
    if (e->type == 0) {
        // draw player
    } else if (e->type == 1) {
        DrawPolyLines(e->pos, 3, 10, e->angle, RAYWHITE);

    }
}

// Update all entities
void updateEntities(struct Entities* es) {
    for (int i = 0; i < es->count; i++) {
        updateEntity(&es->entities[i]);
        drawEntity(&es->entities[i]);
        if (es->entities[i].is_destroyed) removeEntity(es, i);
    }
}


int main() {printf("stop");
    bool running = true;

    InitWindow(800, 800, "Spacewar");
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
            10 ,
        false}};

    struct Entities entities ={};

    initEntities(&entities);



    while (running) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_W)) {
            struct Projectile p = {
                player.entity.pos,
                {cos(p.entity.angle) * p.entity.acceleration, sin(p.entity.angle) * p.entity.acceleration},
                player.entity.angle,
                10.0f,
                1,
                false,
                1
            };


            putEntity(&entities, (struct Entity*)&p);
        }

        player.update();
        updateEntities(&entities);




        EndDrawing();


        if (IsKeyPressed(KEY_ESCAPE)) running = false;
    }


}