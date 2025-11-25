#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Connect4/game/board.h"
#include "Connect4/ui/text_element.h"

bool Connect4_Init_Dependencies();
void Connect4_Quit_Dependencies();

typedef struct {
    C4_Board board;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font_regular;
    TTF_Font* font_bold;
    C4_TextUIElement* testText;
} C4_Game;

C4_Game* C4_Game_Create(uint8_t boardWidth, uint8_t boardHeight);
void C4_Game_Destroy(C4_Game* game);
void C4_Game_Run(C4_Game* game);