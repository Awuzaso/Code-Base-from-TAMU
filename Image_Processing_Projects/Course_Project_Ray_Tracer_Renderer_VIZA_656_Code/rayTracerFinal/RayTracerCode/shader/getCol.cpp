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
