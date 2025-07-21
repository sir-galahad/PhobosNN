#include <stdio.h>
#include "perceptron.h"

double and_inputs[4][2]={{0,0}, {0,1}, {1,0}, {1,1}};
double and_expected[]={0,0,0,1};

double or_inputs[4][2]={{0,0}, {0,1}, {1,0}, {1,1}};
double or_expected[]={0,1,1,1};

double learning_rate=0.001;

int main(int argc, char ** argv) {
	perceptron *and_p = new_perceptron(
		2,
		NULL,
		0,
		activator_step
	);

	while(1) {
		int wins = 0;
		for(int i = 0; i < 4; i++) {
			printf("weights %f %f, bias %f\n",
				and_p->weights[0], 
				and_p->weights[1], 
				and_p->bias
			);
			double result = perceptron_execute(and_p,and_inputs[i]);
			if(result == and_expected[i]) {
				++wins;
			} else {
				perceptron_learn_step(and_p, learning_rate, and_expected[i]);
			}	
		}
		if( wins == 4) {
			break;
		}
	}

	perceptron *or_p = new_perceptron(
		2,
		NULL,
		0,
		activator_step
	);

	while(1) {
		int wins = 0;
		for(int i = 0; i < 4; i++) {
			printf("weights %f %f, bias %f\n",
				or_p->weights[0], 
				or_p->weights[1], 
				or_p->bias
			);
			double result = perceptron_execute(or_p,or_inputs[i]);
			if(result == or_expected[i]) {
				++wins;
				printf("win");
			} else {
				perceptron_learn_step(or_p, learning_rate, or_expected[i]);
			}	
		}
		if( wins == 4) {
			break;
		}
	}


	printf("\nand: weights %f %f, bias %f\n\n",
		and_p->weights[0], 
		and_p->weights[1], 
		and_p->bias
		);

	printf("or: weights %f %f, bias %f\n\n",
		or_p->weights[0], 
		or_p->weights[1], 
		or_p->bias
	);


	return 0;
}
