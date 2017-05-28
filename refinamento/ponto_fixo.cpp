#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include "../model/function.cpp"

using namespace std;
typedef std::vector<float> vetor;

int grau;
float alto, baixo;
double tempoPrint;
vetor coeficiente(grau+1, 0);

float g_(float n, vetor &derivada){
	float aux=0;
	for (int i = 0; i < grau; ++i)
	{
		aux = aux + derivada[i]*pow(n,i);
	}

	return aux;
}

float g(float n){
	float aux=0;
	for (int i = 0; i < grau+1; ++i)
	{
		aux = aux + coeficiente[i]*pow(n,i);
	}

	return aux;
}

void ponto_fixo(){
	srand(time(NULL));
	float xap=baixo + alto*((float)(rand())/RAND_MAX);
	
	float xnovo, resposta;
	do{
		xnovo = g(xap);
		cout << xap<<"\n";
		resposta = xnovo-xap;
		if(resposta<0)
			resposta = -1*resposta;

		xap = xnovo;		
	}while(resposta>0);
	
	auto t1 = std::chrono::high_resolution_clock::now();
	
	cout << "A aproximação desejada é "<<xap<<"\n";
	
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	tempoPrint += tempo.count();
}


void verificacao(){
	vetor derivada(grau,0);
	int n;
	for (int i = grau; i > 0; --i)
	{
		n = i-1;
		derivada[n]= i*coeficiente[i];
		
	}

	for (float i = baixo; i <= alto; ++i)
	{
		if (g_(i,derivada)>=1){
			cout << "Função n válida\n";
			exit(-1);
		}
	}

	ponto_fixo();
	
}


void lerArgs(int argc, const char * argv[]){
	// if(argc > 1){
	// 	xxxxx = string(argv[1]);
	// }if(argc > 2){
	// 	xxxxx = string(argv[2]);
	// }if(argc > 3){
	// 	xxxxx = atoi(argv[3]);
	// }
}

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

int main(int argc, const char * argv[]){
	
	// auto t1 = std::chrono::high_resolution_clock::now();

	lerArgs(argc, argv);
	
	cout << "Qual o grau do polinômio?\n";
	cin >> grau;


	for (int i = grau; i >= 0; --i)
	{
		cout << "Qual o coeficiente de X^"<<i<<"?\n";
		cin >> coeficiente[i];
		if(i==grau && coeficiente[i]<=0){
			cout << "a_n deve ser maior que zero, por favor informe um outro número\n";
			cin >> coeficiente[i];
		}
		if (i ==0 && coeficiente[i]==0)
		{
			cout << "a_0 não pode ser zero, por favor informe um outro número\n";
			cin >> coeficiente[i];
		}
	}

	/*imprime na tela*/
	cout << "Sua função: ";
	for (int i = grau; i >= 0; --i)
	{
		if(i==grau ||coeficiente[i]<0)
			cout << coeficiente[i]<<"X^"<<i<<" ";
		else
			cout << "+ "<<coeficiente[i]<<"X^"<<i<<" ";
	}
	cout << "\n";

	cout << "Limite inferior:\n";
	cin >> baixo;
	cout << "Limite Superior:\n";
	cin >> alto;

	
    auto t1 = std::chrono::high_resolution_clock::now();
    
	verificacao();
	
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);
	
	return 0;
}