#include "../vectorFiles/vector.h"
#include "../shader/shader.h"
#include <iostream>
#ifndef LGT_CLASS
#define LGT_CLASS
using namespace std;
class Light
{
	private:
	Vector3d pl,n0,n1,n2,vUp;
	
	public:
	Shader shader;
	Light(Vector3d init_pl);
	//Camera(Vector3d pt,Vector3d vV,Vector3d vU,double dd, double x, double y, double sx);//Default constructor.	
	~Light();//Noisy destructor.
	void setNormal(Vector3d ph);
	Vector3d get_pl();
	Vector3d get_n0();
	Vector3d get_n1();
	Vector3d get_n2();
};
#endif
