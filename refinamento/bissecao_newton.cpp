#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>

using namespace std;
typedef std::vector<float> vetor;

double tempoPrint;

int grau;
float alto, baixo;
vetor coeficiente(grau+1, 0);

float f_(float n, vetor &derivada){
	float aux=0;
	for (int i = 0; i < grau; ++i)
	{
		aux = aux + derivada[i]*pow(n,i);
	}

	return aux;
}

float f(float n){
	float aux=0;
	for (int i = 0; i < grau+1; ++i)
	{
		aux = aux + coeficiente[i]*pow(n,i);
	}

	return aux;
}

void verificacao(vetor &derivada){
	int n;
	for (int i = grau; i > 0; --i)
	{
		n = i-1;
		derivada[n]= i*coeficiente[i];
		
	}
	
}

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

void newton(){
	srand(time(NULL));
	float xap=baixo + alto*((float)(rand())/RAND_MAX);
	vetor derivada(grau, 0);
	verificacao(derivada);
	float xnovo, resposta;
	do{
		xnovo = xap - (f(xap)/f_(xap, derivada));
		cout << xap<<"\n";
		resposta = xnovo-xap;
		if(resposta<0)
			resposta = -1*resposta;

		xap = xnovo;		
	}while(resposta>0);
	
	//Verifica tempo de impressão
	auto t1 = std::chrono::high_resolution_clock::now();
	
	cout << "A aproximação desejada é "<<xap<<"\n";
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	tempoPrint += tempo.count();
}

void bissecao(){
	float m, resposta;
	float alto_baixo;
	do{
		alto_baixo = alto + baixo;
		m = (alto_baixo/2);
		if (f(m)*f(baixo)>0)
		{
			baixo = m;
		}else{
			if(f(m)== 0){
			
                auto t1 = std::chrono::high_resolution_clock::now();
				
				cout << "A raiz é "<<m<<"\n";
				
                auto t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> tempo = t2 - t1;
                tempoPrint += tempo.count();
		    
		    }
			else{
				alto = m;
			    
			}
		}
		resposta = alto - baixo;
	}while(fabs(resposta) >2);
	newton();
}

int main(){
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
	
	bissecao();
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);
	
	return 0;
}