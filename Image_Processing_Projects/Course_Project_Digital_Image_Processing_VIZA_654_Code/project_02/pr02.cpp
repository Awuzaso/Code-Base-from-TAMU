// =============================================================================
// Include files.
// =============================================================================
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include <fstream>
#include <cassert>
#include <sstream>
#include <string>
#include <string.h>
#include <math.h>
#include "vector.h"
#include "vector.cpp"

using namespace std;

// =============================================================================
// Basic variables
// =============================================================================
int width, height;
int x, y;
unsigned char *pixmap;
// =============================================================================
// Get normal function.
// =============================================================================
Vector2d getNormal(Vector2d pt1, Vector2d pt2){
	Vector2d n_vec;
	float mag;
	n_vec.x=pt1.y-pt2.y;
	n_vec.y=-(pt1.x-pt2.x);
	/*Getting the unit vector.*/
	mag=sqrt(pow(n_vec.x,2)+pow(n_vec.y,2));
	n_vec.x=n_vec.x/mag;
	n_vec.y=n_vec.y/mag;

	return n_vec;
}

void pixmapFunc(int x, int y,int px, int py, int pz,int samples){
	int i = (y * width + x) * 3; 	//output colors for x,y,z
	pixmap[i++] = px/samples;
        pixmap[i++] = py/samples; 
        pixmap[i] = pz/samples; 
}
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void convexShape(bool a_option){
	int x, y;
	int j;	
	int samples= 1;		//number of samples for anti-aliasing
	
	Vector2d *p0= new Vector2d[7];	//array for points
	p0[0].set(400,400);			// Setting points
	p0[1].set(425,100);
	p0[2].set(450,50);
	p0[3].set(475,100);			// Setting points
	p0[4].set(500,400);
	p0[5].set(475,350);
	p0[6].set(425,350);			// Setting points

	Vector2d *n= new Vector2d[7];	//array for normals
	n[0]=getNormal(p0[0],p0[6]);
	n[1]=getNormal(p0[1],p0[0]);
	n[2]=getNormal(p0[2],p0[1]);
	n[3]=getNormal(p0[3],p0[2]);
	n[4]=getNormal(p0[4],p0[3]);
	n[5]=getNormal(p0[5],p0[4]);
	n[6]=getNormal(p0[6],p0[5]);
	
	
	  for(int y = 0; y < height ; y++) {
     		for(int x = 0; x < width; x++) {
		Vector3d SetColor (0,0,0);	// Setting the default color
		Vector3d inColor (255,255,0);	//inside of shape will be red
		Vector3d outColor (0,0,255);	//outside shapde will be blue
			for( int j=0; j<samples; j++){					
				Vector2d p;

				if(a_option==true){
				p.x=(x+(1.0*rand())/RAND_MAX);
				p.y=(y+(1.0*rand())/RAND_MAX);
				samples=15;
				}
				else{
				p.x=x;
				p.y=y;
				}	
					int count=0;
					for(int i=0;i<7;i++){
						if((n[i]*(p-p0[i]) <=0)){
						count++;
						}	
					}
					if(count==7){
						SetColor.x+=inColor.x;		
						SetColor.y+=inColor.y;
						SetColor.z+=inColor.z;
					}
					else{					
						SetColor.x+=outColor.x+(x/3);
						SetColor.y+=outColor.y;
						SetColor.z+=outColor.z;
					}
			}
			pixmapFunc(x,y,SetColor.x,SetColor.y,SetColor.z,samples);
		}
	}
/*End for loop.*/
}
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void starShape(bool a_option){
	int x, y;
	int j;	
	int samples= 1;		//number of samples for anti-aliasing
	
	Vector2d *p0= new Vector2d[5];	//array for points
	p0[0].set(50,200);			// Setting points
	p0[1].set(300,200);
	p0[2].set(100,100);
	p0[3].set(150,300);			// Setting points
	p0[4].set(300,100);
				// Setting points

	Vector2d *n= new Vector2d[5];	//array for normals
	n[0]=getNormal(p0[0],p0[1]);
	n[1]=getNormal(p0[1],p0[2]);
	n[2]=getNormal(p0[2],p0[3]);
	n[3]=getNormal(p0[3],p0[4]);
	n[4]=getNormal(p0[4],p0[0]);

	
	
	  for(int y = 0; y < height ; y++) {
     		for(int x = 0; x < width; x++) {
		Vector3d SetColor (0,0,0);	// Setting the default color
		Vector3d inColor (255,255,0);	//inside of shape will be red
		Vector3d outColor (0,0,255);	//outside shapde will be blue
			for( int j=0; j<samples; j++){					
				Vector2d p;

				if(a_option==true){
				p.x=(x+(1.0*rand())/RAND_MAX);
				p.y=(y+(1.0*rand())/RAND_MAX);
				samples=15;
				}
				else{
				p.x=x;
				p.y=y;
				}	
					int count=0;
					for(int i=0;i<5;i++){
						if((n[i]*(p-p0[i]) <=0)){
						count++;
						}	
					}
					if(count>=4){
						SetColor.x+=inColor.x;		
						SetColor.y+=inColor.y;
						SetColor.z+=inColor.z;
					}
					else{					
						SetColor.x+=outColor.x;
						SetColor.y+=outColor.y;
						SetColor.z+=outColor.z;
					}
			}
			pixmapFunc(x,y,SetColor.x,SetColor.y,SetColor.z,samples);
		}
	}
/*End for loop.*/
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void functionShape(bool a_option){
	int x, y;
	int j;	
	int samples= 1;		  
	for(int y = 0; y < height ; y++){
     		for(int x = 0; x < width; x++) {
		Vector3d SetColor (0,0,0);	// Setting the default color
		Vector3d inColor (255,255,0);	//inside of shape will be red
		Vector3d outColor (0,0,255);	//outside shapde will be blue
			for( int j=0; j<samples; j++){					
				Vector2d p;

				if(a_option==true){
				p.x=(x+(1.0*rand())/RAND_MAX);
				p.y=(y+(1.0*rand())/RAND_MAX);
				samples=15;
				}
				else{
				p.x=x;
				p.y=y;
				}	
				float scale=1;
				int nwidth=width-(x/scale);
				nwidth=nwidth*nwidth;
				int nheight=height-(y/scale);
				nheight=nheight*nheight;
				//int value = (1*1)*((nwidth)+(nheight));
				int value = (0.035*0.035)*(-(x*x)+(y*y));	
					
					if(value<=0){
						SetColor.x+=inColor.x;		
						SetColor.y+=inColor.y;
						SetColor.z+=inColor.z;
					}
					else{					
						SetColor.x+=outColor.x;
						SetColor.y+=outColor.y;
						SetColor.z+=outColor.z;
					}
			}
			pixmapFunc(x,y,SetColor.x,SetColor.y,SetColor.z,samples);
		}
	}	
}	

//////////////////////////////////////
void blobbyShape(bool a_option){
	int x, y;
	int j;	
	int samples= 1;		
	
	int p1,p2;
	p1=p2=200;
	Vector2d *p0= new Vector2d[5];	//array for points
	p0[0].set(p1,p2);			// Setting points
	p0[1].set(p0[0].x-100,p0[0].y);
	p0[2].set(p0[0].x+100,p0[0].y);
	p0[3].set(p0[0].x,p0[0].y-100);			// Setting points
	p0[4].set(p0[0].x,p0[0].y+100);				// Setting points
	//*/ 


	 float alpha = .0015;
      
	float r[5];	//array for points
	r[0]=10;
	r[1]=30;
	r[2]=30;
	r[3]=40;
	r[4]=40;
	//*/ 
  
	for(int y = 0; y < height ; y++){
     		for(int x = 0; x < width; x++) {
		Vector3d SetColor (0,0,0);	// Setting the default color
		Vector3d inColor (255,255,0);	//inside of shape will be red
		Vector3d outColor (0,0,255);	//outside shapde will be blue
			for( int j=0; j<samples; j++){					
				Vector2d p;

				if(a_option==true){
				p.x=(x+(1.0*rand())/RAND_MAX);
				p.y=(y+(1.0*rand())/RAND_MAX);
				samples=15;
				}
				else{
				p.x=x;
				p.y=y;
				}	
				
				///*
				double blob[5];
				double b_value=0;
				for(int i=0;i<5;i++){
					blob[i]=pow(2.7182, -alpha*((p-p0[i])*(p-p0[i])-r[i]*r[i]));
					b_value+=b_value+blob[i];
				}

				float value = -(log(b_value)/alpha);	
				//*/

         
                                //float value = -(1/alpha)*log((double)(F0+F1+F2+F3+F4));	
					
					if(y<value){
						SetColor.x+=inColor.x;		
						SetColor.y+=inColor.y;
						SetColor.z+=inColor.z;
					}
					else{					
						SetColor.x+=outColor.x;
						SetColor.y+=outColor.y;
						SetColor.z+=outColor.z;
					}
			}
			pixmapFunc(x,y,SetColor.x,SetColor.y,SetColor.z,samples);
		}
	}	                                          
}
/////////////////////////////////////
void shadedShape(bool a_option){
	int x, y;
	int j;	
	int samples= 1;	
	
	Vector2d center(width/2, height/2);	
	
	for(int y = 0; y < height ; y++){
     		for(int x = 0; x < width; x++) {
		 int i = (y * width + x) * 3; 

		Vector3d SetColor (0,0,0);	// Setting the default color
	
		///*
		int rgb1[3]={255,255,0};
		int rgb2[3]={0,255,0};//*/
                float grade;
              
		              for (int sample = 0; sample < 15; sample++) {
				   Vector2d p;
				   Vector2d p0(200,250);
                                   int radius = 400;

                                   if(a_option==true){
					p.x=(x+(1.0*rand())/RAND_MAX);
					p.y=(y+(1.0*rand())/RAND_MAX);
					samples=15;
				   }
				   else{
				       p.x=x;
				       p.y=y;
				  }
					

			           if(pow(p.x-center.x,2)+pow(p.y-center.y,2)-pow(radius,2)*0.125<=0){
                                   //if ( (1.0*rand())*((p-pc)*(p-pc) - radSquared) <= 0 ) {
                                          
                                         
                                          Vector2d v = p-(p0);
					  /*Normalizing grade values.*/ 
					  float mag=sqrt((v.x*v.x)+(v.y*v.y));       
                                          grade = (mag)/(radius);
                                          if (grade<=0){grade=0;}



					  /*Creating gradient.*/
                                        
						SetColor.x+=rgb1[0]*(1-grade)+rgb2[0]*grade;
						SetColor.y+=rgb1[1]*(1-grade)+rgb2[1]*grade;
						SetColor.z+=rgb1[2]*(1-grade)+rgb2[2]*grade;
                                   }
                                   else {
                                          Vector2d p0(width/2,0);
                                          Vector2d p1(width/2,height);
					  
                                          Vector2d v1 = p-p0;
                                          Vector2d v2 = p1-p0;
         
                                          float mag=sqrt((v1.x*v1.x)+(v1.y*v1.y));       
                                          grade = (mag)/(height);
                                          
                                         
					    SetColor.x+=rgb1[0]*(1-grade)+rgb2[0]*grade;
					    SetColor.y+=rgb1[1]*(1-grade)+rgb2[1]*grade;
					    SetColor.z+=rgb1[2]*(1-grade)+rgb2[2]*grade;

						
                                   }                                          
                            }  
                           pixmapFunc(x,y,SetColor.x,SetColor.y,SetColor.z,samples);
			    
			

		}
	}
}

void specialShape(bool a_option){
	int x, y;
	int j;	
	int samples= 1;		
	
	int p1,p2;
	p1=width/2;
	p2=height/2;
	Vector2d *p0= new Vector2d[5];	//array for points
	p0[0].set(p1,p2);			// Setting points
	p0[1].set(p0[0].x-100,p0[0].y);
	p0[2].set(p0[0].x+100,p0[0].y);
	p0[3].set(p0[0].x,p0[0].y-100);			// Setting points
	p0[4].set(p0[0].x,p0[0].y+100);				// Setting points
	//*/ 


	 float alpha = .0015;
      
	float r[5];	//array for points
	r[0]=10;
	r[1]=30;
	r[2]=30;
	r[3]=40;
	r[4]=40;
	//*/ 
  
	for(int y = 0; y < height ; y++){
     		for(int x = 0; x < width; x++) {
		Vector3d SetColor (0,0,0);	// Setting the default color
		Vector3d inColor (255,255,0);	//inside of shape will be red
		Vector3d outColor (0,0,255);	//outside shapde will be blue

		int rgb1[3]={255,255,0};
		int rgb2[3]={0,255,0};
                float grade;
			for( int j=0; j<samples; j++){					
				Vector2d p;
				Vector2d pa(width/2,height/2);
                                int radius = 400;
				
				if(a_option==true){
				p.x=(x+(1.0*rand())/RAND_MAX);
				p.y=(y+(1.0*rand())/RAND_MAX);
				samples=15;
				}
				else{
				p.x=x;
				p.y=y;
				}	
				
				///*
				double blob[5];
				double b_value=0;
				for(int i=0;i<5;i++){
					blob[i]=pow(2.7182, -alpha*((p-p0[i])*(p-p0[i])-r[i]*r[i]));
					b_value+=b_value+blob[i];
				}

				float value = -(log(b_value)/alpha);	
				//*/

         
                                //float value = -(1/alpha)*log((double)(F0+F1+F2+F3+F4));

				
				
	
			
					
					if(value-y<=0){
						Vector2d v1 = p-(pa);
					  /*Normalizing grade values.*/ 
					  float mag=sqrt((v1.x*v1.x)+(v1.y*v1.y));       
                                          grade = (mag*15)/(radius);
                                          if (grade<=0){grade=0;}



					  /*Creating gradient.*/
                                        
						SetColor.x+=rgb1[0]*(1-grade)+rgb2[0]*grade;
						SetColor.y+=rgb1[1]*(1-grade)+rgb2[1]*grade;
						SetColor.z+=rgb1[2]*(1-grade)+rgb2[2]*grade;
					}
					else{					
						SetColor.x+=outColor.x+sin(y);
						SetColor.y+=outColor.y;
						SetColor.z+=outColor.z;
					}
			}
			pixmapFunc(x,y,SetColor.x,SetColor.y,SetColor.z,samples);
		}
	}	                                       
}
// =============================================================================
// OpenGL Display and Mouse Processing Functions.
//
// You can read up on OpenGL and modify these functions, as well as the commands
// in main(), to perform more sophisticated display or GUI behavior. This code
// will service the bare minimum display needs for most assignments.
// =============================================================================
static void windowResize(int w, int h)
{   
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,(w/2),0,(h/2),0,1); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity() ;
}
static void windowDisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixmap);
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

// =============================================================================
// main() Program Entry
// =============================================================================
int main(int argc, char *argv[])
{

  //initialize the global variables
  pixmap = new unsigned char[width * height * 3];  //Do you know why "3" is used?
	
	/*Selection variables.*/
	string shapeOption,aliasOption;
	bool a_option;


	cout << "Please select a desired from the following listed options:" << endl;
	cout << "//////////////////////////////////////////////////////////" << endl;
	cout << "Type 'convex' for convex shape." << endl;
	cout << "Type 'star' for star shape." << endl;
	cout << "Type 'function' for function shape." << endl;	
	cout << "Type 'blobby' for blobby shape." << endl;
	cout << "Type 'shaded' for shaded circle shape." << endl;
	cout << "Type 'the special' for something cool." << endl;
	cout << "//////////////////////////////////////////////////////////" << endl;
	
	cin >> shapeOption;

	cout << "Do you want the shape to feature anti-aliasing?" <<endl;
	cout << "Type 'y' for yes or 'n' for no." <<endl;
	cin >> aliasOption;

	if(aliasOption == "y"){
		a_option = true;
	}
	else{
		a_option = false;
	}
	//initialize the global variables
	x=0;
	y=0;
	width = 720;
	height = 480;
	pixmap = new unsigned char[width * height * 3]; 
	

	if(shapeOption == "convex") {
			convexShape(a_option);
	}
	else if (shapeOption == "star"){
			starShape(a_option);
	}
	else if (shapeOption == "function"){
			functionShape(a_option);
	}
	else if (shapeOption == "blobby"){
			blobbyShape(a_option);
	}
	else if (shapeOption == "shaded"){
			shadedShape(a_option);
	}
	else if (shapeOption == "special"){
			specialShape(a_option);
	}
	else{
		cout << "Incorrect input. Closing.";
		return 0;
	}


  // OpenGL Commands:
  // Once "glutMainLoop" is executed, the program loops indefinitely to all
  // glut functions.  
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100); // Where the window will display on-screen.
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Project 02: Vector to Raster Conversion and Antializing");
  init();
  glutReshapeFunc(windowResize);
  glutDisplayFunc(windowDisplay);
  glutMouseFunc(processMouse);
  glutMainLoop();

  return 0; //This line never gets reached. We use it because "main" is type int.
}
