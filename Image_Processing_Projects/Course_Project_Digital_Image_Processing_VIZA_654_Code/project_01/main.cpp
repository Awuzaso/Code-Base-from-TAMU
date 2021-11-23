//
//  main.cpp
//  VIZA_654_Project_01
//
//  Created by Awuzaso on 12/18/16.
//  Copyright © 2016 Awuzaso. All rights reserved.
//

#include "glutFunctions.h"
#include "programClass.h"
#include "project01_setPixels.h"
#include "instructionForUser.h"



using namespace std;

int main(int argc, char **argv)
{
    //1
    string choice = instructionForUser();
    
    //2
    graphicProgram project01 (800, 800, "Rasterization Program");
    
    //3
    int width = project01.getWindowWidth();
    int height = project01.getWindowHeight();
    const char* title = project01.getWindowTitle();
    
    //4
    //
    project01.setPixMap(setPixels(choice,width, height));
    unsigned char* pmap = project01.getPixMap();
    
    //5
    glutInitialize(argc, argv, width, height,pmap, title);
    
}
