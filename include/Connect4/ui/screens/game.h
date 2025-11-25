#pragma once
#include "Connect4/ui/text_element.h"
#include "Connect4/game/board.h"

typedef struct {
    // [Ref] Shared resources owned by C4_Game
    C4_Board* board;
    TTF_Font* fontRegular;
    TTF_Font* fontBold;
    SDL_Renderer* renderer;
    
    // [Owns] properties specific to this screen
    C4_TextUIElement* testText;
} C4_GameScreen;

C4_GameScreen* C4_GameScreen_Create(C4_Board* board, SDL_Renderer* renderer, TTF_Font* fontRegular, TTF_Font* fontBold);
void C4_GameScreen_Destroy(C4_GameScreen* screen);
void C4_GameScreen_Draw(C4_GameScreen* screen);
void C4_GameScreen_HandleKeyboardInput(C4_GameScreen* screen, int scancode);
void C4_GameScreen_TestStrUpdate(C4_GameScreen* screen);