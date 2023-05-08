#pragma once
#include <SDL.h>

// define the Character struct
typedef struct{
	float x;
	float y;
	int w;
	int h;
	SDL_Texture* texture;
	void (*MoveUp)(struct Character* self, float speed);
	void (*MoveDown)(struct Character* self, float speed);
	void (*MoveLeft)(struct Character* self, float speed);
	void (*MoveRight)(struct Character* self, float speed);
} Character;

// define character functions
Character CreateCharacter(SDL_Renderer* renderer, const char* imgPath, float x, float y, int width, int height);
void FreeCharacter(Character* character);
