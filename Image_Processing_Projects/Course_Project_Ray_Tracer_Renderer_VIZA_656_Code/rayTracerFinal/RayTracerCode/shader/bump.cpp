#include "../objectClass/object.h"
#include <iostream>
#include <cfloat> 
#include <vector>
#include <math.h>
#include "perlinCode.cpp"
//#include "3Dnoise.cpp"
extern float pi;
extern unsigned char *bumpMap;
extern unsigned char *ppmPixmap;
extern int width,height;
extern int iWidth, iHeight;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3d getCol(int i,int j, unsigned char *type){
	Vector3d retCol;
	//cout << "Value of i and j within getCol()." << endl;
	//output(i);
	//output(j);
	//cout << "iHeight:"<< iHeight<< endl;
	
	
	if(i<0){
		i=0;
	}
	if(i>iWidth-1){
		i=iWidth-1;
	}
	if(j<0){
		j=0;
	}
	if(j>iHeight-1){
		j=iHeight-1;
	}


	int pixel = (j *iWidth + i)*3;
	
	retCol.x=type[pixel++];
	retCol.y=type[pixel++];
	retCol.z=type[pixel];

	return retCol;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Vector3d getOmega(double u0, double v0,Vector3d pos){
	Vector3d omega;
	float radius=24;
	omega.x=pos.x+(radius*sin(pi*v0)*cos(2*pi*u0));
	omega.y=pos.y+(radius*sin(pi*v0)*cos(2*pi*u0));
	omega.z=pos.z+(radius*cos(pi*v0));

	
	//cout << "I work." << endl;
	return omega;
}*/
Vector3d getBump(Vector3d ph,Vector3d pc,Vector3d nh){

	//1)ESTABLISH NORMALS.
	Vector3d n1(1,0,0);
	Vector3d n2(0,-1,0);
	Vector3d n0(0,0,-1);
	//Vector3d n0(1,0,0);
	//Vector3d n1(0,1,0);
	//Vector3d n2(0,0,1);
	

	//2)THESE VALUES ARE PLACED HERE FOR DEBUGGING PURPOSES, THE DIMENSIONS OF OBJ.
	float s0=300;
	float s1=300;
	float s2=300;

	
	//3)DETERMINE THE VALUE OF A,B,C(THE DIFFERENCE BETWEEN PH AND PC AVG OVER THE OBJ'S RAD.
	float A=(n0*(ph-pc))/s0;
	float B2=(n1*(ph-pc))/s1;
	float C=(n2*(ph-pc))/s2;

	//4)DETERMINE THE VALUE OF PHI AND THETA
	float phi=acos(C);
	float theta=acos(B2/sin(phi));

	//5)DETERMINE THE VALUE OF U AND V, COORDINATES OF TEXTURE SPACE.
	double u,v;

	u=theta/(2*pi);
	v=phi/(pi);
	if(A<0){
		theta=(2*pi)-theta;
		u=theta/(2*pi);
		v=phi/(pi);
	}
	u=u*1024;

	v=v*1024;
	
	//Compute N0 and N1 using those values as u and v in the following:
	float delta_u,delta_v;
	delta_u=delta_v=0.00001;
	Vector3d v0;
	Vector3d v1;
	
	v0.set(getOmega(u+delta_u,v,pc)-getOmega(u-delta_u,v,pc));//Need to define Vector3d getOmega(double x, double y)
	v1.set(getOmega(u,v+delta_v,pc)-getOmega(u,v-delta_v,pc));

	Vector3d n_0;
	n_0.set(v0/v0.norm());
	Vector3d n_1;
	n_1.set(v1/v1.norm());




	//Get the bump value.
	Vector3d bumpVal;
	bumpVal.set(getCol((int)u,(int)v,bumpMap));
	//bumpVal.set(getCol(theta,phi,bumpMap));
	float r,g,b;

	r=bumpVal.x/255.0;
	g=bumpVal.y/255.0;
	b=bumpVal.z/255.0;


	Vector3d pA;
	pA.set(((2*b)-1)*nh);
	Vector3d pB;
	pB.set(((2*r)-1)*n_0);
	Vector3d pC;
	pC.set(((2*g)-1)*n_1);
	//Using the color value in u and v to move the original vector N.
	Vector3d vecVal;
	//vecVal.set(nh+(n_0*(bumpVal.x/255.0))+(n_1*(bumpVal.y/255.0)));
	vecVal.set(pA+pB+pC);
	//vecVal.set((nh*(2));
	//The final normal value.
	Vector3d normVal;
	normVal.set(vecVal/vecVal.norm());



	//Return value.
	return normVal;
	
}
//////////////////////////////////////////////////////////////////////
float noise(int x, int y, int z){
	int n= x+y+z*57;
	n=pow((n<<13),n);
	float retVal=( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589)) / 1073741824.0); 
	return retVal; 	
}



float smNoise(float x,float y,float z){
    float corners = ( noise(x-1,y-1,z)+noise(x+1,y-1,z)+noise(x-1,y+1,z)+noise(x+1,y+1,z))/32.0;
    float sides   = ( noise(x-1,y,z)+noise(x+1,y,z)+noise(x,y-1,z)+noise(x,y+1,z)+noise(x,y,z+1)+noise(x,y,z-1))/16.0;
    float center  =  noise(x,y,z)/8.0;
    return corners + sides + center;
}

float interpNoise(float ptx, float pty, float ptz){
	int ix=(int)ptx;
	int iy=(int)pty;
	int iz=(int)ptz;

	float fx=ptx-ix;
	float fy=pty-iy;
	float fz=ptz-iz;



	float v1=smNoise(ix,iy,iz);
	float v2=smNoise(ix+1,iy,iz);	
	float v3=smNoise(ix,iy+1,iz);
	float v4=smNoise(ix+1,iy+1,iz);

	float v5=smNoise(ix,iy,iz+1);
	float v6=smNoise(ix+1,iy,iz+1);
	float v7=smNoise(ix,iy+1,iz+1);
	float v8=smNoise(ix+1,iy+1,iz+1);

	
	
	float i1=lerp(v1,v2,fx);
	float i2=lerp(v3,v4,fx);
	float i3=lerp(v5,v6,fx);
	float i4=lerp(v7,v8,fx);

	float i5=lerp(i2,i3,fy);
	float i6=lerp(i1,i4,fy);

	float i7=lerp(i5,i6,fz);
	
	return i7;
}

double PerlinNoise3D(Vector3d pt,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   float p[3],scale = 1;

   p[0] = pt.x;
   p[1] = pt.y;
   p[2] = pt.z;
   for (i=0;i<n;i++) {
      val = noise3D(p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
      p[2] *= beta;
   }
   return(sum);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3d solidTexture(Vector3d ph,Vector3d pl){
	Vector3d retVal;
	Vector3d n0(-1,0,0);
	Vector3d n1(0,-1,0);
	Vector3d n2(0,0,1);

	float s0,s1;
	s0=s1=60;

	

	Vector3d ph_pl;
	ph_pl.set(ph-pl);

	double d=ph_pl.norm();//The distance d from projection center in n2 diection.

	double x,y;

	Vector3d A;
	A.set(d*(ph_pl/(n2*ph_pl)));
	Vector3d B2;
	B2.set(pl-(d*n2));
	Vector3d C;
	C.set(A-B2);
	x=(n0/s0)*(C);
	y=(n1/s1)*(C);


	double u,v;

	u=(x+1)/2;
	v=(y+1)/2;

	if(x>0)u=(x-(int)x);
	if(x<0)u=(int)x-x;

	if(y>0)v=(y-(int)y);
	if(y<0)v=(int)y-y;

	
	//output(u);
	//output(v);
	//u=(int)u;
	//v=(int)v;

	retVal.set(getCol(u*1024,v*1024,ppmPixmap));
	
	//retVal.set(getCol(u,v,ppmPixmap));
	return retVal;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3d solidTextureWall(Vector3d ph,Vector3d p0){
	Vector3d retVal;
	Vector3d n0(-1,0,0);
	Vector3d n1(0,1,0);
	Vector3d n2(0,0,1);

	float s0,s1;
	s0=s1=50;

	double d;//The distance d from projection center in n2 diection.

	Vector3d ph_p0;
	ph_p0.set(ph-p0);

	double x,y;


	x=(n0/s0)*ph_p0;
	y=(n1/s1)*ph_p0;
	
	

	float u,v;
	if(x>0)u=(x-(int)x);
	if(x<0)u=(int)x-x;

	if(y>0)v=(y-(int)y);
	if(y<0)v=(int)y-y;
	
	if(x<0)u=1-u;
	if(y<0)v=1-v;
	//output(u);
	//output(v);
	retVal.set(getCol(u*1024,v*1024,ppmPixmap));
	float vec[2]={u,v};
	//retVal.set(noise2D(vec)*255.0,noise2D(vec)*255.0,noise2D(vec)*255.0);
	//retVal.set(getCol(u,v,ppmPixmap));
	return retVal;
}


/*
	double x,y;


	x=(n0/s0)*ph_p0;
	y=(n1/s1)*ph_p0;
	
	

	double u=x-(int)x;
	if(x<0)u=1-u;
	//output(u);
	
	double v=y-(int)y;
	if(y<0)v=1-v;
	///output(v);
	retVal.set(getCol(u*1024,v*1024,ppmPixmap));
	//retVal.set(getCol(u,v,ppmPixmap));
	return retVal;*/

