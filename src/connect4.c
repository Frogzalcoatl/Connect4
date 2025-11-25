#include "Connect4/connect4.h"
#include <stdlib.h>
#include <time.h>

bool Connect4_Init_Dependencies() {
    srand(time(NULL));
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        // The error is inserted at %s
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    if (!TTF_Init()) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Connect4_Quit_Dependencies() {
    TTF_Quit();
    SDL_Quit();
}

C4_Game* C4_Game_Create(uint8_t boardWidth, uint8_t boardHeight) {
    C4_Game* game = calloc(1, sizeof(C4_Game));
    if (!game) {
        // Out of memory
        return NULL;
    }
    game->window = SDL_CreateWindow("Connect4", 1280, 720, 0);
    if (!game->window) {
        C4_Game_Destroy(game);
        return NULL;
    }
    game->renderer = SDL_CreateRenderer(game->window, NULL);
    if (!game->renderer) {
        C4_Game_Destroy(game);
        return NULL;
    }
    SDL_SetRenderVSync(game->renderer, 1);
    game->fontRegular = TTF_OpenFont("./assets/fonts/Monocraft.ttf", 32);
    if (!game->fontRegular) {
        C4_Game_Destroy(game);
        return NULL;
    }
    game->fontBold = TTF_OpenFont("./assets/fonts/Monocraft-Bold.ttf", 32);
    if (!game->fontBold) {
        C4_Game_Destroy(game);
        return NULL;
    }
    game->board = C4_Board_Create(boardWidth, boardHeight);
    game->gameScreen = C4_GameScreen_Create(&game->board, game->renderer, game->fontRegular, game->fontBold);
    game->currentScreen = GameScreen;
    if (!game->gameScreen) {
        C4_Game_Destroy(game);
        return NULL;
    }
    C4_GameScreen_TestStrUpdate(game->gameScreen);
    return game;
}

void C4_Game_Destroy(C4_Game* game) {
    if (!game) {
        return;
    }
    if (game->gameScreen) {
        C4_GameScreen_Destroy(game->gameScreen);
    }
    C4_Board_Destroy(&game->board);
    if (game->fontRegular) {
        TTF_CloseFont(game->fontRegular);
    }
    if (game->fontBold) {
        TTF_CloseFont(game->fontBold);
    }
    if (game->renderer) {
        SDL_DestroyRenderer(game->renderer);
    }
    if (game->window) {
        SDL_DestroyWindow(game->window);
    }
    free(game);
}

static void C4_Game_HandleKeyboardInput(C4_Game* game, int scancode) {
    switch (game->currentScreen) {
        case MenuScreen: {
            // Menu Screen keyboard input
        }; break;
        case GameScreen: {
            C4_GameScreen_HandleKeyboardInput(game->gameScreen, scancode);
        }; break;
        case SettingsScreen: {
            // Settings Screen keyboard input
        }; break;
    }
}

static void C4_Game_HandleEvents(C4_Game* game, SDL_Event* event, bool* running) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_EVENT_QUIT) {
            *running = false;
        } else if (event->type == SDL_EVENT_KEY_DOWN) {
            if (event->key.repeat) {
                continue;
            }
            C4_Game_HandleKeyboardInput(game, event->key.scancode);
        }
    }
}

static void C4_Game_DrawCurrentScreen(C4_Game* game) {
    switch (game->currentScreen) {
        case MenuScreen: {
            // Draw Menu Screen
        }; break;
        case GameScreen: {
            C4_GameScreen_Draw(game->gameScreen);
        }; break;
        case SettingsScreen: {
            // Draw Settings Screen
        }; break;
    }
}

void C4_Game_Run(C4_Game* game) {
    bool running = true;
    SDL_Event event;
    while (running) {
        C4_Game_HandleEvents(game, &event, &running);
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);
        C4_Game_DrawCurrentScreen(game);
        SDL_RenderPresent(game->renderer);
    }
}