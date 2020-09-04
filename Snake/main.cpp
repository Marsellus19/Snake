//
//        _______  __    _  _______  ___   _  _______      _______  _______  __   __  _______
//       |       ||  |  | ||   _   ||   | | ||       |    |       ||   _   ||  |_|  ||       |
//       |  _____||   |_| ||  |_|  ||   |_| ||    ___|    |    ___||  |_|  ||       ||    ___|
//       | |_____ |       ||       ||      _||   |___     |   | __ |       ||       ||   |___
//       |_____  ||  _    ||       ||     |_ |    ___|    |   ||  ||       ||       ||    ___|
//        _____| || | |   ||   _   ||    _  ||   |___     |   |_| ||   _   || ||_|| ||   |___
//       |_______||_|  |__||__| |__||___| |_||_______|    |_______||__| |__||_|   |_||_______|
//
//
//  main.cpp
//
//  Created by Marcel Krol on 04/05/2020.
//  Copyright © 2020 marcelkrol99@gmail.com

//Disclaimer. This game was written for macOS. It hasn't been tested on Windows, althought it should work with very minor adjustments. I left comments next to macOS only commands

#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <list>
#include <string>
#include "Game.h"
#include "Fruit.h"
#include "Snake.h"
#include "Menu.h"
#include "Progress.h"

Game game;
Fruit fruit(game.gameArea); //The gameArea is a window used by the ncurses library where the game happens
Snake snake(game.gameArea); //Both fruit and snake objects need acces to it so that they appear on screen

Progress progress;

/* Each object derived fromm the Menu class is a separate menu. The first parameter is a menu message and the following
   ones are individual menu list items. */
Menu mainMenu("Welcome to the game of snake!", "New Game", "Load Game", "Exit Game");
Menu difficultyMenu("Choose difficulty", "Easy", "Normal", "Extreme", "Ridiculous!");
Menu pauseMenu("Paused!", "Go Back", "Main Menu");
Menu deadMenu("Game Over!!!", "Play Again", "Main Menu");


int main(int argc, const char * argv[]) {
   
    /* Main game loop */
    while(game.isActive()){
        game.refreshwin();
        
        snake.move(game.getInput());
        
        /* Menu displayed after the snake runs into itself */
        if(snake.isDead()){
            progress.wipe();
            
            deadMenu.show();
            
            if(deadMenu.outcome() == "Play Again"){
                game.newGame();
                snake.newSnake();
                fruit.newFruit();
            }
            else if(deadMenu.outcome() == "Main Menu"){
                game.end();
            }
        }
        
        if(snake.hasEaten(fruit)){
            snake.grow();
            fruit.newFruit();
        }
        
        /* Pause menu */
        if(game.isPaused()){
            progress.save(game, snake, fruit);
            
            pauseMenu.show();
            
            if(pauseMenu.outcome() == "Go Back"){
                game.resume();
            }
            else if(pauseMenu.outcome() == "Main Menu"){
                game.end();
            }
        }
        
        /* Main menu */
        mainMenu:
        if(game.hasEnded()){
            mainMenu.show();
            
            if(mainMenu.outcome() == "New Game"){
                game.newGame();
                game.resetDirection();
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
                    progress.showError();
                    goto mainMenu;
                    // I know that some people find the use of goto inappropriate, however I think I can be helpful and there's nothing wrong with it when used correctly.
                    // In this instance it prevents the main loop from refreshing and therefore showing the game Area with snake for a split second
                    // It could be achieved differently however the effort is not worth it in my opinion.
                }
                else{
                    progress.load(game, snake, fruit);
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
