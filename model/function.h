#ifndef __FUNC__
#define __FUNC__

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


class Function{
	
	private:
		string name;
		vector<float> coeficientes;
	
	public:
		Function();
		Function(vector<float> coeficientes);
		Function(string name, vector<float> coeficientes);
		~Function();
		void readFromUser();
		float solve(float);
		void show();
		vector<float> getCoeficientes();
		void setCoeficientes(vector<float> coeficientes);
		int getGrau();
		Function calculateDerivada();
		
	
};


#endif