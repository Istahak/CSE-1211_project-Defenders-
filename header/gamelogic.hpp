Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;
void sound_effect(string s)
{
    Mix_FreeChunk(gScratch);
    gScratch = NULL;
    gScratch = Mix_LoadWAV(s.c_str());
    Mix_PlayChannel(-1, gScratch, 0);
}
void music(string s, int state)
{
    // if (state)
    //     Mix_PauseMusic();
    // else
    //     Mix_ResumeMusic();
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    gMusic = Mix_LoadMUS(s.c_str());
    Mix_PlayMusic(gMusic, -1);
}
bool check_collision(SDL_Rect a, SDL_Rect b)
{
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    if (bottom_a <= top_b)
    {
        return false;
    }

    if (top_a >= bottom_b)
    {
        return false;
    }

    if (right_a <= left_b)
    {
        return false;
    }

    if (left_a >= right_b)
    {
        return false;
    }
    return true;
}
bool collision_circle_circle(float x1, float y1, float r1, float x2, float y2, float r2)
{

    auto dx = x1 - x2;
    auto dy = y1 - y2;

    auto combined_radius = r1 + r2;

    if (dx * dx + dy * dy > combined_radius * combined_radius)
        return false;

    return true;
}
double dist(int x1, int y1, int x2, int y2)
{
    int x = (x2 - x1) * (x2 - x1);
    int y = (y2 - y1) * (y2 - y1);
    return x + y;
}
int ball_vel_x = 5, ball_vel_y = 5;
int disk_vel_x = 0, disk_vel_y = 0;
int bar_vel_x = 10;

void move_bar(SDL_Rect &bar)
{
    if (bar.x <= 0 || bar.x >= WINDOW_WIDTH - bar.w)
        bar_vel_x *= -1;
    bar.x += bar_vel_x;
}
bool move(SDL_Rect &ball, SDL_Rect &disk, SDL_Rect &bar)
{
    ball.x += ball_vel_x;
    ball.y += ball_vel_y;
    disk.x += disk_vel_x;
    disk.y += disk_vel_y;
    move_bar(bar);

    if (ball.x <= 0)
    {
        sound_effect("music/wall_hit.wav");
        ball.x = 0;
        ball_vel_x *= -1;
    }
    else if (ball.x >= WINDOW_WIDTH - ball.w)
    {
        sound_effect("music/wall_hit.wav");
        ball.x = WINDOW_WIDTH - ball.w;
        ball_vel_x *= -1;
    }
    if (ball.y <= 0)
    {
        sound_effect("music/wall_hit.wav");
        ball.y = 0;
        ball_vel_y *= -1;
    }
    else if (ball.y >= WINDOW_HEIGHT - ball.h)
    {
        sound_effect("music/wall_hit.wav");
        ball.y = WINDOW_HEIGHT - ball.h;
        ball_vel_y *= -1;
    }
    if (disk.x <= 100)
    {
        disk.x = 100;
    }
    else if (disk.x >= WINDOW_WIDTH - 100 - disk.w)
    {
        disk.x = WINDOW_WIDTH - 100 - disk.w;
    }
    if (disk.y <= 375)
    {
        disk.y = 375;
    }
    else if (disk.y >= WINDOW_HEIGHT - disk.h - 85)
    {
        disk.y = WINDOW_HEIGHT - disk.h - 85;
    }

    if (collision_circle_circle(disk.x + disk.w / 2, disk.y + disk.h / 2, disk.h / 2, ball.x + ball.w / 2, ball.y + ball.h / 2, ball.h / 2)) // check_collision(ball, disk)
    {
        ball.x -= ball_vel_x;
        ball.y -= ball_vel_y;

        disk.x -= disk_vel_x;
        disk.y -= disk_vel_y;
        if (disk_vel_x == 0 && disk_vel_y == 0)
        {
            ball_vel_x *= -1;
            ball_vel_y *= -1;
        }
        else
        {
            ball_vel_x = disk_vel_x;
            ball_vel_y = disk_vel_y;

            if (ball_vel_x > 0)
            {
                ball_vel_x = min(ball_vel_x, 10);
            }
            else if (ball_vel_x < 0)
            {
                ball_vel_x = max(-10, ball_vel_x);
            }
            if (ball_vel_y > 0)
            {
                ball_vel_y = min(ball_vel_y, 10);
            }
            else if (ball_vel_y < 0)
            {
                ball_vel_y = max(-10, ball_vel_y);
            }
        }
        ball.x += 5 * ball_vel_x;
        ball.y += 5 * ball_vel_y;
        // disk.x -= 2*ball_vel_x;
        // disk.y -= 2*ball_vel_y;
        return true;
    }
    return false;
}
void follow(SDL_Rect &ball, SDL_Rect &disk, SDL_Rect &bar)
{
    int cur_x, cur_y;
    SDL_PumpEvents();
    SDL_GetMouseState(&cur_x, &cur_y);
    move(ball, disk, bar);
    int temp_x = cur_x - disk.x;
    int temp_y = cur_y - disk.y;
    int d = dist(temp_x, temp_y, 0, 0);
    if (d > 500)
    {
        disk_vel_x = (temp_x / sqrt(d)) * sqrt(500);
        disk_vel_y = (temp_y / sqrt(d)) * sqrt(500);
    }
    else
    {
        disk_vel_x = temp_x;
        disk_vel_y = temp_y;
    }
}
bool enemy_life(SDL_Rect &ball, SDL_Rect &enemy, SDL_Rect &bar)
{
    if (check_collision(ball, enemy))
    {
        bar.x -= WINDOW_WIDTH / 15;
        if (bar.x <= -930)
        {
            return true;
        }
    }
    return false;
}
int curr_enemy = 9;
int state = 0;
int vel_x = 5;
int vel_y = 5;
int curr_life = 0;

MENU_OPTIONS enemycollision(SDL_Rect &enemy, SDL_Rect &ball, SDL_Rect &bar)
{
    if (check_collision(ball, enemy))
    {
        // ball.x -= ball_vel_x;
        // ball.y -= ball_vel_y;
        if (curr_game == LEVEL_ONE)
        {
            if (enemy_life(ball, enemy, bar))
            {
                curr_enemy = 9;
                curr_life = 0;
                start = 0;
                curr_game = LEVEL_TWO;
                return LEVEL_TWO;
            }
        }
        sound_effect("music/enemy_hit.wav");
        ball_vel_x *= -1;
        ball_vel_y *= -1;
        ball.x += 6 * ball_vel_x;
        ball.y += 6 * ball_vel_y;
        curr_enemy--;
        score += 500;
    }
    if (curr_enemy == -1)
    {
        start = 0;
        curr_enemy = 9;
        curr_life = 0;
        curr_game = LEVEL_ONE;
        return LEVEL_ONE;
    }
    return curr_game;
}
bool life_update(SDL_Rect &ball, SDL_Rect &bar)
{
    if (curr_life >= 6)
    {
        ball.x = WINDOW_WIDTH / 2;
        ball.y = WINDOW_HEIGHT / 2;
        return false;
    }
    if (check_collision(ball, bar))
    {
        score = max(0, score - 100);
        sound_effect("music/life_loss.wav");
        if (curr_game == NEW_GAME)
            ball_vel_y *= -1;
        curr_life++;
    }
    return true;
}
void move_enemy(int curr_time, int start_time, SDL_Rect &enemy)
{

    if (enemy.x <= 50)
    {
        enemy.x = 50;
        vel_x *= -1;
        state ^= 1;
    }
    if (enemy.x >= WINDOW_WIDTH - enemy.w - 50)
    {
        enemy.x = WINDOW_WIDTH - enemy.w - 50;
        vel_x *= -1;
        state ^= 1;
    }
    double t = ((double)abs(curr_time - start_time)) / 1000;
    enemy.x += vel_x;
    vel_y = 5 * sin(2 * 3.1415926535 * t);
    enemy.y += vel_y;
}
