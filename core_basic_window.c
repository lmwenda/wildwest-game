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

#include <stdio.h>
#include <unistd.h>

#include "raylib.h"
#include "./Player/player.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 950;
    int screenHeight = 1200;
    float framespersecond;

    InitWindow(screenWidth, screenHeight, "raylib [core] game - New Mexico");
    InitAudioDevice();
    readlink("/proc/self/exe");
    
    SetTargetFPS(240);

    
    // Loading Payload
    
    Music gamemusic = LoadMusicStream("assets/level1_soundtrack.mp3");
    Sound gunshot = LoadSound("assets/gunshots.wav");
    Texture2D player = LoadTexture("assets/character.png");
    Texture2D background = LoadTexture("assets/Desert.png");
    Texture2D midground = LoadTexture("assets/Desert.png");
    Texture2D foreground = LoadTexture("assets/Desert.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    float posX = -player.width;
    bool *isShoot = false;
    
    // printf("Path: %s ", GetWorkingDirectory()); -- TO GET WORKING PATH FOR ASSETS

    //--------------------------------------------------------------------------------------
    
    ToggleFullscreen();
    if (IsWindowFullscreen()) { 
        // SetWindowSize(GetMonitorHeight(0), GetMonitorHeight(0)); // returns wrong values
        SetWindowSize(1920, 1200); // hardcoded values work fine!
    } 
    else {
        SetWindowSize(640, 360);
    }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        UpdateMusicStream(gamemusic);

        PlayMusicStream(gamemusic);

        framespersecond = GetFPS();

          scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;

        posX += GetFrameTime() * 300;
		if (posX > 1920)
		{ 
		    posX = -player.width;
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
		{
            isShoot = true;
            PlaySound(gunshot);
            isShoot = false;
		}
    
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw background image twice
            // NOTE: Texture is scaled twice its size
            DrawTextureEx(background, (Vector2){ scrollingBack, -900 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, -900}, 2.0f, 2.0f, WHITE);

            // Draw midground image twice
            DrawTextureEx(midground, (Vector2){ scrollingMid, -900 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, -900 }, 2.0f, 2.0f, WHITE);

            // Draw foreground image twice
            DrawTextureEx(foreground, (Vector2){ scrollingFore, -900 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, -900}, 2.0f, 2.0f, WHITE);

            char _strfps[50];
            snprintf(_strfps, sizeof _strfps, "%f", framespersecond);
            DrawText(_strfps, 1600, 25, 50, BLACK);

            player.width = 250;
            player.height = 250;
            DrawTexture(player, posX, 750, WHITE); 
        EndDrawing();
        //----------------------------------------------------------------------------------
    } 

    // De-Initialization
    
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground);  // Unload foreground texture
    UnloadTexture(player);

    StopMusicStream(gamemusic);
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
