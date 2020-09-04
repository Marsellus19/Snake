//  Progress.h
//  Snake
//
//  Created by Marcel Krol on 15/08/2020.
//  Copyright © 2020 marcelkrol99@gmail.com

#ifndef Progress_h
#define Progress_h

class Progress{
    std::string filePath= "/Documents/game_progress.txt";
    
public:
    
    void save(Game game, Snake snake, Fruit fruit);
    
    void load(Game &game, Snake &snake, Fruit &fruit);
    
    void wipe();
    
    bool fileNotFound();
    
    void showError();

};

#endif /* Progress_h */
