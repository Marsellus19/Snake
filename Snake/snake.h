//  snake.h
//  Snake
//
//  Created by Marcel on 05/05/2020.
//  Copyright © 2020 Marcel. All rights reserved.

class Snake{
    
    Game::directions dir;
    
    std::list<int> body_y;
    std::list<int> body_x;
    
    int head_y;
    int head_x;
    
    WINDOW *local_win;
    
public:
    
    Snake(WINDOW *local_win){
        this-> local_win = local_win;
        newSnake();
    }
    
    void move(Game::directions dir){
        this-> dir = dir;
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
    
    void show(){
        std::list<int>::iterator y_it, x_it;
        for(y_it=body_y.begin(), x_it=body_x.begin(); y_it!=body_y.end(); y_it++, x_it++){
            wattron(local_win, COLOR_PAIR(CYAN));
            mvwprintw(local_win, *y_it, *x_it, "#");
            wattroff(local_win, COLOR_PAIR(CYAN));
        }
        wrefresh(local_win);
    }
    
    bool hasEaten(Fruit fruit){
        if(fruit.get_y() == head_y && fruit.get_x() == head_x) return true;
        else return false;
    }
    
    void grow(){
        
        #define NEW_GROWING_IMP
        
        #ifdef NEW_GROWING_IMP
            body_y.push_back(body_y.back());
            body_x.push_back(body_x.back());
        #endif
        
        /* Old implementation, waits for the tail to reach the fruit position before grownig on screen.  */
        /* The newer one above doesn't                                                                   */
        #ifndef NEW_GROWING_IMP
            body_y.push_front(head_y);
            body_x.push_front(head_x);
        #endif
    }
    
    int getLength(){
        int length = int(body_y.size());
        return length;
    }
    
    bool isDead(){
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
    
    void newSnake(){
        body_y.clear();
        body_x.clear();
        head_y = 20;
        head_x = 40;
        body_y.push_front(head_y);
        body_x.push_front(head_x);
    }
    
    void saveProgress(){
        std::ofstream progressFile;
        progressFile.open("/Users/marcel/Documents/XCode/Snake/game_progress.txt");
        
        std::list<int>::iterator y_it, x_it;
        for(y_it=body_y.begin(); y_it!=body_y.end(); y_it++){
            progressFile << int(*y_it) << " ";
        }
        
        progressFile << "\n";
        
        for(x_it=body_x.begin(); x_it!=body_x.end(); x_it++){
            progressFile << int(*x_it) << " ";
        }
        
        progressFile << "\n";
        progressFile << dir;
    }
    
    //working sorta?
    void loadProgress(){
        body_y.clear();
        body_x.clear();
        
        std::string dataLine;
        std::string singleNum;
        
        std::ifstream progressFile;
        progressFile.open("/Users/marcel/Documents/XCode/Snake/game_progress.txt");
        
        getline(progressFile, dataLine);
        std::stringstream ss(dataLine);

        while (ss >> singleNum){
            body_y.push_back(std::stoi(singleNum));
        }
        
        getline(progressFile, dataLine);
        std::stringstream pp(dataLine);

        while (pp >> singleNum){
            body_x.push_back(std::stoi(singleNum));
        }
        
        getline(progressFile, dataLine);
        
        dir = Game::directions(std::stoi(dataLine));
        
        head_y = body_y.front();
        head_x = body_x.front();
        
        progressFile.close();
    }
    
}snake(game.gameArea);
