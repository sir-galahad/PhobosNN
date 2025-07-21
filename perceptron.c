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

	tmp->inputs=malloc(sizeof(double)*input_count);
	if(tmp->weights == NULL) {
		//todo set errno
		free(tmp->weights);
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
	double sum = 0;	
	for( int i = 0; i < p->input_count; ++i)  {
		p->inputs[i] = inputs[i];
		sum += p->weights[i]*inputs[i];
	}
	sum += p->bias;
	p->z_result = sum;
	
	p->activation_result = p->activation_function(sum);
	return p->activation_result;
}


void perceptron_learn_step(perceptron *p, double learn_rate, double expected) {
	for(int i = 0; i < p->input_count; ++i) {
		p->weights[i] = p->weights[i] + learn_rate * (expected - p->activation_result)* p->inputs[i];
	}
	p->bias = p->bias + learn_rate * (expected - p->activation_result);
}

double activator_step(double x) {
	return x >= 0 ? 1 : 0;
}

	
