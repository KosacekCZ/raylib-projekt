#include "raylib.h"
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SNAKE_SIZE 20

struct SnakeTile {
    Vector2 vec;
    Color color;
};

struct Apple {
    Vector2 position;
    Color color;
};

struct SnakeTile *snake = NULL;
int snakeLength = 1;
struct Apple apple;
char close = 1;
int direction = 0;

void reallocSnakeArr(struct SnakeTile **arr, int size) {
    if (arr == NULL) {
        exit(EXIT_FAILURE);
    }

    struct SnakeTile *temp = (struct SnakeTile *)realloc(*arr, sizeof(struct SnakeTile) * size);
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
    *arr = temp;
}

void spawnSnake(int x, int y) {
    snake[0].vec = (Vector2){x, y};
    snake[0].color = GREEN;
}

void spawnApple() {
    apple.position = (Vector2){
        (float)(rand() % (SCREEN_WIDTH / SNAKE_SIZE)) * SNAKE_SIZE,
        (float)(rand() % (SCREEN_HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE
    };
    apple.color = RED;
}

void moveSnake() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i].vec = snake[i - 1].vec;
        snake[i].color = snake[i - 1].color;
    }


    if (direction == 0) {
        snake[0].vec.x += SNAKE_SIZE;
    } else if (direction == 1) {
        snake[0].vec.y -= SNAKE_SIZE;
    } else if (direction == 2) {
        snake[0].vec.x -= SNAKE_SIZE;
    } else if (direction == 3) {
        snake[0].vec.y += SNAKE_SIZE;
    }
}

void checkAppleCollision() {
    if (CheckCollisionRecs((Rectangle){snake[0].vec.x, snake[0].vec.y, SNAKE_SIZE, SNAKE_SIZE},
                           (Rectangle){apple.position.x, apple.position.y, SNAKE_SIZE, SNAKE_SIZE})) {

        snakeLength++;
        reallocSnakeArr(&snake, snakeLength);
        spawnApple();
    }
}

int checkWallCollision() {
    if (snake[0].vec.x < 0 || snake[0].vec.x >= SCREEN_WIDTH ||
        snake[0].vec.y < 0 || snake[0].vec.y >= SCREEN_HEIGHT) {
        return 1;
    }
    return 0;
}

int checkSelfCollision() {
    for (int i = 1; i < snakeLength; i++) {
        if (snake[i].vec.x == snake[0].vec.x && snake[i].vec.y == snake[0].vec.y) {
            return 1;
        }
    }
    return 0;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snek");
    SetTargetFPS(10);
    srand((unsigned int)time(NULL));


    snake = (struct SnakeTile *)malloc(sizeof(struct SnakeTile) * snakeLength);
    if (snake == NULL) {
        exit(EXIT_FAILURE);
    }

    spawnSnake(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    spawnApple();

    // Main game loop
    while (!WindowShouldClose() && close) {

        if ((IsKeyPressed(KEY_D) || IsKeyDown(KEY_D)) && direction != 2) direction = 0;
        if ((IsKeyPressed(KEY_W) || IsKeyDown(KEY_W)) && direction != 3) direction = 1;
        if ((IsKeyPressed(KEY_A) || IsKeyDown(KEY_A)) && direction != 0) direction = 2;
        if ((IsKeyPressed(KEY_S) || IsKeyDown(KEY_S)) && direction != 1) direction = 3;


        moveSnake();
        checkAppleCollision();

        if (checkWallCollision() || checkSelfCollision()) {
            close = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < snakeLength; i++) {
            DrawRectangleV(snake[i].vec, (Vector2){SNAKE_SIZE, SNAKE_SIZE}, snake[i].color);
        }

        DrawRectangleV(apple.position, (Vector2){SNAKE_SIZE, SNAKE_SIZE}, apple.color);
        EndDrawing();
    }


    free(snake);
    CloseWindow();
    return 0;
}
