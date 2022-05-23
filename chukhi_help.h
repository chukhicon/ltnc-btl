#ifndef CHUKHI_HELP_H_
#define CHUKHI_HELP_H_
#include "chukhi_base.h"
#include "chukhi_LTexture.h"

class Help
{
public:
	Help();

	~Help();

	void LoadFromFile(string path, SDL_Renderer* gRenderer);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posX, posY;

	int hWidth, hHeight;

	SDL_Texture *HelpTexture;
};
#endif // CHUKHI_HELP_H_
