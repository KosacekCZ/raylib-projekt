#include "raylib.h"
#include "Sorting.h"
#include <stdlib.h>


void draw_data(int data[]) {
  for (int i = 0; i < 10; i++) {
      DrawRectangle((30 + 5) * i, GetScreenHeight() - (data[i] * 30), 30, data[i] * 30, RED);
      }
  }

void sort_array(int arr[], int size) {

}


int main() {
    int arr[] = {8, 9, 1, 4, 0, 7, 6, 4, 9, 1, 5, 3, 2, 8, 9, 1};

    InitWindow(800,600,"Raylib");
    SetTargetFPS(60);
    Texture2D texture = LoadTexture("assets/ctverec.png"); //načtení textury na GPU

    // Main game loop
    // DrawRectangle(100, 100, 200, 200, GRAY);

    int i = 0;
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int j = 0; j < 16 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the numbers
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            draw_data(arr);
        }
        i++;
        WaitTime(0.5);



        // vykreslení textury
        EndDrawing();
    }

    UnloadTexture(texture); // vymazání textury z paměti
    CloseWindow();


    return 0;
}
