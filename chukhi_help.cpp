#include "chukhi_help.h"

Help::Help()
{
   posX = 0;
   posY = 0;
   hWidth = 0;
   hHeight = 0;
   HelpTexture = nullptr;
}

Help::~Help()
{
    posX = 0;
	posY = 0;

	hWidth = 0;
	hHeight = 0;

	if (HelpTexture != nullptr)
	{
		HelpTexture = nullptr;
	}
}

void Help::LoadFromFile(string path, SDL_Renderer* gRenderer)
{
    SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			LogError("Can not create texture from surface.", SDL_ERROR);
		}
		else
		{
			hWidth = tmpSurface->w;
			hHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	HelpTexture = tmpTexture;
}

void Help::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
    SDL_Rect renderSpace = { posX, posY, hWidth, hHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, HelpTexture, currentClip, &renderSpace);
}

int Help::GetPosX()
{
	return posX;
}

int Help::GetPosY()
{
	return posY;
}

int Help::GetWidth()
{
	return hWidth;
}

int Help::GetHeight()
{
	return hHeight;
}
