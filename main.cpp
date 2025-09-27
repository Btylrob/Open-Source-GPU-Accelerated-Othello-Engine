#include "raylib.h"

int main() {
    const int screenW = 480;
    const int screenH = 640;
    InitWindow(screenW, screenH, "Othello Game");
    SetTargetFPS(60);

    const int BOARD_SIZE = 8;
    const int boardSizePx = 400;
    const int boardX = (screenW - boardSizePx) / 2;
    const int boardY = 120;
    const int cellSize = boardSizePx / BOARD_SIZE;
    
    // Hamburger menu variables
    Rectangle menuButton = {screenW - 50, 20, 30, 30};
    bool menuOpen = false;
    Rectangle menuBox = {screenW - 200, 60, 180, 150};
    bool menuHover = false;

    while (!WindowShouldClose()) {
        // Get mouse position for hover detection
        Vector2 mousePos = GetMousePosition();
        menuHover = CheckCollisionPointRec(mousePos, menuButton);
        
        // Toggle menu on click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePos, menuButton)) {
                menuOpen = !menuOpen;
            } else if (menuOpen && !CheckCollisionPointRec(mousePos, menuBox)) {
                // Close menu if clicking outside
                menuOpen = false;
            }
        }

        BeginDrawing();
        ClearBackground(Color{245, 240, 230, 255});

        // --- Top UI (timer & moves with labels) ---
        DrawText("Time left", 80, 5, 16, DARKGRAY);
        DrawRectangleRounded((Rectangle){80, 20, 140, 40}, 0.3f, 6, Color{100, 180, 255, 255});
        DrawText("1:34", 120, 30, 20, WHITE);

        DrawText("Moves left", 260, 5, 16, DARKGRAY);
        DrawRectangleRounded((Rectangle){260, 20, 140, 40}, 0.3f, 6, Color{120, 200, 100, 255});
        DrawText("12", 320, 30, 20, WHITE);

        // --- Hamburger Menu Button (draw early so it's behind the dropdown) ---
        Color menuButtonColor = menuHover ? (Color){200, 200, 200, 255} : (Color){220, 220, 220, 255};
        DrawRectangleRounded(menuButton, 0.2f, 4, menuButtonColor);
        
        // Draw the three lines of the hamburger menu
        float lineY = menuButton.y + 7;
        for (int i = 0; i < 3; i++) {
            DrawRectangle(menuButton.x + 5, lineY, menuButton.width - 10, 3, DARKGRAY);
            lineY += 8;
        }

        // --- Player Labels ---
        DrawText("Player 1", screenW/2 - MeasureText("Player 1", 20)/2, 80, 20, DARKGRAY);
        DrawText("Player 2", screenW/2 - MeasureText("Player 2", 20)/2, boardY + boardSizePx + 50, 20, DARKGRAY);

        // --- Board background (rounded rectangle) ---
        DrawRectangleRounded((Rectangle){(float)boardX-10, (float)boardY-10, (float)boardSizePx+20, (float)boardSizePx+20},
                             0.1f, 8, (Color){210, 200, 180, 255});
        DrawRectangle(boardX, boardY, boardSizePx, boardSizePx, (Color){230, 220, 200, 255});

        // --- Grid ---
        for (int i = 1; i < BOARD_SIZE; i++) {
            DrawLineEx(
                (Vector2){(float)(boardX + i*cellSize), (float)boardY},
                (Vector2){(float)(boardX + i*cellSize), (float)(boardY + boardSizePx)},
                3.0f,
                (Color){190, 180, 160, 255}
            );
            DrawLineEx(
                (Vector2){(float)boardX, (float)(boardY + i*cellSize)},
                (Vector2){(float)(boardX + boardSizePx), (float)(boardY + i*cellSize)},
                3.0f,
                (Color){190, 180, 160, 255}
            );
        }

        // --- Center discs ---
        const int discRadius = cellSize / 2 - 5;
        DrawCircle(boardX + 3*cellSize + cellSize/2, boardY + 3*cellSize + cellSize/2, discRadius, WHITE);
        DrawCircle(boardX + 4*cellSize + cellSize/2, boardY + 4*cellSize + cellSize/2, discRadius, WHITE);
        DrawCircle(boardX + 4*cellSize + cellSize/2, boardY + 3*cellSize + cellSize/2, discRadius, BLACK);
        DrawCircle(boardX + 3*cellSize + cellSize/2, boardY + 4*cellSize + cellSize/2, discRadius, BLACK);

        // --- Dropdown menu (drawn LAST so it appears on top) ---
        if (menuOpen) {
            DrawRectangleRounded(menuBox, 0.1f, 6, (Color){240, 240, 240, 255});
            DrawRectangleRoundedLines(menuBox, 0.1f, 6, (Color){240, 240, 240, 255});
            
            // Menu options
            DrawText("New Game", menuBox.x + 10, menuBox.y + 15, 18, DARKGRAY);
            DrawText("Settings", menuBox.x + 10, menuBox.y + 55, 18, DARKGRAY);
            DrawText("Exit", menuBox.x + 10, menuBox.y + 95, 18, DARKGRAY);
            
            // Separator lines
            DrawLine(menuBox.x + 5, menuBox.y + 45, menuBox.x + menuBox.width - 5, menuBox.y + 45, LIGHTGRAY);
            DrawLine(menuBox.x + 5, menuBox.y + 85, menuBox.x + menuBox.width - 5, menuBox.y + 85, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
