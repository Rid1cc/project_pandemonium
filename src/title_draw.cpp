#include "headers/title_draw.h"
#include "headers/globals.h"
#include <cstdio>

#include "headers/title_update.h"

void Init3DTitleTexture() {
    BeginTextureMode(space3d);
    UpdateCamera(&camera, CAMERA_ORBITAL);
    ClearBackground(BLACK);
    BeginMode3D(camera);
    if(play_highl){DrawModel(model_globe, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.40f, primaryColor);}
    if(settings_highl){DrawModel(model_cog, (Vector3){ 0.0f, 0.0f, 0.0f }, 10.0f, primaryColor);}
    if(data_highl){DrawModel(model_data, (Vector3){ 0.0f, -1.0f, 0.0f }, 0.1f, primaryColor);}
    if(exit_highl){DrawModel(model_door, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.5f, primaryColor);}
    EndMode3D();
    EndTextureMode();
}

void DrawButton(Rectangle button, const char* text, bool highlighted, float y_offset) {
    if (highlighted) {
        DrawRectangleRec(button, primaryColor);
        DrawRectangleLinesEx(button, 3, BLACK);
        DrawTextB(text, ShakeXY(110, 1.5), ShakeXY(y_offset, 1.5), 40, BLACK);
    } else {
        DrawRectangleRec(button, BLACK);
        DrawRectangleLinesEx(button, 3, primaryColor);
        DrawTextB(text, 110, y_offset, 40, primaryColor);
    }
}

void DrawDescription(const char* lines[], int lineCount, float y_start) {
    for (int i = 0; i < lineCount; i++) {
        DrawTextC(lines[i], 890, y_start + i * 20, 20, primaryColor);
    }
}

void DrawTitle() {
    // drawing backgrounds
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    
    //ScreenShake + Barriers
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
        DrawRectangleLinesEx(ShakeRectangle(screen, 5), 6, primaryColor);
    }
    else{
        DrawRectangleLinesEx(screen, 3, primaryColor);
    }
    
    DrawTextC("ParadisiOS ver 7.3, up to date.", 5, 2, 12, WHITE);  
    //Title
    DrawTextB("PANDEMONIUM", screenWidth/4, screenHeight/8, 100, primaryColor);
    DrawRectangleLinesEx(title, 5, primaryColor);

    // Buttons
    DrawButton(button_exit, "QUIT", exit_highl, float(screenHeight) - 125);
    DrawButton(button_lore, "DATA", data_highl, float(screenHeight) - 205);
    DrawButton(button_settings, "SETTINGS", settings_highl, float(screenHeight) - 285);
    DrawButton(button_play, "MISSIONS", play_highl, float(screenHeight) - 365);

    // MOTD
    DrawTextC("Good day to you EXORCIST_432.", float(screenWidth/5), float(screenHeight)-520, 15, primaryColor);
    DrawTextC("All systems Online.", float(screenWidth/5), float(screenHeight)-500, 15, primaryColor);

    // models texture
    DrawTexturePro(space3d.texture,
    Rectangle{ 0, 0, (float)space3d.texture.width, -(float)space3d.texture.height }, // Flipping Y-axis
    desc_window,
    Vector2{ 0, 0 },  
    0.0f,            
    WHITE);

    // 3d window borders
    DrawRectangleLinesEx(desc_window, 3, primaryColor);
    
    // Description window
    DrawRectangleLinesEx(anim_window_title, 3, primaryColor);

    if (play_highl) {
        const char* play_desc[] = {
            ">BLASPHEMY IS", " EVERYWHERE.", ">FIGHT THEM WITH", " THEIR OWN WEAPONS.",
            ">DO NOT LOSE YOUR", " FAITH.", "----------------", "CHOOSE A MISSION",
            "AND PLAY AGAINST", "VARIOUS ENEMIES."
        };
        DrawDescription(play_desc, 10, float(screenHeight) - 360);
    }
    if (settings_highl) {
        const char* settings_desc[] = {
            ">ADAPT TO THE", " BATTLEFIELD.", ">CHANGE YOUR", " ENVIRONMENT.",
            ">THINK SMART.", "----------------", "TWEAK SETTINGS", "AND PREFERENCES "
        };
        DrawDescription(settings_desc, 8, float(screenHeight) - 360);
    }
    if (data_highl) {
        const char* data_desc[] = {
            ">SCAVENGE THEIR", " SYSTEMS.", ">LEARN YOUR", " ENEMIES.",
            ">BE AWARE.", "----------------", "DATA FRAGMENTS,", "RECOVERED FROM",
            "ENEMIES."
        };
        DrawDescription(data_desc, 9, float(screenHeight) - 360);
    }
}
