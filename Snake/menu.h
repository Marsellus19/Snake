//  Menu.h
//  Snake
//
//  Created by Marcel on 24/07/2020.
//  Copyright © 2020 Marcel. All rights reserved.
//

#ifndef Menu_h
#define Menu_h

class Menu{
    
    int numberOfMenuItems, currentItem;
    std::string menuMessage, *itemName;
    
    void printInTheMiddle(WINDOW *local_win, int height, std::string text);
 
public:
    
    template <typename T, typename... Ts>
    Menu(std::string menuMessage, T item1, Ts... item2); //Constructor defining a menu object with any number of menu list items
    
    void show();
    
    template <typename N, typename... Ns>
    void showError(N item1, Ns... item2);
    
    std::string outcome();

};


//The constructor has to stay inside the header file because of the use of a template.
template <typename T, typename... Ts>
Menu::Menu(std::string menuMessage, T item1, Ts... item2){
    this-> menuMessage = menuMessage;
    
    std::string item[] = {item1, item2...};
    
    itemName = new std::string[sizeof(item)/sizeof(item[0])];
    
    numberOfMenuItems = sizeof(item) / sizeof(item[0]);
    
    for(int i = 0; i< numberOfMenuItems; i++){
        itemName[i] = item[i];
    }
}

#endif /* Menu_h */

