//  main.cpp
//  Snake
//
//  Created by Marcel on 04/05/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <list>
#include <string>
#include "game.h"
#include "fruit.h"
#include "snake.h"
#include "menus.h"


int main(int argc, const char * argv[]) {
    
    while(game.play){
        game.refreshwin();
        
        snake.move(game.getInput());
        
        if(snake.isDead()){
            switch(DeadMenu::action(dead_menu.show())){
                case DeadMenu::PLAY_AGAIN:
                    game.pause = false;
                    game.end = false;
                    snake.newSnake();
                    fruit.newPos();
                    break;
                    
                case DeadMenu::MAIN_MENU:
                    game.pause = true;
                    game.end = true;
                    break;
                    
                case DeadMenu::EXIT_GAME:
                    game.play = false;
                    break;
            }
        }
        
        if(game.pause && !game.end){
            switch(PauseMenu::action(pause_menu.show())){
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
        
        if(game.pause && game.end){
            switch(MainMenu::action(main_menu.show())){
                case MainMenu::NEW_GAME:
                    game.pause = false;
                    game.end = false;
                    snake.newSnake();
                    fruit.newPos();
                    switch(DifficultyMenu::action(difficulty_menu.show())){
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
        
        if(snake.hasEaten(fruit)){
            snake.grow();
            fruit.newPos();
        }
        
        snake.show();
        
        fruit.show();
        
        snake.saveProgress();
        
        game.showScore(snake.getLength());
    }
    
    endwin();
    
    return 0;
}
