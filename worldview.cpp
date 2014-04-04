#include <ncurses.h>
#include <vector>
#include <iostream>
#include "player.h"
#include "world.h"

// std::vector<std::vector<char> > world(90, std::vector<char>::vector(90, '.'));
World world;
Player player;

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

void displayOutput(WINDOW* window)
{
    int left = getScrollX();
    int top = getScrollY();
    displayTiles(window, left, top);
    mvwprintw(window, player.y - top, player.x - left, "%c", player.glyph);
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

    screenWidth = COLS - 10;
    screenHeight = LINES - 10;

    WINDOW* window = create_newwin(screenHeight, screenWidth, 0, 0);
    WINDOW* debug = create_newwin(4, 20, screenHeight, 0);
    keypad(window, TRUE);

    world.addToWorld(&player);

    displayOutput(window);
    mvwprintw(debug, 0, 0, "%3d %3d", player.x, player.y);
    mvwprintw(debug, 1, 0, "%d", world.tiles[player.x][player.y].type);
    wrefresh(window);
    wrefresh(debug);
    int input;
    while((input = wgetch(window)) != 113)
    {
        respondToUserInput(input);
        displayOutput(window);
        mvwprintw(debug, 0, 0, "%3d %3d", player.x, player.y);
        mvwprintw(debug, 1, 0, "%d", world.tiles[player.x][player.y].type);
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
