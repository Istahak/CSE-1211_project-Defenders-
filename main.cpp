#include "header/header.hpp"
#include "header/high_score.hpp"
#include "header/gamelogic.hpp"
#include "header/loadmedia.hpp"
#include "header/menu.hpp"
int main()
{
    init();
    TTF_Init();
    loadmedia();
    bool gameover = false;
    MENU_OPTIONS menu = MENU;
    bool done = true;
    bool first = true;

    music("music/intro_theme.mp3", 1);
    // SDL_Delay(5000);
    while (!gameover)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameover = true;
                break;
            }
        }
        if (menu == MENU)
        {
            start = 0;
            curr_level = 1;
            SDL_ShowCursor(SDL_ENABLE);
            curr_game = NEW_GAME;
            curr_life = 0;
            load_menu();
            render_menu();
            menu = check(event);
        }
        if (menu == NEW_GAME)
        {
            if (!life_update(ball, bar))
            {
                if (first)
                {
                    save_high_score("high_score.txt");
                    first = false;
                }
                menu = show_score_win();
            }
            else
            {
                if (start == 0)
                {
                    start = SDL_GetTicks();
                }
                SDL_ShowCursor(SDL_DISABLE);
                follow(ball, disk, bar);
                menu = enemycollision(enemy, ball, bar);
                move_enemy(SDL_GetTicks(), start, enemy);
                Renderer_Update(curr_enemy, curr_life, state);
                update_score_board();
            }
        }
        if (menu == LEVEL_ONE)
        {
            if (!life_update(ball, powr))
            {
                menu = show_score_win();
            }
            else
            {
                if (start == 0)
                {
                    load_level_one();
                    start = SDL_GetTicks();
                }
                SDL_ShowCursor(SDL_DISABLE);
                follow(ball, disk, bar);
                power();
                menu = enemycollision(enemy1, ball, enemy_health);
                move_enemy(SDL_GetTicks(), start, enemy1);
                Renderer_Update_level_1(curr_enemy, curr_life, state);
                update_score_board();
            }
        }
        if (menu == LEVEL_TWO)
        {
            if (curr_life >= 6)
            {
                menu = show_score_win();
            }
            else
            {
                if (start == 0)
                {
                    load_level_two();
                    start = SDL_GetTicks();
                }
                SDL_ShowCursor(SDL_DISABLE);
                follow(ball, disk, bar);
                power_2();
                menu = move_bullet(disk);
                menu = enemycollision(enemy1, ball, enemy_health);
                move_enemy(SDL_GetTicks(), start, enemy1);
                Renderer_Update_level_2(curr_enemy, curr_life, state);
                update_score_board();
            }
        }
        if (menu == LEVELS)
        {
            menu = load_level_menu();
        }
        if (menu == REGISTER_MENU)
        {
            menu = load_register();
        }
        if (menu == LOGIN_MENU)
        {
            menu = load_log_in();
        }
        if (menu == HELP_MENU)
        {
            menu = render_help_menu();
        }
        if (menu == SHOW_SCORE)
        {
            menu = render_high_score_menu("high_score.txt");
        }
        if (menu == FULL_EXIT)
        {
            music("music/intro_theme.mp3", 1);
            menu = quitmenu();
        }
        if (menu == EXIT)
        {
            music("music/intro_theme.mp3", 1);
            gameover = true;
        }
    }
    close();
}
