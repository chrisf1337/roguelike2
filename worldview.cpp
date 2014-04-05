#include <ncurses.h>
#include <vector>
#include <iostream>
#include "player.h"
#include "world.h"
#include "monster.h"

// std::vector<std::vector<char> > world(90, std::vector<char>::vector(90, '.'));
World world;
Player player(&world, "player");

int screenWidth;
int screenHeight;

void print_menu(WINDOW *menu_win, int highlight, int n_choices,
                const char** choices)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {
        if(highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}

int getScrollX()
{
    return std::max(0, std::min(player.x - screenWidth / 2,
                                world.width - screenWidth));
}

int getScrollY()
{
    return std::max(0, std::min(player.y - screenHeight / 2,
                                world.height - screenHeight));
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW* local_win;

    local_win = newwin(height, width, starty, startx);
    wrefresh(local_win);
    return local_win;
}

void displayTiles(WINDOW* window, int left, int top)
{
    for(int x = 0; x < screenWidth; x++)
    {
        for(int y = 0; y < screenHeight; y++)
        {
            int wx = x + left;
            int wy = y + top;

            mvwprintw(window, y, x, "%c", world.tiles[wx][wy].glyph);
        }
    }
}

void displayOutput(WINDOW *window)
{
    int left = getScrollX();
    int top = getScrollY();
    displayTiles(window, left, top);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    wattron(window, COLOR_PAIR(2));
    for(std::vector<Creature*>::iterator it = world.creatures.begin(); it != world.creatures.end(); it++)
    {
        mvwprintw(window, (*it)->y - top, (*it)->x - left, "%c", (*it)->glyph);
    }
    wattroff(window, COLOR_PAIR(2));

    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, player.y - top, player.x - left, "%c", player.glyph);
    wattroff(window, COLOR_PAIR(1));
}

void updatePlayerStats(WINDOW *window)
{
    wclear(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "Lv:  %d", player.level);
    mvwprintw(window, 2, 1, "HP:  %d/%d", player.hp, player.maxhp);
    mvwprintw(window, 3, 1, "MP:  %d/%d", player.mp, player.maxmp);
    mvwprintw(window, 4, 1, "Exp: %d/%d", player.exp, player.expToNextLevel);
    wrefresh(window);
}

void respondToUserInput(int input)
{
    switch(input)
    {
        case KEY_UP:
            player.moveBy(0, -1);
            break;
        case KEY_DOWN:
            player.moveBy(0, 1);
            break;
        case KEY_LEFT:
            player.moveBy(-1, 0);
            break;
        case KEY_RIGHT:
            player.moveBy(1, 0);
            break;
    }
}

int main()
{
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    start_color();

    screenWidth = COLS - 30;
    screenHeight = LINES - 10;

    WINDOW* window = create_newwin(screenHeight, screenWidth, 0, 0);
    WINDOW* debug = create_newwin(LINES - screenHeight, COLS, screenHeight, 0);
    WINDOW* status = create_newwin(screenHeight, COLS - screenWidth, 0, screenWidth);
    keypad(window, TRUE);


    world.add(&player, 99, 99);

    Monster m1(&world, "monster");
    world.addToWorld(&m1, 99, 99);
    Monster m2(&world, "monster");
    world.addToWorld(&m2, 99, 99);

    displayOutput(window);
    mvwprintw(debug, 1, 1, "%3d %3d", player.x, player.y);
    mvwprintw(debug, 2, 1, "%d", world.tiles[player.x][player.y].type);
    for(int i = 0; i < world.creatures.size(); i++)
    {
        mvwprintw(debug, i + 3, 1, "%3d %3d", world.creatures[i]->x, world.creatures[i]->y);

    }
    box(debug, 0, 0);

    updatePlayerStats(status);

    wrefresh(window);
    wrefresh(debug);
    wrefresh(status);

    int input;
    while((input = wgetch(window)) != 113)
    {
        respondToUserInput(input);
        displayOutput(window);
        mvwprintw(debug, 1, 1, "%3d %3d", player.x, player.y);
        mvwprintw(debug, 2, 1, "%d", world.tiles[player.x][player.y].type);
        for(int i = 0; i < world.creatures.size(); i++)
        {
            mvwprintw(debug, i + 3, 1, "%3d %3d", world.creatures[i]->x, world.creatures[i]->y);

        }
        for(std::vector<Creature*>::iterator it = world.creatures.begin(); it != world.creatures.end(); it++)
        {
            (*it)->act();
        }
        updatePlayerStats(status);
        wrefresh(debug);
    }
    clrtoeol();
    endwin();
}

int main2()
{
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    int startx = 0;
    int starty = 0;

    const char* choices[] = {"New Game", "Quit"};

    int n_choices = sizeof(choices) / sizeof(char*);

    const int WIDTH = 20;
    const int HEIGHT = n_choices + 4;

    initscr();
    clear();
    noecho();
    cbreak();
    // keypad(stdscr, TRUE);
    curs_set(0);
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0,
             "Use arrow keys to go up and down. Press enter to select a choice");
    refresh();
    print_menu(menu_win, highlight, n_choices, choices);
    while(1)
    {
        c = wgetch(menu_win);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                {
                    highlight = n_choices;
                }
                else
                {
                    --highlight;
                }
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                {
                    highlight = 1;
                }
                else
                {
                    ++highlight;
                }
                break;
            case 10:
                choice = highlight;
                break;
        }
        print_menu(menu_win, highlight, n_choices, choices);
        /* entry */
        if(choice == 1)
        {
            break;
        }
        else if(choice == 2)
        {
            break;
        }
    }
    clrtoeol();
    endwin();
    return 0;
}
