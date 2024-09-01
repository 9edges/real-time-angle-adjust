#include "stm32f10x.h"                  // Device header
#include "math.h"

double Sqrt(double x){
	double k=x;
	double delta = 1e-6;
	
	while(k*k-x>delta | x-k*k>delta){
		k=(k+x/k)/2;
	}
	return k;
} 
	