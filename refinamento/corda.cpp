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
vetor coeficiente(grau+1, 0);

float f(float n){
	float aux=0;
	for (int i = 0; i < grau+1; ++i)
	{
		aux = aux + coeficiente[i]*pow(n,i);
	}

	return aux;
}

void corda(){
	float cn, resposta;
	float alto_baixo;
	float falto_fbaixo;
	do{
		alto_baixo = alto - baixo;
		falto_fbaixo = f(alto) - f(baixo);
		cn = baixo - ((alto_baixo/falto_fbaixo)*f(baixo));
		if (f(cn)*f(baixo)>0)
		{
			baixo = cn;
		}else{
			if(f(cn)== 0.00)
				cout << "A raiz é "<<cn<<"\n";
			else
				alto = cn;
		}
		resposta = f(cn);
		if(resposta<0)
			resposta = -1*resposta;
	}while(resposta>0.001);
	cout << "A aproximação desejada é "<<cn<<"\n";
}

// void lerArgs(int argc, const char * argv[]){
// 	// if(argc > 1){
// 	// 	xxxxx = string(argv[1]);
// 	// }if(argc > 2){
// 	// 	xxxxx = string(argv[2]);
// 	// }if(argc > 3){
// 	// 	xxxxx = atoi(argv[3]);
// 	// }
// }



int main(int argc, const char * argv[]){
	
	// auto t1 = std::chrono::high_resolution_clock::now();

	// lerArgs(argc, argv);

	
	// auto t2 = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> tempo = t2 - t1;
	// double tempoTotal = tempo.count();
	
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

	corda();
	
	
	
	return 0;

}