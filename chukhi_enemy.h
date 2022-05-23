#ifndef CHUKHI_ENEMY_H_
#define CHUKHI_ENEMY_H_
#include "chukhi_LTexture.h"
#include "chukhi_base.h"

class Enemy
{
public:
	Enemy();

	~Enemy();

	void LoadFromFile(string path, SDL_Renderer* gRenderer);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	void Move(int& vitriX);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posX, posY;

	int eWidth, eHeight;


	SDL_Texture *EnemyTexture;
};
#endif // CHUKHI_ENEMY_H_
