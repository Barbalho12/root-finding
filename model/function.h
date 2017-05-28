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
		vector<float> coeficientes;
	
	public:
		Function(string name, vector<float> coeficientes);
		Function(vector<float> coeficientes);
		~Function();
		float solve(float);
		void show();
		vector<float> getCoeficientes();
	
};

#endif