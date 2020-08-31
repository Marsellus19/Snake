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
    
    
    void load(Game &game, Snake &snake, Fruit &fruit){
        
        std::string dataLine;
        std::string singleNum;
        
        std::ifstream progressFile;
        progressFile.open("/Users/marcel/Documents/XCode/Snake/game_progress.txt");
        
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

}progress;
