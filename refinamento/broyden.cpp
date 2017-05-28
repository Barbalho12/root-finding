#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <math.h>
#include "../model/function.cpp"

using namespace std;



void lerArgs(int argc, const char * argv[]){
	// if(argc > 1){
	// 	xxxxx = string(argv[1]);
	// }if(argc > 2){
	// 	xxxxx = string(argv[2]);
	// }if(argc > 3){
	// 	xxxxx = atoi(argv[3]);
	// }
}



int main(int argc, const char * argv[]){
	
	// auto t1 = std::chrono::high_resolution_clock::now();

	lerArgs(argc, argv);

	
	// auto t2 = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> tempo = t2 - t1;
	// double tempoTotal = tempo.count();
	
	return 0;
}