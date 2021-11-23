#include <iostream>
#include "../vectorFiles/vector.h"
#include "camera.h"
//#include "debugTool.cpp"
#include "../vectorFiles/Vector.cpp"
#include "../support/rotateFunc.cpp"
#include "../shader/shader.h"

using namespace std;



Camera::Camera()
{
	std::cout <<"Default constructor called."<< endl;
	pe.set(0,0,0);
	vView.set(0,0,0);
	vUp.set(0,0,0);
	n0.set(0,0,0);
	n1.set(0,0,0);
	n2.set(0,0,0);
	pc.set(0,0,0);
	p00.set(0,0,0);
	d=xMax=yMax=sX=sY=0;
}
Camera::Camera(Vector3d pt,Vector3d vV,Vector3d vU,double dd, double x, double y, double sx)
{
	Vector3d obj;//Container vector object.

	//std::cout <<"Normal constructor called."<< endl;
	//Set eye position.
	pe.set(pt);
	//output(pe);

	//Set view direction.

	float degree =0;	
	float theta = degree*3.14159265/180;
	float rotM[3][3]=   {{1,0,0},
			     	     {0,cos(theta),-sin(theta)},
			             {0,sin(theta),cos(theta)}};/*{{1,0,0},
			     {0,cos(theta),sin(theta)},
			     {0,-sin(theta),cos(theta)}};*/
		
	Matrix3x3 matrix = Matrix3x3(rotM);

	Vector3D pix (vV.x,vV.y,1);

		
	Vector3D pixT = matrix * pix;
	

	//vView.set(rotateFunc(vView,theta,'x'));
	vView.x=pixT.x;
	vView.y=pixT.y;
	vView.z=pixT.z;







	//vView.set(vV);
	//output(vView);

	//Set world up.
	vUp.set(vU);
	

        //Calculating normal, n2 in direction of vector view.
	n2=vView/(vView.norm()); 
	
        //Calculating normal, n0.
	obj=(vView%vUp);	
	n0=obj/(obj.norm());
	
        //Calculating normal, n1.
	obj=(n0%n2); 
	n1=(obj/(obj.norm()));
	

	d=dd;//Camera depth.
	xMax=x;//Image plane width dimension.
	yMax=y;//Image plane height dimension.
	sX=sx;//Scale value for x.
	sY=(sX*yMax)/xMax;//Scale value for y.
	
	//Calculating p_c, the center of viewpoint.
	Vector3d val;
	val.x=n2.x*d;
	val.y=n2.y*d;
	val.z=n2.z*d;
	pc=pe+val;
	
	//Calculating lower left corner of the viewport: p(0,0).
	p00=pc-((sX/2)*n0)-((sY/2)*n1);
	
	
}


Camera::~Camera()
{
	//std::cout << "Camera object removed from memory." << endl;
}
/*
void Camera::setEyePosition(Vector3d pos)
{
	pe.set(pos);
	output(pos);
}

void Camera::setCameraDir(Vector3d view,Vector3d upVec)
{
	vView.set(view);
	output(vView);
	vUp.set(upVec);
	output(vUp);	
}

void Camera::setCamAttr(float depth,float xmax,float ymax, float scaleX){
	d=depth;output(d);
	xMax=xmax;output(xmax);
	yMax=ymax;output(yMax);
	sX=scaleX;output(sX);
	sY=(ymax*sX)/xMax;output(sY);
}
*/
Vector3d Camera::getPP(float px,float py){
	
	//return p00 + ( sX*n0*px ) + ( sY*n1*py ) ;

	float X=px/xMax;
	float Y=py/yMax;

	//n0.set(1,0,0);
	//n1.set(0,1,0);

	return p00 + ( sX*n0*X ) + ( sY*n1*Y) ;
}
Vector3d Camera::getNpe(float px,float py)
{
	double X=px/xMax;
	double Y=py/yMax;
	Vector3d retVal;
	Vector3d valA=(sX*n0*X);
	Vector3d valB=(sY*n1*Y);
	Vector3d pixPos=p00+valA+valB;
	
	
	Vector3d pp_pe=pixPos-pe; //NOTE:Calculating the difference between pixel postion and camera position.
	Vector3d n_pe=(pp_pe/pp_pe.norm()); //NOTE:Creating the unit vector of normalized eye position.
	//output(n_pe);
	return n_pe;	
}
Vector3d Camera::getNpePaint(Vector3d cVal)
{

	
	float A,B,C;
	A=1;
	B=1;
	C=1;
	float r,g,b;

	r=cVal.x;
	g=cVal.y;
	b=cVal.z;
	
	
	Vector3d valA=(A*r*n0);
	Vector3d valB=(B*g*n1);
	Vector3d valC=(C*b*n2);
			
	
	Vector3d pixPos=p00+valA+valB+valC;
	
	
	Vector3d pp_pe=pixPos-pe; //NOTE:Calculating the difference between pixel postion and camera position.
	Vector3d n_pe=(pp_pe/pp_pe.norm()); //NOTE:Creating the unit vector of normalized eye position.
	return n_pe;
	//Vector3d nn(0,0,0);
	//return nn;	
	
}
Vector3d Camera::getPe()
{
	return pe;
}

void Camera::cameraTrack(Vector3d lookAt){

	
	Vector3d A;Vector3d B;
	A.set(pe-lookAt);
	B.set(pe);
	
	float costheta=A*B;




	Vector3d obj;


	
	
/*
	float degree =costheta;	
	float theta = degree*3.14159265/180;
	float rotM[3][3]=   {{1,0,0},
			     {0,cos(theta),sin(theta)},
			     {0,-sin(theta),cos(theta)}};
	
	Matrix3x3 matrix = Matrix3x3(rotM);

	Vector3D pix (vV.x,vV.y,1);

		
	Vector3D pixT = matrix * pix;
*/	vView.set(rotateFunc(vView,costheta,'x'));
	//vView.x=pixT.x;
	//vView.y=pixT.y;
	//vView.z=pixT.z;
	
        //Calculating normal, n2 in direction of vector view.
	n2=vView/(vView.norm()); 
	
        //Calculating normal, n0.
	obj=(vView%vUp);	
	n0=obj/(obj.norm());
	
        //Calculating normal, n1.
	obj=(n0%n2); 
	n1=(obj/(obj.norm()));
	
	//Calculating p_c, the center of viewpoint.
	Vector3d val;
	val.x=n2.x*d;
	val.y=n2.y*d;
	val.z=n2.z*d;
	pc=pe+val;
	
	//Calculating lower left corner of the viewport: p(0,0).
	p00=pc-((sX/2)*n0)-((sY/2)*n1);


}













