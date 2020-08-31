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
    std::string *itemName;
    std::string menuMessage;
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text){
        unsigned long stringLength = text.size();
        mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
    }
 
public:
    int show(){
        bool menuActiv = true;
        int menuItem = 0;
        menu_win = newwin(20, 80, 5, 10);
        
        while(menuActiv){
            napms(1000 / 10);
            werase(menu_win);
            clear();
            box(menu_win, 0, 0);
            
            int input;
            input = getch();
            
            if(input == KEY_UP || input == KEY_LEFT) menuItem--;
            else if(input == KEY_DOWN || input == KEY_RIGHT) menuItem++;
            else if(input == 10) menuActiv = false; //Enter key
            
            if(menuItem == -1) menuItem = numberOfMenuItems - 1;
            else if(menuItem == numberOfMenuItems) menuItem = 0;
            
            printInTheMiddle(menu_win, 5, menuMessage);
            
            for(int i=0; i<numberOfMenuItems; i++){
                if(menuItem != i)printInTheMiddle(menu_win, 10 + i, itemName[i]);
            }
            
            wattron(menu_win, COLOR_PAIR(CYAN));
            printInTheMiddle(menu_win, 10+menuItem, itemName[menuItem]);
            wattroff(menu_win, COLOR_PAIR(CYAN));
            
            wrefresh(menu_win);
        }
        
        return menuItem;
    }

};

class MainMenu: public Menu{
public:
    MainMenu(){
        numberOfMenuItems = 3;
        menuMessage = "Welcome to the game of snake!";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "New Game";
        itemName[1] = "Load Game";
        itemName[2] = "Exit Game";
    }
    
    enum action{NEW_GAME = 0, LOAD_GAME, EXIT_GAME};
    
}main_menu;

class DifficultyMenu: public Menu{
public:
    
    DifficultyMenu(){
        numberOfMenuItems = 3;
        menuMessage = "Choose difficulty";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "Easy";
        itemName[1] = "Normal";
        itemName[2] = "Extreme";
    }
    
    enum action{EASY = 0, NORMAL, EXTREME};
    
}difficulty_menu;

class PauseMenu: public Menu{
public:
    PauseMenu(){
        numberOfMenuItems = 3;
        menuMessage = "Paused";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "Go Back";
        itemName[1] = "Main Menu";
        itemName[2] = "Exit Game";
    }
    
    enum action{GO_BACK = 0, MAIN_MENU, EXIT_GAME};
    
}pause_menu;

class DeadMenu: public Menu{
public:
    DeadMenu(){
        numberOfMenuItems = 3;
        menuMessage = "Game Over!!!";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "Play Again";
        itemName[1] = "Main Menu";
        itemName[2] = "Exit Game";
    }
    
    enum action{PLAY_AGAIN = 0, MAIN_MENU, EXIT_GAME};
    
}dead_menu;


template<typename T>

class BetterMenu : public T{
protected:
    WINDOW *menu_win;
    
    int numberOfMenuItems;
    std::string *itemName;
    std::string menuMessage;
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text){
        unsigned long stringLength = text.size();
        mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
    }

public:
    
    int show(){
        bool menuActiv = true;
        int menuItem = 0;
        menu_win = newwin(20, 80, 5, 10);
        
        while(menuActiv){
            napms(1000 / 10);
            werase(menu_win);
            clear();
            box(menu_win, 0, 0);
            
            int input;
            input = getch();
            
            if(input == KEY_UP || input == KEY_LEFT) menuItem--;
            else if(input == KEY_DOWN || input == KEY_RIGHT) menuItem++;
            else if(input == 10) menuActiv = false; //Enter key
            
            if(menuItem == -1) menuItem = numberOfMenuItems - 1;
            else if(menuItem == numberOfMenuItems) menuItem = 0;
            
            printInTheMiddle(menu_win, 5, menuMessage);
            
            for(int i=0; i<numberOfMenuItems; i++){
                if(menuItem != i)printInTheMiddle(menu_win, 10 + i, itemName[i]);
            }
            
            wattron(menu_win, COLOR_PAIR(CYAN));
            printInTheMiddle(menu_win, 10+menuItem, itemName[menuItem]);
            wattroff(menu_win, COLOR_PAIR(CYAN));
            
            wrefresh(menu_win);
        }
        
        return menuItem;
    }
    
    
    
};
