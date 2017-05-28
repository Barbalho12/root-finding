#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include "../model/function.cpp"

using namespace std;
typedef std::vector<float> vetor;

int grau;
int k=-1;
float b=0;
double tempoPrint;
vetor coeficiente(grau+1, 0);


void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

float lx(){
	for (int i = 0; i < grau; ++i)
	{
		if(coeficiente[i]<0){
			k = i;
			if (b>coeficiente[i])
				b = coeficiente[i];
		}
	}
	b = b*(-1);
	float a =grau - k;
	float exp = 1/a;
	float n = b/coeficiente[grau];
	float resultado = 1 +  pow(n,exp);
	return resultado;
}

float l1x(){
	vetor coeficiente_(grau+1, 0);
	for (int i = grau; i >= 0; --i)
	{
		coeficiente_[i] = coeficiente[grau-i];
	}
	if (coeficiente_[grau]<0)
	{
		for (int i = 0; i < grau+1; ++i)
		{
			coeficiente_[i] = -1*coeficiente_[i];
		}
	}
	for (int i = 0; i < grau; ++i)
	{
		if(coeficiente_[i]<0){
			k = i;
			if (b>coeficiente_[i])
				b = coeficiente_[i];
		}
	}
	b = b*(-1);
	float a =grau - k;
	float exp = 1/a;
	float n = b/coeficiente_[grau];
	float resultado = 1 +  pow(n,exp);
	return 1/resultado;
}

float l_x(){
	vetor coeficiente_(grau+1, 0);
	for (int i = grau; i >= 0; --i)
	{
		if(i%2 == 0)
			coeficiente_[i] = coeficiente[i];
		else
			coeficiente_[i] = -1*coeficiente[i];
	}
	if (coeficiente_[grau]<0)
	{
		for (int i = 0; i < grau+1; ++i)
		{
			coeficiente_[i] = -1*coeficiente_[i];
		}
	}

	for (int i = 0; i < grau; ++i)
	{
		if(coeficiente_[i]<0){
			k = i;
			if (b>coeficiente_[i])
				b = coeficiente_[i];
		}
	}
	b = b*(-1);
	float a =grau - k;
	float exp = 1/a;
	float n = b/coeficiente_[grau];
	float resultado = 1 +  pow(n,exp);
	return -1*resultado;
}

float l_1x(){
	vetor coeficiente_(grau+1, 0);
	for (int i = grau; i >= 0; --i)
	{
		if(i%2 == 0)
			coeficiente_[i] = coeficiente[grau-i];
		else
			coeficiente_[i] = -1*coeficiente[grau-i];
	}
	if (coeficiente_[grau]<0)
	{
		for (int i = 0; i < grau+1; ++i)
		{
			coeficiente_[i] = -1*coeficiente_[i];
		}
	}

	for (int i = 0; i < grau; ++i)
	{
		if(coeficiente_[i]<0){
			k = i;
			if (b>coeficiente_[i])
				b = coeficiente_[i];
		}
	}
	b = b*(-1);
	float a =grau - k;
	float exp = 1/a;
	float n = b/coeficiente_[grau];
	float resultado = 1 +  pow(n,exp);
	return 1/(resultado*(-1));
}

void lagrange(){
	float p_superior = lx();
	float p_inferior = l1x();
	float n_inferior = l_x();
	float n_superior = l_1x();

	auto t1 = std::chrono::high_resolution_clock::now();
	cout << "Intervalo das raízes positivas: [" << p_inferior << ";" << p_superior << "]\nIntervalo das raízes Negativas: [" << n_inferior << ";" << n_superior << "]\n";
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	tempoPrint += tempo.count();
}


void lagrange(Function f, bool positivo, float &baixo, float &alto){
	
	coeficiente = f.getCoeficientes();
	
	if(positivo){
		baixo = l1x();
		alto = lx();
	}else{
		baixo = l_x();
		alto = l_1x();
	}
	
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
	
	
	auto t1 = std::chrono::high_resolution_clock::now();

	lagrange();
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	showTime(tempoTotal);
	
	return 0;
}