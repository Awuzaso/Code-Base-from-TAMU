#include "../vectorFiles/vector.h"
#include <iostream>
using namespace std;
void output(Vector3d vec){
	cout << "X value: " << vec.x << "" << endl;
	cout << "Y value: " << vec.y << "" << endl;
	cout << "Z value: " << vec.z << "" << endl;
	cout << " " << endl;
}
void output(int value){
	cout << "Value:" << value << endl;
	cout << " " << endl;
}

void output(float value){
	cout << "Value:" << value << endl;
	cout << " " << endl;
}

void output(double value){
	cout << "Value:" << value << endl;
	cout << " " << endl;
}


