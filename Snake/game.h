//  game.h
//  Snake
//
//  Created by Marcel on 25/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Game {
    const static int height = 50, width = 100;
    int fps;
    
    bool playGame, pauseGame, endGame;
    
public:
    enum difficulty {EASY = 5, NORMAL = 10, EXTREME = 20, RIDICULOUS = 50};
    enum directions {UP = 1, RIGHT, DOWN, LEFT};
    WINDOW *gameArea;
    
private: directions dir;
    
public:
    
    Game();
    
    directions getInput();
    
    void pause();
    void resume();
    bool isPaused();
    
    void end();
    void newGame();
    bool hasEnded();
    
    bool isActive();
    void exit();
    
    void setDirection(directions dir);
    
    void setDifficulty(int difficulty);
    
    int getFps();
    
    void setFps(int fps);
    
    void showScore(int score);
    
    void refreshwin();
    
    void drawBox();
    
    void defColors();
    
};//game;

#endif
