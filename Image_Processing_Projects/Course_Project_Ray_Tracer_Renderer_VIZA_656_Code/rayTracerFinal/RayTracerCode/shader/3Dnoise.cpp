#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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


float perlinNoise3D(Vector3d pt,int per,int octCnt){
	float total=0;
	int n=octCnt-1;
	for(int i=0;i<=n;i++){
		int freq=pow(2,i);
		int amp=pow(p,i);
		total=total+(interpNoise(pt.x*freq,pt.y*freq,pt.z*freq)*amp);
	}
	float total;
}
