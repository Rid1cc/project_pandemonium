#include "headers/title_draw.h"
#include "headers/globals.h"
#include <cstdio>

#include "headers/title_update.h"

void Init3DTitleTexture() {
    BeginTextureMode(space3d);
    UpdateCamera(&camera, CAMERA_ORBITAL);
    ClearBackground(BLACK);
    BeginMode3D(camera);
    if(play_highl){DrawModel(model_globe, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.40f, ORANGE);}
    if(settings_highl){DrawModel(model_cog, (Vector3){ 0.0f, 0.0f, 0.0f }, 10.0f, ORANGE);}
    if(data_highl){DrawModel(model_data, (Vector3){ 0.0f, -1.0f, 0.0f }, 0.1f, ORANGE);}
    if(exit_highl){DrawModel(model_door, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.5f, ORANGE);}
    EndMode3D();
    EndTextureMode();
}

void DrawTitle() {
    
    
    // drawing backgrounds
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    
    //ScreenShake + Barriers
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
        DrawRectangleLinesEx(ShakeRectangle(screen, 5), 6, ORANGE);
    }
    else{
        DrawRectangleLinesEx(screen, 3, ORANGE);
    }
    
    

    DrawTextC("ParadisiOS ver 7.3, up to date.", 5, 2, 12, WHITE);  
    //Title
    DrawTextB("PANDEMONIUM", screenWidth/4, screenHeight/8, 100, ORANGE);
    DrawRectangleLinesEx(title, 5, ORANGE);

    //Buttons
    //Exit
    if(exit_highl == true){
        DrawRectangleRec(button_exit, ORANGE);
        DrawRectangleLinesEx(button_exit, 3, BLACK);
        DrawTextB("QUIT", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-125, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_exit, BLACK);
        DrawRectangleLinesEx(button_exit, 3, ORANGE);
        DrawTextB("QUIT", 110, float(screenHeight)-125, 40, ORANGE);
    }
    

    //Lore
    if(data_highl == true){
        DrawRectangleRec(button_lore, ORANGE);
        DrawRectangleLinesEx(button_lore, 3, BLACK);
        DrawTextB("DATA", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-205,1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_lore, BLACK);
        DrawRectangleLinesEx(button_lore, 3, ORANGE);
        DrawTextB("DATA", 110, float(screenHeight)-205, 40, ORANGE);
    }

    //Settings
    if(settings_highl == true){
        DrawRectangleRec(button_settings, ORANGE);
        DrawRectangleLinesEx(button_settings, 3, BLACK);
        DrawTextB("SETTINGS", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-285, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_settings, BLACK);
        DrawRectangleLinesEx(button_settings, 3, ORANGE);
        DrawTextB("SETTINGS", 110, float(screenHeight)-285, 40, ORANGE);
    }

    //Play
    if(play_highl == true){
        DrawRectangleRec(button_play, ORANGE);
        DrawRectangleLinesEx(button_play, 3, BLACK);
        DrawTextB("MISSIONS", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-365, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_play, BLACK);
        DrawRectangleLinesEx(button_play, 3, ORANGE);
        DrawTextB("MISSIONS", 110, float(screenHeight)-365, 40, ORANGE);
    }
    
    //MOTD
    DrawTextC("Good day to you EXORCIST_432.", float(screenWidth/5), float(screenHeight)-520, 15, ORANGE);
    DrawTextC("All systems Online.", float(screenWidth/5), float(screenHeight)-500, 15, ORANGE);

    //models texture
    DrawTexturePro(space3d.texture,
    Rectangle{ 0, 0, (float)space3d.texture.width, -(float)space3d.texture.height }, // Flipping Y-axis
    desc_window,
    Vector2{ 0, 0 },  
    0.0f,            
    WHITE);

    //3d window borders
    DrawRectangleLinesEx(desc_window, 3, ORANGE);
    

    //Description window
    DrawRectangleLinesEx(anim_window_title, 3, ORANGE);
    if(play_highl){
    DrawTextC(">BLASPHEMY IS", 890, float(screenHeight)-360, 20, ORANGE);
    DrawTextC(" EVERYWHERE.", 890, float(screenHeight)-340, 20, ORANGE);
    DrawTextC(">FIGHT THEM WITH", 890, float(screenHeight)-320, 20, ORANGE);
    DrawTextC(" THEIR OWN WEAPONS.", 890, float(screenHeight)-300, 20, ORANGE);
    DrawTextC(">DO NOT LOSE YOUR", 890, float(screenHeight)-280, 20, ORANGE);
    DrawTextC(" FAITH.", 890, float(screenHeight)-260, 20, ORANGE);
    DrawTextC("----------------", 890, float(screenHeight)-240, 20, ORANGE);
    DrawTextC("CHOOSE A MISSION", 890, float(screenHeight)-200, 20, ORANGE);
    DrawTextC("AND PLAY AGAINST", 890, float(screenHeight)-180, 20, ORANGE);
    DrawTextC("VARIOUS ENEMIES.", 890, float(screenHeight)-160, 20, ORANGE);
    }
    if(settings_highl){
    DrawTextC(">ADAPT TO THE", 890, float(screenHeight)-360, 20, ORANGE);
    DrawTextC(" BATTLEFIELD.", 890, float(screenHeight)-340, 20, ORANGE);
    DrawTextC(">CHANGE YOUR", 890, float(screenHeight)-320, 20, ORANGE);
    DrawTextC(" ENVIRONMENT.", 890, float(screenHeight)-300, 20, ORANGE);
    DrawTextC(">THINK SMART.", 890, float(screenHeight)-280, 20, ORANGE);
    DrawTextC("----------------", 890, float(screenHeight)-260, 20, ORANGE);
    DrawTextC("TWEAK SETTINGS", 890, float(screenHeight)-220, 20, ORANGE);
    DrawTextC("AND PREFERENCES ", 890, float(screenHeight)-200, 20, ORANGE);  
    }
    if(data_highl){
    DrawTextC(">SCAVENGE THEIR", 890, float(screenHeight)-360, 20, ORANGE);
    DrawTextC(" SYSTEMS.", 890, float(screenHeight)-340, 20, ORANGE);
    DrawTextC(">LEARN YOUR", 890, float(screenHeight)-320, 20, ORANGE);
    DrawTextC(" ENEMIES.", 890, float(screenHeight)-300, 20, ORANGE);
    DrawTextC(">BE AWARE.", 890, float(screenHeight)-280, 20, ORANGE);
    DrawTextC("----------------", 890, float(screenHeight)-260, 20, ORANGE);
    DrawTextC("DATA FRAGMENTS,", 890, float(screenHeight)-220, 20, ORANGE);
    DrawTextC("RECOVERED FROM", 890, float(screenHeight)-200, 20, ORANGE);  
    DrawTextC("ENEMIES.", 890, float(screenHeight)-180, 20, ORANGE);  
    }

}
