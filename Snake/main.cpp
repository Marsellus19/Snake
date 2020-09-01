//  main.cpp
//  Snake
//
//  Created by Marcel on 04/05/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <list>
#include <string>
#include "game.h"
#include "fruit.h"
#include "snake.h"
#include "menus.h"
#include "progress.h"


int main(int argc, const char * argv[]) {
    
    while(game.play){
        game.refreshwin();
        
        snake.move(game.getInput());
        
        if(snake.isDead()){
            int item = deadMenu.show();
            if(deadMenu.itemName[item] == "Play Again"){
                game.pause = false;
                game.end = false;
                snake.newSnake();
                fruit.newPos();
            }
            else if(deadMenu.itemName[item] == "Main Menu"){
                game.pause = true;
                game.end = true;
            }
            else if(deadMenu.itemName[item] == "Exit Game"){
                game.play = false;
            }
        }
        
        if(game.pause && !game.end){
            progress.save(game, snake, fruit);
            
            int item = pauseMenu.show();
            
            if(pauseMenu.itemName[item] == "Go Back"){
                game.pause = false;
            }
            else if(pauseMenu.itemName[item] == "Main Menu"){
                game.end = true;
            }
            else if(pauseMenu.itemName[item] == "Exit Game"){
                game.play = false;
            }
        }
        
        if(game.pause && game.end){
            int item = mainMenu.show();
            
            if(mainMenu.itemName[item] == "New Game"){
                game.pause = false;
                game.end = false;
                snake.newSnake();
                fruit.newPos();
                int newItem = difficultyMenu.show();
                
                if(difficultyMenu.itemName[newItem] == "Easy"){
                    game.setDifficulty(Game::EASY);
                }
                else if(difficultyMenu.itemName[newItem] == "Normal"){
                    game.setDifficulty(Game::NORMAL);
                }
                else if(difficultyMenu.itemName[newItem] == "Extreme"){
                    game.setDifficulty(Game::EXTREME);
                }
            }
            else if(mainMenu.itemName[item] == "Load Game"){
                game.pause = false;
                game.end = false;
                progress.load(game, snake, fruit);
            }
            else if(mainMenu.itemName[item] == "Exit Game"){
                game.play = false;
            }
        }
        
        if(snake.hasEaten(fruit)){
            snake.grow();
            fruit.newPos();
        }
        
        snake.show();
        
        fruit.show();
        
        game.showScore(snake.getLength());
    }
    
    endwin();
    
    return 0;
}
