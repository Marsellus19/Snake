//  snake.h
//  Snake
//
//  Created by Marcel on 05/05/2020.
//  Copyright © 2020 Marcel. All rights reserved.

void defColors(){
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

class Game {
    
    const static int height = 50, width = 100;
    
public:
    int fps = 10;
    
    enum directions {UP = 1, RIGHT, DOWN, LEFT} dir;
    bool play, pause;
    
    WINDOW *gameArea;
    
    Game(); //just a definition, look below
    
    void getInput(){
        int input;
        input = getch();
        if(input == KEY_UP && dir != DOWN) dir = UP;
        else if(input == KEY_RIGHT && dir != LEFT) dir = RIGHT;
        else if(input == KEY_DOWN && dir != UP) dir = DOWN;
        else if(input == KEY_LEFT && dir != RIGHT) dir = LEFT;
        else if(input == 27) pause = true; //escape key
    }
    
    void drawBox(){
        box(gameArea, 0, 0);
        wrefresh(gameArea);
    }
    
    void refreshwin(){
        drawBox();
        napms(1000 / fps);
        werase(gameArea);
        clear();
    }
    
}game;


class Snake{
    
    Game::directions *dir;
    
    std::list<int> body_y;
    std::list<int> body_x;
    
    WINDOW *local_win;
    
public:
    
    int head_y;
    int head_x;
    
    Snake(WINDOW *local_win, Game::directions *dir){
        this-> local_win = local_win;
        this-> dir = dir;
        newSnake();
    }
    
    void update(){
        if(*dir == Game::UP) head_y --;
        else if(*dir == Game::RIGHT) head_x += 2;
        else if(*dir == Game::DOWN ) head_y ++;
        else if(*dir == Game::LEFT) head_x -= 2;
        
        if(head_y == 0) head_y = 38;
        else if (head_y == 39) head_y = 1;
        else if (head_x == 0) head_x = 78;
        else if (head_x == 80) head_x = 2;
        
        body_y.push_front(head_y);
        body_x.push_front(head_x);
        body_y.pop_back();
        body_x.pop_back();
    }
    
    void grow(){
        body_y.push_back(body_y.back());
        body_x.push_back(body_x.back());
        
        /* old implementation, waits for the tail to reach the fruit      */
        /* position before grownig on screen. The newer one above doesn't */
        //body_y.push_front(head_y);
        //body_x.push_front(head_x);
    }
    
    void show(){
        std::list<int>::iterator y_it, x_it;
        for(y_it=body_y.begin(), x_it=body_x.begin(); y_it!=body_y.end(); y_it++, x_it++){
            wattron(local_win, COLOR_PAIR(2));
            mvwprintw(local_win, *y_it, *x_it, "#");
            wattroff(local_win, COLOR_PAIR(2));
        }
        wrefresh(local_win);
    }
    
    void showScore(){
        WINDOW *score_win;
        score_win = newwin(5, 20, 0, 9);
        
        mvwprintw(score_win, 2, 0, "SCORE: %d", body_y.size());
        wrefresh(score_win);
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
        *dir = Game::RIGHT;
    }
    
}snake(game.gameArea, &game.dir);


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


Game::Game(){
    system("printf '\e[8;50;100t'"); //resize the window to 100x50
    initscr(); //initialize ncurses library
    resizeterm(height, width);
    refresh();
    keypad(stdscr, TRUE); //enable arrow keys for ncurses
    nodelay(stdscr, true); //don't wait for input
    curs_set(0); //hide cursor
    defColors();
    gameArea = newwin(height-10, width-19, 10/2, 19/2);
    play = true;
    pause = true;
}

/*
Menu::Menu(bool *playGame, bool *pauseGame){
    defColors();
    this-> playGame = playGame;
    this-> pauseGame = pauseGame;
}
*/
