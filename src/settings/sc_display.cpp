#include "sc_display.h"

Rectangle debug_mode_frame = {settings_screen.x+300,settings_screen.y+50,270,50};

void HandleSetDisplay() {
    multiple_choice("DEBUG MODE" ,debug_mode_frame, "OFF", "MID", "MAX", mousePos, debugMode);
}