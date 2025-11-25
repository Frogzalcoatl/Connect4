#include "Connect4/connect4.h"
#include <stdlib.h>

bool Connect4_Init_Dependencies() {
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
    game->window = SDL_CreateWindow("C4_Game", 1280, 720, 0);
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
    game->font_regular = TTF_OpenFont("./assets/fonts/Monocraft.ttf", 32);
    if (!game->font_regular) {
        C4_Game_Destroy(game);
        return NULL;
    }
    game->font_bold = TTF_OpenFont("./assets/fonts/Monocraft-Bold.ttf", 32);
    if (!game->font_bold) {
        C4_Game_Destroy(game);
        return NULL;
    }
    game->board = C4_Board_Create(boardWidth, boardHeight);
    game->testText = C4_TextUIElement_Create(game->renderer, "", game->font_regular, (SDL_Color){255, 255, 255, 255}, 800.f);
    return game;
}

void C4_Game_Destroy(C4_Game* game) {
    if (!game) {
        return;
    }
    C4_Board_Destroy(&game->board);
    if (game->testText) {
        C4_TextUIElement_Destroy(game->testText);
    }
    if (game->font_regular) {
        TTF_CloseFont(game->font_regular);
    }
    if (game->font_bold) {
        TTF_CloseFont(game->font_bold);
    }
    if (game->renderer) {
        SDL_DestroyRenderer(game->renderer);
    }
    if (game->window) {
        SDL_DestroyWindow(game->window);
    }
    free(game);
}

void C4_Game_Run(C4_Game* game) {
    C4_Board_SetSlot(&game->board, 0, game->board.height - 1, Player1);
    char tempBuffer[100];
    C4_Board_UpdateTestStr(&game->board, tempBuffer, 100);
    C4_TextUIElement_ChangeStr(game->testText, tempBuffer);
    C4_TextUIElement_Refresh(game->testText, game->renderer);
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);
        C4_TextUIElement_Draw(game->testText, game->renderer);
        SDL_RenderPresent(game->renderer);
    }
}