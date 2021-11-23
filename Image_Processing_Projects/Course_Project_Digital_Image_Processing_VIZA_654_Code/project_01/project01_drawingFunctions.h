//
//  project01_drawingFunctions.h
//  VIZA_654_Project_01
//
//  Created by Awuzaso on 12/18/16.
//  Copyright © 2016 Awuzaso. All rights reserved.
//

#ifndef project01_drawingFunctions_h
#define project01_drawingFunctions_h

#include <cmath>


unsigned char* npixmap;

void drawRed(int i) {
    npixmap[i++] = 255;
    npixmap[i++] = 0;
    npixmap[i] = 0;
}

void drawGreen(int i) {
    npixmap[i++] = 0;
    npixmap[i++] = 255;
    npixmap[i] = 0;
}

void drawBlue(int i) {
    npixmap[i++] = 0;
    npixmap[i++] = 0;
    npixmap[i] = 255;
}

void drawAllColors(int i, int x, int y, int width, int height) {
    //Green quadrant.
    if ((x>(width / 2)) && (y >= (height / 2))) {
        npixmap[i++] = 0;
        npixmap[i++] = 255;
        npixmap[i] = 0;
    }
    //Red quadrant.
    if ((x <= (width / 2)) && (y >= (height / 2))) {
        npixmap[i++] = 255;
        npixmap[i++] = 0;
        npixmap[i] = 0;
    }
    //Blue quadrant.
    if ((x <= (width / 2)) && (y <= (height / 2))) {
        npixmap[i++] = 0;
        npixmap[i++] = 0;
        npixmap[i] = 255;
    }
    //Yellow quadrant.
    if ((x >= (width / 2)) && (y<(height / 2))) {
        npixmap[i++] = 255;
        npixmap[i++] = 255;
        npixmap[i] = 0;
    }
}

void drawCircle(int i, int x, int y, int width) {
    float diameter = 10000;
    float y_portion = pow((y - width / 2), 2);
    float x_portion = pow((x - width / 2), 2);
    float areaCircle = x_portion + y_portion;
    
    if (areaCircle <= diameter) {		//inside circle yellow. Calls distance function and radius int
        npixmap[i++] = 255;
        npixmap[i++] = 255;
        npixmap[i++] = 0;
    }
    else {			//outside circle blue
        npixmap[i++] = 0;
        npixmap[i++] = 0;
        npixmap[i++] = 255;
    }
}

void drawOther(int i, int x, int y, int width) {
    float diameter = 50000;
    float y_portion = pow((y - width / 2), 2);
    float x_portion = pow((x - width / 2), 2);
    float areaCircle = x_portion + y_portion;
    
    if (areaCircle <= diameter / 4) {		//inside circle yellow. Calls distance function and radius int
        npixmap[i++] = x*y;
        npixmap[i++] = sin(y)*i;
        npixmap[i++] = y;
    }
    else if (areaCircle <= diameter / 2) {		//inside circle yellow. Calls distance function and radius int
        npixmap[i++] = x*x;
        npixmap[i++] = y;
        npixmap[i++] = y;
    }
    else if (areaCircle <= diameter) {			//outside circle blue	
        npixmap[i++] = x*y;
        npixmap[i++] = x*y;
        npixmap[i++] = y;
    }
}



#endif /* project01_drawingFunctions_h */
