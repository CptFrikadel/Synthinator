#include "CursesUI.hpp"


#include <format>
#include <curses.h>
#include <iostream>
#include <string>

void CursesUI::Init()
{
    initscr();

    // Enable line buffering.
    raw();

    setlocale(LC_ALL, "");

    // Don't wait for newline. Make chars immediately available
    cbreak();

    // Make cursor invisible
    curs_set(0);

    // Also get F_KEYS
    keypad(stdscr, true);

    // Don't echo characters
    noecho();
}


void CursesUI::Update()
{
    int row, col;
    getmaxyx(stdscr, row, col);

    std::string mesg = "Yo Whaddup!";

    attron(A_BOLD);
    mvprintw(row/2, (col - mesg.length())/2, "%s", mesg.c_str());
    attroff(A_BOLD);

    mesg = "Current mode: " + std::to_string(mMode);
    attron(A_BOLD);
    mvprintw(row-2, (col - mesg.length())/2, "%s", mesg.c_str());
    attroff(A_BOLD);

    mesg = "Synthesizer DSP load: " + std::format("{:.1f}", mSynthLoad * 100) + "%";
    mvprintw(row/2 + 4, (col - mesg.length())/2, "%s", mesg.c_str());

    refresh();
}


void CursesUI::Exit()
{
    curs_set(1);
    flushinp();
    endwin();
    refresh();
}
