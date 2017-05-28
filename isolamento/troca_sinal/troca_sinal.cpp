#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include <cmath>
#include "function.cpp"
#include <vector>

using namespace std;

void lerArgs(int argc, const char * argv[], double &x_init, double &passo){
	if(argc > 1){
		x_init = atof(argv[1]);
	}if(argc > 2){
		passo = atof(argv[2]);
	}
}




// double troca_sinal(double x_init, double passo){
// 	double x = x_init;
// 	while( f(x) * f(x + p) > 0){
// 		x = x + p;
// 	}
// }



int main(int argc, const char * argv[]){
	

	
	vector<double> c(3);
	c[0] = 1;
	c[1] = 0;
	c[2] = -2;
	Function f(c);
	f.show();
	

	
	double x;
	double step;
	
	lerArgs(argc, argv, x, step);
	
	cout << x << " ------------- " << step << " = " << f.solve(x) << endl;
	
	
	
	//while the signal doesn't change
	while(f.solve(x) * f.solve(x + step) > 0){
		x += step;
	}
	
	std::cout << "The root is inside the inteval [" << x << ", "<< x+step << "]" << std::endl;
	
	return 0;
}