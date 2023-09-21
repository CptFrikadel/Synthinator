#include "CursesUI.hpp"

#include <curses.h>
#include <iostream>

void CursesUI::Init()
{
    std::cout << "Gonna init them scr yo!" << std::endl;
    
    initscr();
    printw("Yo Whaddup!");
}


void CursesUI::Update()
{
    refresh();
}


void CursesUI::Exit()
{
    endwin();
}
