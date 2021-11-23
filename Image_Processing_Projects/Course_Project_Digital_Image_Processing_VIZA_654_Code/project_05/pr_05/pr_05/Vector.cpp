class Vector3D
{
	public:
		float x, y, z;
		void setV(float x1, float y1, float z1)
		{
			x = x1, y = y1, z = z1;
		}
		Vector3D(float x1,float y1, float z1)
		{
			x = x1, y = y1, z = z1;
		}
		Vector3D(){x=0;y=0;z=0;}
		Vector3D operator +(const Vector3D& v) const
		{
		    return (Vector3D(x + v.x, y + v.y, z + v.z));
		}
		Vector3D operator /(const float& v) const
		{
		    return (Vector3D(x / v, y / v, z / v));
		}
		Vector3D operator *(const float& v) const
		{
		    return (Vector3D(x * v, y * v, z * v));
		}
};
class Vector2D
{
	public:
		float x, y;
		Vector2D(){x=0;y=0;}
		Vector2D(float x1, float y1)
		{
		    x = x1;
		    y = y1;
		}
		void setV(float x1, float y1)
		{
			x = x1, y = y1;
		}
	Vector2D operator -(const Vector2D& v) const
        {
            return (Vector2D(x - v.x, y - v.y));
        }
        
        float operator *(const Vector2D& v) const
        {
            return (x * v.x + y * v.y);
        }
};
class Matrix3x3
{
	public:
		float matrix [3][3];
		float mat [3][3];//copy for operations

		Matrix3x3(){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				matrix[j][k] = 0;
		}
		Matrix3x3(float x[3][3]){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				matrix[j][k] = x[j][k];
		}
		float get(int row, int col){
			return matrix[row][col];
		}
		void set(int row, int col, float val){
			matrix[row][col] = val;
		}
		void set(float val){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				matrix[j][k] = val;
		}
		void set(float x[3][3]){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				matrix[j][k] = x[j][k];
		}
		Matrix3x3 operator +(const Matrix3x3& x){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				mat[j][k] = matrix[j][k] + x.matrix[j][k];
			return mat;
		}
		Matrix3x3 operator +(const float& x){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				mat[j][k] = matrix[j][k] + x;
			return mat;
		}
		Matrix3x3 operator -(const Matrix3x3& x){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				mat[j][k] = matrix[j][k] - x.matrix[j][k];
			return mat;
		}
		Matrix3x3 operator -(const float& x){
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				mat[j][k] = matrix[j][k] - x;
			return mat;
		}
		Vector3D operator *(const Vector3D& b){
			float newM [] = {0,0,0};
			float oldM [] = {b.x,b.y,b.z};
			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
				newM[j] += matrix[j][k]*oldM[k];
			return Vector3D(newM[0],newM[1],newM[2]);
		}
		Matrix3x3 operator *(const Matrix3x3& b){
			for(int j = 0;j<3;j++)//make sure mat is initially 0
			  for(int k = 0;k<3;k++)
				mat[j][k] = 0;

			for(int j = 0;j<3;j++)
			  for(int k = 0;k<3;k++)
			    for(int l = 0;l<3;l++)
				mat[j][k] += matrix[j][l]*b.matrix[l][k];
			return mat;
		}
};
