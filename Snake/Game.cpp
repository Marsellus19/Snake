//  Game.cpp
//  Snake
//
//  Created by Marcel Krol on 25/07/2020.
//  Copyright © 2020 marcelkrol99@gmail.com

#include <iostream>
#include <ncurses.h>
#include "Game.h"

Game::directions Game::getInput(){
    int input;
    input = getch();
    if(input == KEY_UP && dir != DOWN) dir = UP;
    else if(input == KEY_RIGHT && dir != LEFT) dir = RIGHT;
    else if(input == KEY_DOWN && dir != UP) dir = DOWN;
    else if(input == KEY_LEFT && dir != RIGHT) dir = LEFT;
    else if(input == 27) pauseGame = true; //esc key
    
    return dir;
}

void Game::pause(){
    pauseGame = true;
}

void Game::resume(){
    pauseGame = false;
}

void Game::end(){
    pauseGame = true;
    endGame = true;
}

void Game::newGame(){
    pauseGame = false;
    endGame = false;
}

void Game::resetDirection(){
    setDirection(RIGHT);
}

bool Game::isActive(){
    return playGame;
}

void Game::exit(){
    playGame = false;
}

bool Game::isPaused(){
    if(!endGame && pauseGame) return true;
    else return false;
}

bool Game::hasEnded(){
    if(endGame && pauseGame) return true;
    else return false;
}
    
void Game::setDifficulty(int difficulty){
    fps = difficulty;
}

void Game::setDirection(directions dir){
    this-> dir = dir;
}

int Game::getFps(){
    return fps;
}

void Game::setFps(int fps){
    this-> fps = fps;
}

void Game::showScore(int score){
    WINDOW *score_win;
    score_win = newwin(5, 20, 0, 9);
    
    mvwprintw(score_win, 2, 0, "SCORE: %d", score);
    wrefresh(score_win);
}

void Game::refreshwin(){
    drawBox();
    wrefresh(gameArea);
    napms(1000 / fps);
    werase(gameArea);
    clear();
}

void Game::drawBox(){
    box(gameArea, 0, 0);
}

Game::Game(){
    system("printf '\e[8;50;100t'"); //resize the teminal window to 100x50 //I belive this a macOs only command
    initscr(); //initialize ncurses library
    resizeterm(height, width);
    refresh();
    keypad(stdscr, true); //enable arrow keys for ncurses
    nodelay(stdscr, true); //don't wait for input
    curs_set(0); //hide cursor
    defColors();
    gameArea = newwin(height-10, width-19, 10/2, 19/2);
    playGame = true;
    pauseGame = true;
    endGame = true;
    dir = RIGHT;
    fps = NORMAL; //default fps for when the game starts up for the first time
}

void Game::defColors(){
    use_default_colors();
    start_color();
    
    #define YELLOW 1
    #define CYAN 2
    #define RED 3
    #define BLUE 4
    
    init_pair(1, COLOR_YELLOW, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_BLUE, -1);
}
