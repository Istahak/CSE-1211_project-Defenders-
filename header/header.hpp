#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

#define WINDOW_HEIGHT (800)
#define WINDOW_WIDTH (1400)
using namespace std;
SDL_Window *win = NULL;
SDL_Renderer *wrend = NULL;
string user_name, user_password;
int score = 0;
int start = 0;

// SDL_Surface *Enemies[10];
// SDL_Texture *Enemies_tex[10];

// A class to render an object

TTF_Font *font = TTF_OpenFont("font/game.ttf", 100);
SDL_Color colour = {255, 255, 255};

// Starts up SDL and creates window

enum MENU_OPTIONS
{
    FULL_EXIT,
    NEW_GAME,
    LEVELS,
    LEVEL_ONE,
    LEVEL_TWO,
    LOGIN_MENU,
    REGISTER_MENU,
    HELP_MENU,
    LOADING_SCREEN,
    SHOW_SCORE,
    M_HIGHSCORE,
    MENU,
    EXIT
};
extern MENU_OPTIONS curr_game = LEVEL_TWO;
void loadFromsurface(std::string path, SDL_Texture *mTex)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    mTex = SDL_CreateTextureFromSurface(wrend, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    win = SDL_CreateWindow("project window", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    wrend = SDL_CreateRenderer(win, -1, render_flags);
}
void load()
{
}
void close()
{
    SDL_DestroyRenderer(wrend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
}