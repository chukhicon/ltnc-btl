#include "chukhi_character.h"


Character::Character()
{
    c_x=135;
    c_y=100;
    check=move_right;
}

void Character::CheckEvent(SDL_Event& e, Mix_Chunk *gJump)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_up;
                break;
            case SDLK_w:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_up;
                break;
			case SDLK_DOWN:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_down;
                break;
            case SDLK_s:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_down;
                break;
            case SDLK_LEFT:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_left;
                break;
            case SDLK_a:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_left;
                break;
            case SDLK_RIGHT:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_right;
                break;
            case SDLK_d:
                Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                check = move_right;
                break;
		}
	}
}

void Character::Move()
{
    c_x += stepX;
    c_y += stepY;
    if(check == move_up)
    {
        stepX = 0;
        stepY = -MOVE_Y;
    }
    if(check == move_down)
    {
        stepX = 0;
        stepY = MOVE_Y;
    }
    if(check == move_left)
    {
        stepX = -MOVE_X;
        stepY = 0;
    }
    if(check == move_right)
    {
        stepX = MOVE_X;
        stepY = 0;
    }
}



void Character::Render(SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
    gCharacterTexture.Render(c_x, c_y, gRenderer);
}


int Character::Getc_X()
{
    return c_x;
}

int Character::Getc_Y()
{
    return c_y;
}
