// =============================================================================
// [pr05.cpp]
// [Osazuwa Okundaye]
// To Use: 
// [./pr05 <input.ppm> <output.ppm> <transform>]
// =============================================================================
#include <cstdlib>
#include <iostream>
#include <GLUT/GLUT.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>  
#include "Vector.cpp"
#include <sstream>
#include <string>  
#include <fstream>          
using namespace std;
// =============================================================================
// These variables will store the input ppm image's width, height, and color
// depth values read in from the ppm header.
// =============================================================================
int width, height, maxcolor;
FILE *input_fileRead; //*input_fileWrite;
FILE *output_fileRead; 

	struct IMG{
		unsigned char red;
		unsigned char green;
		unsigned char blue;		
	};	

IMG *original;
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
void readPPM(FILE *input_fileRead, IMG *&ppmPixmap, int &width, int &height);
void rotation(float degree);
void translation(float tX,float tY);
void scale(float sX,float sY);
void shear(float shX,float shY);
void mirror(float mrX,float mrY);
void perspective(float pX,float pY);
void bilinear(float bX, float bY);
void custom(float cX, float cY);
void writePPM();


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
  
  
	

  

  input_fileRead = fopen(argv[1],"r");
  readPPM(input_fileRead, original, iWidth, iHeight);
  cout <<  "helllo." << endl;
  string outputfile = argv[2];
  //output_fileRead = fopen(argv[2],"w");
  const char *name;
	
////////////////////////////////////////////
  	
		 float n = 0;
		 /*Loop creates images between frames, 1 through 120.*/
		 for (int i = 1; i <= 120; i++)
		 {
			//cout <<"inside";
			/*Create new stringstream object, sstm.*/
			std::stringstream sstm;
			/*New file, proj9_"i".ppm.*/
			sstm << "proj6_" << i << ".ppm";
			
			/*Store contents within address of name.*/
			name = (sstm.str()).c_str();
		        /*Open up filestream, insert a name and open as
			"write".*/
			
			output_fileRead = fopen(name, "w");
			
			/*Create image/*/
			custom(2+n,2+n);
			/*Write out image.*/
			writePPM();
			/*If frame count is under 60, increment value by .67,
			else, decrement by .67.*/
			if(i<60){
				n=n+.05;
			}
			else {
				n=n-.05;
			}

		 }
///////////////////////////////////////////




  // OpenGL commands
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100); // Where the window will display on-screen.
  glutInitWindowSize(iWidth, iHeight);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Test Val");
  init();
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutMouseFunc(processMouse);
  glutMainLoop();

  // Check command line arguments and read in the output input_fileRead if present.
  // Then call writePPM() if necessary.

  //return 0;
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
  glDrawPixels(iWidth, iHeight, GL_RGB, GL_UNSIGNED_BYTE, result);
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
/////////////////////////////////////////////////////////////////////////
//FUNCTIONS/////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////
//ROTATION FUNCTION///////////////////////////////////////////////
void rotation(float degree){
	cout << "Rotation viewing mode."  << endl;
	float theta = degree*3.14159265/180;
	float rotM[3][3]=   {{cos(theta),-sin(theta),0},
			    {sin(theta),cos(theta),0},
			    {0,0,1}};
	Matrix3x3 matrix = Matrix3x3(rotM);
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		Vector3D pixT = matrix * pix;

		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newX = (int)(pixT.x);
		newY = (int)(pixT.y);

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		dimensions.*/
		newY=((int)newY + iHeight) % iHeight;
		newX=((int)newX + iWidth) % iWidth;
		
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}

//////////////////////////////////////////////////////////////////
//TRANSLATION FUNCTION///////////////////////////////////////////////
void translation(float tX, float tY){
	cout << "Translation viewing mode."  << endl;
	float tranM[3][3]=   {	{1,0,-tX},
				{0,1,-tY},
				{0,0,1}};
	Matrix3x3 matrix = Matrix3x3(tranM);
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		Vector3D pixT = matrix * pix;

		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newX = (int)(pixT.x);
		newY = (int)(pixT.y);

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		dimensions.*/
		newY=((int)newY + iHeight) % iHeight;
		newX=((int)newX + iWidth) % iWidth;
		
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}
//////////////////////////////////////////////////////////////////
//SCALE FUNCTION///////////////////////////////////////////////
void scale(float sX, float sY){
	cout << "Scale viewing mode."  << endl;
	float scaM[3][3]=   {	{1/sX,0,0},
				{0,1/sY,0},
				{0,0,1}};
	Matrix3x3 matrix = Matrix3x3(scaM);
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		Vector3D pixT = matrix * pix;

		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newX = (int)(pixT.x);
		newY = (int)(pixT.y);

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		dimensions.*/
		newY=((int)newY + iHeight) % iHeight;
		newX=((int)newX + iWidth) % iWidth;
		
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}
//////////////////////////////////////////////////////////////////
//SHEAR FUNCTION///////////////////////////////////////////////
void shear(float shX, float shY){
	cout << "Scale viewing mode."  << endl;
	float dif=1-(shX*shY);
	float sheM[3][3]=   {	{1,-shX,0},
				{-shY,1,0},
				{0,0,dif}};
	Matrix3x3 matrix = Matrix3x3(sheM);
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		Vector3D pixT = matrix * pix;

		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newX = (int)(pixT.x);
		newY = (int)(pixT.y);

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		dimensions.*/
		newY=((int)newY + iHeight) % iHeight;
		newX=((int)newX + iWidth) % iWidth;
		
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}
//////////////////////////////////////////////////////////////////
//MIRROR FUNCTION///////////////////////////////////////////////
void mirror(float mrX, float mrY){
	cout << "Mirror viewing mode."  << endl;
	float mirM[3][3]=   {	{-mrX,0,0},
				{0,-mrY,0},
				{0,0,1}};
	Matrix3x3 matrix = Matrix3x3(mirM);
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		Vector3D pixT = matrix * pix;

		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newX = (int)(pixT.x);
		newY = (int)(pixT.y);

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		dimensions.*/
		newY=((int)newY + iHeight) % iHeight;
		newX=((int)newX + iWidth) % iWidth;
		
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}
//////////////////////////////////////////////////////////////////
//PERSPECTIVE FUNCTION///////////////////////////////////////////////
void perspective(float pX, float pY){
	cout << "Perspective viewing mode."  << endl;
	float perM[3][3]=   {	{1,0,0},
				{0,1,0},
				{-pX,-pY,1}};
	Matrix3x3 matrix = Matrix3x3(perM);
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		Vector3D pixT = matrix * pix;

		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newX = (int)(pixT.x*(1.0/pixT.z));
		newY = (int)(pixT.y*(1.0/pixT.z));

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		dimensions.*/
		newY=((int)newY + iHeight) % iHeight;
		newX=((int)newX + iWidth) % iWidth;
		
		
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}
//////////////////////////////////////////////////////////////////
//BILINEAR FUNCTION///////////////////////////////////////////////
void bilinear(float bX, float bY){
	cout << "Perspective viewing mode."  << endl;
	
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		
		//cout << "Hello?" << endl;
		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newY = (int)abs(y+bY*sin(x/bY));
		newX = x+bX;

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		//dimensions.*/
		//newY=((int)newY + iHeight) % iHeight;
		//newX=((int)newX + iWidth) % iWidth;
		
		if(newX<0)
		  newX += iWidth;
		else if (newX>iWidth)
		  newX -= iWidth;
		if(newY<0)
		  newY += iHeight;
		else if (newY>iHeight)
		  newY -= iHeight;
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=original[f].red;
		result[i].green=original[f].green;
		result[i].blue=original[f].blue;
		
	  }
	}
}//////////////////////////////////////////////////////////////////
//BILINEAR FUNCTION///////////////////////////////////////////////
void custom(float bX, float bY){
	cout << "Custom viewing mode."  << endl;
	
        result = new IMG[iWidth * iHeight ];
	int newX,newY;
/////////////////////////////////////////////////////////////////////
        bilinear(bX,bY);
	/*NOTE:Specify pixel's row.*/
	for(int y = 0; y < iHeight; y++) {
	  /*NOTE:Specify pixel's column.*/
	  for(int x = 0; x < iWidth; x++){

		/*NOTE:Variable, "i" holds the value of the current
		pixel under consideration within loop.*/
		int i = y * iWidth +x;

                /*NOTE:Create a new object of type Vector3D that holds
		current x,y and additional 1 for matrix size.*/
		Vector3D pix (x,y,1);

		 /*NOTE:Create an additonal object of type Vector3D that
		holds the multiplied value between matrix and and pix.*/
		
		//cout << "Hello?" << endl;
		 /*NOTE:Store value specified by matrix mutiplication
  		in int variables, newX and newY.*/
		newY = (int)abs(y+bY*sin(x/bY));
		newX = (int)abs(x+bX*cos(y/bX));

		/*NOTE:This code segment exists for the purpose
		of safeguarding the image in case it goes over, specified 
		//dimensions.*/
		//newY=((int)newY + iHeight) % iHeight;
		//newX=((int)newX + iWidth) % iWidth;
		
		if(newX<0)
		  newX += iWidth;
		else if (newX>iWidth)
		  newX -= iWidth;
		if(newY<0)
		  newY += iHeight;
		else if (newY>iHeight)
		  newY -= iHeight;
		
		/*NOTE:Variable, "f" holds the value of the
		specified pixel after matrix processing from
		the old pixmap,"original".*/
		int f=1*(newY*iWidth+newX);
		result[i].red=result[f].red;
		result[i].green=result[f].green;
		result[i].blue=result[f].blue;
		
	  }
	}
}
//WRITE PPM
void writePPM(){
    
       
       string input;
       
       
       fprintf(output_fileRead, "P6\n");

       fprintf(output_fileRead, "%d %d\n", iWidth, iHeight);
	/*Write to new file the the width and 
	height and introduce linebreak.*/ 
       fprintf(output_fileRead, "%d\n", maxcolor);

	

  

  /*Note that we reverse how y values are placed in file given
  the differences between how images are displayed in OpenGL vs
  how values of images are arranged.*/ 
  for(y = iHeight-1; y >= 0; y--) {
    for(x = 0; x < iWidth; x++) {
      
      /*Specifying pixel.*/ 
      pixel = (y * iWidth + x); 
       
      red = result[pixel].red;	 
      green = result[pixel].green;   	
      blue =result[pixel].blue;
      
      
     
     
      
      fputc(red,output_fileRead);
      fputc(green,output_fileRead);
      fputc(blue,output_fileRead);
      
	
      


    }
  }
}

