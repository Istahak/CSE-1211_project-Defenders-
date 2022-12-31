#include <SDL2/SDL.h>
#include <bits/stdc++.h>
SDL_Rect menubg, level_show, level, name_Rect, pass_Rect, reg, register_bg, log_in_bg, log_in, newgame, highscore, help, quitgame, quitbg, music_button;
SDL_Texture *texmenubg, *tex_level_show, *tex_level, *tex_level_bg, *tex_help, *tex_error, *tex_name, *tex_register, *tex_pass, *tex_register_bg, *tex_log_in_bg, *tex_log_in, *texnewgame, *texhighscore, *texhelp, *texquitgame, *texquitbg, *tex_music_button[2];
int music_state = 0;
vector<string> names;
vector<string> passwords;
void load_menu()
{
    SDL_Surface *surface = IMG_Load("image/men.png");
    texmenubg = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/new_game.png");
    texnewgame = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/levels.png");
    tex_level = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/high_scores.png");
    texhighscore = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/help_.png");
    texhelp = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/quit_game.png");
    texquitgame = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/level_menu.png");
    tex_level_bg = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/music_button.png");
    tex_music_button[0] = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/music_button2.png");
    tex_music_button[1] = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/login.png");
    tex_log_in = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("image/register.png");
    tex_register = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);

    menubg.h = WINDOW_HEIGHT;
    menubg.w = WINDOW_WIDTH;
    menubg.x = 0;
    menubg.y = 0;

    newgame.h = 100;
    newgame.w = 250;
    newgame.x = WINDOW_WIDTH / 2 - newgame.w / 2;
    newgame.y = WINDOW_HEIGHT / 2 - 220;

    level.h = 100;
    level.w = 250;
    level.x = WINDOW_WIDTH / 2 - newgame.w / 2;
    level.y = WINDOW_HEIGHT / 2 - 110;

    highscore.h = 100;
    highscore.w = 250;
    highscore.x = WINDOW_WIDTH / 2 - newgame.w / 2;
    highscore.y = WINDOW_HEIGHT / 2;

    help.h = 100;
    help.w = 250;
    help.x = WINDOW_WIDTH / 2 - newgame.w / 2;
    help.y = WINDOW_HEIGHT / 2 + 110;

    quitgame.h = 100;
    quitgame.w = 250;
    quitgame.x = WINDOW_WIDTH / 2 - newgame.w / 2;
    quitgame.y = WINDOW_HEIGHT / 2 + 220;

    music_button.h = 80;
    music_button.w = 80;
    music_button.x = WINDOW_WIDTH - 1.5 * music_button.w;
    music_button.y = music_button.h / 2;

    reg.h = 70;
    reg.w = 70;
    reg.x = WINDOW_WIDTH - 2.85 * reg.w;
    reg.y = reg.h / 2 + 10;

    log_in.h = 70;
    log_in.w = 70;
    log_in.x = WINDOW_WIDTH - 4.2 * log_in.w;
    log_in.y = log_in.h / 2 + 10;

    log_in_bg.w = WINDOW_WIDTH;
    log_in_bg.h = WINDOW_HEIGHT;
    log_in_bg.x = 0;
    log_in_bg.y = 0;

    level_show.w = 70;
    level_show.h = 140;
    level_show.x = (WINDOW_WIDTH - level_show.w) / 2;
    level_show.y = (WINDOW_HEIGHT - level_show.h) / 2;
}
MENU_OPTIONS write_on_file(char path[], string nam, string pass, MENU_OPTIONS res)
{
    FILE *fptr = fopen(path, "a");
    // cout << nam << ' ' << pass << endl;
    for (auto ch : nam)
        fprintf(fptr, "%c", ch);
    for (auto ch : pass)
        fprintf(fptr, "%c", ch);
    fclose(fptr);
    return res;
}
bool search(string name, string pass)
{
    string curr = name + pass;
    FILE *fptr = fopen("database.txt", "r");
    char temp[100] = "";
    while (!feof(fptr))
    {
        fscanf(fptr, "%s", temp);

        int sz1 = 0;
        int sz2 = curr.size();
        while (temp[sz1++])
            ;
        if (sz1 != sz2)
            continue;
        bool flag = false;
        for (int i = 0; i < sz1 - 1; ++i)
        {
            if (temp[i] != curr[i + 1])
            {
                flag = true;
            }
        }
        if (flag)
            continue;
        fclose(fptr);
        return true;
    }
    fclose(fptr);
    return false;
}
MENU_OPTIONS check(SDL_Event &event)
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            return FULL_EXIT;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x > (WINDOW_WIDTH / 2 - newgame.w / 2) && x < WINDOW_WIDTH / 2 + newgame.w / 2)
            {
                if (y > newgame.y && y < newgame.y + newgame.h)
                {
                    Mix_PauseMusic();
                    sound_effect("music/change_tab.wav");
                    return NEW_GAME;
                }
                else if (y > level.y && y < level.y + level.h)
                {
                    Mix_PauseMusic();
                    sound_effect("music/change_tab.wav");
                    return LEVELS;
                }
                else if (y > highscore.y && y < highscore.y + highscore.h)
                {
                    Mix_PauseMusic();
                    sound_effect("music/change_tab.wav");
                    return SHOW_SCORE;
                }
                else if (y > help.y && y < help.y + help.h)
                {
                    Mix_PauseMusic();
                    sound_effect("music/change_tab.wav");
                    return HELP_MENU;
                }
                else if (y > quitgame.y && y < quitgame.y + quitgame.h)
                {
                    Mix_PauseMusic();
                    sound_effect("music/change_tab.wav");
                    return FULL_EXIT;
                }
            }
            if (x > log_in.x && x < log_in.x + log_in.w && y > log_in.y && y < log_in.y + log_in.h)
            {
                sound_effect("music/change_tab.wav");
                return LOGIN_MENU;
            }
            if (x > reg.x && x < reg.x + reg.w && y > reg.y && y < reg.y + reg.h)
            {
                sound_effect("music/change_tab.wav");
                return REGISTER_MENU;
            }
            if (x > music_button.x && x < music_button.x + music_button.w && y > music_button.y && y < music_button.y + music_button.h)
            {
                music_state ^= 1;
                if (music_state)
                    Mix_PauseMusic();
                else
                    Mix_ResumeMusic();
            }
        }
    }
    return MENU;
}
MENU_OPTIONS quitmenu()
{
    SDL_Surface *qbg_surface = IMG_Load("image/quitmenu.png");
    texquitbg = SDL_CreateTextureFromSurface(wrend, qbg_surface);
    SDL_FreeSurface(qbg_surface);
    quitbg.w = WINDOW_WIDTH;
    quitbg.h = WINDOW_HEIGHT;
    quitbg.x = 0;
    quitbg.y = 0;
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, texquitbg, NULL, &quitbg);
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
            if (x > 386 && x < 600 && y > 450 && y < 550)
            {
                Mix_PauseMusic();
                sound_effect("music/change_tab.wav");
                SDL_Delay(300);
                return EXIT;
            }
            else if (x > 745 && x < 950 && y > 450 && y < 550)
            {
                sound_effect("music/change_tab.wav");
                return MENU;
            }
        }
    }
    return FULL_EXIT;
}
MENU_OPTIONS password_print(int type)
{
    string password = " ";
    string temp = "";
    SDL_Event e;

    bool rendertext = true;
    bool quit = false;
    ;
    SDL_StartTextInput();

    while (rendertext)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            if (e.type == SDL_TEXTINPUT)
            {
                if (e.text.text[0] != ' ')
                {
                    password.push_back('*');
                    temp.push_back(e.text.text[0]);
                }
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (password.size() > 1)
                        password.pop_back();
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    rendertext = false;
                }
            }
        }
        user_password = temp;
        TTF_Font *font = TTF_OpenFont("font/game.ttf", 100);
        SDL_Color colour = {255, 255, 255};
        SDL_Surface *surf = TTF_RenderText_Solid(font, password.c_str(), colour);
        tex_pass = SDL_CreateTextureFromSurface(wrend, surf);
        SDL_FreeSurface(surf);
        pass_Rect.h = 80;
        pass_Rect.w = password.size() * 30;
        pass_Rect.x = 700;
        pass_Rect.y = 300;
        SDL_Surface *log_in_surface = IMG_Load("image/log_in_bg_2.png");
        tex_log_in_bg = SDL_CreateTextureFromSurface(wrend, log_in_surface);
        SDL_FreeSurface(log_in_surface);
        SDL_RenderClear(wrend);
        SDL_RenderCopy(wrend, tex_log_in_bg, NULL, &log_in_bg);
        SDL_RenderCopy(wrend, tex_pass, NULL, &pass_Rect);
        SDL_RenderPresent(wrend);
    }
    SDL_StopTextInput();
    if (type == 1)
    {
        passwords.push_back(temp);
    }
    return MENU;
}
MENU_OPTIONS nameprint(int type)
{
    string name = " ";
    SDL_Event e;

    bool rendertext = true;
    bool quit = false;
    SDL_StartTextInput();

    while (rendertext)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            if (e.type == SDL_TEXTINPUT)
            {
                if (e.text.text[0] != ' ')
                {
                    name.push_back(e.text.text[0]);
                }
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (name.size() > 1)
                        name.pop_back();
                }
                else if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    rendertext = false;
                }
            }
        }
        if (rendertext == false)
            break;
        user_name = name;
        TTF_Font *font = TTF_OpenFont("font/game.ttf", 100);
        SDL_Color colour = {255, 255, 255};
        SDL_Surface *surf = TTF_RenderText_Solid(font, name.c_str(), colour);
        tex_name = SDL_CreateTextureFromSurface(wrend, surf);
        SDL_FreeSurface(surf);
        name_Rect.h = 80;
        name_Rect.w = name.size() * 30;
        name_Rect.x = 700;
        name_Rect.y = 300;
        SDL_Surface *log_in_surface = IMG_Load("image/log_in_bg_1.png");
        tex_log_in_bg = SDL_CreateTextureFromSurface(wrend, log_in_surface);
        SDL_FreeSurface(log_in_surface);
        SDL_RenderClear(wrend);
        SDL_RenderCopy(wrend, tex_log_in_bg, NULL, &log_in_bg);
        SDL_RenderCopy(wrend, tex_name, NULL, &name_Rect);
        SDL_RenderPresent(wrend);
    }
    SDL_StopTextInput();
    if (type == 1)
    {
        names.push_back(name);
    }
    return LOGIN_MENU;
}
MENU_OPTIONS load_register()
{
    register_bg.w = WINDOW_WIDTH;
    register_bg.h = WINDOW_HEIGHT;
    register_bg.x = 0;
    register_bg.y = 0;
    MENU_OPTIONS op1 = nameprint(1);
    if (op1 == EXIT)
        return op1;
    MENU_OPTIONS op2 = password_print(1);
    string temp_n = names[names.size() - 1];
    string temp_p = passwords[passwords.size() - 1];
    return write_on_file("database.txt", temp_n, temp_p, op2);
}
MENU_OPTIONS error()
{
    SDL_Surface *surface = IMG_Load("image/error.png");
    tex_error = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, tex_error, NULL, NULL);
    SDL_RenderPresent(wrend);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0 || 1)
    {
        if (event.type == SDL_QUIT)
        {
            return EXIT;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            cout << x << ' ' << y << endl;
            if (x > 527 && x < 866 && y > 417 && y < 567)
            {
                Mix_PauseMusic();
                sound_effect("music/change_tab.wav");
                SDL_Delay(300);
                return REGISTER_MENU;
            }
        }
    }
}
MENU_OPTIONS load_log_in()
{
    MENU_OPTIONS op1 = nameprint(0);
    if (op1 == EXIT)
        return op1;
    MENU_OPTIONS op2 = password_print(0);
    if (search(user_name, user_password))
    {
        return MENU;
    }
    else
    {
        return error();
    }
}
int curr = 0;
MENU_OPTIONS render_help_menu()
{
    string path = "image/help" + to_string(curr) + ".png";
    SDL_Surface *surface = IMG_Load(path.c_str());
    tex_help = SDL_CreateTextureFromSurface(wrend, surface);
    SDL_FreeSurface(surface);
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, tex_help, NULL, NULL);
    SDL_RenderPresent(wrend);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0 || 1)
    {
        if (event.type == SDL_QUIT)
        {
            return EXIT;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x > 563 && x < 816 && y > 703 && y < 779)
            {
                curr++;
                if (curr == 4)
                    return MENU;
                return HELP_MENU;
            }
        }
    }
    return HELP_MENU;
}
void render_menu()
{
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, texmenubg, NULL, &menubg);
    SDL_RenderCopy(wrend, texnewgame, NULL, &newgame);
    SDL_RenderCopy(wrend, texhighscore, NULL, &highscore);
    SDL_RenderCopy(wrend, texhelp, NULL, &help);
    SDL_RenderCopy(wrend, tex_level, NULL, &level);
    SDL_RenderCopy(wrend, texquitgame, NULL, &quitgame);
    SDL_RenderCopy(wrend, tex_log_in, NULL, &log_in);
    SDL_RenderCopy(wrend, tex_register, NULL, &reg);
    SDL_RenderCopy(wrend, tex_music_button[music_state], NULL, &music_button);
    SDL_RenderPresent(wrend);
    SDL_Delay(1000 / 60);
}
int curr_level = 1;
MENU_OPTIONS load_level_menu()
{
    TTF_Font *font = TTF_OpenFont("font/game.ttf", 100);
    SDL_Color colour = {255, 255, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(font, to_string(curr_level).c_str(), colour);
    tex_level_show = SDL_CreateTextureFromSurface(wrend, surf);
    SDL_FreeSurface(surf);
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, tex_level_bg, NULL, NULL);
    SDL_RenderCopy(wrend, tex_level_show, NULL, &level_show);
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
            if (x > 894 && x < 988 && y > 336 && y < 472)
            {
                curr_level = min(3, curr_level + 1);
            }
            else if (x > 402 && x < 498 && y > 331 && y < 470)
            {
                curr_level = max(1, curr_level - 1);
            }
            else if (x > 554 && x < 844 && y > 636 && y < 754)
            {
                if (curr_level == 1)
                {
                    curr_game = NEW_GAME;
                    return NEW_GAME;
                }
                else if (curr_level == 2)
                {
                    curr_game = LEVEL_ONE;
                    return LEVEL_ONE;
                }
                else if (curr_level == 3)
                {
                    curr_game = LEVEL_TWO;
                    return LEVEL_TWO;
                }
            }
            else if (x > 1172 && x < 1320 && y > 64 && y < 226)
            {
                return MENU;
            }
        }
    }
    return LEVELS;
}
