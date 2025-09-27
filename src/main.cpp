#include "raylib.h"

int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raylib Test Window");

    // Set target FPS
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Begin drawing
        BeginDrawing();

        // Clear the background
        ClearBackground(RAYWHITE);

        // Draw some text
        DrawText("Raylib is working!", 250, 280, 20, LIGHTGRAY);

        // End drawing
        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
