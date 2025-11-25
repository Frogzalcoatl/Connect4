#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Connect4/connect4.h"

int main(int argc, char *argv[]) {
    if (!Connect4_Init_Dependencies()) {
        return 1;
    }
    C4_Game* connect4 = C4_Game_Create(7, 6);
    if (connect4) {
        C4_Game_Run(connect4);
        C4_Game_Destroy(connect4);
    }
    Connect4_Quit_Dependencies();
    return 0;
}