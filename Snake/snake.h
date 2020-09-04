//  Snake.h
//  Snake
//
//  Created by Marcel Krol on 05/05/2020.
//  Copyright © 2020 marcelkrol99@gmail.com

#ifndef Snake_h
#define Snake_h

class Snake{
    
    std::list<int> body_y;
    std::list<int> body_x;
    
    int head_y;
    int head_x;
    
    WINDOW *local_win;
    
public:
    
    Snake(WINDOW *local_win);
    
    void move(Game::directions dir);
    
    void show();
    
    bool hasEaten(Fruit fruit);
    
    void grow();
    
    bool isDead();
    
    void newSnake();
    
    int getLength();
    
    std::list<int> *getBodyPtr_y();
    std::list<int> *getBodyPtr_x();
    
    void setBody_y(std::list<int> body_y);
    void setBody_x(std::list<int> body_x);
    
    void setHead_y(int head_y);
    void setHead_x(int head_x);
    
};

#endif /* Snake_h */
