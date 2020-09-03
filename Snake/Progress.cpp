//  Progress.cpp
//  Snake
//
//  Created by Marcel on 15/08/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <ncurses.h>
#include "Game.h"
#include "Fruit.h"
#include "Snake.h"
#include "Progress.h"


void Progress::save(Game game, Snake snake, Fruit fruit){
    std::ofstream progressFile;
    progressFile.open(filePath);
    
    
    /* Save snake body coordinates and the direction */
    
    std::list<int> body_y = *snake.getBodyPtr_y();
    std::list<int> body_x = *snake.getBodyPtr_x();
    std::list<int>::iterator y_it, x_it;
    
    for(y_it=body_y.begin(); y_it!=body_y.end(); y_it++){
        progressFile << int(*y_it) << " ";
    }
    
    progressFile << "\n";
    
    for(x_it=body_x.begin(); x_it!=body_x.end(); x_it++){
        progressFile << int(*x_it) << " ";
    }
    
    progressFile << "\n";
    progressFile << game.getInput();
    progressFile << "\n";
    
    
    /* Save fruit coordinates */
    progressFile << fruit.get_y() << "\n" << fruit.get_x();
    progressFile << "\n";
    
    /* Save game difficulty */
    progressFile << game.getFps ();
    progressFile << "\n";
    
    progressFile.close();
    
}

void Progress::load(Game &game, Snake &snake, Fruit &fruit){
    
    std::string dataLine;
    std::string singleNum;
    
    std::ifstream progressFile;
    progressFile.open(filePath);
    
    if(progressFile.is_open()){
        
        /* Load snake body coordinates and set the direction */
        std::list<int> body_y = *snake.getBodyPtr_y();
        std::list<int> body_x = *snake.getBodyPtr_x();
        body_y.clear();
        body_x.clear();
        
        getline(progressFile, dataLine);
        std::stringstream ss(dataLine);
        
        while (ss >> singleNum){
            body_y.push_back(std::stoi(singleNum));
        }
        
        snake.setBody_y(body_y);
        
        getline(progressFile, dataLine);
        std::stringstream pp(dataLine);
        
        while (pp >> singleNum){
            body_x.push_back(std::stoi(singleNum));
        }
        
        snake.setBody_x(body_x);
        
        snake.setHead_y(body_y.front());
        snake.setHead_x(body_x.front());
        
        getline(progressFile, dataLine);
        game.setDirection(Game::directions(std::stoi(dataLine)));
        
        
        /* Load fruit coordinates */
        getline(progressFile, dataLine);
        fruit.set_y(std::stoi(dataLine));
        getline(progressFile, dataLine);
        fruit.set_x(std::stoi(dataLine));
        
        
        /* Load game difficulty */
        getline(progressFile, dataLine);
        game.setFps(std::stoi(dataLine));
        
        progressFile.close();
    }
}

void Progress::wipe(){
    remove(filePath.c_str());
}

bool Progress::fileNotFound(){
    
    std::ifstream progressFile;
    progressFile.open(filePath);
    progressFile.close();
    
    return progressFile.fail();
}

void Progress::showError(){
    bool active = true;
    
    WINDOW *error_win;
    error_win = newwin(8, 80, 5, 10);
    
    std::string message1 = "No game progress saved";
    std::string message2 = "Hit Enter to go back";
    
    unsigned long stringLength1 = message1.size();
    unsigned long stringLength2 = message2.size();
    
    while(active){
        napms(1000 / 10);
        werase(error_win);
        clear();
        
        int input = getch();
        if(input == 10) active = false;
        
        mvwprintw(error_win, 3, (40-((int)stringLength1/2)), "%s", message1.c_str());
        wprintw(error_win, "\n");
        mvwprintw(error_win, 4, (40-((int)stringLength2/2)), "%s", message2.c_str());
        
        box(error_win, 0, 0);
        wrefresh(error_win);
    }
}


