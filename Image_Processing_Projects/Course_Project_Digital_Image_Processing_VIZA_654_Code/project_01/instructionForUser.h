//
//  instructionForUser.h
//  VIZA_654_Project_01
//
//  Created by Awuzaso on 12/18/16.
//  Copyright © 2016 Awuzaso. All rights reserved.
//

#ifndef instructionForUser_h
#define instructionForUser_h

#include <string>
#include <iostream>
using namespace std;
string choice;

void message() {
    cout << "Select choice." << endl;
    cout << "Type ""red"" for a red window." << endl;
    cout << "Type ""green"" for a red window." << endl;
    cout << "Type ""blue"" for a red window." << endl;
    cout << "Type ""all"" for all colored window." << endl;
    cout << "Type ""circle"" for a red window." << endl;
    cout << "Type ""other"" for a red window." << endl;
    cin >> choice;
}

void evaluateChoice() {
    bool status = false;
    while (status == false) {
        
        if (choice == "red") {
            status = true;
        }
        else if (choice == "green") {
            status = true;
        }
        else if (choice == "blue") {
            status = true;
        }
        else if (choice == "all") {
            status = true;
        }
        else if (choice == "circle") {
            status = true;
        }
        else if (choice == "other") {
            status = true;
        }
        else {
            status = false;
            cout << "Meow! Incorrect input. Please try again." << endl;
            message();
        }
        
    }
    
}
string instructionForUser() {
    message();
    evaluateChoice();
    return choice;
    
}





#endif /* instructionForUser_h */
