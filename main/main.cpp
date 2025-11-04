#include "raylib.h"

#include "loggerMacros.h"
#include "raylibLogging.h"
#include "villageRNG_Interface.h"

int main() {
    SetTraceLogCallback(raylib_logging_function);
    InitWindow(800, 450, "Raylib Test");
    LOG_INFO("Hi from the Logger System's Default Logger.");

    auto myRNG = GetVillageRNGInterface();
    printf("I Rolled %u", myRNG->next(0, 99));

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
