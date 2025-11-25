#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    Empty,
    Player1,
    Player2
} SlotState;

typedef struct {
    uint8_t width;
    uint8_t height;
    SlotState* cells;
    SlotState currentPlayer;
} C4_Board;

C4_Board C4_Board_Create(uint8_t width, uint8_t height);
void C4_Board_Destroy(C4_Board* board);
SlotState C4_Board_GetSlot(C4_Board* board, uint8_t x, uint8_t y);
bool C4_Board_SetSlot(C4_Board* board, uint8_t x, uint8_t y, SlotState state);
// Returns true if valid move was made
bool C4_Board_DoMove(C4_Board* board, uint8_t inColumn);
void C4_Board_UpdateTestStr(C4_Board* board, char* buffer, size_t bufferSize);
SlotState C4_Board_GetWinner(C4_Board* board);