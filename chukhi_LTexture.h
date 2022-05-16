#ifndef CHUKHI_LTEXTURE_H_
#define CHUKHI_LTEXTURE_H_

#include "chukhi_base.h"
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Deallocates texture
        void free();

        bool loadFromRenderedText(string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer *gRenderer);

        bool loadFromFile(string path, SDL_Renderer *gRenderer);

        void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip);

        int getWidth();

        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;

        int mHeight;
};

#endif // CHUKHI_LTEXTURE_H_
