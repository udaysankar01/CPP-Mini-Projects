#include <iostream>
#include <math.h>

int A = 30, B=30, C=30;

float calculateX(int i, int j, int k)
{
	return j*sin(A)*sin(B)*cos(C) - 
		k*cos(A)*sin(B)*cos(C) + 
		j*cos(A)*sin(C) + 
		k*sin(A)*sin(C) + 
		i*cos(B)*cos(C);
}

float calculateY(int i, int j, int k)
{
	return j*cos(A)*cos(C) + 
		k*sin(A)*cos(C) - 
		j*sin(A)*sin(B)*sin(C) +
		k*cos(A)*sin(B)*sin(C) - 
		i*cos(B)*sin(C);
}

float calculateZ(int i, int j, int k)
{
	return k*cos(A)*cos(B) - j*sin(A)*cos(B) + i*sin(B);
}
	
int main()
{
	std::cout << calculateX(1, 2, 3) << '\n';
	std::cout << calculateY(1, 2, 3) << '\n';
	std::cout << calculateZ(1, 2, 3) << '\n';
	return 0;
}
