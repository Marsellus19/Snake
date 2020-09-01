//  fruit.h
//  Snake
//
//  Created by Marcel on 25/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Fruit{
    
    int fruit_x, fruit_y;
    WINDOW *local_win;
    
public:
    
    Fruit(WINDOW *local_win){
        this-> local_win = local_win;
        newPos();
    }
    
    Fruit(){
        newPos();
    }
    
    void newPos(){
        fruit_x = ((rand() % 38) * 2) +2;
        fruit_y = (rand() % 38) +1;
    }
    
    int get_x(){
        return fruit_x;
    }
    
    int get_y(){
        return fruit_y;
    }
    
    void set_y(int fruit_y){
        this-> fruit_y = fruit_y;
    }
    
    void set_x(int fruit_x){
        this-> fruit_x = fruit_x;
    }
    
    void show(){
        wattron(local_win, COLOR_PAIR(YELLOW));
        mvwprintw(local_win, fruit_y, fruit_x, "*");
        wattroff(local_win, COLOR_PAIR(YELLOW));
        //wrefresh(local_win);
    }
    
} fruit(game.gameArea);

