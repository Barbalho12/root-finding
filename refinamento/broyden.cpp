#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include <vector>
#include "../model/function.cpp"

using namespace std;

// declarações de tipos
typedef std::vector<std::vector<float>> matriz;
typedef std::vector<float> vetor;

// declarações globais
int m = 2;
int n = 2;
double tempoPrint;

//x_1² + x_2² - 1
float f1( float x1, float x2){
	return x1*x1 + x2*x2 - 1;
}

//x_1 + x_2 - 1
float f2( float x1, float x2){
	return x1 + x2 - 1;
}

// gera o vetor da F aplicado à um vetor resposta X
vetor f(vetor X){
	// cria um vetor resposta
	vetor Z(m, 0);
	
	// calcula a diferença de cada posicao
	Z[0] = f1(X[0], X[1]);
	Z[1] = f2(X[0], X[1]);
	
	return Z;
}

// calcula || delta_f ||
float norma( vetor delta_f){
	float distancia;
	
	//calcula o produto das posiçoes e soma
	for(int i = 0; i < n; i++){
		distancia += delta_f[i] * delta_f[i];
	}
	//tira a raiz quadrada
	distancia = sqrt(distancia);
	
	return fabs(distancia);
}

// calcula a soma entre duas matrizes de mesma dimensão
matriz soma( matriz X, matriz Y) {
	
	// cria uma matriz resultado
	matriz Z(m, vetor(n, 0));
	
	// calcula a soma
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i][j] = X[i][j] + Y[i][j];
		}
	}
	return Z;
}

// calcula a diferença entre dois vetores de mesma dimensão
vetor diferenca( vetor X, vetor Y) {
	
	// cria um vetor resposta
	vetor Z(m, 0);
	
	// calcula a diferença de cada posicao
	for(int i = 0; i < m; i++){
		Z[i] = X[i] - Y[i];
	}
	return Z;
}

// calcula a diferença entra duas matrizes de mesma dimensão
matriz diferenca( matriz X, matriz Y) {
	
	//cria uma matriz resposta
	matriz Z(m, vetor(n, 0));
	
	//calcula a diferença
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i][j] = X[i][j] - Y[i][j];
		}
	}
	
	return Z;
}

// calcula a divisão entre uma matriz e um número
matriz divisao( matriz X, float y){
	
	// cria uma matriz resposta
	matriz Z(m, vetor(n, 0));
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
				Z[i][j] += X[i][j]/y;
		}
	}
	return Z;
}

// calcula a divisão entre um vetor e um número
vetor divisao( vetor X, float y){
	
	// cria um vetor resposta
	vetor Z(m, 0);
	
	// calcula a diferença de cada posicao
	for(int i = 0; i < m; i++){
		Z[i] = X[i]/y;
	}
	return Z;
}

// calcula a multiplicação entre matriz e vetor 
vetor produto( matriz X, vetor Y) {
	//no problema, a matrix é 2x2 e o vetor é 2x1
	//cria um vetor resposta 2x1
	vetor Z(m, 0);
	
	//calcula a multiplicação
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i] += X[i][j] * Y[j];
		}
	}
	return Z;
}

// calcula a multiplicação de matrizes
matriz produto( matriz X, matriz Y){
	
	// cria uma matriz resposta
	matriz Z(m, vetor(n, 0));
	
	// calcula a multiplicação
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				Z[i][j] += X[i][k] * Y[k][j];
			}
		}
	}
	return Z;
}

// calcula a multiplicação entre um vetor transposto e outro normal
float produto_transposto_esquerdo( vetor X, vetor Y){
	
	//cria um float resposta
	float produto;
	
	for(int i = 0; i < m; i++){
		produto += X[i] * Y[i];
	}
	
	return produto;
}

// calcula a multiplicação entre vetor normal e um vetor transposto
matriz produto_transposto_direito( vetor X, vetor Y) {
	
	// cria uma matriz resposta
	matriz Z(m, vetor(n, 0));
	
	// Calcula a multiplicação
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i][j] = X[i] * Y[j];
		}
	}
	
	return Z;
}

// Gera a identidade 
void identidade( matriz &X) {
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(i==j){
				X[i][j] = 1;
			}else{
				X[i][j] = 0;
			}
		}
	}
}
	

//calcula Broyden
vetor broyden( vetor x_ap, float erro){
	
	//dados importantes
	matriz b_ap(m, vetor(n, 0));
	matriz b_ap_inv(m, vetor(n, 0));
	vetor x_novo, delta_f, delta_x, u;
	
	// coloca a identidade
	identidade(b_ap);
	identidade(b_ap_inv);
	
	//auxiliares
	vetor u_numerador;
	float u_denominador;
	matriz b_ap_inv_numerador;
	float b_ap_inv_denominador;
	
	do{
		// vetor - (matriz x vetor)
		x_novo = diferenca( x_ap, produto( b_ap_inv, f(x_ap) ));
		
		// vetor - vetor
		delta_f = diferenca( f( x_novo), f( x_ap));
		
		// vetor - vetor
		delta_x = diferenca( x_novo, x_ap);
		
		// vetor - (matriz x vetor)
		u_numerador = diferenca( delta_f, produto( b_ap, delta_x));
		//cout << "u_numerador: (" << u_numerador[0] << ", " << u_numerador[1] << ")^t" << endl;
		
		// vetor x transposto
		u_denominador = produto_transposto_esquerdo( delta_x, delta_x);
		//cout << "u_denominador: " << u_denominador << endl;
		
		// numerador / denominador
		u = divisao(u_numerador, u_denominador);

		// matriz + (vetor x transposto)
		b_ap = soma(b_ap, produto_transposto_direito( u, delta_x));
		
		// ( (matriz x vetor) x transposto) x matriz
		b_ap_inv_numerador = produto( produto_transposto_direito( produto( b_ap_inv, u), delta_x), b_ap_inv); 
		
		// transposto x ( matriz x vetor)
		b_ap_inv_denominador = 1 + produto_transposto_esquerdo( delta_x, produto( b_ap_inv, u));
		
		// inversa - ( numerador / denominador)
		b_ap_inv = diferenca(b_ap_inv, divisao( b_ap_inv_numerador, b_ap_inv_denominador));
		
		x_ap = x_novo;
		
		//calcula o tempo dos prits
		auto t1 = std::chrono::high_resolution_clock::now();
		
		cout << "\nx_novo: (" << x_novo[0] << ", " << x_novo[1] << ")^t" << endl;
		cout << "delta_f: (" << delta_f[0] << ", " << delta_f[1] << ")^t" << endl;
		cout << "delta_x: (" << delta_x[0] << ", " << delta_x[1] << ")^t" << endl;
		cout << "u: (" << u[0] << ", " << u[1] << ")^t" << endl;
		cout << "b_ap: |" << b_ap[0][0] << ", " << b_ap[0][1] << "|" << endl;
		cout << "      |" << b_ap[1][0] << ", " << b_ap[1][1] << "|" << endl;
		cout << "b_ap_inv: |" << b_ap_inv[0][0] << ", " << b_ap_inv[0][1] << "|" << endl;
		cout << "          |" << b_ap_inv[1][0] << ", " << b_ap_inv[1][1] << "|" << endl;
		
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tempo = t2 - t1;
		tempoPrint += tempo.count();
		
	} while( norma(delta_f) > erro);
	return x_novo;
}

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}

int main(int argc, const char * argv[]){
	
	vetor x_ap(2);
	x_ap[0] =0;
	x_ap[1] =0;
	
	float erro = 0.001;
	
	cout << "x_ap inicial: (" << x_ap[0] << ", " << x_ap[1] << ")^t" << endl;
	cout << "erro: " << erro << endl;
	
	auto t1 = std::chrono::high_resolution_clock::now();
	
	vetor resposta = broyden(x_ap, erro);
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	
	cout << "\n O vetor resposta é: ("<< resposta[0] << ", " << resposta[1] << ")^t" << endl;
	
	showTime(tempoTotal);
	
	return 0;
}