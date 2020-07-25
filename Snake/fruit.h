//
//  fruit.h
//  Snake
//
//  Created by Marcel on 25/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Fruit{
public:
    int *snake_head_y, *snake_head_x;
    int fruit_x, fruit_y;
    WINDOW *local_win;
    
    Fruit(WINDOW *local_win, int *head_y, int *head_x){
        this-> local_win = local_win;
        this-> snake_head_y = head_y;
        this-> snake_head_x = head_x;
        update();
    }
    
    bool isEaten(){
        if(fruit_y == *snake_head_y && fruit_x == *snake_head_x) return true;
        else return false;
    }
    
    void update(){
        fruit_x = ((rand() % 38) * 2) +2;
        fruit_y = (rand() % 38) +1;
    }
    
    void show(){
        wattron(local_win, COLOR_PAIR(1));
        mvwprintw(local_win, fruit_y, fruit_x, "*");
        wattroff(local_win, COLOR_PAIR(1));
        wrefresh(local_win);
    }
    
} fruit(game.gameArea, &snake.head_y, &snake.head_x);

