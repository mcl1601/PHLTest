#include "NPC.h"
SDL_Texture* loadBmpTextureNPC(SDL_Renderer* renderer, const char* bmpPath) {
    // load the image into a surface
    SDL_Surface* surface = SDL_LoadBMP(bmpPath);
    // make sure it loaded
    if (surface == NULL) {
        printf("Error loading .bmp image: %s\n", SDL_GetError());
        return NULL;
    }

    // make the texture and free the surface after
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    // make sure the texture created successfully
    if (texture == NULL) {
        printf("Error creating texture: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

// implement the "constructor"
NPC CreateNPC(SDL_Renderer* renderer, const char* imgPath, float x, float y, int width, int height) {
    NPC newNPC;
    newNPC.x = x;
    newNPC.y = y;
    newNPC.w = width;
    newNPC.h = height;
    newNPC.texture = loadBmpTextureNPC(renderer, imgPath);
    return newNPC;
}

// clean up the texture
void FreeNPC(NPC* npc) {
    if (npc->texture) {
        SDL_DestroyTexture(npc->texture);
    }
}
