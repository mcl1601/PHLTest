#include "Character.h"
// implement movement functions
static void MoveUp(Character* self, float speed) {
    self->y -= speed;
}

static void MoveDown(Character* self, float speed) {
    self->y += speed;
}

static void MoveLeft(Character* self, float speed) {
    self->x -= speed;
}

static void MoveRight(Character* self, float speed) {
    self->x += speed;
}

SDL_Texture* loadBmpTexture(SDL_Renderer* renderer, const char* bmpPath) {
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
Character CreateCharacter(SDL_Renderer* renderer, const char* imgPath, float x, float y, int width, int height) {
    Character newCharacter;
    newCharacter.x = x;
    newCharacter.y = y;
    newCharacter.w = width;
    newCharacter.h = height;
    newCharacter.texture = loadBmpTexture(renderer, imgPath);
    newCharacter.MoveUp = MoveUp;
    newCharacter.MoveDown = MoveDown;
    newCharacter.MoveLeft = MoveLeft;
    newCharacter.MoveRight = MoveRight;
    return newCharacter;
}

// clean up the texture
void FreeCharacter(Character* character) {
    if (character->texture) {
        SDL_DestroyTexture(character->texture);
    }
}
