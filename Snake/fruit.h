//  Fruit.h
//  Snake
//
//  Created by Marcel Krol on 25/07/2020.
//  Copyright © 2020 marcelkrol99@gmail.com

#ifndef Fruit_h
#define Fruit_h

class Fruit{
    
    int fruit_x, fruit_y;
    WINDOW *local_win;
    
public:
    
    Fruit(WINDOW *local_win);
    Fruit();
    
    void newFruit();
    
    int get_x();
    int get_y();
    
    void set_y(int fruit_y);
    void set_x(int fruit_x);
    
    void show();
    
};

#endif /* Fruit_h */
