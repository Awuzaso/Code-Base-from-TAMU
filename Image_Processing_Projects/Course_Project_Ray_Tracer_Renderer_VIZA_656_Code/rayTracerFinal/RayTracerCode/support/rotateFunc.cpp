
Vector3d rotateFunc(Vector3d vec,float degree,char axis){
	Vector3d retVal;
	float theta=degree*3.14159265/180;
	if(axis=='x'){
		float rotMX[3][3]=   {{1,0,0},
			     	     {0,cos(theta),-sin(theta)},
			             {0,sin(theta),cos(theta)}};

		Matrix3x3 matrix = Matrix3x3(rotMX);
		Vector3D dir (vec.x,vec.y,vec.z);
		Vector3D dirT = matrix * dir;
		retVal.x=dirT.x;
		retVal.y=dirT.y;
		retVal.z=dirT.z;
		return retVal;
	}

	if(axis=='y'){
		float rotMY[3][3]=   {{cos(theta),0,sin(theta)},
			     	     {0,1,0},
			             {-sin(theta),0,cos(theta)}};

		Matrix3x3 matrix = Matrix3x3(rotMY);
		Vector3D dir (vec.x,vec.y,vec.z);
		Vector3D dirT = matrix * dir;
		retVal.x=dirT.x;
		retVal.y=dirT.y;
		retVal.z=dirT.z;
		return retVal;
	}

	if(axis=='z'){
		float rotMZ[3][3]=   {{cos(theta),-sin(theta),0},
			     	     {sin(theta),cos(theta),0},
			             {0,0,1}};

		Matrix3x3 matrix = Matrix3x3(rotMZ);
		Vector3D dir (vec.x,vec.y,vec.z);
		Vector3D dirT = matrix * dir;
		retVal.x=dirT.x;
		retVal.y=dirT.y;
		retVal.z=dirT.z;
		return retVal;
	}
}

Vector3d rotate(Vector3d V0, Vector3d V1, float t){

	//Slerp
	Vector3d V_r;
	V_r.set( ( (1-t)*V0 ) + ( t*V1 ) );

	//Normal
	Vector3d N;
	N.set(V_r/V_r.norm());

	//Theta
	float theta= V_r.norm();

	Vector3d r;


	r.set( (cos(theta)*V0) + ( (1-cos(theta)) * (V0*N) * (N) ) + ( sin(theta) * (N%V0) ) );

	return r;

}
