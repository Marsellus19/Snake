//  Progress.h
//  Snake
//
//  Created by Marcel on 15/08/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#ifndef Progress_h
#define Progress_h

class Progress{
    std::string filePath= "/Users/marcel/Documents/XCode/Snake/game_progress.txt";
    
public:
    
    void save(Game game, Snake snake, Fruit fruit);
    
    void load(Game &game, Snake &snake, Fruit &fruit);
    
    void wipe();
    
    bool fileNotFound();
    
    void showError();

};

#endif /* Progress_h */
