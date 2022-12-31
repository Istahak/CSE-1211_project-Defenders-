SDL_Rect rect[5];
SDL_Texture *tex_rect[5], *tex_high_score_bg;
void save_high_score(char path[])
{
    if (user_name.size() == 0)
        return;
    vector<pair<string, int>> v;
    FILE *fptr = fopen(path, "r");
    char temp_name[100];
    int temp_score;
    while (!feof(fptr))
    {
        char dummy[100];
        fscanf(fptr, "%s %d", temp_name, &temp_score);
        v.push_back({temp_name, temp_score});
    }
    if (v.size())
        v.pop_back();
    fclose(fptr);
    fptr = fopen(path, "w");
    bool flag = false;
    char u_name[100];
    int i = 0;
    for (auto c : user_name)
        u_name[i++] = c;
    u_name[i] = '\0';
    for (auto val : v)
    {
        int i = 0;
        cout << val.first << ' ' << val.second << endl;
        for (auto c : val.first)
            temp_name[i++] = c;
        temp_name[i] = '\0';
        if (flag)
        {
            fprintf(fptr, "%s %d ", temp_name, val.second);
            continue;
        }
        else
        {
            if (score > val.second)
            {
                fprintf(fptr, "%s %d ", u_name, score);
                fprintf(fptr, "%s %d ", temp_name, val.second);
                flag = true;
            }
            else
                fprintf(fptr, "%s %d ", temp_name, val.second);
        }
    }

    if (flag == false)
        fprintf(fptr, "%s %d ", u_name, score);
    fclose(fptr);
}
MENU_OPTIONS render_high_score_menu(char path[])
{

    vector<pair<string, int>> v;
    FILE *fptr = fopen(path, "r");
    char temp_name[100];
    int temp_score;
    while (!feof(fptr))
    {
        char dummy[100];
        fscanf(fptr, "%s %d", temp_name, &temp_score);
        v.push_back({temp_name, temp_score});
    }
    if (v.size())
        v.pop_back();
    int curr = 0;
    for (int i = 0; i < 5; ++i)
    {
        rect[i].h = 100;
        rect[i].w = (v[i].first.size() + to_string(v[i].second).size() + 1) * 30;
        rect[i].x = 320;
        rect[i].y = 170 + curr;
        curr += 108;
    }
    for (int i = 0; i < 5; ++i)
    {
        TTF_Font *font = TTF_OpenFont("font/game.ttf", 100);
        SDL_Color colour = {255, 255, 255};
        SDL_Surface *surf = TTF_RenderText_Solid(font, (v[i].first + " " + to_string(v[i].second)).c_str(), colour);
        tex_rect[i] = SDL_CreateTextureFromSurface(wrend, surf);
        SDL_FreeSurface(surf);
    }
    SDL_Surface *bg = IMG_Load("image/high_score_menu.png");
    tex_high_score_bg = SDL_CreateTextureFromSurface(wrend, bg);
    SDL_FreeSurface(bg);
    SDL_RenderClear(wrend);
    SDL_RenderCopy(wrend, tex_high_score_bg, NULL, NULL);
    for (int i = 0; i < 5; ++i)
    {
        SDL_RenderCopy(wrend, tex_rect[i], NULL, &rect[i]);
    }
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
            if (x > 1246 && x < 1354 && y > 17 && y < 146)
            {
                Mix_ResumeMusic();
                return MENU;
            }
        }
    }
    return SHOW_SCORE;
}