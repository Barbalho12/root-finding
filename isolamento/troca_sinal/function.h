#ifndef __FUNC__
#define __FUNC__

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include <vector>

using namespace std;


class Function{
	
	private:
		string name;
		vector<double> coeficientes;
	
	public:
		Function(string name, vector<double> coeficientes);
		Function(vector<double> coeficientes);
		~Function();
		double solve(double);
		void show();
	
};

#endif