//  fruit.h
//  Snake
//
//  Created by Marcel on 25/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Fruit{
    
    int fruit_x, fruit_y;
    
public:
    WINDOW *local_win;
    
    Fruit(WINDOW *local_win){
        this-> local_win = local_win;
        update();
    }
    
    int get_x(){
        return fruit_x;
    }
    
    int get_y(){
        return fruit_y;
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
    
} fruit(game.gameArea);

