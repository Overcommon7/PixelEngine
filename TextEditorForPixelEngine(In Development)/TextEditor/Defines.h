#pragma once
extern float DeltaTime;
extern float SCREEN_WIDTH, SCREEN_HEIGHT;
extern float WINDOW_SCALE;
extern const float MAX_WIDTH, MAX_HEIGHT;
extern float TEXT_SIZE;

#define DT DeltaTime
#define K_FONT_CANDARA "Candara"
#define K_TEXTURE_PLAYER "Player"
#define LETTERSPACING 1.f

extern unordered_map<string, Texture2D> textures;
extern unordered_map<string, Font> fonts;
