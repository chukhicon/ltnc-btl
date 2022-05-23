#ifndef CHUKHI_LTEXTURE_H_
#define CHUKHI_LTEXTURE_H_

#include "chukhi_base.h"

class LTexture
{
    public:
        LTexture();

        ~LTexture();

        void free();

        bool LoadFromRenderedText(string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer *gRenderer);

        bool LoadFromFile(string path, SDL_Renderer *gRenderer);

        void Render(int x, int y, SDL_Renderer* gRenderer);

        int getWidth();

        int getHeight();

    private:
        SDL_Texture* mTexture;

        int mWidth;

        int mHeight;
};

#endif // CHUKHI_LTEXTURE_H_
