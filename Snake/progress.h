//
//  progress.h
//  Snake
//
//  Created by Marcel on 31/08/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

class Progress{
public:
    
    void save(Game game, Snake snake, Fruit fruit){
        std::ofstream progressFile;
        progressFile.open("/Users/marcel/Documents/XCode/Snake/game_progress.txt");
        
        
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
        progressFile << snake.getDir();
        progressFile << "\n";
        
        
        /* Save fruit coordinates */
        progressFile << fruit.get_y() << " " << fruit.get_x();
        progressFile << "\n";
        
        /* Save game difficulty */
        progressFile << game.getDifficulty();
        progressFile << "\n";
        
        progressFile.close();
        
    }
    
    
    void load(){
        
        
    }

    
    
}progress;
