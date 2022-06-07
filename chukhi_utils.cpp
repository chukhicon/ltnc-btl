#include "chukhi_utils.h"

string GetHighScoreFromFile(string path) {
    fstream HighScoreFile;
    string highscore;

    HighScoreFile.open(path, ios::in);
    HighScoreFile >> highscore;

    return highscore;
}

void UpdateHighScore(string path, const int& score,
                     const string& old_high_score) {
    int oldHighScore = 0;
    fstream HighScoreFile;
    string newHighScore;
    stringstream ConvertToInt(old_high_score);

    HighScoreFile.open(path, ios::out);

    ConvertToInt >> oldHighScore;
    if (score > oldHighScore) {
        oldHighScore = score;
    }
    newHighScore = to_string(oldHighScore);

    HighScoreFile << newHighScore;
}

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu,
                      bool& Play, Mix_Chunk* gClick) {
    if (e->type == SDL_QUIT) {
        QuitMenu = true;
    }

    if (PlayButton.IsInside(e, COMMON_BUTTON)) {
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            Play = true;
            QuitMenu = true;
            Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
        }
    } else {
        PlayButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleHelpButton(SDL_Event* e, SDL_Rect& gBackButton, Button& HelpButton,
                      Button& BackButton, LTexture gInstructionTexture,
                      LTexture gBackButtonTexture, SDL_Renderer* gRenderer,
                      bool& Quit_game, Mix_Chunk* gClick) {
    if (HelpButton.IsInside(e, COMMON_BUTTON)) {
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

            bool ReadDone = false;
            while (!ReadDone) {
                do {
                    if (e->type == SDL_QUIT) {
                        ReadDone = true;
                        Quit_game = true;
                        Close();
                    }

                    else if (BackButton.IsInside(e, COMMON_BUTTON)) {
                        if (e->type == SDL_MOUSEBUTTONDOWN) {
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            Mix_PlayChannel(MIX_CHANNEL, gClick,
                                            NOT_REPEATITIVE);
                            ReadDone = true;
                        }
                    } else {
                        BackButton.currentSprite = BUTTON_MOUSE_OUT;
                    }

                    gInstructionTexture.Render(0, 0, gRenderer);

                    SDL_RenderPresent(gRenderer);
                } while (SDL_PollEvent(e) != 0 &&
                         e->type == SDL_MOUSEBUTTONDOWN);
            }
        }
    } else {
        HelpButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit,
                      Mix_Chunk* gClick) {
    if (ExitButton.IsInside(e, COMMON_BUTTON)) {
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            Quit = true;
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
        }
    } else {
        ExitButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}
void GenerateEnemy(Enemy& enemy1, Enemy& enemy2, Enemy& enemy3,
                   SDL_Renderer* gRenderer) {
    enemy1.LoadFromFile("imgs/Enemy/Enemy1.png", gRenderer);
    enemy2.LoadFromFile("imgs/Enemy/Enemy2.png", gRenderer);
    enemy3.LoadFromFile("imgs/Enemy/Enemy3.png", gRenderer);
}

void GenerateHelp(Help& help1, Help& help2, SDL_Renderer* gRenderer) {
    help1.LoadFromFile("imgs/Help/Help1.png", gRenderer);
    help2.LoadFromFile("imgs/Help/Help2.png", gRenderer);
}

bool CheckInside(Character character, LTexture char_img, const int CHIEU_DAI,
                 const int CHIEU_RONG) {
    return (character.Getc_X() >= 0 && character.Getc_Y() >= 0 &&
            character.Getc_X() + char_img.getWidth() < CHIEU_DAI &&
            character.Getc_Y() + char_img.getHeight() < CHIEU_RONG);
}

bool CheckColission(Character character, LTexture char_img, Enemy enemy) {
    int leftChar, leftEnem;
    int rightChar, rightEnem;
    int topChar, topEnem;
    int bottomChar, bottomEnem;

    leftChar = character.Getc_X();
    rightChar = character.Getc_X() + char_img.getWidth();
    topChar = character.Getc_Y();
    bottomChar = character.Getc_Y() + char_img.getHeight();

    leftEnem = enemy.GetPosX();
    rightEnem = enemy.GetPosX() + enemy.GetWidth();
    topEnem = enemy.GetPosY();
    bottomEnem = enemy.GetPosY() + enemy.GetHeight();
    if (bottomChar <= topEnem) {
        return false;
    }

    if (topChar >= bottomEnem) {
        return false;
    }

    if (rightChar <= leftEnem) {
        return false;
    }

    if (leftChar >= rightEnem) {
        return false;
    }

    return true;
}
bool CheckEnemyColission(Enemy enemy1, Enemy enemy2){
    int leftEnem1, leftEnem2;
    int rightEnem1, rightEnem2;
    int topEnem1, topEnem2;
    int bottomEnem1, bottomEnem2;

    leftEnem1 = enemy1.GetPosX();
    rightEnem1 = enemy1.GetPosX() + enemy1.GetWidth();
    topEnem1 = enemy1.GetPosY();
    bottomEnem1 = enemy1.GetPosY() + enemy1.GetHeight();

    leftEnem2 = enemy2.GetPosX();
    rightEnem2 = enemy2.GetPosX() + enemy2.GetWidth();
    topEnem2 = enemy2.GetPosY();
    bottomEnem2 = enemy2.GetPosY() + enemy2.GetHeight();
    if (bottomEnem1 <= topEnem2) {
        return false;
    }

    if (topEnem1 >= bottomEnem2) {
        return false;
    }

    if (rightEnem1 <= leftEnem2) {
        return false;
    }

    if (leftEnem1 >= rightEnem2) {
        return false;
    }

    return true;
}
void DrawPlayerScore(LTexture gTextTexture, LTexture gScoreTexture,
                     SDL_Color textColor, SDL_Renderer* gRenderer,
                     TTF_Font* gFont, const int& score) {
    gTextTexture.Render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
    if (gScoreTexture.LoadFromRenderedText(to_string(score), gFont, textColor,
                                           gRenderer)) {
        gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
    }
}

void DrawPlayerHighScore(LTexture gTextTexture, LTexture gHighScoreTexture,
                         SDL_Color textColor, SDL_Renderer* gRenderer,
                         TTF_Font* gFont, const string& HighScore) {
    gTextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
    if (gHighScoreTexture.LoadFromRenderedText(HighScore, gFont, textColor,
                                               gRenderer)) {
        gHighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
    }
}

void DrawPlayerHeath(LTexture gTextTexture, LTexture gHeathTexture,
                     SDL_Color textColor, SDL_Renderer* gRenderer,
                     TTF_Font* gFont, const int& Heath) {
    gTextTexture.Render(TEXT_3_POSX, TEXT_3_POSY, gRenderer);
    if (gHeathTexture.LoadFromRenderedText(to_string(Heath), gFont, textColor,
                                           gRenderer)) {
        gHeathTexture.Render(HEATH_POSX, HEATH_POSY, gRenderer);
    }
}



void DrawPlayerYourScore(LTexture gTextTexture, LTexture gYourScoreTexture,
                         SDL_Color textColor, SDL_Renderer* gRenderer,
                         TTF_Font* gFont, const int& YourScore) {
    gTextTexture.Render(TEXT_5_POSX, TEXT_5_POSY, gRenderer);
    if (gYourScoreTexture.LoadFromRenderedText(to_string(YourScore), gFont,
                                               textColor, gRenderer)) {
        gYourScoreTexture.Render(YOUR_SCORE_POSX, YOUR_SCORE_POSY, gRenderer);
    }
}

void DrawPlayerYourHighScore(LTexture gTextTexture,
                             LTexture gYourHighScoreTexture,
                             SDL_Color textColor, SDL_Renderer* gRenderer,
                             TTF_Font* gFont, const int& YourScore) {
    gTextTexture.Render(TEXT_5_POSX, TEXT_5_POSY, gRenderer);
    if (gYourHighScoreTexture.LoadFromRenderedText(to_string(YourScore), gFont,
                                                   textColor, gRenderer)) {
        gYourHighScoreTexture.Render(YOUR_SCORE_POSX, YOUR_SCORE_POSY,
                                     gRenderer);
    }
}

void DrawEndGameSelection(LTexture gLoseTexture, LTexture gText5Texture,
                          LTexture gText6Texture, LTexture gYourScoreTexture,
                          SDL_Event* e, SDL_Renderer* gRenderer,
                          SDL_Color textcolor, TTF_Font* gFont,
                          bool& Play_Again, bool& Return_Menu, bool& Quit_Menu,
                          const int& YourScore, const string& highscore, Mix_Music* gMenuMusic) {
    if (Play_Again) {
        bool End_Game = false;
        while (!End_Game) {
            while (SDL_PollEvent(e) != 0) {
                if (e->type == SDL_QUIT) {
                    Play_Again = false;
                    Return_Menu = false;
                    return;
                }

                if (e->type == SDL_KEYDOWN) {
                    switch (e->key.keysym.sym) {
                        case SDLK_SPACE:
                            End_Game = true;
                            Return_Menu = false;
                            Play_Again = true;
                            break;
                        case SDLK_b:
                            End_Game = true;
                            Play_Again = false;
                            Return_Menu = true;
                            Quit_Menu = false;
                            Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
                            break;
                    }
                }
            }

            gLoseTexture.Render(0, 0, gRenderer);
            int Highscore = stoi(highscore, nullptr, 10);
            if (YourScore > Highscore) {
                DrawPlayerYourHighScore(gText6Texture, gYourScoreTexture,
                                        textcolor, gRenderer,
                                        gFont, YourScore);
            }
            else{
                DrawPlayerYourScore(gText5Texture, gYourScoreTexture, textcolor,
                                    gRenderer, gFont, YourScore);
            }
            
            SDL_RenderPresent(gRenderer);
        }
    }
}
