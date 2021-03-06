#include "chukhi_LTexture.h"

LTexture::LTexture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}
LTexture::~LTexture() {
    //free();
}
void LTexture::free() {
    SDL_DestroyTexture(mTexture);
    if (mTexture != nullptr) {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}
bool LTexture::LoadFromRenderedText(string textureText, TTF_Font* gFont,
                                    SDL_Color textColor,
                                    SDL_Renderer* gRenderer) {
    free();

    SDL_Surface* textSurface =
        TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",
               TTF_GetError());
    } else {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL) {
            printf(
                "Unable to create texture from rendered text! SDL Error: %s\n",
                SDL_GetError());
        } else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

bool LTexture::LoadFromFile(string path, SDL_Renderer* gRenderer) {
    free();

    SDL_Texture* tmpTexture = nullptr;

    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr) {
        LogError("Can not load image.", IMG_ERROR);
    } else {
        SDL_SetColorKey(tmpSurface, SDL_TRUE,
                        SDL_MapRGB(tmpSurface->format, 0, 255, 255));

        tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (tmpTexture == nullptr) {
            LogError("Can not create texture from surface.", SDL_ERROR);
        } else {
            mWidth = tmpSurface->w;
            mHeight = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }

    mTexture = tmpTexture;

    return mTexture != nullptr;
}

void LTexture::Render(int x, int y, SDL_Renderer* gRenderer) {
    SDL_Rect renderSpace = {x, y, mWidth, mHeight};
    int w;
    int h;
    SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);

    renderSpace.w = w;
    renderSpace.h = h;
    SDL_Rect clip = {0, 0, w, h};
    SDL_RenderCopy(gRenderer, mTexture, &clip, &renderSpace);
}

int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }
