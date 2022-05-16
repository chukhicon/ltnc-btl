#ifndef CHUKHI_UTILS_H_
#define CHUKHI_UTILS_H_

#include "chukhi_base.h"
#include "chukhi_button.h"
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

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick);
#endif // CHUKHI_UTILS_H_
