#ifndef CHUKHI_BUTTON_H_
#define CHUKHI_BUTTON_H_

#include "chukhi_base.h"
#include "chukhi_LTexture.h"

class Button
{
public:
    ButtonSprite currentSprite;

    Button();

    Button(int x, int y);


    void SetPosition( int x, int y );

    void handleEvent( SDL_Event* e );

    bool IsInside(SDL_Event *e, int size);

    void Render(SDL_Renderer* gRenderer, LTexture gButtonTexture);

private:
    SDL_Point mPosition;
};

#endif // CHUKHI_BUTTON_H_
