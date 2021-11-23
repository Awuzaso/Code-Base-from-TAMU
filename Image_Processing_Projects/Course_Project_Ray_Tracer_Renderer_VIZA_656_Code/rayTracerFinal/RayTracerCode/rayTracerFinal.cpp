//[./test <source.ppm>]
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
#include <vector>
#include "vectorFiles/vector.h"
#include "vectorFiles/vector.cpp"
#include "cameraClass/camera.h"
#include "cameraClass/camera.cpp"
#include "objectClass/object.h"
#include "objectClass/object.cpp"
#include "lightClass/light.h"
#include "lightClass/light.cpp"
#include "shader/shader.h"
#include "raytracer.cpp"


using namespace std;

// =============================================================================
// Basic variables
// =============================================================================
	int width, height,maxcolor;
	int x, y;
	unsigned char *pixmap;
	unsigned char *ppmPixmap;
	unsigned char *bumpMap;
//LOADING IMAGE.
FILE *input_fileRead; 

//PPM VARS
int iWidth, iHeight, cWidth, cHeight, oWidth, oHeight;
//IMG DATATYPE
struct IMG{
	unsigned char red;
	unsigned char green;
	unsigned char blue;		
};	

IMG *original;
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
//////////////////////////////////////////////////////////////////////////////////
// =============================================================================
// main() Program Entry
// =============================================================================
int main(int argc, char *argv[])
{
//PLACE OBJECTS IN FUNCTION.	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
width=720;
height=480;
//Initialize the global variables
pixmap = new unsigned char[width * height * 3]; 



input_fileRead = fopen("./ppmFolder/normal.ppm","r");
readPPM(input_fileRead, iWidth, iHeight);


input_fileRead = fopen("./ppmFolder/normal.ppm","r");
readPPM2(input_fileRead, iWidth, iHeight);


/*struct map testMap;
input_fileRead = fopen("./ppmFolder/normal.ppm","r");
testMap=testPPM(input_fileRead);*/











  
	
//INITIALIZE CAMERA
Vector3d posPt(50,75,-450);	
Vector3d viewDir(0,0,5);
Vector3d worldUp(0,1,0);	
double depth=10;
double scalex=20;
Camera camera(posPt,viewDir,worldUp,depth,width,height,scalex);
Vector3d lookAt(0,0,0);


	
//INITIALIZE LIGHT	
Vector3d pl(150,100,-500);
//Vector3d pl(0,200,50);
Light light(pl);
pl.set(-150,100,-500);
Light light2(pl);
//ARRAY OF LIGHTS
Light lightGRP[2]={light,light2};



//ENV LIGHT
FILE *file; 
pl.set(0,0,0);
file = fopen("./ppmFolder/envMap4.ppm","r");
struct map eMap=testPPM(file);

Light envLight(pl);
envLight.shader.setShader(pl,eMap,eMap,'Z');		
	
file = fopen("./ppmFolder/controlPPMs/control7.ppm","r");
struct map pMap1=testPPM(file);	

file = fopen("./ppmFolder/controlPPMs/control1.ppm","r");
struct map pMap2=testPPM(file);	

	




//INITIALIZE SPHERES
	//SPHERE1.
	int radius=50;
	Vector3d col(255,0,0);
	Vector3d sPos(-100,0,0);
	Sphere sphere1(radius,sPos,col);
	input_fileRead = fopen("./ppmFolder/test.ppm","r");
	struct map tMap=testPPM(input_fileRead);
	//sphere1.Shader shader(col,tMap,tMap,'L');
	sphere1.shader.setShader(col,tMap,tMap,'L');
	sphere1.setTag('A');
	sphere1.shader.setKs(0);
	sphere1.shader.texOn=false;

	//SPHERE2.
	radius=50;
	Vector3d col2(0,255,0);
	Vector3d sPos2(150,0,50);
	Sphere sphere2(radius,sPos2,col2);
	input_fileRead = fopen("./ppmFolder/bump.ppm","r");
	tMap=testPPM(input_fileRead);	
	sphere2.shader.setShader(col,tMap,tMap,'L');
	sphere2.setTag('B');
	sphere2.shader.setKs(0);
	sphere2.shader.texOn=false;
	sphere2.shader.setIOR(0);
	//SPHERE3.
	radius=50;
	Vector3d col3(255,0,150);
	Vector3d sPos3(50,0,0);
	Sphere sphere3(radius,sPos3,col3);
	input_fileRead = fopen("./ppmFolder/fractal.ppm","r");
	tMap=testPPM(input_fileRead);	
	input_fileRead = fopen("./ppmFolder/egypt.ppm","r");
	struct map nMap=testPPM(input_fileRead);
	nMap=testPPM(input_fileRead);
	sphere3.shader.setShader(col,tMap,nMap,'L');
	sphere3.setTag('C');
	sphere3.shader.setKs(0);
	sphere3.shader.texOn=false;
	sphere3.shader.setIOR(0);
	sphere3.shader.normalOn=false;














//INITIALIZE PLANES
//PLANE1.
Vector3d intPt(0,0,1);
//Vector3d pos2(200,400,1000);
Vector3d pos2(0,0,0);
col3.set(255,0,160);
Plane plane1(1,1,intPt,pos2,col3);
input_fileRead = fopen("./ppmFolder/test.ppm","r");
tMap=testPPM(input_fileRead);	
plane1.shader.setShader(col,tMap,tMap,'L');
plane1.setTag('D');
//PLANE2.
intPt.set(0,1,0);
pos2.set(0,-150,0);
col3.set(255,255,0);
Plane plane2(1,1,intPt,pos2,col3);
input_fileRead = fopen("./ppmFolder/test.ppm","r");
tMap=testPPM(input_fileRead);	
plane2.shader.setShader(col,tMap,tMap,'L');
plane2.setTag('E');
plane2.shader.setKs(0);
plane2.shader.texOn=false;
plane2.shader.normalOn=false;
//ARRAY OF PLANES.
Plane planeGRP[2]={plane1,plane2};	

//INITIALIZE OBJS
FILE *objFile;
objFile=fopen("./objFolder/cube.obj","r");
Vector3d objPos(0,0,0);
Obj obj1(objFile,objPos,col);
input_fileRead = fopen("./ppmFolder/egypt.ppm","r");
tMap=testPPM(input_fileRead);	
obj1.shader.setShader(col,tMap,tMap,'L');
obj1.setTag('F');
obj1.shader.setKs(0);
obj1.shader.texOn=true;
obj1.shader.setIOR(1.5);

//obj1.showValue();

Vector3d p[3];
Vector2d u[3];
Vector3d n[3];

p[0].set(-0.000000, -1.205467, 2.410934);
p[1].set(2.410934, -1.205467, 0.000000);
p[2].set(0.000000, 1.205467, 0.000000);

u[0].set( 0.500000, 0.500000);
u[1].set(0.625000, 0.500000);
u[2].set(0.500000, 1.000000);

n[0].set(0.577350, 0.577350, 0.577350);
n[1].set(0.577350, 0.577350 ,0.577350);
n[2].set(0.577350, 0.577350, 0.577350);
objPos.set(0,0,0);
Triangle tri(p,u,n,objPos,col);

















vector<Object*> objectGRP = vector<Object*>();

//objectGRP.push_back(dynamic_cast<Object*>(&tri));
//objectGRP.push_back(dynamic_cast<Object*>(&obj1));

//objectGRP.push_back(dynamic_cast<Object*>(&obj1));
//objectGRP.push_back(dynamic_cast<Object*>(&plane1));
objectGRP.push_back(dynamic_cast<Object*>(&plane2));
objectGRP.push_back(dynamic_cast<Object*>(&sphere1));
objectGRP.push_back(dynamic_cast<Object*>(&sphere2));
objectGRP.push_back(dynamic_cast<Object*>(&sphere3));






/*for(int a=0;a<objectGRP.size();a++){
	Object* obj=objectGRP.at(a);
	float tVal=obj->rayEq(pt,n);
	output(tVal);

}*/
//BEGIN LOOP PROCESS.
  
  /*Loop creates images between frames, 1 through 120.*/
  float animVal=0;
  for(int i = 0; i < 1; i++){
	//int i=0;
	std::stringstream sstm;
	/*New file, proj9_"i".ppm.*/
	sstm << "testImage_" << i << ".ppm";
	
	/*Store contents within address of name.*/
	const char * name = (sstm.str()).c_str();
	//sphere3.shader.setIOR(animVal);
	
		//animVal=(-(25.0/150)*i)+45.0;	
		animVal=animVal+0.01;
	
	
	cout << "Rendering  frame" << i << endl;
	processFunc(camera,lightGRP,objectGRP,envLight,eMap,pMap1,pMap2,name,animVal);
  }







  // OpenGL Commands:
  // Once "glutMainLoop" is executed, the program loops indefinitely to all
  // glut functions.  
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 100); // Where the window will display on-screen.
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Ray Tracer");
  init();
  glutReshapeFunc(windowResize);
  glutDisplayFunc(windowDisplay);
  glutMouseFunc(processMouse);
  glutMainLoop();

  return 0; 
}








