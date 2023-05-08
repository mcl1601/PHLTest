#pragma once
#include <SDL.h>

// define the NPC struct
typedef struct {
	float x;
	float y;
	int w;
	int h;
	SDL_Texture* texture;
} NPC;

// define NPC functions
NPC CreateNPC(SDL_Renderer* renderer, const char* imgPath, float x, float y, int width, int height);
void FreeNPC(NPC* npc);