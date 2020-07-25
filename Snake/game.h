//  game.h
//  Snake
//
//  Created by Marcel on 25/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

void defColors();

class Game {
    
    const static int height = 50, width = 100;
    const static int easy = 5, normal = 10, hard = 20; //fps for each difficulty
    int fps = normal; //default fps when the game starts up
    
    enum difficulty {EASY = 0, NORMAL, HARD};
    
public:
    
    enum directions {UP = 1, RIGHT, DOWN, LEFT} dir;
    bool play, pause;
    
    WINDOW *gameArea;
    
    Game(); //just a definition, look below
    
    directions getInput(){
        int input;
        input = getch();
        if(input == KEY_UP && dir != DOWN) dir = UP;
        else if(input == KEY_RIGHT && dir != LEFT) dir = RIGHT;
        else if(input == KEY_DOWN && dir != UP) dir = DOWN;
        else if(input == KEY_LEFT && dir != RIGHT) dir = LEFT;
        else if(input == 27) pause = true; //escape key
        
        return dir;
    }
    
    void setDifficulty(difficulty diff){
        if(diff == EASY) fps = easy;
        else if(diff == NORMAL) fps = normal;
        else if(diff == HARD) fps = hard;
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
