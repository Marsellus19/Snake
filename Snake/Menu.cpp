//  Menu.cpp
//  Snake
//
//  Created by Marcel Krol on 25/07/2020.
//  Copyright © 2020 marcelkrol99@gmail.com

#include <iostream>
#include <string>
#include <ncurses.h>
#include "Menu.h"

void Menu::show(){
    bool menuActive = true;
    currentItem = 0;
    WINDOW *menu_win;
    menu_win = newwin(numberOfMenuItems + 15, 80, 5, 10);
    
    while(menuActive){
        napms(1000 / 10);
        werase(menu_win);
        clear();
        box(menu_win, 0, 0);
        
        int input;
        input = getch();
        
        if(input == KEY_UP || input == KEY_LEFT) currentItem--;
        else if(input == KEY_DOWN || input == KEY_RIGHT) currentItem++;
        else if(input == 10) menuActive = false; //Enter key
        
        if(currentItem == -1) currentItem = numberOfMenuItems - 1;
        else if(currentItem == numberOfMenuItems) currentItem = 0;
        
        printInTheMiddle(menu_win, 5, menuMessage);
        
        for(int i=0; i<numberOfMenuItems; i++){
            if(currentItem != i)printInTheMiddle(menu_win, 10 + i, itemName[i]);
        }
        
        wattron(menu_win, COLOR_PAIR(2));
        printInTheMiddle(menu_win, 10+currentItem, itemName[currentItem]);
        wattroff(menu_win, COLOR_PAIR(2));
        
        wrefresh(menu_win);
    }
    
}

std::string Menu::outcome(){
    return itemName[currentItem];
}

void Menu::printInTheMiddle(WINDOW *local_win, int height, std::string text){
    unsigned long stringLength = text.size();
    mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
}
