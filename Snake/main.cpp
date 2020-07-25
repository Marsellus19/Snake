//  main.cpp
//  Snake
//
//  Created by Marcel on 04/05/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#include <iostream>
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
        
        if(game.pause && !game.end){
            showPauseMenu();
        }
        if(game.pause && game.end){
            showMainMenu();
        }
        
        if(snake.isDead()){
            showDeadMenu();
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
