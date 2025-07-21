#ifndef PERCEPTRON_H

typedef struct _perceptron {
	double *weights;
	double bias;
	double z_result;
	double activation_result;
	double activation;
	double (*activation_function)(double);
	int input_count;
} perceptron;


perceptron *new_perceptron(int input_count, int *weights, int bias, double (*activation_function)(double)) ;
void perceptron_free(perceptron *p) ;
double perceptron_execute(perceptron *p, double *inputs) ;
double activator_step(double x) ;

#endif

