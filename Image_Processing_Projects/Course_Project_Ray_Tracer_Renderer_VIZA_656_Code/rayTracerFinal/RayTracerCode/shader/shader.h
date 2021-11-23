#include "../vectorFiles/vector.h"

#include <iostream>
using namespace std;



#ifndef SHADER_CLASS
#define SHADER_CLASS
struct map
{
	float width;
	float height;	
	unsigned char * map;
};

class Shader
{
	private:
		Vector3d color;
		map textureMap;
		map normalMap;
		char shaderType;
		float Ks; 
		float indexRefr;
		/*TYPES:
		'L'=Lambert
		'P'=Phong
		'G'=Gooch
		*/
	public:
		bool texOn;
		bool normalOn;
		Shader(){
			color.set(0,0,0);
			shaderType='n';
		};
		Shader(Vector3d col, map tMap, map nMap, char type){
					color.set(col);
					shaderType=type;
					textureMap=tMap;
					normalMap=nMap;
					
		};
		void setKs(float ksVal){Ks=ksVal;};
		float getKs(){return Ks;};
		
		void setIOR(float ior){
		//cout << "You put in: " << ior << endl;		
		indexRefr=ior;};



		float getIOR(){
		//cout << "The value: " << indexRefr << endl;	
		return indexRefr;};
		void setShader(Vector3d col, map tMap, map nMap, char type){
			color.set(col);
			shaderType=type;
			textureMap=tMap;
			normalMap=nMap;
		};
		Vector3d getColor(){
			return color;
		};
		char getType(){
			return shaderType;
		};
		map getTexMap(){
			return textureMap;
		};
		map getNormMap(){
			return normalMap;
		};
		












};
#endif
