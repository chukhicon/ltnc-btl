#include "chukhi_enemy.h"
Enemy::Enemy() {
    posX = 0;
    posY = 0;
    eWidth = 0;
    eHeight = 0;
    type = 0;
    r = 0;
}

Enemy::Enemy(int _posX, int _posY, int _type, const string& path,
             SDL_Renderer* gRenderer, int _r) {
    posX = _posX;
    posY = _posY;
    LoadFromFile(path, gRenderer);
    type = _type;
    r=_r;
}
Enemy::~Enemy() {
    
}
void Enemy::LoadFromFile(std::string path, SDL_Renderer* gRenderer) {
    SDL_Texture* tmpTexture = nullptr;

    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr) {
        LogError("Can not load image.", IMG_ERROR);
    } else {
        SDL_SetColorKey(tmpSurface, SDL_TRUE,
                        SDL_MapRGB(tmpSurface->format, 0, 255, 255));

        tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (tmpTexture == nullptr) {
            LogError("Can not create texture from surface.", SDL_ERROR);
        } else {
            eWidth = tmpSurface->w;
            eHeight = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }

    EnemyTexture = tmpTexture;
}

void Enemy::Render(SDL_Renderer* gRenderer) {
    SDL_Rect renderSpace = {posX, posY, eWidth, eHeight};
    int w, h;
    SDL_QueryTexture(EnemyTexture, NULL, NULL, &w, &h);
    renderSpace.w = w;
    renderSpace.h = h;
    SDL_Rect clip = {0, 0, w, h};
    SDL_RenderCopy(gRenderer, EnemyTexture, &clip, &renderSpace);
}

void Enemy::move(){
    if(r==0 && type == 3)
    {
        posX+=MOVE_ENEMY_X;
    }
    if(r==1 && type == 3)
    {
        posX-=MOVE_ENEMY_X;
    }
    if(r==2 && type == 3)
    {
        posY+=MOVE_ENEMY_Y;
    }
    if(r==3 && type == 3)
    {
        posY-=MOVE_ENEMY_Y;
    }   
}

void Enemy::startInterval() { intervalStart = SDL_GetTicks(); }

void Enemy::free(){
    if (EnemyTexture) {
        SDL_DestroyTexture(EnemyTexture);
    }
}

int Enemy::getExistTime() {
    intervalEnd = SDL_GetTicks();
    return intervalEnd - intervalStart;
}

int Enemy::GetPosX() { return posX; }

int Enemy::GetPosY() { return posY; }

int Enemy::GetWidth() { return eWidth; }

int Enemy::GetHeight() { return eHeight; }

int Enemy::GetType() { return type; }
