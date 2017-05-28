#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include <cmath>
#include "../model/function.cpp"
#include <vector>

using namespace std;

double tempoPrint;

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

void lerArgs(int argc, const char * argv[], float &x_init, float &passo){
	if(argc > 1){
		x_init = atof(argv[1]);
	}if(argc > 2){
		passo = atof(argv[2]);
	}
}

void troca_sinal(Function f, float x_init, float passo, float &baixo, float &alto){

	float x = x_init;
	
	while(f.solve(x) * f.solve(x + passo) > 0){
		cout << x <<  " = " << f.solve(x) << " ------ " << passo + x << " = " << f.solve(passo+ x) << endl;
		x += passo;
	}
	
	baixo = x;
	alto = x + passo;
}


int main(int argc, const char * argv[]){

	vector<float> c(3);
	c[0] = 1;
	c[1] = 0;
	c[2] = -2;
	Function f(c);
	
	cout << "\nA função recebida:  ";
	f.show();
	cout << endl;
	
	float x;
	float passo;
	
	lerArgs(argc, argv, x, passo);
	
	auto t1 = std::chrono::high_resolution_clock::now();
	//Enquanto o sinal não muda
	while(f.solve(x) * f.solve(x + passo) > 0){
		
		auto t2 = std::chrono::high_resolution_clock::now();
		
		cout << x <<  " = " << f.solve(x) << " ------ " << passo + x << " = " << f.solve(passo+ x) << endl;
		
		auto t3 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tempo1 = t3 - t2;
		tempoPrint += tempo1.count();
		
		x += passo;
	}
	
	auto t4 = std::chrono::high_resolution_clock::now();
	
	cout << x <<  " = " << f.solve(x) << " ------ " << passo + x << " = " << f.solve(passo+ x) << endl;
	cout << "\nA raiz está no intervalo [" << x << ", "<< x+passo << "]" << endl;
	
	auto t5 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo2 = t5 - t4;
	tempoPrint += tempo2.count();
	
	
	auto t6 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo3 = t6 - t1;
	double tempoTotal = tempo3.count();
	showTime(tempoTotal);
	
	return 0;
}