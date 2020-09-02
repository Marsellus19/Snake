//  menus.h
//  Snake
//
//  Created by Marcel on 24/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Menu{
    
    int numberOfMenuItems, currentItem;
    std::string menuMessage, *itemName;
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text);
 
public:
    
    template <typename T, typename... Ts>
    
    Menu(std::string menuMessage, T item1, Ts... item2); //Constructor defining a menu object with any number of menu list items
    
    void show();
    
    template <typename N, typename... Ns>
    void showError(N item1, Ns... item2);
    
    std::string outcome();

};




Menu mainMenu("Welcome to the game of snake!", "New Game", "Load Game", "Exit Game");

Menu difficultyMenu("Choose difficulty", "Easy", "Normal", "Extreme", "Ridiculous!");

Menu pauseMenu("Paused!", "Go Back", "Main Menu");

Menu deadMenu("Game Over!!!", "Play Again", "Main Menu");




template <typename T, typename... Ts>
Menu::Menu(std::string menuMessage, T item1, Ts... item2){
    this-> menuMessage = menuMessage;
    
    std::string item[] = {item1, item2...};
    
    itemName = new std::string[sizeof(item)/sizeof(item[0])];
    
    numberOfMenuItems = sizeof(item) / sizeof(item[0]);
    
    for(int i = 0; i< numberOfMenuItems; i++){
        itemName[i] = item[i];
    }
}

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
        
        wattron(menu_win, COLOR_PAIR(CYAN));
        printInTheMiddle(menu_win, 10+currentItem, itemName[currentItem]);
        wattroff(menu_win, COLOR_PAIR(CYAN));
        
        wrefresh(menu_win);
    }
    
}

template <typename N, typename... Ns>
void Menu::showError(N item1, Ns... item2){
    bool active = true;
    std::string item[] = {item1, item2...};
    
    WINDOW *error_win;
    error_win = newwin(sizeof(item)/sizeof(item[0]) + 6, 80, 5, 10);
    
    while(active){
        napms(1000 / 10);
        werase(error_win);
        clear();
        int input = getch();
        if(input == 10) active = false;
        
        for(int i=0; i< sizeof(item)/sizeof(item[0]); i++){
            printInTheMiddle(error_win, 3 + i, item[i]);
            wprintw(error_win, "\n");
        }
        
        box(error_win, 0, 0);
        
        wrefresh(error_win);
    }
}

std::string Menu::outcome(){
    return itemName[currentItem];
}

void Menu::printInTheMiddle(WINDOW *local_win, int height, std::string text){
    unsigned long stringLength = text.size();
    mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
}
