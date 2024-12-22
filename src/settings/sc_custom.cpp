#include "sc_custom.h"

// ...existing code...

extern float DrawSlider(Rectangle sliderRect, float minValue, float maxValue, float value, int position);

float darkenFactor = 1.0f; // Default darken factor
Color pickedColor = WHITE; // Store the picked color

Color ColorPicker(Vector2 mousePos, Vector2 position, float width, float height) {
    Color selectedColor = WHITE;
    if (CheckCollisionPointRec(mousePos, (Rectangle){position.x, position.y, width, height})) {
        float hue = (mousePos.x - position.x) / width;
        float saturation = 1.0f - (mousePos.y - position.y) / height;
        selectedColor = ColorFromHSV(hue * 360.0f, saturation, 1.0f);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return selectedColor;
        }
    }

    for (int y = 0; y < height; y++) {
        float saturation = 1.0f - (float)y / height;
        for (int x = 0; x < width; x++) {
            float hue = (float)x / width;
            Color color = ColorFromHSV(hue * 360.0f, saturation, 1.0f);
            DrawPixel(position.x + x, position.y + y, color);
        }
    }

    DrawRectangleLines(position.x, position.y, width, height, BLACK);
    return selectedColor;
}

Color DarkenColor(Color color, float factor) {
    return (Color){ (unsigned char)(color.r * factor), (unsigned char)(color.g * factor), (unsigned char)(color.b * factor), color.a };
}

struct DarkenSlider {
    Rectangle slider;
    std::string text;
    float value;
    const char* label;
};

void DrawDarkenSlider(DarkenSlider& darkenSlider) {
    darkenSlider.value = DrawSlider(darkenSlider.slider, 0.0f, 1.0f, darkenSlider.value, 2);
    DrawRectangleLinesEx(darkenSlider.slider, 3, primaryColor);
    darkenSlider.text = std::string(darkenSlider.label) + " " + floatToString(Enround(darkenSlider.value * 100,2)) + "%";
    DrawText(darkenSlider.text.c_str(), darkenSlider.slider.x + darkenSlider.slider.width + 10, darkenSlider.slider.y + 5, 20, primaryColor);
}

void HandleSetCustom() {
    Vector2 pickerPosition = { settings_screen.x + 30, settings_screen.y + 20 };
    float pickerWidth = 300;
    float pickerHeight = 300; // Revert to rectangle shape
    Color highlightedColor = ColorPicker(mousePos, pickerPosition, pickerWidth, pickerHeight);
    DrawRectangleLinesEx({pickerPosition.x, pickerPosition.y, pickerWidth, pickerHeight}, 3, primaryColor);

    // Draw darken factor slider
    DarkenSlider darkenSlider = {{pickerPosition.x, pickerPosition.y + pickerHeight + 20, pickerWidth, 20}, "", darkenFactor, " Dim Factor"};
    DrawDarkenSlider(darkenSlider);
    darkenFactor = darkenSlider.value;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, (Rectangle){pickerPosition.x, pickerPosition.y, pickerWidth, pickerHeight})) {
        pickedColor = highlightedColor; // Save the picked color
    }

    displayColor = DarkenColor(pickedColor, darkenFactor); // Apply darken factor

    DrawTextC("System Colour", settings_screen.x + 350, settings_screen.y + 20, 20, primaryColor);
    
    DrawRectangle(settings_screen.x + 350, settings_screen.y + 60, 50, 50, displayColor);
}
