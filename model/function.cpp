#include "function.h"


Function::Function(){
	this->name = "f";
}

Function::Function(vector<float> coeficientes){
	this->name = "f";
	this->coeficientes = coeficientes;
}

Function::Function(string name, vector<float> coeficientes){
	this->name = name;
	this->coeficientes = coeficientes;
}


Function::~Function(){
	// this->coeficientes.clear();
}

float Function::solve(float x){
	
	//creates the result variable
	float result = 0;
	
	//runs throught the coefficients
	for(int i = 0; i < this->coeficientes.size(); i++){
		float coeff = float (this->coeficientes[i]);
		
		//put the multiplication inside the result
		result += coeff * pow(x, i);

	}
	
	return result;
}

void Function::show(){
	int grau = this->coeficientes.size()-1;

	cout << this->name << "(x) = ";
	for (int i = grau; i >= 0; --i){

		stringstream coeficiente;

		if(this->coeficientes[i] == 1 && i > 0){
			coeficiente << "";
		}else{
			coeficiente << fabs(this->coeficientes[i]);
		}

		if(this->coeficientes[i] == 0){
			continue;
		}


		if(i == grau || this->coeficientes[i] < 0){
			if(i == 0){
				cout << "- " << coeficiente.str() << " ";
			}else if(i == 1){
				cout << "- " << coeficiente.str() << "x" << " ";
			}else{
				cout << "- "<< coeficiente.str() << "x^" << i <<"  ";
			}
			
		}else{
			if(i == 0){
				cout << "+ " << coeficiente.str() << " ";
			}else if(i == 1){
				cout << "+ " << coeficiente.str() << "x" << " ";
			}else{
				cout << "+ " << coeficiente.str() << "x^" << i << " ";
			}
		}
	}
	cout << endl;
}

vector<float> Function::getCoeficientes(){
	return this->coeficientes;
}

void Function::readFromUser(){
	int grau;

	cout << "Qual o grau do polinômio?" << endl;
	cin >> grau;
	
	this->coeficientes = vector<float>(grau+1, 0);

	for (int i = grau; i >= 0; --i){
		
		cout << "Qual o coeficiente de x^" << i << "?" << endl;
		cin >> this->coeficientes[i];

		if(i == grau && this->coeficientes[i] <= 0){

			cout << "a_n deve ser maior que zero, por favor informe um outro número\n";
			cin >> this->coeficientes[i]; 
		}
		if (i == 0 && this->coeficientes[i] == 0){

			cout << "a_0 não pode ser zero, por favor informe um outro número\n";
			cin >> this->coeficientes[i];
		}
	}

	show();
}

int Function::getGrau(){
	return this->coeficientes.size()-1;
}