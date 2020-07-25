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
            
            if(input == KEY_UP) menuItem--;
            else if(input == KEY_DOWN) menuItem++;
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
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text){
        unsigned long stringLength = text.size();
        mvwprintw(local_win, height, (40-((int)stringLength/2)), "%s", text.c_str());
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
        
        defColors();
    }
    
    enum mainAction{NEW_GAME = 0, LOAD_GAME, EXIT_GAME} action;
    
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
        
        defColors();
    }
    
    enum difficultyAction{EASY = 0, NORMAL, EXTREME}action;
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
        
        defColors();
    }
    
    enum pauseAction{GO_BACK = 0, MAIN_MENU, EXIT_GAME}action;
    
}pause_menu;

class DeadMenu: public Menu{
public:
    DeadMenu(){
        numberOfMenuItems = 2;
        menuMessage = "Game Over!!!";
        itemName = new std::string[numberOfMenuItems];
        itemName[0] = "Play Again";
        itemName[1] = "Exit Game";
        
        defColors();
    }
    
    enum deadAction{PLAY_AGAIN = 0, EXIT_GAME}action;
    
}dead_menu;


void showPauseMenu(){
    pause_menu.action = PauseMenu::pauseAction(pause_menu.show());
    
    switch(pause_menu.action){
        case PauseMenu::GO_BACK:
            game.pause = false;
            break;
        case PauseMenu::MAIN_MENU:
            game.end = true;
            break;
        case PauseMenu::EXIT_GAME:
            game.play = false;
            break;
    }
}

void showMainMenu(){
    main_menu.action = MainMenu::mainAction(main_menu.show());
    
    switch(main_menu.action){
        case MainMenu::NEW_GAME:
            game.pause = false;
            game.end = false;
            snake.newSnake();
            fruit.newPos();
            difficulty_menu.action = DifficultyMenu::difficultyAction(difficulty_menu.show());
            switch(difficulty_menu.action){
                case DifficultyMenu::EASY:
                    game.setDifficulty(Game::EASY);
                    break;
                case DifficultyMenu::NORMAL:
                    game.setDifficulty(Game::NORMAL);
                    break;
                case DifficultyMenu::EXTREME:
                    game.setDifficulty(Game::EXTREME);
                    break;
            }
            break;
        case MainMenu::LOAD_GAME:
            game.pause = false;
            game.end = false;
            break;
        case MainMenu::EXIT_GAME:
            game.play = false;
            break;
    }
}

void showDeadMenu(){
    dead_menu.action = DeadMenu::deadAction(dead_menu.show());
    
    switch(dead_menu.action){
        case DeadMenu::PLAY_AGAIN:
            game.pause = false;
            game.end = false;
            snake.newSnake();
            fruit.newPos();
            difficulty_menu.action = DifficultyMenu::difficultyAction(difficulty_menu.show());
            switch(difficulty_menu.action){
                case DifficultyMenu::EASY:
                    game.setDifficulty(Game::EASY);
                    break;
                case DifficultyMenu::NORMAL:
                    game.setDifficulty(Game::NORMAL);
                    break;
                case DifficultyMenu::EXTREME:
                    game.setDifficulty(Game::EXTREME);
                    break;
            }
            break;
        case DeadMenu::EXIT_GAME:
            game.play = false;
            break;
    }
}
