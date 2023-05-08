#include <stdio.h>
#include <SDL.h>
#include "Character.h"
#include "NPC.h"

// define struct to hold movement key states
typedef struct {
    int up;
    int down;
    int left;
    int right;
} InputStates;

// define functions
void HandleKeyPress(SDL_Keycode key, SDL_Window* win, InputStates* states);
void HandleKeyUp(SDL_Keycode key, InputStates* states);
void HandleWindowEvents(SDL_Event e, SDL_Window* win, SDL_Renderer* rend);
void MovePlayer(Character* player, InputStates state);

int main(int argc, char* argv[]) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // define the window
    SDL_Window* window = SDL_CreateWindow("PHL Test",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // make sure the window created successfully 
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // define the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // check for successful renderer creation
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // set up variables
    SDL_Event event;
    SDL_bool running = SDL_TRUE;
    InputStates inputStates = { 0,0,0,0 };

    // define the player
    const char* playerTex = "Assets/Character.bmp";
    Character player = CreateCharacter(renderer, playerTex, 50.0, 50.0, 150, 300);

    // define NPC
    const char* npcTex = "Assets/NPC.bmp";
    NPC npc = CreateNPC(renderer, npcTex, 300.0, 50.0, 150, 150);

    // define the main loop
    while (running) {
        // poll for events
        while (SDL_PollEvent(&event)) {
            // analyze the event
            switch (event.type) {
            case SDL_QUIT:
                // quit from the main loop when the window is closed
                running = SDL_FALSE;
                break;

            case SDL_WINDOWEVENT:
                // handle window events
                HandleWindowEvents(event, window, renderer);
                break;

            case SDL_KEYDOWN:
                // handle when a key is pressed
                HandleKeyPress(event.key.keysym.sym, window, &inputStates);
                break;

            case SDL_KEYUP:
                // handle when a key is no longer pressed
                HandleKeyUp(event.key.keysym.sym, &inputStates);
                break;

            default:
                break;
            }
        }

        // Move the player if needed
        MovePlayer(&player, inputStates);

        // clear the screen
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        SDL_RenderClear(renderer);

        // render the character
        SDL_Rect charRect = { (int)player.x, (int)player.y, player.w, player.h };
        SDL_RenderCopy(renderer, player.texture, NULL, &charRect);

        // render NPC
        SDL_Rect npcRect = { (int)npc.x, (int)npc.y, npc.w, npc.h };
        SDL_RenderCopy(renderer, npc.texture, NULL, &npcRect);

        // draw to the screen
        SDL_RenderPresent(renderer);
    }

    // clean stuff up and quit
    FreeCharacter(&player);
    FreeNPC(&npc);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void HandleKeyPress(SDL_Keycode key, SDL_Window* win, InputStates* states) {
    // toggle fullscreen 
    if (key == SDLK_f) {
        // get the current window flag
        Uint32 windowFlags = SDL_GetWindowFlags(win);
        // check if we are fullscreen already
        if (windowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
            SDL_SetWindowFullscreen(win, 0);
        }
        else {
            SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }
    // set movement key states
    if (key == SDLK_d) states->right = 1;
    if (key == SDLK_s) states->down = 1;
    if (key == SDLK_a) states->left = 1;
    if (key == SDLK_w) states->up = 1;
}

void HandleKeyUp(SDL_Keycode key, InputStates* states) {
    // set movement key states
    if (key == SDLK_d) states->right = 0;
    if (key == SDLK_s) states->down = 0;
    if (key == SDLK_a) states->left = 0;
    if (key == SDLK_w) states->up = 0;
}

void HandleWindowEvents(SDL_Event e, SDL_Window* win, SDL_Renderer* rend) {
    // resize the viewport when the window changes size
    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
        SDL_Rect viewport;
        viewport.x = 0;
        viewport.y = 0;
        viewport.w = e.window.data1;
        viewport.h = e.window.data2;
        SDL_RenderSetViewport(rend, &viewport);
    }
}

void MovePlayer(Character* player, InputStates state) {
    // set movement speed
    float moveSpeed = 0.05;

    // move player along active axes
    if (state.up) player->MoveUp(player, moveSpeed);
    if (state.down) player->MoveDown(player, moveSpeed);
    if (state.left) player->MoveLeft(player, moveSpeed);
    if (state.right) player->MoveRight(player, moveSpeed);
}