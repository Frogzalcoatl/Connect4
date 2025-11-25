#include "Connect4/ui/screens/game.h"
#include "Connect4/game/random.h"

C4_GameScreen* C4_GameScreen_Create(C4_Board* board, SDL_Renderer* renderer, TTF_Font* fontRegular, TTF_Font* fontBold) {
    if (!board || !renderer || !fontRegular || !fontBold) {
        return NULL;
    }
    C4_GameScreen* screen = calloc(1, sizeof(C4_GameScreen));
    if (!screen) {
        return NULL;
    }
    screen->board = board;
    screen->fontRegular = fontRegular;
    screen->fontBold = fontBold;
    screen->renderer = renderer;
    screen->testText = C4_TextUIElement_Create(screen->renderer, "", screen->fontRegular, (SDL_Color){255, 255, 255, 255}, 800.f);
    return screen;
}

void C4_GameScreen_Destroy(C4_GameScreen* screen) {
    if (!screen) {
        return;
    }
    C4_TextUIElement_Destroy(screen->testText);
    free(screen);
}

void C4_GameScreen_Draw(C4_GameScreen* screen) {
    C4_TextUIElement_Draw(screen->testText, screen->renderer);
}

void C4_GameScreen_TestStrUpdate(C4_GameScreen* screen) {
    char tempBuffer[100];
    C4_Board_UpdateTestStr(screen->board, tempBuffer, 100);
    C4_TextUIElement_ChangeStr(screen->testText, tempBuffer);
    C4_TextUIElement_Refresh(screen->testText, screen->renderer);
}

void C4_GameScreen_HandleKeyboardInput(C4_GameScreen* screen, int scancode) {
    // Temporary just for testing
    switch (scancode) {
        case SDL_SCANCODE_1: {
            C4_Board_DoMove(screen->board, 0);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
        case SDL_SCANCODE_2: {
            C4_Board_DoMove(screen->board, 1);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
        case SDL_SCANCODE_3: {
            C4_Board_DoMove(screen->board, 2);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
        case SDL_SCANCODE_4: {
            C4_Board_DoMove(screen->board, 3);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
        case SDL_SCANCODE_5: {
            C4_Board_DoMove(screen->board, 4);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
        case SDL_SCANCODE_6: {
            C4_Board_DoMove(screen->board, 5);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
        case SDL_SCANCODE_7: {
            C4_Board_DoMove(screen->board, 6);
            C4_GameScreen_TestStrUpdate(screen);
        }; break;
    }
}