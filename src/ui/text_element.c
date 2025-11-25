#include "Connect4/ui/text_element.h"
#include <stdlib.h>
#include <string.h>

C4_TextUIElement* C4_TextUIElement_Create(SDL_Renderer* renderer, const char* str, TTF_Font* font, SDL_Color color, float wrapWidth) {
    if (!font) {
        return NULL;
    }
    C4_TextUIElement* element = calloc(1, sizeof(C4_TextUIElement));
    if (!element) {
        return NULL;
    }
    element->font = font;
    element->destination = (SDL_FRect){0, 0, 800.f, 0.f};
    element->color = color;
    element->wrapWidth = wrapWidth;
    C4_TextUIElement_ChangeStr(element, str);
    C4_TextUIElement_Refresh(element, renderer);
    return element;
}

void C4_TextUIElement_Destroy(C4_TextUIElement* element) {
    SDL_DestroyTexture(element->texture);
    free(element);
}

void C4_TextUIElement_Refresh(C4_TextUIElement* element, SDL_Renderer* renderer) {
    SDL_DestroyTexture(element->texture);
    SDL_Surface* tempSurface = TTF_RenderText_Blended_Wrapped(element->font, element->str, 0, element->color, element->wrapWidth);
    if (tempSurface) {
        element->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        element->destination.w = (float)tempSurface->w;
        element->destination.h = (float)tempSurface->h;
        SDL_DestroySurface(tempSurface);
    } else {
        element->destination.w = 0;
        element->destination.h = 0;
    }
}

void C4_TextUIElement_ChangeStr(C4_TextUIElement* element, const char* newStr) {
    size_t totalSize = sizeof(element->str) / sizeof(element->str[0]);
    snprintf(element->str, totalSize, "%s", newStr);
}

void C4_TextUIElement_Draw(C4_TextUIElement* element, SDL_Renderer* renderer) {
    if (!element->texture || !renderer) {
        return;
    }
    SDL_RenderTexture(renderer, element->texture, NULL, &element->destination);
}