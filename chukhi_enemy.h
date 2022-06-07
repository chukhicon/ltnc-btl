#ifndef CHUKHI_ENEMY_H_
#define CHUKHI_ENEMY_H_
#include "chukhi_LTexture.h"
#include "chukhi_base.h"

class Enemy
{
public:
	Enemy();

	Enemy(int _posX, int _posY, int _type, const string& path, SDL_Renderer* gRenderer, int r);

	~Enemy();

	void LoadFromFile(string path, SDL_Renderer* gRenderer);

	void Render(SDL_Renderer* gRenderer);

	void move();

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();

	void startInterval();

	int getExistTime();

	int GetType();
	int posX, posY;
	int type;
	SDL_Texture *EnemyTexture;
	int intervalStart;
	void free();
private:

	int eWidth, eHeight;

	int intervalEnd;

	int r;


};
#endif // CHUKHI_ENEMY_H_
