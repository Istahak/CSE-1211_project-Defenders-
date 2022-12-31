// #include "header.hpp"

#include <SDL2/SDL_ttf.h>
SDL_Rect ball, powr, powr_2, disk, bg, bullet[5], enemy, enemy_health, enemy1, life, border, bar, score_board, score_menu_rect, final_score;
SDL_Texture *texball, *tex_bullet[5], *texdisk, *tex_enemy_health, *texEnemies[10][2], *texenemy1[2][2], *texbg, *texlife[6], *texborder, *texbar, *texscore_board, *score_menu_tex;
SDL_Texture *texfinal_score;
SDL_Texture *texpower[8];
void life_update()
{
    for (int i = 0; i < 6; i++)
    {
        string path = "image/life";
        int j = i + 1;
        string temp = "";
        while (j >= 1)
        {
            temp.push_back((j % 10) + '0');
            j /= 10;
        }
        reverse(temp.begin(), temp.end());
        path += temp;
        path += ".png";
        SDL_Surface *surface = IMG_Load(path.c_str());
        texlife[i] = SDL_CreateTextureFromSurface(wrend, surface);
        SDL_FreeSurface(surface);
    }
}
void loadmedia()
{

    // loadFromsurface("image/disk.png",texdisk);
    // loadFromsurface("image/ball.png",texball);
    SDL_Surface *surface = IMG_Load("image/bg1.png");
    texbg = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/disk.png");
    texdisk = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/ball.png");
    texball = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/border.png");
    texborder = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/bar.png");
    texbar = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/score_menu.png");
    score_menu_tex = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    for (int i = 0; i < 10; i++)
    {
        string path_1 = "image/enemy";
        string path_2 = "image/rev_enemy";
        int j = i + 1;
        string temp = "";
        while (j >= 1)
        {
            temp.push_back((j % 10) + '0');
            j /= 10;
        }
        reverse(temp.begin(), temp.end());
        path_1 += temp;
        path_2 += temp;
        path_1 += ".png";
        path_2 += ".png";
        surface = IMG_Load(path_1.c_str());
        texEnemies[i][0] = SDL_CreateTextureFromSurface(wrend, surface);
        SDL_FreeSurface(surface);
        surface = IMG_Load(path_2.c_str());
        texEnemies[i][1] = SDL_CreateTextureFromSurface(wrend, surface);
        SDL_FreeSurface(surface);
    }
    life_update();
    ball.h = 50;
    ball.w = 50;
    ball.x = WINDOW_WIDTH / 2;
    ball.y = WINDOW_HEIGHT / 2;

    disk.h = 130;
    disk.w = 130;
    disk.x = 20;
    disk.y = 580;

    bg.h = WINDOW_HEIGHT;
    bg.w = WINDOW_WIDTH;
    bg.x = 0;
    bg.y = 0;

    enemy.h = 150;
    enemy.w = 150;
    enemy.x = WINDOW_WIDTH / 4;
    enemy.y = WINDOW_HEIGHT / 12;

    life.h = 50;
    life.w = 50;
    life.x = 20;
    life.y = 20;

    border.h = WINDOW_HEIGHT * 0.75;
    border.w = WINDOW_WIDTH;
    border.x = 0;
    border.y = 150;

    bar.h = 30;
    bar.w = WINDOW_WIDTH / 4;
    bar.x = WINDOW_WIDTH / 2 - bar.w / 2;
    bar.y = WINDOW_HEIGHT - bar.h;

    score_menu_rect.h = WINDOW_HEIGHT;
    score_menu_rect.w = WINDOW_WIDTH;
    score_menu_rect.x = 0;
    score_menu_rect.y = 0;

    final_score.h = 70;
    final_score.w = 300;
    final_score.x = 725;
    final_score.y = 230;
    // final_score.h = WINDOW_HEIGHT;
    // final_score.w = WINDOW_WIDTH;
    // final_score.x = 0;
    // final_score.y = 0;
}
void load_level_one()
{
    SDL_Surface *surface = IMG_Load("image/bg2.png");
    texbg = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/disk.png");
    texdisk = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/ball.png");
    texball = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/border.png");
    texborder = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/score_menu.png");
    score_menu_tex = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/enemy_1.png");
    texenemy1[0][0] = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/rev_enemy_1.png");
    texenemy1[1][1] = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/enemy_health.png");
    tex_enemy_health = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    for (int i = 1; i <= 7; i++)
    {
        string path_1 = "image/power" + (string)to_string(i);
        path_1 += ".png";
        surface = IMG_Load(path_1.c_str());
        texpower[i] = SDL_CreateTextureFromSurface(wrend, surface);
        SDL_FreeSurface(surface);
    }
    life_update();
    ball.h = 50;
    ball.w = 50;
    ball.x = WINDOW_WIDTH / 2;
    ball.y = WINDOW_HEIGHT / 2;

    disk.h = 130;
    disk.w = 130;
    disk.x = 20;
    disk.y = 580;

    bg.h = WINDOW_HEIGHT;
    bg.w = WINDOW_WIDTH;
    bg.x = 0;
    bg.y = 0;

    enemy1.h = 150;
    enemy1.w = 120;
    enemy1.x = WINDOW_WIDTH / 4;
    enemy1.y = WINDOW_HEIGHT / 12;

    life.h = 50;
    life.w = 50;
    life.x = 20;
    life.y = 20;

    border.h = WINDOW_HEIGHT * 0.75;
    border.w = WINDOW_WIDTH;
    border.x = 0;
    border.y = 150;

    score_menu_rect.h = WINDOW_HEIGHT;
    score_menu_rect.w = WINDOW_WIDTH;
    score_menu_rect.x = 0;
    score_menu_rect.y = 0;

    final_score.h = 70;
    final_score.w = 300;
    final_score.x = 725;
    final_score.y = 230;

    enemy_health.h = 40;
    enemy_health.w = WINDOW_WIDTH;
    enemy_health.x = 0;
    enemy_health.y = WINDOW_HEIGHT - 40;

    powr.h = WINDOW_HEIGHT;
    powr.w = WINDOW_WIDTH / 12;
    powr.x = -500;
    powr.y = 0;

    powr_2.h = WINDOW_HEIGHT;
    powr_2.w = WINDOW_WIDTH / 12;
    powr_2.x = -500;
    powr_2.y = 0;
}
pair<bool, int> active_power;
void power()
{
    int x = rand() % 100;
    if (x == 1 && !active_power.first)
    {
        int temp = rand() % WINDOW_WIDTH;
        powr.x = temp;
        powr_2.x = temp;
        active_power.first = true;
    }
}
bool bullet_deactive[5];
void power_2()
{
    int x = rand() % 10;
    if (x == 1)
    {
        for (int i = 0; i < 5; ++i)
        {
            if (bullet_deactive[i])
                continue;
            bullet_deactive[i] = true;
            int temp = rand() % WINDOW_WIDTH;
            bullet[i].x = temp;
        }
    }
}

void load_level_two()
{
    SDL_Surface *surface = IMG_Load("image/bg6.png");
    texbg = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/disk.png");
    texdisk = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/ball.png");
    texball = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/border.png");
    texborder = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/score_menu.png");
    score_menu_tex = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/enemy_2.png");
    texenemy1[0][0] = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("image/rev_enemy_2.png");
    texenemy1[1][1] = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/enemy_health.png");
    tex_enemy_health = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    for (int i = 1; i < 5; i++)
    {
        surface = IMG_Load("image/bullet.png");
        tex_bullet[i] = SDL_CreateTextureFromSurface(wrend, surface);
        SDL_FreeSurface(surface);
    }
    life_update();
    ball.h = 50;
    ball.w = 50;
    ball.x = WINDOW_WIDTH / 2;
    ball.y = WINDOW_HEIGHT / 2;

    disk.h = 130;
    disk.w = 130;
    disk.x = 20;
    disk.y = 580;

    bg.h = WINDOW_HEIGHT;
    bg.w = WINDOW_WIDTH;
    bg.x = 0;
    bg.y = 0;

    enemy1.h = 150;
    enemy1.w = 120;
    enemy1.x = WINDOW_WIDTH / 4;
    enemy1.y = WINDOW_HEIGHT / 12;

    life.h = 50;
    life.w = 50;
    life.x = 20;
    life.y = 20;

    border.h = WINDOW_HEIGHT * 0.75;
    border.w = WINDOW_WIDTH;
    border.x = 0;
    border.y = 150;

    score_menu_rect.h = WINDOW_HEIGHT;
    score_menu_rect.w = WINDOW_WIDTH;
    score_menu_rect.x = 0;
    score_menu_rect.y = 0;

    final_score.h = 70;
    final_score.w = 300;
    final_score.x = 725;
    final_score.y = 230;

    enemy_health.h = 40;
    enemy_health.w = WINDOW_WIDTH;
    enemy_health.x = 0;
    enemy_health.y = WINDOW_HEIGHT - 40;

    powr.h = WINDOW_HEIGHT;
    powr.w = WINDOW_WIDTH / 12;
    powr.x = -500;
    powr.y = 0;
    for (int i = 0; i < 5; ++i)
    {
        bullet[i].h = 50;
        bullet[i].w = 50;
        bullet[i].x = 0;
        bullet[i].y = -bullet[i].h;
    }
}

void update_score_board()
{
    TTF_Font *font = TTF_OpenFont("font/game.ttf", 100);
    SDL_Color colour = {255, 255, 255};
    int j = score;
    string result = "Score : ";
    string temp = "";
    while (j >= 1)
    {
        temp.push_back((j % 10) + '0');
        j /= 10;
    }
    reverse(temp.begin(), temp.end());
    result += temp;
    SDL_Surface *score_surface = TTF_RenderText_Solid(font, result.c_str(), colour);
    texscore_board = SDL_CreateTextureFromSurface(wrend, score_surface);
    SDL_FreeSurface(score_surface);
    score_board.h = 60;
    score_board.w = result.size() * 20;
    score_board.x = WINDOW_WIDTH - score_board.w - 100;
    score_board.y = 20;
    SDL_RenderCopy(wrend, texscore_board, NULL, &score_board);
}
void Renderer_Update(int curr_enemy, int curr_life, int state)
{
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, texbg, NULL, &bg);
    SDL_RenderCopy(wrend, texball, NULL, &ball);
    SDL_RenderCopy(wrend, texEnemies[curr_enemy][state], NULL, &enemy);
    SDL_RenderCopy(wrend, texlife[curr_life], NULL, &life);
    SDL_RenderCopy(wrend, texdisk, NULL, &disk);
    SDL_RenderCopy(wrend, texborder, NULL, &border);
    SDL_RenderCopy(wrend, texbar, NULL, &bar);
    update_score_board();
    SDL_RenderPresent(wrend);
    SDL_Delay(1000 / 60);
}
void Renderer_Update_level_1(int curr_enemy, int curr_life, int state)
{
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, texbg, NULL, &bg);
    SDL_RenderCopy(wrend, texball, NULL, &ball);
    SDL_RenderCopy(wrend, texenemy1[state][state], NULL, &enemy1);
    SDL_RenderCopy(wrend, texlife[curr_life], NULL, &life);
    SDL_RenderCopy(wrend, texdisk, NULL, &disk);
    SDL_RenderCopy(wrend, texborder, NULL, &border);
    SDL_RenderCopy(wrend, tex_enemy_health, NULL, &enemy_health);
    if (active_power.first)
    {
        if (active_power.second >= 1)
        {
            powr.x = -500;
            SDL_RenderCopy(wrend, texpower[active_power.second], NULL, &powr_2);
        }
        else
            SDL_RenderCopy(wrend, texpower[active_power.second], NULL, &powr);
        active_power.second++;
        if (active_power.second == 8)
        {
            powr_2.x = -500;
            active_power.first = false;
            active_power.second = 0;
        }
    }
    update_score_board();
    SDL_RenderPresent(wrend);
    SDL_Delay(1000 / 60);
}
void Renderer_Update_level_2(int curr_enemy, int curr_life, int state)
{
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, texbg, NULL, &bg);
    SDL_RenderCopy(wrend, texball, NULL, &ball);
    SDL_RenderCopy(wrend, texenemy1[state][state], NULL, &enemy1);
    SDL_RenderCopy(wrend, texlife[curr_life], NULL, &life);
    SDL_RenderCopy(wrend, texborder, NULL, &border);
    SDL_RenderCopy(wrend, tex_enemy_health, NULL, &enemy_health);
    for (int i = 0; i < 5; ++i)
    {
        if (bullet_deactive)
            SDL_RenderCopy(wrend, tex_bullet[i], NULL, &bullet[i]);
    }
    SDL_RenderCopy(wrend, texdisk, NULL, &disk);
    update_score_board();
    SDL_RenderPresent(wrend);
    SDL_Delay(1000 / 60);
}
MENU_OPTIONS show_score_win()
{
    SDL_ShowCursor(SDL_ENABLE);
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, score_menu_tex, NULL, &score_menu_rect);
    score_board.x = 320;
    score_board.y = 230;
    score_board.w = 350;
    score_board.h = 100;
    SDL_RenderCopy(wrend, texscore_board, NULL, &score_board);
    SDL_RenderPresent(wrend);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            return EXIT;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            // cout << x << ' ' << y << endl;
            if (x > 346 && x < 628 && y > 486 && y < 579)
            {
                score = 0;
                curr_life = 0;
                curr_enemy = 9;
                return NEW_GAME;
            }
            else if (x > 786 && x < 1066 && y > 484 && y < 579)
            {
                Mix_ResumeMusic();
                score = 0;
                curr_life = 0;
                curr_enemy = 9;
                return MENU;
            }
        }
    }
    return curr_game;
    // return NEW_GAME;
}
MENU_OPTIONS move_bullet(SDL_Rect &ball)
{
    for (int i = 0; i < 5; ++i)
    {
        if (bullet_deactive[i])
        {
            if (check_collision(bullet[i], ball))
            {
                score = max(0, score - 100);
                curr_life++;
                // if (curr_life >= 6)
                // {
                //     ball.x = WINDOW_WIDTH / 2;
                //     ball.y = WINDOW_HEIGHT / 2;
                //     return show_score_win();
                // }
                bullet_deactive[i] = false;
            }
            bullet[i].y += 5;
            if (bullet[i].y > WINDOW_HEIGHT)
            {
                bullet[i].y = -bullet[i].h;
                bullet_deactive[i] = false;
            }
        }
    }
    return LEVEL_TWO;
}
