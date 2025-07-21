#include "perceptron.h"
#include <stdlib.h>

perceptron *new_perceptron(int input_count, int *weights, int bias, double (*activation_function)(double)) {
	perceptron *tmp = malloc(sizeof(perceptron));
	if ( tmp == NULL ) {
		//todo set errorno
		return NULL;
	}
	
	tmp->input_count=input_count;
	tmp->weights=malloc(sizeof(double)*input_count);
	if(tmp->weights == NULL) {
		//todo set errno
		free(tmp);
		return NULL;
	}
	
	for(int i = 0; i < tmp->input_count; ++i) {
		double w = 0;
		if (weights != NULL) {
			w = weights[i];
		}
		tmp->weights[i]=w;
	}

	tmp->bias = 0;
	
	tmp->activation_function = activation_function;
	
	return tmp;
}

void perceptron_free(perceptron *p) {
	free(p->weights);
	free(p);
}

double perceptron_execute(perceptron *p, double *inputs) {
	if(p == NULL || inputs == NULL) {
		//todo set errno
		return 0;
	}

	double sum = 0;	
	for( int i = 0; i < p->input_count; ++i)  {
		sum += p->weights[i]*inputs[i];
	}
	sum += p->bias;
	p->z_result = sum;
	
	p->activation_result = p->activation_function(sum);
	return p->activation_result;
}

double activator_step(double x) {
	return x >= 0 ? 1 : 0;
}
	
