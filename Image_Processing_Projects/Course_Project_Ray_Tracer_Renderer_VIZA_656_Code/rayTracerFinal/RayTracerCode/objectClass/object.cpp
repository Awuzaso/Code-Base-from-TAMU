#include <iostream>
#include "../vectorFiles/vector.h"
#include "object.h"
#include "../support/debugTool.cpp"
using namespace std;

Object::Object()
{
	std::cout << "Default constructor called." << endl;
	position.set(0,0,0);
	color.set(0,0,0);

	//output(position);
	//output(color);
}
Object::Object(Vector3d pos,Vector3d col)
{
	position.set(pos);	
	color.set(col);	

	//output(position);
	//output(color);
}

Object::~Object()
{
	//std::cout << "Object removed from memory." << endl;
}

Vector3d Object::getPos()
{	
	return position;	
}

Vector3d Object::getCol()
{
	return color;
}
/*NOW COVERING THE DERIVED CLASSES.*/
//Sphere class.
Sphere::Sphere(float rad, Vector3d pos,Vector3d col):Object(pos,col){
	//std::cout << "Sphere generated." << endl;		
	radius=rad;
	set_sx(rad);
	set_sy(rad);
	set_sz(rad);
}
float Sphere::getRad(){
	return radius;
}







//Plane class
Plane::Plane(float x,float y,Vector3d inter,Vector3d pos,Vector3d col):Object(pos,col){
	//std::cout << "Plane generated." << endl;	
	sizeX=x;
	sizeY=y;
	intersection=inter;
	set_sx(x);
	set_sy(y);
	set_sz(0);
}
float Plane::getX(){
	return sizeX;
}
float Plane::getY(){
	return sizeY;
}
Vector3d Plane::getInter(){
	return intersection;
}


//Triangle Class
Triangle::Triangle(){
	p0.set(0,0,0);
	p1.set(0,0,0);
	p2.set(0,0,0);
	
	uv0.set(0,0);
	uv1.set(0,0);
	uv2.set(0,0);

	n0.set(0,0,0);
	n1.set(0,0,0);
	n2.set(0,0,0);
};
Triangle::Triangle(Vector3d *p,Vector2d *u,Vector3d *n,Vector3d pos,Vector3d col):Object(pos,col){
	float scale=0.5;
	p0.set(p[0]+getPos());
	//p0.set(scale*p0);
	p1.set(p[1]+getPos());
	//p1.set(scale*p1);
	p2.set(p[2]+getPos());
	//p2.set(scale*p2);
	//output(p0);output(p1);output(p2);
	uv0.set(u[0]);
	uv1.set(u[1]);
	uv2.set(u[2]);

	n0.set(n[0]);
	n1.set(n[1]);
	n2.set(n[2]);

	
}


//Object Class
Obj::Obj(FILE * objFile, Vector3d pos,Vector3d col):Object(pos,col){	
	loadOBJ(objFile);

}
void Obj::loadOBJ(FILE * objFile){
	//Temporary Vectors to hold contents of .obj file.
	//Triangle tempFace;
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< Vector3d > temp_vertices;
	vector< Vector2d > temp_uvs;
	vector< Vector3d > temp_normals;

	/*We first determine if the file was opened or not.*/
	if( objFile == NULL){
		cout << "File unable to open." << endl;
		//return false;
		exit(1);
	}
	else{
		cout << "File opened!" << endl;
		//return true;
	}
		int i=0;
		/*Function continues to parse through file until E0F.*/
		while(1){
				
				
				char lineHeader[128];//Read through first word of line.
				int res = fscanf(objFile, "%s",lineHeader);
				if(res == EOF)
					break; //EOF = End of File. Quit the loop.
				//Else: Parse Line Header.
				
				
				//Read vertices.
				if(strcmp(lineHeader, "v") == 0){
						Vector3d vertex;
						float a,b,c;
						fscanf(objFile, "%f %f %f\n", &a,&b,&c);
						vertex.set(a,b,c);
						//i=i+1;
						temp_vertices.push_back(vertex+getPos());
						//cout << "Vertex " << endl;
						//output(vertex);
						
				}
				//Read vertex texture coordinates.
				else if(strcmp(lineHeader, "vt") == 0){
						Vector2d uv;
						float a,b;
						fscanf(objFile,"%f %f\n", &a, &b);
						uv.set(a,b);
						temp_uvs.push_back(uv);
						//cout << "UV" << endl;	
						//output(uv);
				}
				
				//Read vertex normal coordinates.
				else if(strcmp(lineHeader, "vn") == 0){
						Vector3d normal;
						float a,b,c;
						fscanf(objFile,"%f %f %f\n", &a, &b,&c);
						normal.set(a,b,c);
						temp_normals.push_back(normal);
						//cout << "Normal." << endl;
						//output(normal);
				}
				
				///*//Read faces coordinates.
				else if(strcmp(lineHeader,"f")==0){
					string vertex1,vertex2,vertex3;
					unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
					int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n",  &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
					 if (matches != 9){
						printf("File can't be read by our simple parser : ( Try exporting with other options\n");
						exit(1);
					}
					//cout << "//////////////////////////////" << endl;
					//cout << "FACE " <<  ++i << endl;
					vertexIndices.push_back(vertexIndex[0]);//This vertex index corresponds to the p0.
					vertexIndices.push_back(vertexIndex[1]);//This vertex index corresponds to the p1.
					vertexIndices.push_back(vertexIndex[2]);//This vertex index corresponds to the p2.
					//cout << "Vertex indices" << endl;
					//cout << vertexIndex[0] << endl;
					//cout << vertexIndex[1] << endl;
					//cout << vertexIndex[2] << endl;
					Vector3d p[3];
					p[0]=(temp_vertices[vertexIndex[0]-1]);
					p[1]=(temp_vertices[vertexIndex[1]-1]);
					p[2]=(temp_vertices[vertexIndex[2]-1]);
					//tempFace.setVertex(p);
					






					
					uvIndices.push_back(uvIndex[0]);//This uv index corresponds to the p0.
					uvIndices.push_back(uvIndex[1]);//This uv index corresponds to the p1.
					uvIndices.push_back(uvIndex[2]);//This uv index corresponds to the p2.
					//cout << "UV indices for face" <<  endl;
					//cout << uvIndex[0] << endl;
					//cout << uvIndex[1] << endl;
					//cout << uvIndex[2] << endl;
					Vector2d uv[3];
					uv[0]=(temp_uvs[uvIndex[0]-1]);
					uv[1]=(temp_uvs[uvIndex[1]-1]);
					uv[2]=(temp_uvs[uvIndex[2]-1]);
					//tempFace.setUV(uv);
			

					normalIndices.push_back(normalIndex[0]);//This normal index corresponds to the p0.
					normalIndices.push_back(normalIndex[1]);//This normal index corresponds to the p1.
					normalIndices.push_back(normalIndex[2]);//This normal index corresponds to the p2.
					//cout << "Normal indices for face" <<  endl;
					//cout << normalIndex[0] << endl;
					//cout << normalIndex[1] << endl;
					//cout << normalIndex[2] << endl;
					Vector3d n[3];
					n[0]=(temp_normals[normalIndex[0]-1]);
					n[1]=(temp_normals[normalIndex[1]-1]);
					n[2]=(temp_normals[normalIndex[2]-1]);
					//tempFace.setNorm(n);
					
					//Setting A and N.
					//tempFace.A.set((tempFace.p0-tempFace.p1)%(tempFace.p2-tempFace.p0));
					//tempFace.N.set(tempFace.A/tempFace.A.norm());
					//tempFace.setA_N();
					Triangle tempFace(p,uv,n,getPos(),getCol());
					triGRP.push_back(tempFace);
				}		
	}		
}






