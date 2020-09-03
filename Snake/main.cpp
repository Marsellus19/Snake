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
#include "Game.h"
#include "fruit.h"
#include "snake.h"
#include "menu.h"
#include "progress.h"

Game game;
Fruit fruit(game.gameArea);
Snake snake(game.gameArea);


int main(int argc, const char * argv[]) {
    
    while(game.isActive()){
        game.refreshwin();
        
        snake.move(game.getInput());
        
        if(snake.isDead()){
            progress.wipe();
            
            deadMenu.show();
            
            if(deadMenu.outcome() == "Play Again"){
                game.resume();
                game.newGame();
                snake.newSnake();
                fruit.newFruit();
            }
            else if(deadMenu.outcome() == "Main Menu"){
                game.pause();
                game.end();
            }
        }
        
        if(snake.hasEaten(fruit)){
            snake.grow();
            fruit.newFruit();
        }
        
        if(game.isPaused() && !game.hasEnded()){
            progress.save(game, snake, fruit);
            
            pauseMenu.show();
            
            if(pauseMenu.outcome() == "Go Back"){
                game.resume();
            }
            else if(pauseMenu.outcome() == "Main Menu"){
                game.end();
            }
        }
        
        mainMenu:
        if(game.isPaused() && game.hasEnded()){
            mainMenu.show();
            
            if(mainMenu.outcome() == "New Game"){
                game.resume();
                game.newGame();
                snake.newSnake();
                fruit.newFruit();
                
                difficultyMenu.show();
                
                if(difficultyMenu.outcome() == "Easy"){
                    game.setDifficulty(Game::EASY);
                }
                else if(difficultyMenu.outcome() == "Normal"){
                    game.setDifficulty(Game::NORMAL);
                }
                else if(difficultyMenu.outcome() == "Extreme"){
                    game.setDifficulty(Game::EXTREME);
                }
                else if(difficultyMenu.outcome() == "Ridiculous!"){
                    game.setDifficulty(Game::RIDICULOUS);
                }
            }
            else if(mainMenu.outcome() == "Load Game"){
                if(progress.fileNotFound()){
                    mainMenu.showError("No game progress saved", "Hit enter to go back");
                    goto mainMenu;
                }
                else{
                    progress.load(game, snake, fruit);
                    game.resume();
                    game.newGame();
                }
                
            }
            else if(mainMenu.outcome() == "Exit Game"){
                game.exit();
            }
        }
        
        snake.show();
        
        fruit.show();
        
        game.showScore(snake.getLength());
    }
    
    endwin();
    
    return 0;
}
