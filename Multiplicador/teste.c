#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct int_n{
	int alg;
	struct int_n *prox;
}int_n;

typedef struct int_n2{
	int casa;
	int alg;
	struct int_n2 *prox;
}int_n2;

int_n* fazer_num(int_n *num, int num_c);
int_n2* fazer_resultado(int_n2 *num, int n_resu);
void multiplicar(int_n **n1, int_n **n2, int_n2 **resul, int n_resu, int q1, int q2);
void print_r(int_n2 **resul, int n_resu, FILE **arq);
void vai_um(int_n2 **resul, int n_resu);
void free_num(int_n **n1, int_n **n2, int_n2 **resul);

int main(){

FILE *arq, *arq2;
int_n *Num_1 = NULL;
int_n *Num_2 = NULL;
int_n2 *resultado = NULL;
int n_resu = 0;
int q1,q2;
q1 = q2 = 0;

char c;

arq = fopen("p.txt","r");





c = getc(arq);
do{
	Num_1 = NULL;
	Num_2 = NULL;
	resultado = NULL;
    n_resu = 0;
	q1 = q2 = 0;

while ( c != ' '){

    //exibe o caracter lido na tela
    printf("%c" , c);
    if( c != '\n'){
    Num_1 = fazer_num( Num_1 , c);
    n_resu++;
    q1++;
	}
	//faz a leitura do caracter no arquivo apontado por pont_arq
    c = getc(arq);

    if(feof(arq)) break;
    
}

printf("n1 = %d\n", q1);
system("pause");
c = getc(arq);
while ( c != '\n' ){

    //exibe o caracter lido na tela
    printf("%c" , c);
    if( c != '\n'){
    Num_2 = fazer_num( Num_2 , c);
    n_resu++;
    q2++;
	}
	//faz a leitura do caracter no arquivo apontado por pont_arq
    c = getc(arq);
    if(feof(arq)) break;
    
}
printf("n2 = %d\n", q2);
printf("resultado = %d\n", n_resu);
system("pause");
resultado = fazer_resultado(resultado, n_resu);
multiplicar( &Num_1, &Num_2, &resultado, n_resu, q1, q2);
printf("%d\n", n_resu);
system("pause");

arq2 = fopen("resultado.txt","a");
print_r(&resultado, n_resu, &arq2);
fclose(arq2);

free_num(&Num_1, &Num_2, &resultado);
printf("do\n");
system("pause");

if(feof(arq)) break;

}while(c != -1);


return 0;
}

int_n* fazer_num(int_n *num, int num_c){

	int_n *aux;

	if( num == NULL){
		printf(	"aki \n");
		num = (int_n*) malloc(sizeof(int_n));

		if(num == NULL) return;

		num->alg = num_c - '0';
		num->prox = NULL;

	}else{
		printf(	"aki2 \n");

		aux = (int_n*) malloc(sizeof(int_n));

		if(aux == NULL) return;

		aux->alg = num_c - '0';
		aux->prox = num;
		num = aux;
	}

return num;
}

int_n2* fazer_resultado(int_n2 *num, int n_resu){

	int_n2 *aux;
	int i;
	int casa = 0;

for (i = 0; i < n_resu; ++i)
{

	if( num == NULL){
		printf(	"1 \n");
		num = (int_n2*) malloc(sizeof(int_n2));

		if(num == NULL) return;
		casa++;
		num->casa = casa;
		num->alg = 0;
		num->prox = NULL;

	}else{
		printf(	"2 \n");
		aux = (int_n2*) malloc(sizeof(int_n2));

		if(aux == NULL) return;

		casa++;
		aux->casa = casa;
		aux->alg = 0;
		aux->prox = num;
		num = aux;
	}

}

return num;
}


void multiplicar(int_n **n1, int_n **n2, int_n2 **resul, int n_resu, int q1, int q2){

	int i,j,a1,a2,mult,v_1,csa_de,k,casa_i = 0;
	int_n *aux1, *aux2;
	int_n2 * auxR;
	csa_de = 10;
	k = 0;
	v_1 = 0;
	auxR = (*resul);
	aux1 = (*n1);
	aux2 = (*n2);

	for ( i = 0; i < q1; i++)
	{
		
		aux2 = (*n2);
		auxR = (*resul);

		while(k != casa_i){
			
			auxR = auxR->prox;
			k++;
			
		}
		if(aux1 != NULL){
			
		a1 = aux1->alg;
		aux1 = aux1->prox;
				
	    }else{
	    	break;
	    }

	    for (j = 0; j < q2; j++)
	    {
	    	
	    	if( aux2 != NULL){
	    		
	    	a2 = aux2->alg;
	    	
			aux2 = aux2->prox;
			
			
		    }
		    
		    if(auxR != NULL){
		    ;
		    mult = a1*a2;
		   
		    
		    v_1 = mult / csa_de;

		    mult = mult % csa_de;
		    
		    (auxR)->alg = (auxR)->alg + mult;
		    
		    (auxR) = auxR->prox;
		    
		    (auxR)->alg = (auxR)->alg + v_1;
		 
			vai_um(resul,n_resu);
		    }
	    }
	k = 0;
	casa_i++;

	}
}

void print_r(int_n2 **resul, int n_resu, FILE **arq){
	char result[n_resu+1];
	int j = 0;
	int i = 0;
	if((*resul) == NULL)return;

	int_n2 *auxR;
	auxR = (*resul);
	for (i; i < n_resu+1; i++)
	{
		result[i] = '0';
	}


	do{
		if(j == 0){
			result[n_resu+1] = '\0';
			j = 1;
		}else{
			if(auxR != NULL){
				result[n_resu] = (auxR)->alg + '0';
				n_resu--;
				auxR = (auxR)->prox;
	    	}
		}
	}while(auxR != NULL);
	fprintf(*arq, "%s\n", result);
	printf(" %s\n", result);
}

void vai_um(int_n2 **resul, int n_resu){
	
	int_n2 *aux;
	
	int v_1, fica;

	v_1 = fica = 0;

	aux = (*resul);
	
	do{
		
		v_1 = aux->alg / 10;
		
		fica = (aux)->alg % 10;
		
		(aux)->alg = fica;
		
		aux = (aux)->prox;
		
		if (aux != NULL)
		{
		(aux)->alg = (aux)->alg + v_1;
		}
		
		
	}while( aux != NULL);
}
void free_num(int_n **n1, int_n **n2, int_n2 **resul){
	
	int_n *aux;
	int_n2 *aux2;
	aux = NULL;
	aux2 = NULL;

	do{
		aux = (*n1);
		(*n1) = (*n1)->prox;

		free(aux); 

	}while( *n1 != NULL);

	do{
		aux = (*n2);
		(*n2) = (*n2)->prox;

		free(aux); 

	}while( *n2 != NULL);

	do{
		aux2 = (*resul);
		(*resul) = (*resul)->prox;

		free(aux2); 

	}while( *resul != NULL);

}