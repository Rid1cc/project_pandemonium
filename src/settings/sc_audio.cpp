#include "sc_audio.h"
#include "../headers/globals.h"
#include "../headers/settings_vars.h"
#include <string>
#include <stdio.h>
#include <cmath>

using namespace std;
struct VolumeSlider {
    Rectangle slider;
    string text;
    float volume;
    const char* label;
};

void DrawVolumeSlider(VolumeSlider& volumeSlider) {
    volumeSlider.volume = DrawSlider(volumeSlider.slider, 0.0, 1.0, volumeSlider.volume, 2);
    DrawRectangleLinesEx(volumeSlider.slider, 3, primaryColor);
    volumeSlider.text = string(volumeSlider.label) + " " + floatToString(volumeSlider.volume * 100) + "%";
    DrawTextC(volumeSlider.text.c_str(), volumeSlider.slider.x - 280, volumeSlider.slider.y + 5, 20, primaryColor);

}

void HandleSetAudio() {
    VolumeSlider masterVolumeSlider = {{settings_screen.x + 300, settings_screen.y + 50, 270, 30}, "", master_volume, "MASTER VOLUME"};
    VolumeSlider musicVolumeSlider = {{settings_screen.x + 300, settings_screen.y + 100, 270, 30}, "", music_volume, "MUSIC VOLUME"};
    VolumeSlider sfxVolumeSlider = {{settings_screen.x + 300, settings_screen.y + 150, 270, 30}, "", sfx_volume, "SFX VOLUME"};

    DrawVolumeSlider(masterVolumeSlider);
    master_volume = masterVolumeSlider.volume;

    DrawVolumeSlider(musicVolumeSlider);
    music_volume = musicVolumeSlider.volume;

    DrawVolumeSlider(sfxVolumeSlider);
    sfx_volume = sfxVolumeSlider.volume;
}
