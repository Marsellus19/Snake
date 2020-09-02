//  menus.h
//  Snake
//
//  Created by Marcel on 24/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Menu{
protected:
    WINDOW *menu_win;
    
    int numberOfMenuItems;
    std::string menuMessage;
    int currentItem;
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text);
 
public:
    std::string *itemName;
    
    Menu();
    
    /* Constructors that can be used to define any menu with a list of 2,3 or 4 menu items */
    
    Menu(std::string message, std::string item_0, std::string item_1);
    
    Menu(std::string message, std::string item_0, std::string item_1, std::string item_2);
    
    Menu(std::string message, std::string item_0, std::string item_1, std::string item_2, std::string item_3);
    
    
    int getSelectedItem(){ return currentItem; }
    
    int show();
    
    std::string outcome(){
        return itemName[currentItem];
    }

};



Menu::Menu(std::string message, std::string item_0, std::string item_1){
    numberOfMenuItems = 2;
    itemName = new std::string[numberOfMenuItems];
    menuMessage = message;
    itemName[0] = item_0;
    itemName[1] = item_1;
}

Menu::Menu(std::string message, std::string item_0, std::string item_1, std::string item_2){
    numberOfMenuItems = 3;
    itemName = new std::string[numberOfMenuItems];
    menuMessage = message;
    itemName[0] = item_0;
    itemName[1] = item_1;
    itemName[2] = item_2;
}

Menu::Menu(std::string message, std::string item_0, std::string item_1, std::string item_2, std::string item_3){
    numberOfMenuItems = 4;
    itemName = new std::string[numberOfMenuItems];
    menuMessage = message;
    itemName[0] = item_0;
    itemName[1] = item_1;
    itemName[2] = item_2;
    itemName[3] = item_3;
}

int Menu::show(){
    bool menuActiv = true;
    currentItem = 0;
    menu_win = newwin(20, 80, 5, 10);
    
    while(menuActiv){
        napms(1000 / 10);
        werase(menu_win);
        clear();
        box(menu_win, 0, 0);
        
        int input;
        input = getch();
        
        if(input == KEY_UP || input == KEY_LEFT) currentItem--;
        else if(input == KEY_DOWN || input == KEY_RIGHT) currentItem++;
        else if(input == 10) menuActiv = false; //Enter key
        
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
    
    return currentItem;
}

void Menu::printInTheMiddle(WINDOW *local_win, int height, std::string text){
    unsigned long stringLength = text.size();
    mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
}


Menu mainMenu("Welcome to the game of snake!", "New Game", "Load Game", "Exit Game");

Menu difficultyMenu("Choose difficulty", "Easy", "Normal", "Extreme");

Menu pauseMenu("Paused!", "Go Back", "Main Menu", "Exit Game");

Menu deadMenu("Game Over!!!", "Play Again", "Main Menu", "Exit Game");
