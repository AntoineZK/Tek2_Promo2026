/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-arcade-antoine.khalidy
** File description:
** Raylib
*/

#include "Raylib.hpp"

extern "C" std::unique_ptr<arcade::IGraphical> GraphEntrypoint()
{
    return std::make_unique<arcade::Raylib>();
}

arcade::Raylib::Raylib()
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1920, 1080, "Arcade Raylib");
    this->camera.position = (Vector3) {5.0f, 40.0f, -30.0f};
    this->camera.target = (Vector3) {0.0f, 0.0f, 0.0f};
    this->camera.up = (Vector3) {0.0f, -1.0f, 0.0f};
    this->camera.fovy = 80.0f;
    this->camera.projection = CAMERA_PERSPECTIVE;
}

arcade::Raylib::~Raylib()
{
    CloseWindow();
}

std::vector<int> arcade::Raylib::getInputs()
{
    std::vector<int> inputs;

    if (WindowShouldClose())
        inputs.push_back(27);
    int key = GetCharPressed();
    if (key != 0) {
        inputs.push_back(key);
    }
    return inputs;
}

void arcade::Raylib::display(std::shared_ptr<IData> data)
{
    (void)data;
    BeginDrawing();
    ClearBackground(BLACK);
    std::string score = "Score: " + std::to_string(data->getScore());
    DrawText(score.c_str(), 10, 40, 20, RED);
    std::string lives = "Lives: " + std::to_string(data->getLives());
    DrawText(lives.c_str(), 10, 70, 20, BLUE);
    std::string level = "Level: " + std::to_string(data->getLevel());
    DrawText(level.c_str(), 10, 100, 20, ORANGE);
    BeginMode3D(this->camera);
    std::pair<std::size_t, std::size_t> mapSize = data->getMapSize();
    for (std::size_t i = 0; i < mapSize.first; i++) {
        for (std::size_t j = 0; j < mapSize.second; j++) {
            IEntity &entity = data->getEntities(i, j);
            DrawCubeWires((Vector3){(-20.0f + j), (0.0f + i), 0.0f}, 1.0f, 1.0f, 1.1f, this->colorMap[entity.getColorBackground()]);
            DrawCube((Vector3){(-20.0f + j), (0.0f + i), 0.0f}, 1.0f, 1.0f, 1.0f, this->colorMap[entity.getColorCharacter()]);
        }
    }
    EndMode3D();
    EndDrawing();
}
