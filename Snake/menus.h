//
//  menus.h
//  Snake
//
//  Created by Marcel on 24/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Menu{
    WINDOW *menu_win;
public:
    
    bool *playGame;
    bool *pauseGame;
    
    bool exit_on_last_item;
    
    int numberOfMenuItems;
    std::string *itemName;
    std::string menuMessage;
    
    void show(){
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
            
            if(input == KEY_UP) menuItem--;
            else if(input == KEY_DOWN) menuItem++;
            else if(input == 10) menuActiv = false; //Enter key
            
            if(exit_on_last_item){
                if(menuActiv == false && menuItem == numberOfMenuItems - 1) *playGame = false;
            }
            
            if(menuItem == -1) menuItem = numberOfMenuItems - 1;
            else if(menuItem == numberOfMenuItems) menuItem = 0;
            
            printInTheMiddle(menu_win, 5, menuMessage);
            
            for(int i=0; i<numberOfMenuItems; i++){
                if(menuItem != i)printInTheMiddle(menu_win, 10 + i, itemName[i]);
            }
            
            wattron(menu_win, COLOR_PAIR(2));
            printInTheMiddle(menu_win, 10+menuItem, itemName[menuItem]);
            wattroff(menu_win, COLOR_PAIR(2));
            
            wrefresh(menu_win);
        }
        *pauseGame = false;
    }
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text){
        unsigned long stringLength = text.size();
        mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
    }
    
    
};

class MainMenu: public Menu{
public:
    MainMenu(bool *playGame, bool *pauseGame){
        numberOfMenuItems = 3;
        menuMessage = "Welcome to the game of snake!";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "New Game";
        itemName[1] = "Load Game";
        itemName[2] = "Exit Game";
        exit_on_last_item = true;
        
        this-> playGame = playGame;
        this-> pauseGame = pauseGame;
        defColors();
    }
    
}main_menu(&game.play, &game.pause);

class DifficultyMenu: public Menu{
public:
    
    DifficultyMenu(bool *playGame, bool *pauseGame){
        numberOfMenuItems = 3;
        menuMessage = "Choose difficulty";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "Easy";
        itemName[1] = "Normal";
        itemName[2] = "Extreme";
        exit_on_last_item = false;
        
        this-> playGame = playGame;
        this-> pauseGame = pauseGame;
        defColors();
    }
    
}difficulty_menu(&game.play, &game.pause);

