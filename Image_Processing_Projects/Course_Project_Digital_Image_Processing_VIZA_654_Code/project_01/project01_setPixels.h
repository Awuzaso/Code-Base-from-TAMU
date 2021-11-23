//
//  project01_setPixels.h
//  VIZA_654_Project_01
//
//  Created by Awuzaso on 12/18/16.
//  Copyright © 2016 Awuzaso. All rights reserved.
//

#ifndef project01_setPixels_h
#define project01_setPixels_h

#include <string>
#include <iostream>

#include "project01_drawingFunctions.h"

using namespace std;

unsigned char* setPixels(string type, int imageWidth, int height){
    //unsigned char* npixmap[imageWidth * height * 3];
    npixmap = new unsigned char[imageWidth * height * 3];
    
    for (int currentPixelColumn = 0; currentPixelColumn < height; currentPixelColumn++) /*Scanline number.*/ {
        
        for (int currentPixelRow = 0; currentPixelRow < imageWidth; currentPixelRow++) /*Pixel number on scanline.*/ {
            
            int pixel = (currentPixelColumn * imageWidth + currentPixelRow) * 3; /*"i" signifies the value of the pixel value fetched from scanline.*/
            /*At this point within the function,we are assigning color values to our RGB npixmap array.*/
            /*This block of code corresponds to command line arguments dictating color of npixmap.*/
            if (type == "red"){
                drawRed(pixel);
            }
            else if (type == "green"){
                drawGreen(pixel);
            }
            else if (type == "blue"){
                drawBlue(pixel);
            }
            else if (type == "all"){
                drawAllColors(pixel,currentPixelRow, currentPixelColumn,imageWidth,height);
            }
            else if (type == "circle") {
                drawCircle(pixel,currentPixelRow, currentPixelColumn,imageWidth);
            }
            else if (type == "other"){
                drawOther(pixel, currentPixelRow, currentPixelColumn, imageWidth);
            }
        }
    }
    return npixmap;
}




#endif /* project01_setPixels_h */
