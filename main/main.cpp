#include "raylib.h"

#include "loggerMacros.h"
#include "raylibLogging.h"

int main() {
    SetTraceLogCallback(raylib_logging_function);
    InitWindow(800, 450, "Raylib Test");
    LOG_INFO("Hi from the Logger System's Default Logger.");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello from Raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
