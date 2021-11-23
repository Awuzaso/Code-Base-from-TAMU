// =============================================================================
// [pr03.cpp]
// [Osazuwa Okundaye]
// To Use: 
// [./pr03 <source.ppm> <control.ppm>]
// =============================================================================
#include <cstdlib>
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <cmath>
#include <vector>   
#include <stdlib.h>     /* srand, rand */
#include <time.h>          
#include "Vector2D.h"
#define maximum(x, y, z) ((x) > (y)? ((x) > (z)? (x) : (z)) : ((y) > (z)? (y) : (z))) 
#define minimum(x, y, z) ((x) < (y)? ((x) < (z)? (x) : (z)) : ((y) < (z)? (y) : (z)))
using namespace std;
// =============================================================================
// These variables will store the input ppm image's width, height, and color
// depth values read in from the ppm header.
// =============================================================================
int width, height, maxcolor;
int cTable[255];
FILE *input_fileRead; //*input_fileWrite;


    struct IMG{
        unsigned char red;
        unsigned char green;
        unsigned char blue;        
    };    

    struct IMG_HSV{
         double h;
         double s;
         double v;
    };

    struct RGB{
      float red;
      float green;
      float blue;
    };

IMG *original;
IMG *control;
IMG *result;


string format;
int x, y;
int pixel;
unsigned char red;
unsigned char green;
unsigned char blue;
char rgb[3];
unsigned char *pixmap;
//PPM VARS
int iWidth, iHeight, cWidth, cHeight, oWidth, oHeight;
/////////////////////////////////////////////////////////
///////////////////////////////////
void readPPM(FILE *input_fileRead, IMG *&ppmPixmap, int &width, int &height){
    //Variables//////
    char magicNumber[2];
    char ch;        
    char comment;   
    /*With function "fscanf" we read the input file and store its
    contents within the 2 character array of magic number.*/
    fscanf(input_fileRead, "%s", magicNumber);
    /*Within this if statement, we process the numbers.*/
    if((magicNumber[0] == 'P') && (magicNumber[1] == '6')){
        /*Parse through the first two characters of the file.*/
        ch=fgetc(input_fileRead);        
        ch =fgetc(input_fileRead);
        /*We do this to read over comments.We read comments if there
        are "#" characters present.*/
        while(ch == '#'){
            /*If a "\n" character is read, we are at the end of comment line.
            A line break is introduced.*/
            /*if(comment == '#'){
                cout << endl;
                ch = comment;
                comment=fgetc(input_fileRead);
                
            }        
            else{
            comment = fgetc(input_fileRead);
            cout << comment;
            }*/

            
            if(comment == '\n'){
                
                ch = fgetc(input_fileRead);
                cout << endl;
            }        
            else{
            comment = fgetc(input_fileRead);
            cout << comment;
            }

        }
    /*Put back the last character so we can start at proper position.*/
    ungetc(ch, input_fileRead);//Put back last character.
    /*we are reading the values for width,height and maxcolor and placing
    them within their variables.*/
    fscanf(input_fileRead, "%d %d %d", &width, &height, &maxcolor);
    /*Our output.*/
    cout << "width = " << width << "" << " height = " << height << "" << " maxcolor = " << maxcolor << "" << endl;
    }
    /*Scenario where the inputfile is an invalid format.*/
    else{
        cout << "Incorrect file format. Please try again." << endl;
        //exit(0);
    }
/*Entering code block for creating pixmap.*////////////////////////////////////////////
        fgetc(input_fileRead);
    
  ppmPixmap = new IMG[width * height ];


  for(y = height-1; y >= 0; y--){
    for(x = 0; x < width; x++){
      

      pixel = (y * width + x); 
        /*We grab the values from the stream
    and place them within the character stream*/
    /*red = fgetc(input_fileRead);
    green = fgetc(input_fileRead);
    blue = fgetc(input_fileRead);*/
      //cout << "Reading into pixmap." << endl;
    /*Pixel value is placed within pixmap and incremented subsequently.*/
      ppmPixmap[pixel].red = fgetc(input_fileRead);
    /*Pixel value is placed within pixmap and incremented subsequently.*/    
      ppmPixmap[pixel].green = fgetc(input_fileRead);
    /*Pixel value is placed within pixmap.*/
      ppmPixmap[pixel].blue = fgetc(input_fileRead);
        //cout << "Done." << endl;

    

    }
  }



    
}
////////////////
void RGBtoHSV(int r, int g, int b, double &h, double &s, double &v){
  /*1)NOTE:Setting up variables.*/
  double red, green, blue; 
  double max, min, delta;
  /*2)NOTE:Putting RGB within range of 0 to 1.*/
  red = r / 255.0; green = g / 255.0; blue = b / 255.0;  /* r, g, b to 0 - 1 scale */
  /*3)NOTE:Finding the max and min of the colors.*/
  max = maximum(red, green, blue); 
  min = minimum(red, green, blue);
  /*4)NOTE:VALUE Assign the max as the V of HSV.*/
  v = max;        /* value is maximum of r, g, b */
  /*5)NOTE:Scenario if the max is equal to zero.*/
  if(max == 0){    /* saturation and hue 0 if value is 0 */ 
    s = 0; 
    h = 0; 
  } 
  /*6)NOTE:Scenario if the max is greater than zero.*/
  else{ 
    /*7)SATURATION is derived from the difference between the max and min
    averaged over the max.*/
    s = (max - min) / max;           /* saturation is color purity on scale 0 - 1 */

    delta = max - min; 
       if(delta == 0)                    /* hue doesn't matter if saturation is 0 */ 
      h = 0; 
    
    else{ 
      if(red == max)                  /* otherwise, determine hue on scale 0 - 360 */ 
        h = (green - blue) / delta; 
      else if(green == max) 
        h = 2.0 + (blue - red) / delta; 
      else /* (blue == max) */ 
        h = 4.0 + (red - green) / delta; 
      h = h * 60.0; 
      if(h < 0) 
        h = h + 360.0; 
    } 
  } 
} 
////////////////
//http://www.cs.rit.edu/~ncs/color/t_convert.html
void HSVtoRGB( int &r, int &g, int &b, float h, float s, float v){
    int i;
    float f, p, q, t;
    float rgb[3]={0};
    if( s == 0 ) {
        // achromatic (grey)
        red = green = blue = v;
        return;
    }
    h /= 60;            // sector 0 to 5
    i = floor( h );
    f = h - i;            // factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );
    switch( i ) {
        case 0:
            rgb[0] = v;
            rgb[1]= t;
            rgb[2] = p;
            break;
        case 1:
            rgb[0] = q;
            rgb[1] = v;
            rgb[2] = p;
            break;
        case 2:
            rgb[0] = p;
            rgb[1] = v;
            rgb[2] = t;
            break;
        case 3:
            rgb[0]= p;
            rgb[1] = q;
            rgb[2] = v;
            break;
        case 4:
            rgb[0] = t;
            rgb[1] = p;
            rgb[2]= v;
            break;
        default:        // case 5:
            rgb[0]= v;
            rgb[1] = p;
            rgb[2]= q;
            break;
    }
    r=rgb[0]*(255.0);
    g=rgb[1]*(255.0);
    b=rgb[2]*(255.0);
}
float hermitianCurve(float p0, float p1, float v0, float v1, int t){

    
    float h0 = (2*(t*t*t)) - (3*(t*t)) +1;
    
    float h1 = -(2*(t*t*t)) + (3*(t*t));
   
    float h2 = (t*t*t) - (2*(t*t)) + t;
  
    float h3 = (t*t*t) - (t*t);

    float ans = p0*h0 + p1*h1 + v0*h2 + v1*h3;

    return ans;
}

void DrawLine(Vector2D p0, Vector2D p1)
{
    int CX0, CX1, CY;
   
    CX0 = (int)(255 * p0.x + 0.5);
     CX1 = (int)(255 * p1.x + 0.5);
    for(int CX = CX0 ; CX < CX1 ; CX++)
    {
       float t = CX/255.0;
        CY = (int)((255 * ((1-t) * p0.y + t * p1.y)) + 0.5);     
        cTable[CX] = CY;            
	
    }

}
//////////////////////////////////////////////////////////
//CURVES FUNCTION//
void curves(){//PART 1: Initialze and Assign Variables
    RGB aRGB={0};
    IMG_HSV table[cWidth*cHeight];
    //PART 2: Set the index to the middle most pixel of pixmap.
    srand (time(NULL));
    int randVal = rand() % (cWidth) + 0;  
	cout << "Rand val:" << randVal << endl;
    aRGB.red=control[randVal].red/(255.0);
    aRGB.green=control[randVal].green/(255.0);
    aRGB.blue=control[randVal].blue/(255.0);
    cout << "Values:" << aRGB.red << " " <<  aRGB.green << " " << aRGB.blue << endl;
    double minH,maxH,minS,maxS,minV,maxV;
    
    for(int y=0; y<cHeight; y++) {
        for(int x = 0; x < cWidth; x++){
            double h,s,v;
            int r,g,b;
            h=s=v=0; 
            int i = y * cWidth +x;
             
            r=control[i].red;
            g=control[i].green;
            b=control[i].blue;
            RGBtoHSV(r,g,b,h,s,v);
            table[i].h=h;
            table[i].s=s;
            table[i].v=v;
            }
        }
    minH=maxH=table[0].h;
    minS=maxS=table[0].s;
    minV=maxV=table[0].v;
    for(int iter=1;iter<cWidth*cHeight;iter++){
        if(table[iter].h>maxH)
            maxH=table[iter].h;
        else if(table[iter].h<minH)
            minH=table[iter].h;

        else if(table[iter].s>maxS)
            maxS=table[iter].s;
        else if(table[iter].s<minS)
            minS=table[iter].s;

        else if(table[iter].v>maxV)
            maxV=table[iter].v;
        else if(table[iter].v<minV)
            minS=table[iter].v;        
    }
    cout << "Max and min H: " << maxH <<" "<< minH <<endl;
    cout << "Max and min S: " << maxS <<" "<< minS <<endl;
    cout << "Max and min V: " << maxV <<" "<< minV <<endl;
     
    //PART 4: Setting up control points based partly on adjustRGB values.
    float ptX[5]={0,minH,minS,minV,1};
    float ptY[5]={0,aRGB.red,aRGB.green,aRGB.blue,1};
    Vector2D pT[5];
    //Lets set the control points based on lowest to highest value for x and lowest to highest saturation. 
      
    for(int i=0;i<5;i++){
        pT[i].x=ptX[i];
       pT[i].y=ptY[i];
    }
    
    //PART 5: Setting up rate of change at each point of spline.
        Vector2D rOc[5];
	rOc[0].x=pT[1].x-pT[0].x;
	rOc[0].y=pT[1].y-pT[0].y;
	rOc[4].x=pT[4].x-pT[3].x;
	rOc[4].y=pT[4].y-pT[3].y;

	for(int i=1;i<4;i++){
		rOc[i].x=(pT[i+1].x-pT[i-1].x)/2;
		rOc[i].y=(pT[i+1].y-pT[i-1].y)/2;
		cout << "rate of change" << rOc[i].x << " " << rOc[i].y << endl;
	}
     
    
    //PART 6: Determine the values of fx and fy through the hermCalc function.
        float fx = hermitianCurve(pT[0].x, pT[1].x, rOc[0].x, rOc[1].x, 0);      
        float fy = hermitianCurve(pT[0].y, pT[1].y, rOc[0].y, rOc[1].y, 0);
        //PART 6.1: Determine the values of fx and fy through the hermCalc function.
        Vector2D P0 = (fx, fy);

    //PART 7: Iterate through points on spline to populate the associated color table based on curve.
    //Drawing composite Hermitian Curves.
    int N = 5;//Number of points.
    int S= 300;//Number of samples.
  
    for(int i = 0; i < N; i++){                         
        for(int T = 1; T< S; T++){                    
		float t = T/(1.0*(S-1));
	  	float fx = hermitianCurve(pT[i].x, pT[i+1].x, rOc[i].x, rOc[i+1].x, t);      
		float fy = hermitianCurve(pT[i].y, pT[i+1].y, rOc[i].y, rOc[i+1].y, t);   
		Vector2D P1(fx, fy); 
		DrawLine(P0, P1);          
		P0 = P1;   
        }
    }
	
    // /* 
    //PART 8 Iterate through pixmap and assign colors from color table.
	cout << "Output" << endl;
        for(int y = 0; y < cHeight; y++){               
            for(int x = 0; x < cWidth; x++){
            int i = y * cWidth + x;
            original[i].red = cTable[original[i].red];
            original[i].green = cTable[original[i].green];
            original[i].blue = cTable[original[i].blue];
            }
        }//*/

    
}
//REPLACE FUNCTION//
void replace(){
    
    int r,g,b;
    double h,s,v;
    h=s=v=0;
    IMG_HSV table[cWidth*cHeight];
    //This variable holds the values that will be summed up and used to populate 
        //our edited image.
        //float r,g,b = 0;

        //PULLING HSV INFO FROM CONTROL IMAGE.
        for(int y=0; y<cHeight; y++) {
        for(int x = 0; x < cWidth; x++){
                  
            int i = y * cWidth +x;
             
            r=control[i].red;
            g=control[i].green;
            b=control[i].blue;
            RGBtoHSV(r,g,b,h,s,v);
            
            
            table[i].h=h;
            //cout << "Hello" << endl;
            table[i].s=s;
            table[i].v=v;
            }
        }
    
        
      for(int y=0; y<iHeight; y++) {
        for(int x = 0; x < iWidth; x++){
            int i = y * iWidth +x;
            
            r=original[i].red;
            g=original[i].green;
            b=original[i].blue;
            RGBtoHSV(r,g,b,h,s,v);
            /*if(i==0){
            cout <<r <<" "<< g <<" "<< b <<" "<< h <<" "<< s <<" "<< v << endl;
            }*/
            h=table[i].h;
            
            HSVtoRGB(r,g,b,h,s,v);
            /*if(i==0){
            cout <<r <<" "<< g <<" "<< b <<" "<< h <<" "<< s <<" "<< v << endl;
            }*/
            
            original[i].red=r;
            original[i].green=g;
            original[i].blue=b;
            }
        }    
    
}
//Offset FUNCTION//
void offset(){
    int r,g,b;
    double h,s,v;
    
    IMG_HSV table[cWidth*cHeight];
    float offVal;
    IMG offSet[cWidth];
    for(int y=0; y<cHeight; y++) {
        offVal=0;

        //PART 1:DETERMINE OFFSET VALUE BASED ON HSV VALUE.
        for(int x = 0; x < cWidth; x++){
                  
            int i = y * cWidth + cHeight/100;
             
            r=control[i].red;
            g=control[i].green;
            b=control[i].blue;
            h=s=v=0;
            RGBtoHSV(r,g,b,h,s,v);
       
            table[i].s=s;      

            offVal+=table[i].s;
            }
        
///*
        //PART 2:STORE OFFSET VALUES IN PIXMAP.
        for(int x=0; x<cWidth; x++){
            int i = y * cWidth +x;    
            int new_i=(x+offVal);
                 
		

            if(new_i>cWidth){
            new_i=new_i-cWidth;
            offSet[new_i].red=original[i].red;            
            offSet[new_i].green=original[i].green;
            offSet[new_i].blue=original[i].blue;
            }
            else{
            
            offSet[new_i].red=original[i].red;
            offSet[new_i].green=original[i].green;
            offSet[new_i].blue=original[i].blue;
            }

        }
        
        //PART 3:STORE OFFSET VALUES IN PIXMAP.
        for(int x=0; x<cWidth; x++){
                int i = y * cWidth +x;
                original[i].red=offSet[x].red;
                original[i].green=offSet[x].green;
                original[i].blue=offSet[x].blue;
        }//*/
    }
}
//Histogram FUNCTION//
void histogram(){
/*PART1:Initialize Variables.*/
char a=2;
char b=4;
char c=a+b;
cout << "answer:" << c << endl;


RGB rgbStore[maxcolor+1];
RGB rgbRun[maxcolor+1];
RGB rgbEq[maxcolor+1];
//RGB rgbMin={0};
int iter=0;

while(iter!=maxcolor+1){
rgbStore[iter].red=0;
rgbStore[iter].green=0;
rgbStore[iter].blue=0;
rgbRun[iter].red=0;
rgbRun[iter].green=0;
rgbRun[iter].blue=0;

rgbEq[iter].red=0;
rgbEq[iter].green=0;
rgbEq[iter].blue=0;
iter++;
}
/*PART2:Count the instances of a given color value.*/
for(int y=0;y<cHeight;y++){
//
for(int x=0;x<cWidth;x++){
int i=y*cWidth+x;
int val_r=original[i].red;
int val_g=original[i].green;
int val_b=original[i].blue;
rgbStore[val_r].red++;
rgbStore[val_g].green++;
rgbStore[val_b].blue++;
//cout << "rgbStore:" << rgbStore[val_r].red << endl;
}
}
cout << "Part3" << endl;
/*PART3:Sum up the histogram values.*/
iter=0;
rgbRun[iter].red=rgbStore[iter].red;    
//cout << "rgbStore:" << rgbStore[val_r].red << endl;
rgbRun[iter].green=rgbStore[iter].green;
rgbRun[iter].blue=rgbStore[iter].blue;
iter=1;
while(iter!=maxcolor+1){
int iterOff=iter-1;
rgbRun[iter].red=rgbStore[iter].red+rgbRun[iterOff].red;    
rgbRun[iter].green=rgbStore[iter].green+rgbRun[iterOff].green;
rgbRun[iter].blue=rgbStore[iter].blue+rgbRun[iterOff].blue;
//cout << rgbRun[iter].red << " " << rgbRun[iter].green << " " << rgbRun[iter].blue << endl;
iter++;
}
cout << "Part4" << endl;
/*PART4:*/
int rM,gM,bM;
rM=gM=bM=0;
for(int rCount=0;rM<=0;rCount++){
rM=rgbRun[rCount].red;
}

for(int gCount=0;gM<=0;gCount++){
gM=rgbRun[gCount].blue;
}

for(int bCount=0;bM<=0;bCount++){
bM=rgbRun[bCount].red;
}

//cout << rM << " " << gM << " " << bM << endl;
cout << "Part5" << endl;
/*PART5:*/
for(int i=0;i<maxcolor+1;i++){
float pix=cWidth*cHeight;
rgbEq[i].red=(rgbRun[i].red-rM);
rgbEq[i].green=(rgbRun[i].green-gM);
rgbEq[i].blue=(rgbRun[i].blue-bM);

cout << rgbEq[i].red << " " << rgbEq[i].green << " " <<rgbEq[i].blue << endl;
rgbEq[i].red=round(rgbEq[i].red/(1.0*(pix) - rM) * maxcolor);

rgbEq[i].green=round(rgbEq[i].green/(1.0*(pix) - gM) * maxcolor);
rgbEq[i].blue=round(rgbEq[i].blue/(1.0*(pix) - bM) * maxcolor);




if(rgbEq[i].red<0){
rgbEq[i].red=0;
}
else if(rgbEq[i].green<0){
rgbEq[i].green=0;
}
else if(rgbEq[i].blue<0){
rgbEq[i].blue=0;
}


cout << "rgbEq:" << rgbEq[i].red << " " << rgbEq[i].green << " " << rgbEq[i].blue << endl;

}
cout << "Part6" << endl;
/*PART6:*/
for(int y=0;y<cHeight;y++){
for(int x=0;x<cWidth;x++){
//cout << "x val is: " << x <<endl;
int i=y*cWidth+x;
//cout << "The value of i:" << i<< endl;
char r,g,b;
r=rgbEq[original[i].red].red;
g=rgbEq[original[i].green].green;
b=rgbEq[original[i].blue].blue;
original[i].red=r;
original[i].green=g;
original[i].blue=b;
//cout << "rgb " << original[i].red << " " << g << " " << b << endl;
//cout << "Hello after red of original" <<  i <<endl;    */
}
//cout << "y val is: " << y <<endl;
}
}
//Inversion FUNCTION//
void inversion(){    
    int r,g,b;
    double h,s,v;
    h=s=v=0;
    IMG_HSV table[cWidth*cHeight];
    //This variable holds the values that will be summed up and used to populate 
        //our edited image.
        //float r,g,b = 0;

        //PULLING HSV INFO FROM CONTROL IMAGE.
        for(int y=0; y<cHeight; y++) {
        for(int x = 0; x < cWidth; x++){
                  
            int i = y * cWidth +x;
             
            r=control[i].red;
            g=control[i].green;
            b=control[i].blue;
            RGBtoHSV(r,g,b,h,s,v);
            
            
            table[i].h=h;
            //cout << "Hello" << endl;
            table[i].s=s;
            table[i].v=v;
            }
        }
    
        
      for(int y=0; y<iHeight; y++) {
        for(int x = 0; x < iWidth; x++){
            int i = y * iWidth +x;
            
            r=original[i].red;
            g=original[i].green;
            b=original[i].blue;
            RGBtoHSV(r,g,b,h,s,v);
            /*if(i==0){
            cout <<r <<" "<< g <<" "<< b <<" "<< h <<" "<< s <<" "<< v << endl;
            }*/
            //h=table[i].h;
            
            HSVtoRGB(r,g,b,h,s,v);
            /*if(i==0){
            cout <<r <<" "<< g <<" "<< b <<" "<< h <<" "<< s <<" "<< v << endl;
            }*/
            int val=table[i].v;
            int sv=table[i].s;
            int inv_r=1-r;
            int inv_g=1-g;
            int inv_b=1-b;
            original[i].red=((r*val)+(inv_r*(1-val)))/s;
            
            original[i].green=((g*val)+(inv_g*(1-val)))/s;
            
            original[i].blue=((b*val)+(inv_b*(1-val)))/s;
            }
        }
}
// =============================================================================
// OpenGL Display and Mouse Processing Function Prototypes.
// =============================================================================
static void resize(int,int);
static void display(void);
static void processMouse(int,int,int,int);
static void init(void);
// =============================================================================
// main() Program Entry
// =============================================================================
int main(int argc, char *argv[])
{
  // Check command line arguments and read in the input_fileRead, then call readPPM().
  //commandLine(argc, argv);
  string choice;
  input_fileRead = fopen(argv[1],"r");
     

  readPPM(input_fileRead, original, iWidth, iHeight);
  input_fileRead = fopen(argv[2],"r");
  readPPM(input_fileRead, control, cWidth, cHeight);
  
  cout << "Type in one of the following options." << endl;

  cout << "*************************************" << endl;
  cout << "Curves" << endl;
  cout << "Replace" << endl;
  cout << "Offset" << endl;
  cout << "Histogram" << endl;
  cout << "Inversion" << endl;
  cout << "*************************************" << endl;

  cin >> choice;





  if(choice == "Curves"){
    cout << "Curve function." << endl;
    curves();
  }
  else if(choice == "Replace"){
    cout << "Replace hues function." << endl;
    replace();
  }
  else if(choice == "Offset"){
    cout << "Offset function." << endl;
    offset();
  }
  else if(choice == "Histogram"){
    cout << "Histogram function." << endl;
    histogram();
    
  }
  else if(choice == "Inversion"){
    inversion();
  }
 
  // OpenGL commands
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100); // Where the window will display on-screen.
  glutInitWindowSize(iWidth, iHeight);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow(argv[1]);
  init();
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutMouseFunc(processMouse);
  glutMainLoop();

  // Check command line arguments and read in the output input_fileRead if present.
  // Then call writePPM() if necessary.

  return 0;
}
// =============================================================================
// OpenGL Display and Mouse Processing Functions.
//
// You can read up on OpenGL and modify these functions, as well as the commands
// in main(), to perform more sophisticated display or GUI behavior. This code
// will service the bare minimum display needs for most assignments.
// =============================================================================
static void resize(int w, int h)
{   
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,(w/2),0,(h/2),0,1); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}
static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glDrawPixels(iWidth, iHeight, GL_RGB, GL_UNSIGNED_BYTE, original);
  glFlush();
}
static void processMouse(int button, int state, int x, int y)
{
  if(state == GLUT_UP)
  exit(0);               // Exit on mouse click.
}
static void init(void)
{
  glClearColor(1,1,1,1); // Set background color.
}
