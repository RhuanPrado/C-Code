
#ifndef MULT_C
	DEFINE MULT_C 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct int_n{
	int alg;
	int *prox;
}int_n;

int *ler_arq (char local){
	FILE *arq;
	
	fopen("parametros.txt","r");
while
}

void fazer_num(int_n **num, int num_c){
	int_n *aux;
	assert(num);

	if((num*) == NULL){

		num* = (int_n*) malloc(sizeof(int_n));
		
		if((*num) == NULL) return;

		(num*)->alg = num_c - '0';
		(num*)->prox = NULL;

	}else{
		aux = (int_n*) malloc(sizeof(int_n));
		aux->alg = num_c - '0';
		aux->prox = (*num);
		(num*) = aux;
	}

}
 
#endif