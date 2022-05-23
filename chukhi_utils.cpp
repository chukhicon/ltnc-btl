#include "chukhi_utils.h"

string GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path, ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(string path, const int& score, const string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
	SDL_Rect& gBackButton,
	Button& HelpButton,
	Button& BackButton,
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer *gRenderer,
	bool &Quit_game,
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, COMMON_BUTTON))
	{
		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_game = true;
						Close();
					}

					else if (BackButton.IsInside(e, COMMON_BUTTON))
					{
						if(e->type == SDL_MOUSEBUTTONDOWN)
						{
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer);

					//SDL_Rect currentClip_Back = gBackButton;
					//BackButton.Render( gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				}
				while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN);
			}
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, COMMON_BUTTON))
	{
		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void speedup(int& time, int& speed)
{
    if(time%20==0 && time>=20)
    {
        speed += /*SPEED_UP*/ 1;
    }
}
void GenerateEnemy(Enemy& enemy1, Enemy& enemy2, Enemy& enemy3, SDL_Renderer* gRenderer)
{
    enemy1.LoadFromFile("imgs/Enemy/Enemy1.png", gRenderer);
	enemy2.LoadFromFile("imgs/Enemy/Enemy2.png", gRenderer);
	enemy3.LoadFromFile("imgs/Enemy/Enemy3.png", gRenderer);
}

bool CheckInside(){return false;}
bool CheckColission(){return false;}

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event *e,
	SDL_Renderer *gRenderer,
	bool &Play_Again, bool& Return_Menu)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
					Return_Menu = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						Return_Menu = false;
						break;
					case SDLK_b:
						End_Game = true;
						Play_Again = false;
						Return_Menu = true;
						break;
					}
				}
			}

			gLoseTexture.Render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
}
