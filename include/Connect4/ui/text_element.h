#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>

typedef struct {
    SDL_Color color;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_FRect destination;
    char str[100];
    float wrapWidth;
} C4_TextUIElement;

C4_TextUIElement* C4_TextUIElement_Create(SDL_Renderer* renderer, const char* str, TTF_Font* font, SDL_Color color, float wrapWidth);
void C4_TextUIElement_Destroy(C4_TextUIElement* element);
void C4_TextUIElement_ChangeStr(C4_TextUIElement* element, const char* newStr);
void C4_TextUIElement_Draw(C4_TextUIElement* element, SDL_Renderer* renderer);
void C4_TextUIElement_Refresh(C4_TextUIElement* element, SDL_Renderer* renderer);