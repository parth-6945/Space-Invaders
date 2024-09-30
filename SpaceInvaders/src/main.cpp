#include <raylib.h>
#include "game.hpp"
#include <string>

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "C++ Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);

        // Title and presentation text
        const char* title = "Parth Gargate presents : Space Invaders";
        const char* description = "Control the spaceship to kill the aliens invading your planet.";
        const char* controls = "Use LEFT and RIGHT arrow keys to move the spaceship.";
        const char* fire = "Press SPACE to fire.";
        const char* lives = "You have three lives. Press ENTER after losing all lives to restart.";
        const char* startGame = "Press ENTER to start";

        // Calculate the center for the title
        int titleWidth = MeasureText(title, 30);
        DrawText(title, (windowWidth - titleWidth +offset) / 2, windowHeight / 4, 30, WHITE);

        // Display description and instructions
        int descriptionWidth = MeasureText(description, 20);
        DrawText(description, (windowWidth - descriptionWidth +offset) / 2, windowHeight / 4 + 50, 20, LIGHTGRAY);

        int controlsWidth = MeasureText(controls, 20);
        DrawText(controls, (windowWidth - controlsWidth +offset) / 2, windowHeight / 4 + 100, 20, LIGHTGRAY);

        int fireWidth = MeasureText(fire, 20);
        DrawText(fire, (windowWidth - fireWidth +offset) / 2, windowHeight / 4 + 130, 20, LIGHTGRAY);

        int livesWidth = MeasureText(lives, 20);
        DrawText(lives, (windowWidth - livesWidth +offset) / 2, windowHeight / 4 + 160, 20, LIGHTGRAY);

        int startGameWidth = MeasureText(startGame, 20);
        DrawText(startGame, (windowWidth - startGameWidth +offset) / 2, windowHeight / 4 + 200, 20, YELLOW);

        // End drawing
        EndDrawing();
    }

    Game game;

    while(WindowShouldClose() == false) {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if(!game.aliensAlive){
            DrawText("You Win", (windowWidth - MeasureText("You Win", 60) + offset)/2, windowHeight/2, 60, yellow);
        }
        else{
            if(game.run){
                DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
            } else {
                DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
            }
            float x = 50.0;
            for(int i = 0; i < game.lives; i ++) {
                DrawTextureV(spaceshipImage, {x, 745}, WHITE);
                x += 50;
            }

            DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
            std::string scoreText = FormatWithLeadingZeros(game.score, 5);
            DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

            DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
            std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
            DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);

            game.Draw();
        }
        EndDrawing();
    }
    
    
    CloseWindow();
    CloseAudioDevice();
}