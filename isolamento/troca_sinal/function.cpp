#include "function.h"


Function::Function(string name, vector<double> coeficientes){
	this->name = name;
	this->coeficientes = coeficientes;
}

Function::Function(vector<double> coeficientes){
	this->coeficientes = coeficientes;
}

Function::~Function(){
	// coeficientes.clear();
}

double Function::solve(double x){
	//start the power of the function
	int power = this->coeficientes.size()-1;
	
	//creates the result variable
	double result = 0;
	
	//runs throught the coefficients
	for(int i = 0; i < this->coeficientes.size(); i++){
		double coeff = coeficientes[i];
		
		//put the multiplication inside the result
		result += coeff * pow(x, power);
		
		power--;
	}
	
	return result;
}

void Function::show(){
	int pot = this->coeficientes.size()-1;
	bool anterior = false;
	for(int i = 0; i < this->coeficientes.size(); i++){
		double x = coeficientes[i];
		
		if(i > 0){
			if(x != 0){
				if(anterior){
	
					if(x > 0){
						cout << " + ";	
					}else if(x < 0){
						cout << " - ";	
					}
					if(x != 1 && x != -1){
						cout << abs(x);
					}
					
				}else{
					cout << x;	
				}
			}
		}else{
			if(x > 1 || x < -1){
				cout << x;	
			}else if(x == -1){
				cout << "-";
			}
		}
		if(x != 0){
			if(pot > 0){
				cout << "x";
				anterior = true;
			}
			
			if(pot > 1){
				cout << "^" << pot;
			}
		}
		pot--;
	}
	cout << " = " << 0 << endl;
}