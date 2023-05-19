/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   It has been re-confirmed with raylib 3.7.0
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*   Simple adjustments on 2021-10-01
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

#include "./Player/player.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    Sound gamemusic;
    Texture2D player;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();


    SetTargetFPS(60);

    float posX = -player.width;
 
    // Loading Payload
    
    gamemusic = LoadSound("assets/level1_soundtrack.mp3");
    player = LoadTexture("assets/character.png");

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        posX += GetFrameTime() * 300;
		if (posX > 800)
		{
			posX = -player.width;
		}
    
        while(true)
        {
            PlaySound(gamemusic);
        }
    
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            DrawTexture(player, posX, 10, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    } 

    // De-Initialization
    
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
