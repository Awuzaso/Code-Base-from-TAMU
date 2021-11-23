#include "../vectorFiles/vector.h"
#include "../shader/shader.h"
//#include "../shader/getCol.cpp"
#include <math.h>
#include <cfloat>
//#include "debugTool.cpp"

using namespace std;

#ifndef OBJ_CLASS
#define OBJ_CLASS
Vector3d getTex(int i,int j,float iWidth,float iHeight, unsigned char *type){
	Vector3d retCol;
	
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
Vector3d getOmega(float radius,double u0, double v0,Vector3d pos){
	Vector3d omega;
	
	float pi=3.14;
	omega.x=pos.x+(radius*sin(pi*v0)*cos(2*pi*u0));
	omega.y=pos.y+(radius*sin(pi*v0)*cos(2*pi*u0));
	omega.z=pos.z+(radius*cos(pi*v0));

	
	//cout << "I work." << endl;
	return omega;
}
using namespace std;
class Object
{
	private:
	Vector3d position;
	Vector3d color;
	float tVal;
	Vector3d n0;
	Vector3d n1;
	Vector3d n2;
	float sx;
	float sy;
	float sz;
	char tag;
	public:
	bool hit;
	Object();//Normal constructor.
	Object(Vector3d pos,Vector3d col);//Default constructor.	
	~Object();//Noisy destructor.	
	Vector3d getPos();
	Vector3d getCol();
	void setPos(Vector3d new_pos){
		position.set(new_pos);
	};
	void ifHit(){
		hit=true;
	};
	bool getHit(){
		return hit;
	}
	void set_Tval(float t){
		tVal=t;
	}
	float getTval(){
		return tVal;
	}
	void setTag(char tagVal){
		tag=tagVal;
	}
	char getTag(){
		return tag;
	}
	Shader shader;
	//RAY EQUATION FUNCTION FOR PLANE.
	virtual bool rayEq(Vector3d p,Vector3d n){
		
		return false;
	};
	virtual void calcNh(){};

	virtual Vector3d getNh(Vector3d p){
		return 0;
	}
	virtual Vector3d normalmapFunc(Vector3d ph,Vector3d pc,Vector3d nh){
		return nh;
	}
	//FUNCTIONS FOR SETTING SIZE OF OBJECT.
	void set_sx(float size){
		sx=size;
	}
	void set_sy(float size){
		sy=size;
	}
	void set_sz(float size){
		sz=size;
	}
	//FUNCTIONS FOR GETTING SIZE OF OBJECT.
	float get_sx(){
		return sx;
	}
	float get_sy(){
		return sy;
	}
	float get_sz(){
		return sz;
	}
	//FUNCTION FOR WRAPPING TEXTURE ACCORDING TO GEOMETRY.
	virtual Vector3d getTexture(Vector3d ph,Vector3d pc){
		return ph;
	}
};
//DERIVED CLASSES
class Sphere : public Object
{
	private:
	float radius;
	public:
	Sphere(float rad, Vector3d pos,Vector3d col);
	float getRad();


	//RAY EQUATION FUNCTION FOR SPHERE.
	bool rayEq(Vector3d p,Vector3d n){
		//cout << "I'm a sphere." <<endl;
		Vector3d pc_p=getPos()-p;		
		int c=/*(pow(n*pc_p,2))-*/(pc_p*pc_p)-(pow(radius,2));//(pc_p*pc_p)+(pow(radius,2));
		float b=n*pc_p;//a1.set((p2-ph)%(p0%ph));a1.set((p2-ph)%(p0%ph));
		float i=pow(b,2)-c;
		if(i>0){
	        	set_Tval(b-sqrt(i));
			//cout << "There is an intersection." << endl;
			return true;
		}
		else{
			set_Tval(0);
			//cout << "There is not a intersection." << endl;
			return false;
		}
	};
	Vector3d getNh(Vector3d p){
		Vector3d retVal;
		retVal.set((p-getPos())/radius);
		return retVal;
	};
//////////////////////////////////////////////////////////////
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	Vector3d getTexture(Vector3d ph,Vector3d pc){
		
	//1)ESTABLISH NORMALS.
	Vector3d n_1(1,0,0);
	Vector3d n_2(0,-1,0);
	Vector3d n_0(0,0,-1);
	
	//2)THESE VALUES ARE PLACED HERE FOR DEBUGGING PURPOSES, THE DIMENSIONS OF OBJ.
	float s0=radius;
	float s1=radius;
	float s2=radius;

	//3)DETERMINE THE VALUE OF A,B,C(THE DIFFERENCE BETWEEN PH AND PC AVG OVER THE OBJ'S RAD.
	float a=(n_0*(ph-pc))/(s0);
	float b=(n_1*(ph-pc))/(s1);
	float c=(n_2*(ph-pc))/(s2);

	//4)DETERMINE THE VALUE OF PHI AND THETA
	float phi=acos(c);
	float theta=acos(b/sin(phi));

	//5)DETERMINE THE VALUE OF U AND V, COORDINATES OF TEXTURE SPACE.
	double u,v;
	float pi=3.14;
	u=theta/(2*pi);
	v=phi/(pi);
	if(a<0){
		theta=(2*pi)-theta;
		u=theta/(2*pi);
		v=phi/(pi);
	}
	
	//6)COMPUTE CORRESPONDING IMAGE COORDINATES BASED ON IMAGE DIMENSIONS.
	struct map tmap=shader.getTexMap();
	double X,Y;
	double Xmax=tmap.width;
	double Ymax=tmap.height;
	unsigned char * texture=tmap.map;
	X=u*Xmax;
	Y=v*Ymax;

	//7)COMPUTE COORDINATES OF PIXEL X,Y
	double I,J;
	I=(int)X;
	J=(int)Y;

	int i=X-I;
	int j=Y-J;
	


	Vector3d c0;
	c0.set(getTex(I,J,Xmax,Ymax,texture));

	Vector3d c1;
	c1.set(getTex(I+1,J,Xmax,Ymax,texture));

	Vector3d c2;
	c2.set(getTex(I+1,J+1,Xmax,Ymax,texture));

	Vector3d c3;
	c3.set(getTex(I,J+1,Xmax,Ymax,texture));

	Vector3d retColor;
	retColor.set( ( (c0)*(1-i)*(1-j) ) + ( (c1)*(i)*(1-j) ) + ( (c2)*(i)*(j) ) + ( (c3)*(1-i)*(j) ) );


	
	/*//8)COMPUTE POSITION OF POINT IN PIXEL i,j
	float i=int(X-I);
	float j=int(Y-J);

	
	Vector3d retColor;
	unsigned char * texture=tmap.map;
	retColor.set(getTex(X,Y,Xmax,Ymax,texture));*/
	

	return retColor;
		
	};















//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//////////////////////////////////////////////////////////////	
	Vector3d normalmapFunc(Vector3d ph,Vector3d pc,Vector3d nh){
		//1)ESTABLISH NORMALS.
		Vector3d n1(1,0,0);
		Vector3d n2(0,-1,0);
		Vector3d n0(0,0,-1);
		//Vector3d n0(1,0,0);
		//Vector3d n1(0,1,0);
		//Vector3d n2(0,0,1);
	

		//2)THESE VALUES ARE PLACED HERE FOR DEBUGGING PURPOSES, THE DIMENSIONS OF OBJ.
		float s0=radius;
		float s1=radius;
		float s2=radius;

	
		//3)DETERMINE THE VALUE OF A,B,C(THE DIFFERENCE BETWEEN PH AND PC AVG OVER THE OBJ'S RAD.
		float A=(n0*(ph-pc))/s0;
		float B2=(n1*(ph-pc))/s1;
		float C=(n2*(ph-pc))/s2;

		//4)DETERMINE THE VALUE OF PHI AND THETA
		float phi=acos(C);
		float theta=acos(B2/sin(phi));

		//5)DETERMINE THE VALUE OF U AND V, COORDINATES OF TEXTURE SPACE.
		double u,v;
		float pi=3.14;
		u=theta/(2*pi);
		v=phi/(pi);
		if(A<0){
			theta=(2*pi)-theta;
			u=theta/(2*pi);
			v=phi/(pi);
		}
		
	
		//Compute N0 and N1 using those values as u and v in the following:
		float delta_u,delta_v;
		delta_u=delta_v=0.00001;
		Vector3d v0;
		Vector3d v1;
	
		v0.set(getOmega(radius,u+delta_u,v,pc)-getOmega(radius,u-delta_u,v,pc));//Need to define Vector3d getOmega(double x, double y)
		v1.set(getOmega(radius,u,v+delta_v,pc)-getOmega(radius,u,v-delta_v,pc));

		Vector3d n_0;
		n_0.set(v0/v0.norm());
		Vector3d n_1;
		n_1.set(v1/v1.norm());




		//Get the bump value.
		//Vector3d bumpVal;

		//////////////////////////////////////////////


		struct map nmap=shader.getNormMap();
	double X,Y;
	double Xmax=nmap.width;
	double Ymax=nmap.height;

	//cout << "Values:" << Xmax << " " << Ymax << endl;
	unsigned char * normal=nmap.map;
	
	u=u*Xmax;

	v=v*Ymax;


	Vector3d bumpVal;
	bumpVal.set(getTex(int(u),int(v),Xmax,Ymax,normal));

	/*Vector3d c1;
	c1.set(getTex(I+1,J,Xmax,Ymax,normal));

	Vector3d c2;
	c2.set(getTex(I+1,J+1,Xmax,Ymax,normal));

	Vector3d c3;
	c3.set(getTex(I,J+1,Xmax,Ymax,normal));

	Vector3d bumpVal;
	bumpVal.set( ( (c0)*(1-i)*(1-j) ) + ( (c1)*(i)*(1-j) ) + ( (c2)*(i)*(j) ) + ( (c3)*(1-i)*(j) ) );*/










		///////////////////////////////////////////

		//bumpVal.set(getCol((int)u,(int)v,shader.));
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




};
class Plane : public Object
{	
	private:
	float sizeX;
	float sizeY;
	Vector3d intersection;
	
	public:
	Plane(float x,float y,Vector3d inter,Vector3d pos,Vector3d col);
	float getX();
	float getY();
	Vector3d getInter();


	
	//RAY EQUATION FUNCTION FOR PLANE.
	bool rayEq(Vector3d p,Vector3d n){
		//cout << "I'm a plane." <<endl;
		//Vector3d pp_p=getPos()-p;
		Vector3d pp_p=getPos()-p;
		double c;
		c=(intersection*n);
			
			/*float t=(intersection*pp_p)/c;
			if(t>0){
	        	set_Tval(t);
			return true;
			}
			else{
			set_Tval(0);
			return false;
			}*/
			
			float t=(intersection*pp_p)/c;
			set_Tval(t);
			if((t>=0) && (t<=9999999)){
				return true;
			}
			else{
				return false;
			}
			/*if(t>=0){
				if(t <= 9999999){
				set_Tval(t);
				return true;
				}
				else{return true;}
			}
			else if(t<0){
				set_Tval(t);
				return false;
			}*/
			
/*
			if(c>0){
	        	set_Tval((-intersection*pp_p)/c);
			return true;
			}
			else{
			set_Tval(0);
			return false;
			}*/
		
	/*
			if(c==0){
			set_Tval(0);
			return false;
		}
		else{
			set_Tval((n*pp_p)/(c));
			return true;
		}*/

	};
	Vector3d getNh(Vector3d p){
		Vector3d retVal;
		retVal.set(intersection);
		return retVal;
	};

	Vector3d getTexture(Vector3d ph,Vector3d pc){

		//1)ESTABLISH NORMALS.
	
		//Vector3d n0(1,0,0);
		//Vector3d n1(0,0,1);
		Vector3d n1;
		if(intersection.z==0)n1.set(0,0,1);
		if(intersection.z==1)n1.set(0,1,0);
		//Vector3d n1(0,1,0);
		//Vector3d n1(0,0,1);
		Vector3d n0(-1,0,0);

		//2)THESE VALUES ARE PLACED HERE FOR DEBUGGING PURPOSES, THE DIMENSIONS OF OBJ.
		float s0=1024/5.0;
		float s1=1024/5.0;
	
		Vector3d ph_pc;
		ph_pc.set(ph-pc);
	
		//3)DETERMINE THE VALUE OF A,B,C(THE DIFFERENCE BETWEEN PH AND PC AVG OVER THE OBJ'S RAD.
		float x=(n0*ph_pc)/(s0);
		float y=(n1*ph_pc)/(s1);
		x=x-(int)x;
		y=y-(int)y;
		float u,v;
		if((0<=x)&&(x<=1)){
	
		
			u=x;
		
		
		}
		if((0<=y)&&(y<=1)){
	
		
			v=y;
		
		}
	
		//u=x-(int)x;
		//v=y-(int)y;
	
	
		if(x>0)u=x-(int)x;
		if(y>0)v=y-(int)y;
		if(x<0)u=(int)x-x;
		if(y<0)v=(int)y-y;

		if(x<0)u=1-u;
		if(y<0)v=1-v;
	
		struct map tmap=shader.getTexMap();
		double X,Y;
		double Xmax=tmap.width;
		double Ymax=tmap.height;
		unsigned char * texture=tmap.map;
		X=u*Xmax;
		Y=v*Ymax;

		//7)COMPUTE COORDINATES OF PIXEL X,Y
		double I,J;
		I=(int)X;
		J=(int)Y;

		int i=X-I;
		int j=Y-J;
	


		Vector3d c0;
		c0.set(getTex(I,J,Xmax,Ymax,texture));

		Vector3d c1;
		c1.set(getTex(I+1,J,Xmax,Ymax,texture));

		Vector3d c2;
		c2.set(getTex(I+1,J+1,Xmax,Ymax,texture));

		Vector3d c3;
		c3.set(getTex(I,J+1,Xmax,Ymax,texture));

		Vector3d retColor;
		retColor.set( ( (c0)*(1-i)*(1-j) ) + ( (c1)*(i)*(1-j) ) + ( (c2)*(i)*(j) ) + ( (c3)*(1-i)*(j) ) );
			//Vector3d retColor;
		
		//struct map texMap=shader.getTexMap();
		//float mWidth=texMap.width;
		//float mHeight=texMap.height;
		//unsigned char * tMap=texMap.map;	
		
		//retColor.set(getTex(u*mWidth,v*mHeight,mWidth,mHeight,tMap));
		
		return retColor;
	};

	
};
//CLASS TRIANGLE
class Triangle : public Object
{	
	private:
	
	
	public:
	Vector3d p0;//1st vertex.
	Vector3d p1;//2nd vertex.
	Vector3d p2;//3rd vertex.

	Vector3d N;//Normal of face.
	Vector3d A;//Area of face.

	Vector3d a0;//Sub area of faces.
	Vector3d a1;
	Vector3d a2;

	Vector2d uv0;//UV texture point of p0.
	Vector2d uv1;//UV texture point of p1.
	Vector2d uv2;//UV texture point of p2.

	Vector3d n0;//Normal of p0.
	Vector3d n1;//Normal of p1.
	Vector3d n2;//Normal of p2.
	Triangle();
	Triangle(Vector3d *p,Vector2d *u,Vector3d *n,Vector3d pos,Vector3d col);
	void setVertex(Vector3d *p){
		p0.set(p[0]);
		p1.set(p[1]);
		p2.set(p[2]);
	
	};
	Vector3d * getP(){
		Vector3d pArray[3];
		pArray[0]=a0;
		pArray[1]=a1;
		pArray[2]=a2;
		return pArray;
	
	};
	void setUV(Vector2d *u){
		uv0.set(u[0]);
		uv1.set(u[1]);
		uv2.set(u[2]);
	};
	Vector2d * getUV(){
		Vector2d uvArray[3];
		uvArray[0]=uv0;
		uvArray[1]=uv1;
		uvArray[2]=uv2;
		return uvArray;
	
	};
	void setNorm(Vector3d *n){
		n0.set(n[0]);
		n1.set(n[1]);
		n2.set(n[2]);
	};
	void setA_N(){
		A.set((p0-p1)%(p2-p0));
		N.set(A/A.norm());
	};
	void showVertex(){
		cout << "P0:" << endl;
		cout << p0.x << endl;
		cout << p0.y << endl;
		cout << p0.z << endl;
		cout << "P1:" << endl;
		cout << p1.x << endl;
		cout << p1.y << endl;
		cout << p1.z << endl;
		cout << "P2:" << endl;
		cout << p2.x << endl;
		cout << p2.y << endl;
		cout << p2.z << endl;
		cout << "//////////" << endl;
	};
	


	
	//RAY EQUATION FUNCTION FOR PLANE.
	bool rayEq(Vector3d p,Vector3d n){
		bool ifHit=false;
		
		//Setting area and normal.
		Vector3d p1_p0;Vector3d p2_p0;
		p1_p0.set(p1-p0);p2_p0.set(p2-p0);
		A.set(p1_p0%p2_p0);
		
		
		N.set(A/A.norm());
		//N.set(-N);
		//Setting the t value, the parameter for ray equation.
		float t=(N*(p0-p))/(N*n);
		set_Tval(t);
			
		Vector3d ph;
		ph.set(p+(t*n));
		
		
		
		//Setting sub areas.
		

		a0.set((ph-p1)%(ph-p2));
		a2.set((ph-p2)%(ph-p0));
		a1.set((ph-p0)%(ph-p1));
	
		//Determine out of the components of A, which has the highest absolute value.
		float comp0,comp1,comp2;
		comp0=a0.z/A.z;
		comp1=a1.z/A.z;
		comp2=a2.z/A.z;

		


		//Determine if ph is within triangle within regions.
		bool cond1,cond2,cond3;
		cond1 = false;
                cond2 = false;
                cond3 = false;
		
		if((0<comp0)&&(comp0<1)){
			cond1=true;
		}
		

		if((0<comp1)&&(comp1<1)){
			cond2=true;
		}
		

		if((0<comp2)&&(comp2<1)){
			cond3=true;
		}
		
		//If all regions are within triangle, ifHit value is set to true, signifying
		//a hit.
		//if(((cond1==true) && (cond2==true))&& (cond3==true)){
		if((cond1 && cond2) && cond3){
			ifHit=true;
			//cout << "Hit!" << endl;
		}
		else
		{
                        //cout << "not Hit" <<endl;
		}
		
		
		return ifHit;

	};
	//"Get" function for nh.
	Vector3d getNh(Vector3d p){
			
	
		a0.set((p-p1)%(p-p2));
		a2.set((p-p2)%(p-p0));
		a1.set((p-p0)%(p-p1));
		
		float tot=a0.z+a1.z+a2.z;
			
		float one_s_t=a0.z/tot;
		float s=a1.z/tot;
		float t=a2.z/tot;

		Vector3d nh;
		nh.set((n0*one_s_t)+(n1*s)+(n2*t));
		//nh.set((n0*comp0)+(n1*comp1)+(n2*comp2));


		return nh;
	}

	//Returns t value.
	
};
//////////////////////////////////////////////////////
/*Object Class*/

class Obj: public Object
{
	private:
	Triangle * hitFace;
	//int hitFace;
	vector <Triangle> triGRP;
	void loadOBJ(FILE * objFile);
	public:
	Obj(FILE * objFile, Vector3d pos,Vector3d col);
	//void setHitFace(int val){hitFace=val;};
	//int getHitFace(){return hitFace;};


	//RAY EQUATION FUNCTION FOR SPHERE.
	bool rayEq(Vector3d p,Vector3d n){	
				
		bool ifHit=false;
		bool retVal=false;
		float temp_t;
		float tMin=FLT_MAX;
		//FUNCTION TRAVERSES THROUGH VECTOR OF TRIANGLES TO DETERMINE IF THERE IS A HIT.
		//cout << "Faces: " << triGRP.size() << endl;
		int faces=triGRP.size(); 
		for(int i=0;i<faces;i++){
			
			ifHit=triGRP.at(i).rayEq(p,n);
			set_Tval(triGRP.at(i).getTval());
			if((ifHit==true)&&((getTval()<tMin))){
				//hitFace=triGRP.at(i);
				tMin=getTval();
				hitFace =&triGRP.at(i);
				retVal=true;
			}
			
			
		}	
		if(retVal==true){return true;}
		else{return false;}
		//return ifHit;

	};
	Vector3d getNh(Vector3d p){
		Vector3d retVal;
		
		retVal.set(hitFace->getNh(p));
		//cout << "This is it." << endl;
		return retVal;
	}
	void showValue(){
		   for(int i=0;i<triGRP.size();++i){
			cout << "Face : " << i+1 << endl;
			
			(triGRP.at(i).showVertex());
		
			
		   }
	}
	Vector3d getTexture(Vector3d ph,Vector3d pc){
		Vector2d * uv[3];
		*uv=hitFace->getUV();
		Vector3d * p[3];
		*p=hitFace->getP();
		
		float total;
		total=(p[0]->x)+(p[1]->x)+(p[2]->x);
		
		float one_s_t=(p[0]->x)/total;
		float s=(p[1]->x)/total;
		float t=(p[2]->x)/total;
		
		float u,v;
		
		double u0=hitFace->uv0.x;
		double u1=hitFace->uv1.x;
		double u2=hitFace->uv2.x;
		double v0=hitFace->uv0.y;
		double v1=hitFace->uv1.y;
		double v2=hitFace->uv2.y;
		//cout << "U0:" << u0 << endl;
		
		//double u2=uv[2]->x;	
		float s0,s1;
		s0=s1=50;

		one_s_t=one_s_t/s0;
		s=s/s0;
		t=t/s0;
		u=(u0*one_s_t)+(u1*s)+(u2*t);
		
		v=(v0*one_s_t)+(v1*s)+(v2*t);
		Vector3d retColor(255,255,0);
		
		struct map texMap=shader.getTexMap();
		
		
		float mWidth=texMap.width;
		float mHeight=texMap.height;
		unsigned char * tMap=texMap.map;	
		
		retColor.set(getTex(u*mWidth,v*mHeight,mWidth,mHeight,tMap));
		
		return retColor;
	};

};








#endif
