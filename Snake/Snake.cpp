//  Snake.cpp
//  Snake
//
//  Created by Marcel on 05/05/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#include <iostream>
#include <list>
#include <ncurses.h>
#include "Game.h"
#include "Fruit.h"
#include "Snake.h"

Snake::Snake(WINDOW *local_win){
    this-> local_win = local_win;
    newSnake();
}

void Snake::move(Game::directions dir){
    if(dir == Game::UP) head_y --;
    else if(dir == Game::RIGHT) head_x += 2;
    else if(dir == Game::DOWN ) head_y ++;
    else if(dir == Game::LEFT) head_x -= 2;
    
    if(head_y == 0) head_y = 38;
    else if (head_y == 39) head_y = 1;
    else if (head_x == 0) head_x = 78;
    else if (head_x == 80) head_x = 2;
    
    body_y.push_front(head_y);
    body_x.push_front(head_x);
    body_y.pop_back();
    body_x.pop_back();
}

void Snake::show(){
    std::list<int>::iterator y_it, x_it;
    for(y_it=body_y.begin(), x_it=body_x.begin(); y_it!=body_y.end(); y_it++, x_it++){
        wattron(local_win, COLOR_PAIR(2));
        mvwprintw(local_win, *y_it, *x_it, "#");
        wattroff(local_win, COLOR_PAIR(2));
    }
}

bool Snake::hasEaten(Fruit fruit){
    if(fruit.get_y() == head_y && fruit.get_x() == head_x) return true;
    else return false;
}

void Snake::grow(){
        body_y.push_back(body_y.back());
        body_x.push_back(body_x.back());
}

bool Snake::isDead(){
       bool dead = false;
       std::list<int>::iterator y_it, x_it;
       y_it = body_y.begin();
       x_it = body_x.begin();
       y_it++;
       x_it++;
       
       while(y_it!=body_y.end()){
           if(*y_it == head_y && *x_it == head_x) dead = true; /* RIP SNAKE 2020 [*] */
           y_it++; x_it++;
       }
       
       return dead;
}

void Snake::newSnake(){
    body_y.clear();
    body_x.clear();
    head_y = 20;
    head_x = 40;
    body_y.push_front(head_y);
    body_x.push_front(head_x);
}

int Snake::getLength(){
    return int(body_y.size());
}

std::list<int> *Snake::getBodyPtr_y(){
    return &body_y;
}

std::list<int> *Snake::getBodyPtr_x(){
    return &body_x;
}

void Snake::setBody_y(std::list<int> body_y){
    this-> body_y = body_y;
}

void Snake::setBody_x(std::list<int> body_x){
    this-> body_x = body_x;
}

void Snake::setHead_y(int head_y){
    this-> head_y = head_y;
}

void Snake::setHead_x(int head_x){
    this-> head_x = head_x;
}
