//
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
#include "snake.h"
#include "menus.h"

int main(int argc, const char * argv[]) {
    
    while(game.play){
        game.refreshwin();
        
        game.getInput();
        
        if(game.pause) main_menu.show();
        
        snake.update();
        
        if(snake.isDead()){
            main_menu.show();
            snake.newSnake();
        }
        
        if(fruit.isEaten()){
            fruit.update();
            snake.grow();
        }
        
        snake.show();
        
        fruit.show();
        
        snake.showScore();
    }
    
    endwin();
    
    return 0;
}
