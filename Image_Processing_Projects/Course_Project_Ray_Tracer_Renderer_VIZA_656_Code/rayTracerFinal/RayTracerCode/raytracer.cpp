#include "cameraClass/camera.h"
#include "objectClass/object.h"
#include <iostream>
#include <cfloat> 
#include <fstream>
#include <cassert>
#include <sstream>
#include "lightClass/light.h"
#include <algorithm>
#include <vector>
#include <fstream>
//#include "shader/bump.cpp"
#include "shader/shader.h"

//#include "perlinCode.cpp"
//#include "support/rotateFunc.cpp"
#define MAX_REFL 4
using namespace std;


extern int width, height,maxcolor;
	extern int x, y;
//Uses externally defined variables.
extern unsigned char *pixmap;
extern unsigned char *ppmPixmap;
extern unsigned char *bumpMap;
extern int width,height;
extern int iWidth, iHeight;
Light * envLight;
vector<Object*> objectGRP;
float pi=3.14;
float animVal;
struct map vMap;
struct map pMap1;
struct map pMap2;

const int maxR=4;
FILE *output_fileRead;

void writePPM(const char *name);
 
;

Vector3d envMap(Vector3d r){
		
	//1)ESTABLISH NORMALS.
	/*Vector3d n1(0,1,0);
	Vector3d n2(0,0,1);
	Vector3d n0(1,0,0);*/
	
	
	/*Vector3d n0(0,1,0);
	Vector3d n1(0,0,1);
	Vector3d n2(1,0,0);*/
///////////////////////
	r.set(r/r.norm());
	//Vector3d n0(0,0,1);//Z
	//Vector3d n1(-1,0,0);//X
	//n1.set(rotateFunc(n1,animVal,'y'));
	//Vector3d n2(0,-1,0);//Y
		//r.set(rotateFunc(r,360,'y'));

	Vector3d n1(1,0,0);
	Vector3d n2(0,-1,0);
	Vector3d n0(0,0,1);

	//n1.set(rotate(n1,n0,animVal));
	//n0.set(rotate(n0,-n1,animVal));
	
	float x=(n0*r);
	float y=(n1*r);
	float z=(n2*r);

	float phi=acos(z);
	float theta=acos(y/sin(phi));
	

	//float v=acos(z)/(pi);
	//float u=( 1/(2*pi) ) * acos( y/sqrt( 1-(z*z) ));
	//if(x<0)u=1-u;
	
	double u,v;
	float pi=3.14;

	v=acos(z)/pi;
	//u=acos(r.y/(sin(pi)))/(2*pi);
	u=acos( y/sqrt( 1-pow(z,2) ) )*( 1/(2*pi) );

	//if(x>0)u=x-(int)x;
	
	//if(x<0)u=(int)x-x;
	


	if(x<0)u=-(1-u);

	Vector3d rotateVal;
	rotateVal.set(u,v,1);
	rotateVal.set(rotateFunc(rotateVal,0,'y'));
	u=rotateVal.x;
	v=rotateVal.y;
	double X,Y;
	double Xmax=vMap.width;
	double Ymax=vMap.height;
	unsigned char * texture=vMap.map;
	X=u*Xmax;
	Y=v*Ymax;

	double I,J;
	I=(int)X;
	J=(int)Y;

	double i=X-I;
	double j=Y-J;
	


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
	//unsigned char * texture=vMap.map;
	//retColor.set(getTex(X,Y,Xmax,Ymax,texture));
	//output(retColor);
	
	return retColor;
		
};

/*Vector3d envMap(Vector3d radius){
	
	Vector3d n1(1,0,0);
	Vector3d n2(0,-1,0);
	Vector3d n0(0,0,-1);

	float piVal=3.14;
	float x,y,z;

	x=radius*n0;
	y=radius*n1;
	z=radius*n2;

	float v=acos(z)/piVal;
	float u=acos(y/(sqrt(1-pow(z,2))))/(2*piVal);

	if(x<0)u=1-u;

	//6)COMPUTE CORRESPONDING IMAGE COORDINATES BASED ON IMAGE DIMENSIONS.
	struct map tmap=envLight->shader.getTexMap();
	float X,Y;
	float Xmax=tmap.width;
	float Ymax=tmap.height;
	X=u*Xmax;
	Y=v*Ymax;

	Vector3d retColor(255,0,0);
	unsigned char * texture=tmap.map;
	retColor.set(getTex(X,Y,Xmax,Ymax,texture));

	return retColor;
}*/











// =============================================================================
// Pixmap function.
// =============================================================================
void pixmapFunc(int x, int y,int px, int py, int pz){
	int i = (y * width + x) * 3; 	//output colors for x,y,z
	pixmap[i++] = px;
        pixmap[i++] = py; 
        pixmap[i] = pz; 
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
Vector3d traceRefraction(Vector3d pos,Vector3d V,Vector3d nh, char tag, Light light[]){
	Vector3d retCol(0,0,0);
	
		
		Vector3d c0(100,100,100);

		Vector3d u;
		u.set(rotateFunc(V,90,'x'));
		Vector3d v;
		v.set(rotateFunc(V,90,'z'));
		float blurSize=0.1;
		int samples=8;
		float Kr=1;
		Vector3d R_i;
		Vector3d C(0,0,0);

		for(int i=0;i<samples;i++){

		float randVal_u=(rand()%10)/10.0;
		
			float randVal_v=(rand()%10)/10.0;		
			//cout << "Random values:" << endl;
			//output(randVal_u);
			//output(randVal_v);
			R_i.set( (V+ ( ( 0.5 - randVal_u ) * blurSize * u ) +  ( 0.5 - randVal_v ) * blurSize * v ) );
			R_i.set( R_i / ( R_i.norm() ) );
		
		///////////////////////////////////////////
			int objIndex=-1;
			float t=0;
			float tMin=FLT_MAX;
			Vector3d ph;
			Vector3d n_nh;
			for(int i=0;i<objectGRP.size();i++){
				if(tag!=objectGRP.at(i)->getTag()){
			
					objectGRP.at(i)->rayEq(pos,R_i);
					t=objectGRP.at(i)->getTval();
			
					if((0<t)&&(t<tMin)){
						tMin=t;
						objIndex=i;	
						ph.set(pos+(t*V));
						n_nh.set(objectGRP.at(i)->getNh(ph));
					
					}
				}
			}
			if(objIndex!=-1){		
				float Ks =objectGRP.at(objIndex)->shader.getKs();
				Vector3d C01;
				//C01.set(objectGRP.at(objIndex)->getCol());
		
			
				if(objectGRP.at(objIndex)->shader.texOn==false){
					C01.set(objectGRP.at(objIndex)->getCol());
				}
				else{
					C01.set(objectGRP.at(objIndex)->getTexture(ph,pos));
				}
				//C01.set((c0*(1-t))+(C01*t));
				//C01.set(objectGRP.at(objIndex)->getTexture(ph,pos));
				//C01.set((c0*(1-t))+(C01*t));
				//C01.set((C01*(1-s))+(c2*s));
				retCol.set((1-Ks)*C01);		
			}
			else{	
				//.set(V/V.norm());
				retCol.set(envMap(R_i));
			}
		/////////////////////////////////////////////
			
			C.set( (retCol + C) );
		}
		C.set(C*(Kr/samples));

		return C;
}
////////////////////////////////////////////////////////////////
Vector3d traceReflection(Vector3d pos,Vector3d normal,Vector3d nh, char tag, Light light[]){
		Vector3d c0(100,100,100);
		Vector3d R;
		R.set((-normal)-(2*(normal*nh)*nh));
		//cout << "Original reflected vector." << endl;
		//output(R);
		////////////////////////////////////////////////////////

		Vector3d u;
		u.set(rotateFunc(R,90,'x'));
		Vector3d v;
		v.set(rotateFunc(R,90,'z'));
		float blurSize=0.1;
		int samples=4;
		float Kr=1;
		Vector3d R_i;
		Vector3d C(0,0,0);
		for(int i=0;i<samples;i++){
	
			
			float randVal_u=(rand()%10)/10.0;
		
			float randVal_v=(rand()%10)/10.0;		
			//cout << "Random values:" << endl;
			//output(randVal_u);
			//output(randVal_v);
			R_i.set( (R+ ( ( 0.5 - randVal_u ) * blurSize * u ) +  ( 0.5 - randVal_v ) * blurSize * v ) );
			R_i.set( R_i / ( R_i.norm() ) );
			//cout << "Random vector." << endl;
			//output(R_i);
			/*

			C.set( (Kr/samples) * ( C + rayTrace(P,R_i) ) );
			*/



		

			///////////////////////////////////////////////////
			int objIndex=-1;
			float t=0;
			float tMin=FLT_MAX;
			Vector3d ph;
			Vector3d n_nh;
			Vector3d retCol;
			for(int i=0;i<objectGRP.size();i++){
				if(tag!=objectGRP.at(i)->getTag()){
			
					objectGRP.at(i)->rayEq(pos,R_i);
					t=objectGRP.at(i)->getTval();
			
					if((0<t)&&(t<tMin)){
						tMin=t;
						objIndex=i;	
						ph.set(pos+(t*R_i));
						n_nh.set(objectGRP.at(i)->getNh(ph));
					
					}
				}
			}
			if(objIndex!=-1){		
				float Ks =objectGRP.at(objIndex)->shader.getKs();
				Vector3d C01;
				//C01.set(objectGRP.at(objIndex)->getCol());
		
			
				if(objectGRP.at(objIndex)->shader.texOn==false){
					C01.set(objectGRP.at(objIndex)->getCol());
				}
				else{
					C01.set(objectGRP.at(objIndex)->getTexture(ph,pos));
				}
				//C01.set((c0*(1-t))+(C01*t));
				//C01.set(objectGRP.at(objIndex)->getTexture(ph,pos));
				//C01.set((c0*(1-t))+(C01*t));
				//C01.set((C01*(1-s))+(c2*s));
				retCol.set((1-Ks)*C01);
					
			}
			else{	
				retCol.set(envMap(R_i));
			}

			C.set( (retCol + C) );
			
		}
		C.set(C*(Kr/samples));
		//exit(1);
		return C;
		
}
Vector3d refraction(float eta,Vector3d pos,Vector3d normal,Vector3d nh, char tag, Light light[]){
		
		Vector3d retCol;
		
				
		float C=nh*(-normal);
		
		float term=(((pow(C,2)-1)/(pow(eta,2)))+1);
		//output(term);
		if(term<0){		
			//cout << "Reflect." << endl;
			retCol.set(traceReflection(pos,normal,nh,tag,light));
			return retCol;
		}
		if(term>0){

			//cout << "Refract." << endl;
			Vector3d t;
			t=( (-1/eta)*(-normal) )+( ( (C/eta) - sqrt(term)) *nh);
		
			retCol.set(traceRefraction(pos,t,nh,tag,light));
			return retCol;
		}	
}
///////////////////////////////////////////////////////////////////////
Vector3d shaderFunc(Vector3d pe,Vector3d n_pe, Vector3d ph,Vector3d pos, Vector3d nh,Vector3d diffuse,Light light[],Vector3d n_pl_ph,Object* object,Vector3d pl){
	Vector3d retVal;
	//Colors
	// PART 1.0: "c0" HOLDS THE COLOR VALUE OF "IN SHADOW".
	Vector3d c0(25,50,200);
	
	float cl=1;//Controls intensity
	Vector3d colLight;
	//colLight.set(solidTexture(ph,light[0].get_pl()));
	colLight.set(light[0].get_pl());
	Vector3d c1;


	if(object->shader.texOn==false){
		c1.set(diffuse);
	}
	else{
		c1.set(object->getTexture(ph,pos));
	}
	
	
	
	Vector3d c2(255,255,255);
	Vector3d c3(255,0,0);

	//GETTING NL(NORMAL OF LIGHT)
	Vector3d nlh;	
	//nl.set(0,0,-1);
	//nl.set(rotateFunc(nl,-90,'y'));
	nlh.set(n_pl_ph);

	//CALCULATING SHADING.
	float s,t;

	//CALCULATING "t", COSTHETA FOR DIFFUSE.
	//if(object->shader.normalOn==true){
	//	nh.set(object->normalmapFunc(ph,pos,nh));
	//}



	/*
	t=nl*nh;
	if(t>1)t=1;
	Vector3d cone;
	cone.set(ph-pl);
	cone.set(cone/cone.norm());
	
	i=nl*
	


	*/
	/*t=(nlh*nh);
	if(t<0){t=0;}
	if(t>1){t=1;}
	t=pow(t,1);
	t=t*cl;
	Vector3d res;
	res.set(t*cl*colLight*(1/255.0));*/

	t=(nlh*nh);
	if(t>1){t=1;};
	if(t<0){t=0;};
	//t=t*cl;
	float i;
	Vector3d nl;
	nl.set(ph-pl);
	nl.set(nl/nl.norm());
	nl.set(rotateFunc(nl,10,'z'));
	i=nl*nlh;
	float delta=0.1;
	float iMin=0;float iMax= 1;
	i=(i-iMin)/(iMax-iMin);
	i=pow(i,10);
	if(i<0)i=0;
	if(i>1)i=1;
	t=t*i*cl;
	

		/*Vector3d nlh;
		Vector3d pl;
		pl.set(colLight);
		nlh.set(pl-ph);
		nlh.set(nlh/nlh.norm());
		nl.set(nlh);
		nl.set(rotateFunc(nl,50,'x'));
		t=nlh*nh;
		//output(t);
		if(t>1)t=1;
		if(t<0)t=0;
		float i=nl*nlh;
		float iMax=1;float iMin=0;
		i=i-iMin/(iMax-iMin);
		if(i<0)i=0;
		if(i>1)i=1;
		t=t*i;*/
		

	
	//CALCULATING, "s" COSTHETA FOR SPECULAR.
	Vector3d rpe;
	rpe.set(n_pe-(2*(n_pe*nh)*nh));
	s=rpe*n_pl_ph;
	float smin,smax;
	smin=0.8;smax=1;
	s=(s-smin)/(smax-smin);
	if(s<0){s=0;}
	if(s>1){s=1;}
	s=pow(s,10);
	s=s*cl;

	//SETTING DIFFUSE
	Vector3d col;
	
	int traces=2;
	float Ks=object->shader.getKs();
	char tag=object->getTag();
	col.set(c1);
	col.set((c0*(1-t))+(c1*t));
	Vector3d newN;newN.set(ph-pe);newN.set(newN.norm());
	
	//col.set((col*(1-Ks))+(Ks*traceReflection(ph,n_pe,nh,tag,light)));
	float eta=object->shader.getIOR();
	
	//exit(1);
	//Vector3d val;
	//val.set(object->getTexture(ph,pos));
	//eta=((val.x+val.y+val.z)/3)*(1/255.0);
	//output(eta);
	col.set((col*(1-Ks))+(Ks*refraction(eta,ph,n_pe,nh,tag,light)));


	//col.set(col*col_I);
	//col.set((c0*(1-t))+(col*t));
	col.set((col*(1-s))+(c2*s));
	//col.set(c1+((1-Ks)*traceReflection(1,n_pe,nh,tag,light)));
	/*
	c01=c01+(Ks*c02)


	*/


	//output(col);
	float Kd=0.5;
	
	//c1.set(diffuse);
	
	//c1.set(c1*irid);
	//c2.set((c1*Kd)+traceReflection(4,n_pe,nh,tag,light));
	//col.set((c0*(1.0-t))+(t*c1));
	//col.set(col/(traces+1));
	//col.set((1/255.0)*col);
	//SETTING SPECULAR
	
	//col.set((col*(1-s))+(c2*s));
	
	
	//SETTING FINAL COLOR VALUE OF A GIVEN PIXEL PROJECTED.
	retVal.set(col);
	return retVal;
}
///////////////////////////////////////////////////////////////////////////
Vector3d rayTracer(Camera camera, Light light[],vector<Object*>& object,float px,float py){
	//0.1 VARIABLES
	Vector3d cVal;//Holds value of returning color value.

	//0.2 DETERMINE n_pe.
	Vector3d pe;
	Vector3d pp;
	pe.set(camera.getPe());
	pp.set(camera.getPP(px,py));
	
	Vector3d n_pe;
	n_pe.set(camera.getNpe(px,py));	
	float samples =1;
	
	Vector3d retVal(0,0,0);
	

	Vector3d u;Vector3d v;Vector3d n;
	u.set(camera.get_n0());
	v.set(camera.get_n1());
	n.set(camera.get_n2());
	for(int i=0;i<samples;i++){
		float aperture=1;
		//if(i>0){
			double a=( (rand()%10) / 10.0 );
			double b=( (rand()%10) / 10.0 );
			double c=( (rand()%10) / 10.0 );
			double d=( (rand()%10) / 10.0 );
			double var=200;
			double pix=(1/(420.0*720.0));
			//pe.set(pe+( (0.5-a)*aperture*u) + ( (0.5-b)*aperture*v)) ;
			//pp.set(pp+ ((pp.x+0.5-c)*1*u) + ((pp.y+0.5-d)*1*v) - (pe.z-10));
			//pp.set(pe + ( (pp.x+0.5-c)*10*u) + ( (pp.y+0.5-d)*10*v ) + (10*pp.z));
			//output(pp);
			n_pe.set(pp-pe);
			n_pe.set(n_pe/n_pe.norm());		
		//}
	

		//output((pe+(px+0.5-r_i_1)*l_p*u));
		//n_pe.set();
		//output(pe+((pp.x+0.5-r_i_1)*l_p*u)+((pp.y+0.5-r_i_2)*l_p*v));
		//output(Q_i);
		//output(n_pe);
		//0.3 INITIALIZE T VALUES.
		float tVal=0;
		float tMin=FLT_MAX;//10000;

		//0.4 INTIALIZE OBJECT INDEX TO NULL CASE.
		int objectIndex=-1;
	
	
		//PART1: DETERMINE IF CAMERA CAN SEE ANY GIVEN OBJECT WITHIN VECTOR.
		for(int a=0;a<object.size();a++)
		{
			//1.1 DETERMINE IF THERE IS AN INTERSECTION.
			bool intersection=object[a]->rayEq(pe,n_pe);
		
			//1.2 GET THE T VALUE.
			float t=object[a]->getTval();
			//1.3:IF IT IS TRUE THAT THERE IS AN INTERSECTION AND THE T VALUE IS LESS THAN INFINITY.
			if( (intersection) && (t<tMin) )
			{
				//1.4: REASSIGN THE "tMin" VALUE TO "t" OF OBJECT.
				//NOTE: THE IDEA BEHIND GOING THROUGH THIS LOOP IS THAT "tMin" IS REASSIGNED IN ORDER TO GET
				//THE LEAST "tMin" VALUE.
				tMin= t;
				objectIndex=a;
				cVal.set(object[objectIndex]->getCol());
			}
		}
	
		//PART2: TRACE SHADOWS
		//2.1 IF THE OBJECT INDEX ISN'T CHANGED, THEN NOTHING HAPPENS IN REGION.
		Vector3d lval(0,0,0);
		if(objectIndex == -1){
			//cVal.set(255,255,255);
		
		
			 cVal.set(envMap(n_pe));
			return cVal;
		}
		//2.2 IF OBJECT INDEX IS CHANGED, WE PROCEED TO TRACE SHADOWS.
		else{
			
			for(int c=0;c<2;c++){
				//2.3 GO THROUGH OBJECTS.
				for(int b=0;b<object.size();b++){
								//cout << "Hello." << endl;	
								//2.4 CALCULATE "ph"		
								Vector3d ph;
								ph.set(pe+(n_pe*tMin));
						
								
									/*
										float rand_a = ( rand()%10 ) / 10.0 ;
										float rand_b = ( rand()%10 ) / 10.0 ;
										Vector3d u(1,0,0);
										Vector3d v(0,1,0);
										float l_size=1;
										pl.set( pl + ( (0.5-rand_a)*l_size*u ) + ( (0.5-rand_b)*l_size*v ) );

									*/
									//2.5 CALCULATE NORMAL, "nh"
									Vector3d nh;
									nh.set(object[b]->getNh(ph));
									//cout << "Midway." << endl;
									//2.6 CALCULATE "d" THE MAGNITUDE OF THE LENGTH
									//BETWEEN "pl" AND "ph"
									Vector3d pl_ph;
									pl_ph.set(light[c].get_pl()-ph);
									float d;
									d=pl_ph.norm();	

									//2.7 CALCULATE THE NORMAL OF "pl_ph"
									Vector3d n_pl_ph;
									n_pl_ph.set(light[c].get_pl()-ph);
									n_pl_ph.set(n_pl_ph/n_pl_ph.norm());
						
									//2.8 CALCULATE THE "t" VALUE OF THE SHADOW RAY.
									float tlVal=d;
									object[b]->rayEq(ph,n_pl_ph);
						
									//cout << "2nd Intersection." << endl;
									float temp=object[b]->getTval();
				
									//If temp value is less than tlVal, then we reassign temp to tlVal.
									if(temp<tlVal){tlVal=temp;}

								//If tlVal is between 0 and "d", then there is an object in the way of the light source.
								if(((0 < tlVal) && (tlVal < d))&&(objectIndex!=b)){	
									Vector3d shadow(0,0,0); 
									/*Vector3d dif;
									dif.set(object[objectIndex]->getCol());
					
									Vector3d pos;
									pos.set(object[objectIndex]->getPos());
					
									cVal.set(shaderFunc(pe,n_pe,ph,pos,nh,dif,light,n_pl_ph,object[objectIndex]));
									cVal.set((cVal-shadow)*(1/255.0));*/
									cVal.set(shadow);
								}
								//If else, then the object is in full view of light source.
								else{
					
									if(objectIndex==b){
					
										Vector3d dif;
										dif.set(object[objectIndex]->getCol());
					
										Vector3d pos;
										pos.set(object[objectIndex]->getPos());
					
										cVal.set(shaderFunc(pe,n_pe,ph,pos,nh,dif,light,n_pl_ph,object[objectIndex],light[c].get_pl()));
						
									}	
								}
					
						}
				lval.set(lval+cVal);
			}
			lval.set(lval*(1/2.0));//2 corresponds to the quantity of lights.
		}
		retVal.set(retVal+lval);
		
	}
	retVal.set(retVal*(1/((float)samples)));
	return retVal;




}





//PROCESS FUNC HOLDS THE LOOPS FOR THE PIXELS AND SUBPIXELS.
void processFunc(Camera camera, Light light[],vector<Object*>& object,Light envLgt,struct map eMap,struct map pntMap1,struct map pntMap2,const char *name,float aVal){
	//FOR EASE OF PROGRAMMING< SETTING VECTOR ADDRESS OF OBJECT TO ONE IN SCOPE OF FILE.	
	animVal=aVal;
	objectGRP=object;
	envLight=&envLgt;
	vMap=eMap;
	pMap1=pntMap1;
	pMap2=pntMap2;
	


	float samples=1;
	for(int y=0;y<height;y++){
		for(int x=0;x<width;x++){
			
			int i=(y*width+x)*3;
			Vector3d rgb(0,0,0);


			for(int sY=0;sY<samples;sY++){
				for(int sX=0;sX<samples;sX++){
				
					float pX=x+(sX/samples)+((rand()%1)/samples);
					float pY=y+(sY/samples)+((rand()%1)/samples);
					Vector3d retCol(0,0,0);
					//ENTER INTO THE NEXT STEP WITHIN PROCESSFUNC.


					/*Before we enter raytracer, we envelope it in a for loop based on sample size for motion blur. Everytime we pass
					  an iteration within the for loop, we*/

					/*int n_samples=1;
					Vector3d C;
					Vector3d oldPos(0,70,0);
					//oldPos.set(object.at(0)->getPos());
					//cout << "Old position:" << endl;
					//output(oldPos);
					for(int val=0;val<n_samples;val++){
						double a=(rand()%50);
						//output(a);
						Vector3d newPos;


					
						newPos.x=a+oldPos.x;
						newPos.y=a+oldPos.y;
						newPos.z=a+oldPos.z;
						//output(newPos);
						object.at(0)->setPos(newPos);
						//output(object.at(0)->getPos());
						C.set(rayTracer(camera,light,object,pX,pY));
						
						retCol.set((C+retCol));
						//output(retCol);
						
					}

					//output(1/((float)n_samples));
					retCol.set((1/((float)n_samples))*retCol);
					
					//output(retCol);
					//exit(1);*/

						retCol.set(rayTracer(camera,light,object,pX,pY));
					rgb.x=rgb.x+retCol.x;
					rgb.y=rgb.y+retCol.y;
					rgb.z=rgb.z+retCol.z;
					

				}
			}		
		rgb.x=rgb.x/(pow(samples,2));
		rgb.y=rgb.y/(pow(samples,2));
		rgb.z=rgb.z/(pow(samples,2));
		
		pixmap[i++] = rgb.x;
                pixmap[i++] = rgb.y; 
        	pixmap[i] = rgb.z; 
		}
	}
	
	writePPM(name);
	
}
//WRITE PPM
void writePPM(const char *name){
    
       unsigned char red;
       unsigned char green;
       unsigned char blue;
       string input;
       //output_fileRead = fopen("./ppmFolder/image.ppm","r");
     
	/*Create new stringstream object, sstm.*/
	std::stringstream sstm;
	//const char *name;
	
        /*Open up filestream, insert a name and open as
	"write".*/
	
	output_fileRead = fopen(name, "w");


       fprintf(output_fileRead, "P6\n");
  	
       iWidth=720;
       iHeight=480;
       fprintf(output_fileRead, "%d %d\n", iWidth, iHeight);
	
	

	/*Write to new file the the width and 
	height and introduce linebreak.*/ 
	maxcolor=255;
       fprintf(output_fileRead, "%d\n", maxcolor);
	
	

  

  /*Note that we reverse how y values are placed in file given
  the differences between how images are displayed in OpenGL vs
  how values of images are arranged.*/ 
  for(y = iHeight-1; y >= 0; y--) {
    for(x = 0; x < iWidth; x++) {
      
      /*Specifying pixel.*/ 
      int i=(y*width+x)*3;
      red = pixmap[i++];
      green = pixmap[i++];   	
      blue = pixmap[i];
      
           
      fputc(red,output_fileRead);
      fputc(green,output_fileRead);
      fputc(blue,output_fileRead);
      
    }
  }
}
///////////////////////////////////////////////////////////////////
void readPPM(FILE *input_fileRead, int &fwidth, int &fheight){
	int pixel,x,y,maxcolor;
	maxcolor=255;
	char magicNumber[2];
	char ch;		
	char comment;   
	fscanf(input_fileRead, "%s", magicNumber);
	if((magicNumber[0] == 'P') && (magicNumber[1] == '6')){
		ch=fgetc(input_fileRead);		
		ch =fgetc(input_fileRead);
		while(ch == '#'){		
			if(comment == '\n'){
				ch = fgetc(input_fileRead);
				cout << endl;
			}		
			else{
				comment = fgetc(input_fileRead);
				//cout << comment;
			}
		}
		ungetc(ch, input_fileRead);
		fscanf(input_fileRead, "%d %d %d", &fwidth, &fheight, &maxcolor);	
		//cout << "width = " << fwidth << "" << " height = " << fheight << "" << " maxcolor = " << maxcolor << "" << endl;
	}
	else{
		cout << "Incorrect file format. Please try again." << endl;	
	}

	fgetc(input_fileRead);
    
  	ppmPixmap = new unsigned char[fwidth * fheight *3];

  	for(y = fheight-1; y >= 0; y--){
    		for(x = 0; x < fwidth; x++){
		      pixel = (y *fwidth + x)*3; 
		      ppmPixmap[pixel++] = fgetc(input_fileRead);
		      ppmPixmap[pixel++] = fgetc(input_fileRead);
		      ppmPixmap[pixel] = fgetc(input_fileRead);
    		}
  	}	
}
///////////////////////////////////////////////////////////////////
void readPPM2(FILE *input_fileRead, int &fwidth, int &fheight){
	int pixel,x,y,maxcolor;
	char magicNumber[2];
	char ch;		
	char comment;   
	fscanf(input_fileRead, "%s", magicNumber);
	if((magicNumber[0] == 'P') && (magicNumber[1] == '6')){
		ch=fgetc(input_fileRead);		
		ch =fgetc(input_fileRead);
		while(ch == '#'){		
			if(comment == '\n'){
				ch = fgetc(input_fileRead);
				cout << endl;
			}		
			else{
				comment = fgetc(input_fileRead);
				//cout << comment;
			}
		}
		ungetc(ch, input_fileRead);
		fscanf(input_fileRead, "%d %d %d", &fwidth, &fheight, &maxcolor);	
		//cout << "width = " << fwidth << "" << " height = " << fheight << "" << " maxcolor = " << maxcolor << "" << endl;
	}
	else{
		cout << "Incorrect file format. Please try again." << endl;	
	}

	fgetc(input_fileRead);
    
  	bumpMap = new unsigned char[fwidth * fheight *3];

  	for(y = fheight-1; y >= 0; y--){
    		for(x = 0; x < fwidth; x++){
		      pixel = (y *fwidth + x)*3; 
		      bumpMap[pixel++] = fgetc(input_fileRead);
		      bumpMap[pixel++] = fgetc(input_fileRead);
		      bumpMap[pixel] = fgetc(input_fileRead);
    		}
  	}	
}
/////////////////////////////////////////////////////////////////////
struct map testPPM(FILE *input_fileRead ){
	int fwidth; int fheight;
	int pixel,x,y,maxcolor;
	char magicNumber[2];
	char ch;		
	char comment;   
	fscanf(input_fileRead, "%s", magicNumber);
	if((magicNumber[0] == 'P') && (magicNumber[1] == '6')){
		ch=fgetc(input_fileRead);		
		ch =fgetc(input_fileRead);
		while(ch == '#'){		
			if(comment == '\n'){
				ch = fgetc(input_fileRead);
				cout << endl;
			}		
			else{
				comment = fgetc(input_fileRead);
				//cout << comment;
			}
		}
		ungetc(ch, input_fileRead);
		fscanf(input_fileRead, "%d %d %d", &fwidth, &fheight, &maxcolor);	
		//cout << "width = " << fwidth << "" << " height = " << fheight << "" << " maxcolor = " << maxcolor << "" << endl;
	}
	else{
		cout << "Incorrect file format. Please try again." << endl;	
	}

	fgetc(input_fileRead);
    
  	bumpMap = new unsigned char[fwidth * fheight *3];

  	for(y = fheight-1; y >= 0; y--){
    		for(x = 0; x < fwidth; x++){
		      pixel = (y *fwidth + x)*3; 
		      bumpMap[pixel++] = fgetc(input_fileRead);
		      bumpMap[pixel++] = fgetc(input_fileRead);
		      bumpMap[pixel] = fgetc(input_fileRead);
    		}
  	}
	struct map testMap;
	testMap.height=fheight;
	testMap.width=fwidth;
	testMap.map=bumpMap;	

	return testMap;
}
