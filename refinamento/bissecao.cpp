#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include <stdlib.h> 
#include "../model/function.cpp"

using namespace std;

//Criei o tipo Function que é um ponteiro para funções
typedef float (*Funcao)(float);

//f(x) = x² - 2
float func1(float x) { 
	return x*x - 2;
}

//Recebe uma f qualquer
//limite é a aproximação de 0.0, aplicando |f(m)| 
float bissecao(Funcao f, float baixo, float alto, float limite){
	float m;
	do{
		m = (alto + baixo)/2;
	
		if(f(baixo) * f(m) > 0){
			baixo = m;
		}else{
			if(f(m) == 0.00){
				break;
			}else{
				alto = m;
			}
		}
	} while( fabs(f(m)) > limite );
	return m;
}


float bissecao(Function f, float baixo, float alto, float limite){
	float m;
	do{
		m = (alto + baixo)/2;
	
		if(f.solve(baixo) * f.solve(m) > 0){
			baixo = m;
		}else{
			if(f.solve(m) == 0.00){
				break;
			}else{
				alto = m;
			}
		}
	} while( fabs(f.solve(m)) > limite );
	return m;
}


int main(int argc, const char * argv[]){
	
	float raiz = bissecao(func1, 0.5, 2.0, 0.0001);
	
	cout << raiz << endl;
	
	return 0;
}