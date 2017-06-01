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
// #include "../isolamento/lagrange.cpp"

using namespace std;

//Criei o tipo Function que é um ponteiro para funções
// typedef float (*Funcao)(float);

double tempoPrint;

int qtdPassos;

// //f(x) = x² - 2
// float func1(float x) { 
// 	return x*x - 2;
// }

//Recebe uma f qualquer
//limite é a aproximação de 0.0, aplicando |f(m)| 
// float bissecao(Funcao f, float baixo, float alto, float limite){
// 	qtdPassos = 0;
	
// 	float m;
// 	do{
// 		qtdPassos++;
		
// 		m = (alto + baixo)/2;
	
// 		if(f(baixo) * f(m) > 0){
// 			baixo = m;
// 		}else{
// 			if(f(m) == 0.00){
// 				break;
// 			}else{
// 				alto = m;
// 			}
// 		}
// 	} while( fabs(f(m)) > limite );
// 	return m;
// }

void lerArgs(int argc, const char * argv[], float &baixo, float &alto, float &limite){
	if(argc > 1){
		baixo = atof(argv[2]);
	}if(argc > 2){
		alto = atof(argv[3]);
	}if(argc > 3){
		limite = atof(argv[4]);
	}
}

Function lerFunction(int argc, const char * argv[]){
	Function f;
	
	if(argc <= 5){
		f.readFromUser();

	}else{
		vector<float> coeficientes(argc-5, 0);
	
		for(int i = 0; i < argc-5; i++){
			coeficientes[i] = atof(argv[argc-i-1]);
		}

		f.setCoeficientes(coeficientes);
		f.show();
	}

	return f;
}


float bissecao(Function f, float baixo, float alto, float limite){
	qtdPassos = 0;
	
	
	float m;
	do{
		qtdPassos++;
		
		m = (alto + baixo)/2;
		
		auto t1 = std::chrono::high_resolution_clock::now();
		cout << qtdPassos<< " Iteração: " << baixo << " ~ " << alto << endl;
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tempo2 = t2 - t1;
		tempoPrint += tempo2.count();
	
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

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

int main(int argc, const char * argv[]){
	
	Function f = lerFunction(argc, argv);
	
	float alto =  2;
	float baixo = 0.5;
	float limite = 0.01;
	
	lerArgs(argc, argv, baixo, alto, limite);
	
	auto t1 = std::chrono::high_resolution_clock::now();
	
	float raiz = bissecao(f, baixo, alto, limite);
	
	cout <<  "A raiz é " << raiz << endl;
	cout <<  "Numero de passos: " << qtdPassos << endl;
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);
	return 0;
}