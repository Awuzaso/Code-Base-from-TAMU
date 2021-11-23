//
//  glutFunctions.h
//  VIZA_654_Project_01
//
//  Created by Awuzaso on 12/18/16.
//  Copyright © 2016 Awuzaso. All rights reserved.
//

#ifndef glutFunctions_h
#define glutFunctions_h

#include <GLUT/GLUT.h>



int width;
int height;
unsigned char* pixmap;
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.3, 0.3, 1.0);
    glutSwapBuffers();
}

static void windowResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (w / 2), 0, (h / 2), 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Function responsible for graphics display.
static void windowDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    /*Call to "glRasterPos2i(0,0)" assures that the image will be
     drawn in the window starting at the lower left corner (pixel 0 on scanline 0).*/
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixmap);
    /*Procedure, "glDrawPixels()" that takes an image pixmap and
     displays it in the graphics window.*/
    
    /*The width and height parameters to "glDrawPixels()" specify the width, in pixels,
     of a scanline, and the height of the image, in the number of scanlines.*/
    
    /*The GL_RGB parameter indicates that the pixels are stored as RGB
     quadruples, with color primaries stored in the order red, green and blue.*/
    
    /*GL_UNSIGNED_BYTE parameter indicates that each color primary is
     stored in a single byte and treated as an unsigned number between zero
     and 255.*/
    glFlush();
}
static void processMouse(int button, int state, int x, int y)
{
    if (state == GLUT_UP){
        //exit(0);               // Exit on mouse click.

    }
}

void glutInitialize(int argc, char **argv, int n_width, int n_height, unsigned char *n_pixmap,const char* nameOfProgram) {
    
    width = n_width;
    height = n_height;
    pixmap = n_pixmap;
    //setPixels(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(250, 250);
    glutInitWindowSize(width, height);
    glutCreateWindow(nameOfProgram);
    glClearColor(1, 1, 1, 1); // Set background color.
    glutReshapeFunc(windowResize);
    glutDisplayFunc(windowDisplay);
    glutMouseFunc(processMouse);
    glutMainLoop();
}

#endif /* glutFunctions_h */
