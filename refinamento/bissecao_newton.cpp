#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include "../model/function.cpp"

using namespace std;
typedef std::vector<float> vetor;

double tempoPrint;
int qtdPassos_bi = 0;
int qtdPassos_ne = 0;

float bissecao(Function f, float baixo, float alto, float limite){
	
	float m;
	// cout << qtdPassos_bi<< " Iteração: " << m << endl;
	do{
		qtdPassos_bi++;
		
		m = (alto + baixo)/2;
		
			auto t1 = std::chrono::high_resolution_clock::now();
			cout << qtdPassos_bi<< " Iteração: " << baixo << " ~ " << alto << endl;
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
	
	} while( fabs(f.solve(m))  > 1);
	return m;
}


float newton(Function f, float limite, float xap){
	
	// float xap = baixo + alto * ((float)(rand())/RAND_MAX);

	auto t1 = std::chrono::high_resolution_clock::now();
	cout << "x inicial da bisseção: " << xap << endl;
	cout << "----------------------------"  << endl;
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo2 = t2 - t1;
	tempoPrint += tempo2.count();
		
	
	Function f_ = f.calculateDerivada();

	float xnovo;
	
	do{
		qtdPassos_ne++;
		
		xnovo = xap - (f.solve(xap)/f_.solve(xap));

		xap = xnovo;
		
		auto t1 = std::chrono::high_resolution_clock::now();
		cout << "Iteração " << qtdPassos_ne << ": " << f.solve(xap) << endl;
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
	
	//calcula o tempo dos prits
	auto t1 = std::chrono::high_resolution_clock::now();
	cout << "Baixo: " << baixo << endl;
	cout << "Alto: " << alto << endl;
	cout << "Precisão: " << limite << endl;
	cout << "----------------------------"  << endl;
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo1 = t2 - t1;
	tempoPrint += tempo1.count();

	
	t1 = std::chrono::high_resolution_clock::now();
	
	float raiz1 = bissecao(f, baixo, alto, 1);
	
	float raiz2 = newton(f, limite, raiz1);
	
		
    t2 = std::chrono::high_resolution_clock::now();
    
    
    
    cout <<  "A raiz é " << raiz2 << endl;
    cout <<  "Numero de passos Bisseçaõ: " << qtdPassos_bi << endl;
	cout <<  "Numero de passos Newton: " << qtdPassos_ne << endl;
    
    std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);
	
	return 0;
}

// #include <unistd.h>
// #include <iostream>
// #include <cstdlib>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <chrono>
// #include <math.h>

// using namespace std;
// typedef std::vector<float> vetor;

// double tempoPrint;

// int grau;
// float alto, baixo;
// vetor coeficiente(grau+1, 0);

// float f_(float n, vetor &derivada){
// 	float aux=0;
// 	for (int i = 0; i < grau; ++i)
// 	{
// 		aux = aux + derivada[i]*pow(n,i);
// 	}

// 	return aux;
// }

// float f(float n){
// 	float aux=0;
// 	for (int i = 0; i < grau+1; ++i)
// 	{
// 		aux = aux + coeficiente[i]*pow(n,i);
// 	}

// 	return aux;
// }

// void verificacao(vetor &derivada){
// 	int n;
// 	for (int i = grau; i > 0; --i)
// 	{
// 		n = i-1;
// 		derivada[n]= i*coeficiente[i];
		
// 	}
	
// }

// void showTime(double tempoTotal){
// 	cout << "----------------------------"  << endl;
// 	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
// 	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
// }

// void newton(){
// 	srand(time(NULL));
// 	float xap=baixo + alto*((float)(rand())/RAND_MAX);
// 	vetor derivada(grau, 0);
// 	verificacao(derivada);
// 	float xnovo, resposta;
// 	do{
// 		xnovo = xap - (f(xap)/f_(xap, derivada));
// 		cout << xap<<"\n";
// 		resposta = xnovo-xap;
// 		if(resposta<0)
// 			resposta = -1*resposta;

// 		xap = xnovo;		
// 	}while(resposta>0);
	
// 	//Verifica tempo de impressão
// 	auto t1 = std::chrono::high_resolution_clock::now();
	
// 	cout << "A aproximação desejada é "<<xap<<"\n";
	
// 	auto t2 = std::chrono::high_resolution_clock::now();
// 	std::chrono::duration<double> tempo = t2 - t1;
// 	tempoPrint += tempo.count();
// }

// void bissecao(){
// 	float m, resposta;
// 	float alto_baixo;
// 	do{
// 		alto_baixo = alto + baixo;
// 		m = (alto_baixo/2);
// 		if (f(m)*f(baixo)>0)
// 		{
// 			baixo = m;
// 		}else{
// 			if(f(m)== 0){
			
//                 auto t1 = std::chrono::high_resolution_clock::now();
				
// 				cout << "A raiz é "<<m<<"\n";
				
//                 auto t2 = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double> tempo = t2 - t1;
//                 tempoPrint += tempo.count();
		    
// 		    }
// 			else{
// 				alto = m;
			    
// 			}
// 		}
// 		resposta = alto - baixo;
// 	}while(fabs(resposta) >2);
// 	newton();
// }

// int main(){
// 	cout << "Qual o grau do polinômio?\n";
// 	cin >> grau;


// 	for (int i = grau; i >= 0; --i)
// 	{
// 		cout << "Qual o coeficiente de X^"<<i<<"?\n";
// 		cin >> coeficiente[i];
// 		if(i==grau && coeficiente[i]<=0){
// 			cout << "a_n deve ser maior que zero, por favor informe um outro número\n";
// 			cin >> coeficiente[i];
// 		}
// 		if (i ==0 && coeficiente[i]==0)
// 		{
// 			cout << "a_0 não pode ser zero, por favor informe um outro número\n";
// 			cin >> coeficiente[i];
// 		}
// 	}

// 	/*imprime na tela*/
// 	cout << "Sua função: ";
// 	for (int i = grau; i >= 0; --i)
// 	{
// 		if(i==grau ||coeficiente[i]<0)
// 			cout << coeficiente[i]<<"X^"<<i<<" ";
// 		else
// 			cout << "+ "<<coeficiente[i]<<"X^"<<i<<" ";
// 	}
// 	cout << "\n";

// 	cout << "Limite inferior:\n";
// 	cin >> baixo;
// 	cout << "Limite Superior:\n";
// 	cin >> alto;
    
//     auto t1 = std::chrono::high_resolution_clock::now();
	
// 	bissecao();
	
// 	auto t2 = std::chrono::high_resolution_clock::now();
// 	std::chrono::duration<double> tempo = t2 - t1;
// 	double tempoTotal = tempo.count();
// 	showTime(tempoTotal);
	
// 	return 0;
// }