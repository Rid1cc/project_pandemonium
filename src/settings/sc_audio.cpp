#include "sc_audio.h"
#include "../headers/globals.h"
#include "../headers/settings_vars.h"
#include <string>
#include <stdio.h>
#include <cmath>

using namespace std;
Rectangle volume_master_slider = {settings_screen.x+300,settings_screen.y+50,270,30};
Rectangle volume_music_slider = {settings_screen.x+300,settings_screen.y+100,270,30};
Rectangle volume_sfx_slider = {settings_screen.x+300,settings_screen.y+150,270,30};

string volume_master_text;
string volume_music_text;
string volume_sfx_text;

void HandleSetAudio(){
   //Master Volume
   DrawTextC(volume_master_text.c_str(), volume_master_slider.x-280, volume_master_slider.y+5, 20, ORANGE);
   master_volume = DrawSlider(volume_master_slider, 0.0, 1.0, master_volume, 2);
   DrawRectangleLinesEx(volume_master_slider, 3, ORANGE);
   volume_master_text = "MASTER VOLUME " + floatToString(master_volume * 100) + "%";

   //Music Volume
   DrawTextC(volume_music_text.c_str(), volume_music_slider.x-280, volume_music_slider.y+5, 20, ORANGE);
   music_volume = DrawSlider(volume_music_slider, 0.0, 1.0, music_volume, 2);
   DrawRectangleLinesEx(volume_music_slider, 3, ORANGE);
   volume_music_text = "MUSIC VOLUME " + floatToString(music_volume * 100) + "%";

   //SFX Volume
   DrawTextC(volume_sfx_text.c_str(), volume_sfx_slider.x-280, volume_sfx_slider.y+5, 20, ORANGE);
   sfx_volume = DrawSlider(volume_sfx_slider, 0.0, 1.0, sfx_volume, 2);
   DrawRectangleLinesEx(volume_sfx_slider, 3, ORANGE);
   volume_sfx_text = "SFX VOLUME " + floatToString(sfx_volume * 100) + "%";
};
