#include <iostream>
//#include "vector.h"
#include "light.h"
//#include "debugTool.cpp"
using namespace std;

Light::Light(Vector3d init_pl)
{
	
	
	//Set eye position.
	pl.set(init_pl);
	

	
	

	

	

	
	
}
Light::~Light()
{
	
}
///////////////////////////////////////
void Light::setNormal(Vector3d ph)
{
	Vector3d obj;//Container vector object.
	
	vUp.set(0,1,0);//Set world up.
	

        //Calculating normal, n2 in direction of light view.
	Vector3d ldir;
	ldir.set(pl-ph);
	n2=ldir/(ldir.norm()); 
	
        //Calculating normal, n0.
	obj=(ldir%vUp);	
	n0=obj/(obj.norm());
	
        //Calculating normal, n1.
	obj=(n0%n2); 
	n1=(obj/(obj.norm()));
	
}
///////////////////////////////////////
Vector3d Light::get_pl()
{	
	return pl;	
}
Vector3d Light::get_n0()
{	
	return n0;	
}
Vector3d Light::get_n1()
{	
	return n1;	
}
Vector3d Light::get_n2()
{
	return n2;
}
















