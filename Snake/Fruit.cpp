//  Fruit.cpp
//  Snake
//
//  Created by Marcel on 25/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#include <iostream>
#include <ncurses.h>
#include "Game.h"
#include "Fruit.h"


Fruit::Fruit(WINDOW *local_win){
    this-> local_win = local_win;
    newFruit();
}

Fruit::Fruit(){
    newFruit();
}

void Fruit::newFruit(){
    fruit_x = ((rand() % 38) * 2) +2;
    fruit_y = (rand() % 38) +1;
}

int Fruit::get_x(){
    return fruit_x;
}

int Fruit::get_y(){
    return fruit_y;
}

void Fruit::set_y(int fruit_y){
    this-> fruit_y = fruit_y;
}

void Fruit::set_x(int fruit_x){
    this-> fruit_x = fruit_x;
}

void Fruit::show(){
    wattron(local_win, COLOR_PAIR(1));
    mvwprintw(local_win, fruit_y, fruit_x, "*");
    wattroff(local_win, COLOR_PAIR(1));
}
