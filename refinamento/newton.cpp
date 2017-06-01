#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include "../model/function.cpp"

using namespace std;
// typedef std::vector<float> vetor;

double tempoPrint;
int qtdPassos = 0;


float newton(Function f, float baixo, float alto, float limite){
	
	float xap = baixo + alto * ((float)(rand())/RAND_MAX);
	cout << "x inicial aleatório no intervalo: " << xap << endl;
	cout << "----------------------------"  << endl;
	
	Function f_ = f.calculateDerivada();

	float xnovo;
	
	do{
		qtdPassos++;
		
		xnovo = xap - (f.solve(xap)/f_.solve(xap));

		xap = xnovo;
		
		auto t1 = std::chrono::high_resolution_clock::now();
		cout << "Iteração " << qtdPassos << ": " << f.solve(xap) << endl;
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tempo = t2 - t1;
		tempoPrint += tempo.count();
		
	}while( fabs(f.solve(xap)) > limite );

	return xap;
}



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

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}


int main(int argc, const char * argv[]){
	
	srand(time(NULL));
	
	Function f = lerFunction(argc, argv);
	
	float alto =  2;
	float baixo = 0.5;
	float limite = 0.01;
	
	lerArgs(argc, argv, baixo, alto, limite);
	
	cout << "Baixo: " << baixo << endl;
	cout << "Alto: " << alto << endl;
	cout << "Precisão: " << limite << endl;
	cout << "----------------------------"  << endl;
	
	auto t1 = std::chrono::high_resolution_clock::now();
	
	float raiz = newton(f, baixo, alto, limite);
	
    auto t2 = std::chrono::high_resolution_clock::now();
    
    
    
    cout <<  "A raiz é " << raiz << endl;
	cout <<  "Numero de passos: " << qtdPassos << endl;
    
    std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);
	
	return 0;
}