#ifndef CHUKHI_CHARACTER_H_
#define CHUKHI_CHARACTER_H_
#include "chukhi_LTexture.h"
#include "chukhi_base.h"

class Character
{
public:

    int MOVE_X = MOVE_START_X, MOVE_Y = MOVE_START_Y;

    enum check_move{move_up=1, move_down=2, move_left=3, move_right=4};

    check_move check;

    int stepX = 0, stepY = 0 ;

    Character();

	void CheckEvent(SDL_Event& e, Mix_Chunk *gJump);

	void Move();



	void Render(SDL_Renderer *gRenderer, LTexture gCharacterTexture);



	int Getc_X();

	int Getc_Y();


private:
    int c_x, c_y;


};

#endif // CHUKHI_CHARACTER_H_
