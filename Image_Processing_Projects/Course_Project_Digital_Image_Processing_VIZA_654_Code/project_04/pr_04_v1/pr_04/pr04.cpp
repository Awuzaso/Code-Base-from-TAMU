// =============================================================================
// [pr04.cpp]
// [Osazuwa Okundaye]
// To Use: 
// [./pr04 <source.ppm> <control.ppm>]
// =============================================================================
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <vector>              
#include "Vector2D.h"
using namespace std;
// =============================================================================
// These variables will store the input ppm image's width, height, and color
// depth values read in from the ppm header.
// =============================================================================
int width, height, maxcolor;
FILE *input_fileRead; //*input_fileWrite;


	struct IMG{
		unsigned char red;
		unsigned char green;
		unsigned char blue;		
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
Vector2D getNormal(Vector2D pt1, Vector2D pt2){
	Vector2D n_vec;
	float mag;
	n_vec.x=pt1.y-pt2.y;
	n_vec.y=-(pt1.x-pt2.x);
	/*Getting the unit vector.*/
	mag=sqrt(pow(n_vec.x,2)+pow(n_vec.y,2));
	n_vec.x=n_vec.x/mag;
	n_vec.y=n_vec.y/mag;

	return n_vec;
}
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
/////////////////////////////////////////////////////////////////////////////////////
void normal(IMG *&ppmPixmap, int &width, int &height){
	cout << "Normal function." << endl;
	
}
///////////////////////////////////////////////////////////////
void motionBlur(IMG *&ppmPixmap, IMG *&cPix, int &width, int &height){
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void emboss(IMG *&ppmPixmap, IMG *&cPix, int &width, int &height){
	cout << "Emboss function." << endl;
	//float kernel[3][3] = {{sin(angle*3.14/180),sin(angle*3.14/180),cos(angle*3.14/180)},
			//{sin(angle*3.14/180),0,-sin(angle*3.14/180)},
			//{-cos(angle*3.14/180),-sin(angle*3.14/180),-sin(angle*3.14/180)}};
	
	int kSize = 3;
        int kHalf = 1;
	IMG nC[width*height];
	//This variable holds the values that will be summed up and used to populate 
        //our edited image.
        float r,g,b = 0;

        for(int y=0; y<height; y++) {
		for(int x = 0; x < width; x++){
			int i = y * width +x;
				int cPixAvg=(cPix[i].red+cPix[i].blue+cPix[i].green)/3;
				int ppmAvg=(ppmPixmap[i].red+ppmPixmap[i].blue+ppmPixmap[i].green)/3;
				int angle=ppmAvg-cPixAvg;


				float kernel[3][3] = {{sin(angle*3.14/180),sin(angle*3.14/180),cos(angle*3.14/180)},
						      {sin(angle*3.14/180),0,-sin(angle*3.14/180)},
						      {-cos(angle*3.14/180),-sin(angle*3.14/180),-sin(angle*3.14/180)}};











				for(int j = y-kHalf, ky = 0; ky<kSize; j++,ky++)
					for(int k = x-kHalf, kx = 0; kx <kSize; k++,kx++){
						
						if(k > width-1 || k < 0)
	    					k = x;

						if(j > height-1 || j < 0)
	    					j = y;
						
						r += ((ppmPixmap[j*width+k].red * kernel[kx][ky]));
	 					g += ((ppmPixmap[j*width+k].green * kernel[kx][ky]));
	  					b += ((ppmPixmap[j*width+k].blue * kernel[kx][ky]));
					}
					r = fmin(fmax((r+127),0),255);
					g = fmin(fmax((g+127),0),255);
					b = fmin(fmax((b+127),0),255);
					
					nC[i].red=r;
					nC[i].green=g;
					nC[i].blue=b;
					r=g=b=0;
		}
	}
	for(int i =0;i<width*height;i++){
		ppmPixmap[i].red=nC[i].red;
		ppmPixmap[i].green=nC[i].green;
		ppmPixmap[i].blue=nC[i].blue;
	}
}

void smartBlur(IMG *&ppmPixmap, IMG *&cPix, int &width, int &height){
	cout << "Smart blur function." << endl;
	
	IMG nC[width*height];
	cout << "Flag." << endl;
	//This variable holds the values that will be summed up and used to populate 
        //our edited image.
        float r,g,b = 0;
        for(int y=0; y<height; y++) {
		//cout << "Entering for y " << y << "time(s)." << endl;
		for(int x = 0; x < width; x++){
		//cout << "Entering for x " << x << "time(s)." << endl;
			int i = y * width +x;
		//cout << "Value i is : " << i << endl;
///////////////////////////////////////////////////
		int kSize = cPix[i].red/10,gx, gy, k = 0, l =0;	
		
		int kHalf = kSize/2;
		float kSum=0;
  		float kernel[kSize][kSize]; 
  		float sigma = pow(2.0, 0.5);
  		//SETTING UP KERNEL.ENTERING ROW.
		for (int ky = -kSize/2; ky <= kSize/2; ky ++) {
			for (int kx = -kSize/2; kx <= kSize/2; kx ++) {
			
			   //KERNEL VALUE IS EQUAL TO THE GUASSIAN FUNCTION ASSIGNING WEIGHTS.
				kernel[k][l] = (1/(2*3.14*sigma*sigma))*exp(-(kx*kx + ky*ky)/(2*sigma*sigma));
				kSum=kSum+kernel[k][l];
				//cout << "Kernel value: " << kernel[k][l] << endl;
				//INCREMENT VALUE 'l"
				l++;	
				//ONCE VALUE L IS EQUAL TO kSize, L VALUE IS SET TO 0 and K VALUE IS INCREMENTED, GOING TO NEXT COLUMN.
				if(l == kSize)
				{
					l = 0;
					k++;
					if(k == kSize)
					{
					   k == 0;	
					}	
				}
			}
		}
			//SETTING UP KERNEL.ENTERING ROW.
		for (int ky = -kSize/2; ky <= kSize/2; ky ++) {
			for (int kx = -kSize/2; kx <= kSize/2; kx ++) {
			
			   //KERNEL VALUE IS EQUAL TO THE GUASSIAN FUNCTION ASSIGNING WEEIGHTS.
				kernel[k][l] = ((1/(2*3.14*sigma*sigma))*exp(-(kx*kx + ky*ky)/(2*sigma*sigma)))/kSum;
				//kSum=kSum+kernel[k][l];
				//cout << "Kernel value: " << kernel[k][l] << endl;
				//INCREMENT VALUE 'l"
				
			}
		}
////////////////////////////////////////////////////////////			
				for(int j = y-kHalf, ky = 0; ky<kSize; j++,ky++)
					for(int k = x-kHalf, kx = 0; kx <kSize; k++,kx++){
						
						if(k > width-1 || k < 0)
	    					k = x;

						if(j > height-1 || j < 0)
	    					j = y;
						
						r += ((ppmPixmap[j*width+k].red * kernel[kx][ky]));
	 					g += ((ppmPixmap[j*width+k].green * kernel[kx][ky]));
	  					b += ((ppmPixmap[j*width+k].blue * kernel[kx][ky]));
					}
					
					nC[i].red=r;
					nC[i].green=g;
					nC[i].blue=b;
					r=g=b=0;
		}
	}
	for(int i =0;i<width*height;i++){
		ppmPixmap[i].red=nC[i].red;
		ppmPixmap[i].green=nC[i].green;
		ppmPixmap[i].blue=nC[i].blue;
	}
}

void dilation(IMG *&ppmPixmap, IMG *&cPix,int &width, int &height){
	
	cout << "Dilation function." << endl;
	
	IMG nC[width*height];
	IMG max;
	//This variable holds the values that will be summed up and used to populate 
        //our edited image.
        //float r,g,b = 0;

        for(int y=0; y<height; y++) {
		for(int x = 0; x < width; x++){
			int i = y * width +x;
			max.red=ppmPixmap[i].red;
			max.green=ppmPixmap[i].green;
			max.blue=ppmPixmap[i].blue;

			//int greatest=fmax(max.red,max.blue);
			//greatest=fmax(greatest,max.green);
			int kSize = cPix[i].red/10;
        		int kHalf = kSize/2;
				for(int j = y-kHalf, ky = 0; ky<kSize; j++,ky++)
					for(int k = x-kHalf, kx = 0; kx <kSize; k++,kx++){
						
						if(k > width-1 || k < 0)
	    					k = x;

						if(j > height-1 || j < 0)
	    					j = y;
						
						IMG cur;
						cur.red=ppmPixmap[j*width+k].red;
						cur.green=ppmPixmap[j*width+k].green;
						cur.blue=ppmPixmap[j*width+k].blue;

						
	 						max.red = fmax(cur.red,max.red);
	  						max.green = fmax(cur.green,max.green);
	  						max.blue = fmax(cur.blue,max.blue);
						
					}
					nC[i].red=max.red;
					nC[i].green=max.green;
					nC[i].blue=max.blue;
		}
		
	}
	for(int i =0;i<width*height;i++){
		ppmPixmap[i].red=nC[i].red;
		ppmPixmap[i].green=nC[i].green;
		ppmPixmap[i].blue=nC[i].blue;
	//img.setColor(pix[i],i);
	}
}

void erosion(IMG *&ppmPixmap, IMG *&cPix, int &width, int &height){
	cout << "Erosion function." << endl;
	
	IMG nC[width*height];
	IMG min;
	//This variable holds the values that will be summed up and used to populate 
        //our edited image.
        //float r,g,b = 0;

        for(int y=0; y<height; y++) {
		for(int x = 0; x < width; x++){
			int i = y * width +x;
			min.red=ppmPixmap[i].red;
			min.green=ppmPixmap[i].green;
			min.blue=ppmPixmap[i].blue;

			//int greatest=fmax(max.red,max.blue);
			//greatest=fmax(greatest,max.green);
			int kSize = cPix[i].red/10;
        		int kHalf = kSize/2;
				for(int j = y-kHalf, ky = 0; ky<kSize; j++,ky++)
					for(int k = x-kHalf, kx = 0; kx <kSize; k++,kx++){
						
						if(k > width-1 || k < 0)
	    					k = x;

						if(j > height-1 || j < 0)
	    					j = y;
						
						IMG cur;
						cur.red=ppmPixmap[j*width+k].red;
						cur.green=ppmPixmap[j*width+k].green;
						cur.blue=ppmPixmap[j*width+k].blue;

						
	 						min.red = fmin(cur.red,min.red);
	  						min.green = fmin(cur.green,min.green);
	  						min.blue = fmin(cur.blue,min.blue);
						
					}
					nC[i].red=min.red;
					nC[i].green=min.green;
					nC[i].blue=min.blue;
		}
		
	}
	for(int i =0;i<width*height;i++){
		ppmPixmap[i].red=nC[i].red;
		ppmPixmap[i].green=nC[i].green;
		ppmPixmap[i].blue=nC[i].blue;
	//img.setColor(pix[i],i);
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
  int angle;		

  readPPM(input_fileRead, original, iWidth, iHeight);
  input_fileRead = fopen(argv[2],"r");
  readPPM(input_fileRead, control, cWidth, cHeight);
  
  cout << "Type in one of the following options." << endl;

  cout << "*************************************" << endl;
  cout << "normal" << endl;
  cout << "motionBlur" << endl;
  cout << "emboss" << endl;
  cout << "smartBlur" << endl;
  cout << "dilation" << endl;
  cout << "erosion" << endl;
  cout << "*************************************" << endl;

  cin >> choice;





  if(choice == "normal"){
	normal(original, iWidth, iHeight);
  }
  else if(choice == "motionBlur"){
	motionBlur(original, control, iWidth, iHeight);
  }
  else if(choice == "emboss"){
	
	emboss(original, control, iWidth, iHeight);
  }
  else if(choice == "smartBlur"){
	smartBlur(original,control, iWidth, iHeight);
  }
  else if(choice == "dilation"){
	dilation(original,control, iWidth, iHeight);
  }
  else if(choice == "erosion"){
	erosion(original,control, iWidth, iHeight);
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