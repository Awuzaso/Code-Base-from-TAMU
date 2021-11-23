//
//  programClass.h
//  VIZA_654_Project_01
//
//  Created by Awuzaso on 12/18/16.
//  Copyright © 2016 Awuzaso. All rights reserved.
//

#ifndef programClass_h
#define programClass_h

class graphicProgram {
    
private:
    int windowHeight;
    int windowWidth;
    const char* windowTitle;
    unsigned char *gPixmap;
    
public:
    //Constructors
    graphicProgram(int nHeight, int nWidth, const char* nTitle);
    
    graphicProgram();
    
    //Set functions.
    void setWindowHeight(int nHeight);
    
    void setWindowWidth(int nWidth);
    
    void setWindowTitle(const char* nTitle);
    
    void setPixMap(unsigned char* nPixMap);
    
    //Get functions.
    int getWindowHeight();
    
    int getWindowWidth();
    
    const char* getWindowTitle();
    
    unsigned char* getPixMap();
};

//Constructors
graphicProgram::graphicProgram(int nHeight, int nWidth, const char* nTitle) {
    windowHeight = nHeight;
    windowWidth = nWidth;
    windowTitle = nTitle;
}

graphicProgram::graphicProgram() {
    windowHeight = 500;
    windowWidth = 500;
    windowTitle = "Graphic Program";
}

//Set functions.
void graphicProgram::setWindowHeight(int nHeight) {
    windowHeight = nHeight;
}

void graphicProgram::setWindowWidth(int nWidth) {
    windowWidth = nWidth;
}

void graphicProgram::setWindowTitle(const char* nTitle) {
    windowTitle = nTitle;
}

void graphicProgram::setPixMap(unsigned char* nPixMap) {
    gPixmap = nPixMap;
}
//Get functions.
int graphicProgram::getWindowHeight() {
    int rHeight = windowHeight;
    return rHeight;
    
}

int graphicProgram::getWindowWidth() {
    return windowWidth;
}

const char* graphicProgram::getWindowTitle() {
    return windowTitle;
}

unsigned char* graphicProgram::getPixMap(){
    return gPixmap;
}






#endif /* programClass_h */
