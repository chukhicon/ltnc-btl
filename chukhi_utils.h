#ifndef CHUKHI_UTILS_H_
#define CHUKHI_UTILS_H_

#include "chukhi_base.h"
#include "chukhi_LTexture.h"
#include "chukhi_button.h"
#include "chukhi_character.h"
#include "chukhi_enemy.h"
#include "chukhi_help.h"

bool Init();
bool LoadMedia();
void Close();

string GetHighScoreFromFile(string path);

void UpdateHighScore(string path,
	const int& score,
	const string& old_high_score);

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,
	SDL_Rect& gBackButton,
	Button& HelpButton,
	Button& BackButton,
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer *gRenderer,
	bool &Quit_game,
	Mix_Chunk *gClick);

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick);

void GenerateEnemy();

void GenerateHelp();

bool CheckInside();

bool CheckColission();

void XuLyDiem(int& health,
               Enemy enemy1, Enemy enemy2, Enemy enemy3,
               bool CheckColission );
#endif // CHUKHI_UTILS_H_
