#ifndef AERO
	#define AERO
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "aero.h"
#define ENT 3
#define COMB 20

/* 1°carregar filas de aterrisagem
 *------------------------ATUALIZAR COMBUSTIVEL------------------------------------
 * 2°ver quais aviões tem prioridade(emergencia) passar pra fila de emergência
 * 3°verificar quais pistas estão livres
 * 4°aterrisar aviões na pista 1 e 2 caso tiver emergencia de um avião pousar na pista 3 se houver mais que 1 parar filas e colocar aviões com emergencia nas pista 1 ou 2.
 * 5°passar aviões da aterrisagem para o hangar 
 * 6°verificar se a pista de decolagem está livre
 * 7°decolar aviao.
 *
 *
 *		Fila-1          Aterrisagem
 *      ()()() ->   ______|_____________________indo para o Hangar __ 20s
 *			pista1______________________-------------------------->	 |	
 *										  ^						  |()|
 *		Fila-2			Arerrisagem		  |						  |()|
 *      ()()() ->	______|_______________|						  |()|
 *			pista2______________________--|						  |()|
 *										  |						  |()|
 *	Fila de decolagem	DECOLAR	<-------  |  <----saida do hangar |()|
 *	    ()()() ->->                       |                       |()|
 *			        ______________________________________________|__|
 *				    |					  |
 *                  |                     |
 *Fila Emergencia	|                     |
 *     ()()() ->    V _______________ ___  |					Decolar
 *			pista3______________________----------------------------->
 *
 *
 *
 *
 */


//essa função inicia a inserção nas prateleiras
void Inserefila(TAviao **ult, int id){
	//verefica algo anomolo(estranho) kkk...
	assert(ult);
	
	//verifica se a prateleira há algium avião
	if(*ult == NULL){

		TAviao *aux = (TAviao*) malloc(sizeof(TAviao));
		//condição para ver se foi alocado com sucesso.
		if(aux == NULL)return;

		aux -> id_air = id;
		aux -> temp = time(NULL);
		//aqui o avião recebe seu combustivel aleatóriamente de 1 a 20
		aux -> fuel = (rand()%COMB)+1;
		//aqui verifica se o avião está em uma faixa de emergencia que é de 1 à 5
		if((aux -> fuel)<6) aux->pri = 1;
		
		aux->prox = aux;
		aux->ant = aux;

	}else{

		TAviao *aux = (TAviao*) malloc(sizeof(TAviao)), *prim = NULL;
		
		if(aux == NULL)return;
		
		aux -> prox = *ult;
		aux -> ant = (*ult)->ant;
		prim = (*ult) -> ant;
		prim->prox = aux;
		(*ult) -> ant = aux;
		
		aux -> id_air = id;
		aux -> temp = time(NULL);
		aux -> fuel = (rand()%COMB)+1;

		if((aux -> fuel)<6) aux -> pri = 1;
		
		*ult = aux;
	}
}
// Aqui ele passa o 1° da fila pra outra
void Tranplante_fila(TAviao **Prat,TAviao **Pista){

	assert(Prat);
	assert(Pista);

	if(*Prat == NULL)
		return;

	TAviao *aux = (*Prat)->ant, *prim = NULL;

	(*Prat)->ant =  aux->ant;
	prim = aux->ant;
	prim->prox = (*Prat);

	if(*Pista == NULL){
	    
		aux->prox = aux;
		aux->ant = aux;
		*Pista = aux;
  	   	
	}else{
	
		aux->prox = (*Pista);
		aux->ant  = (*Pista)->ant;
		(*Pista)->ant = aux;
		aux2 = (*Pista)->ant;
		aux2->prox = aux;
		 *Pista = aux;
		
	}
}
//verifica e transfere todos o aviões de uma prateleira que tiverem na faixa de emergencia
void VerificaComb_FilaEmergencia(TAviao **Prat,TAviao **Fila_Emerg){
	
	
	assert(Prat);
	assert(Fila_Emerg);
	
	TAviao *aux = (*Prat), *auxAnt = NULL, *auxProx = NULL, *AvEmerg = NULL;
	
	if(*Prat == NULL) return;
	
	do{
		if(aux->pri != 0){

			auxAnt = aux->ant;
			auxProx = aux->prox;
			auxAnt->prox = auxProx;
			auxProx->ant = auxAnt;
			AvEmerg = aux;

			if(*Fila_Emerg == NULL){
	    
	    		AvEmerg->prox = AvEmerg;	
				AvEmerg->ant = AvEmerg;
				*Fila_Emerg = AvEmerg;
  	   	
			}else{
	
				AvEmerg->prox = (*Fila_Emerg);
				AvEmerg->ant  = (*Fila_Emerg)->ant;
				(*Fila_Emerg)->ant = AvEmerg;
				auxAnt = (*Fila_Emerg)->ant;
				auxAnt->prox = AvEmerg;
				 *Fila_Emerg = AvEmerg;
			}

			auxAnt = NULL;
			auxProx = NULL;
			AvEmerg = NULL;

			aux = aux->prox;
		}else{
			aux = aux->prox;
		}
	}while(aux->prox != (*Prat));
}

int verifica_Pistas(TAviao *P1, TAviao *P2, TAviao *P3){

	int indicador = 0;
	
	if(P1 == NULL) indicador += 1;
	if(P2 == NULL) indicador += 2;
	if(P3 == NULL) indicador += 4;

	return indicador;
}

void Atualizar_Comb(TAviao **Fila){
	
	assert(Fila);

	TAviao *aux = (*Fila);

	do{
		aux->fuel-= 1;
		aux = aux->prox;
	}while(aux->prox != (*Fila));
}
//verefica se algum aviao caiu
int Verica_Aviao(TAviao **Fila){
	
	assert(Fila);

	TAviao *aux = (*Fila), *auxAnt = NULL, *auxProx = NULL, *Plane = NULL;
	int av = 0;
	do{
		if(aux->fuel < 0){
			
			av++;

			auxAnt = aux->ant;
			auxProx = aux->prox;
			auxAnt->prox = auxProx;
			auxProx->ant = auxAnt;
			Plane = aux;

			free(Plane);
		}
		aux = aux->prox;
	}while(aux-prox != (*Fila));

	return av;
}
//passa o avião com menos combustivel para aux
void Plane_Menos_fuel(TAviao **Fila_Emerg, TAviao **aux_Emerg){

	assert(Fila_Emerg);
	assert(aux_Emerg);

	if(*Fila_Emerg == NULL) return;

	TAviao *aux = (*Fila_Emerg), aux2 = NULL;
	int menor = aux->fuel;
	aux2 = aux;
	aux = aux->prox;
	do{
		
		if((aux->fuel) < menor){
			menor = aux->fuel;
			aux2 = aux;
		}

		aux = aux->prox
	}while(aux->prox != (*Fila_Emerg));

	aux = aux2->ant;
	aux->prox = aux2->prox;
	aux = aux2->prox;
	aux->ant = aux2->ant;

	aux2->prox = aux2;
	aux2->ant = aux2;

	(*aux_Emerg) = aux2;
}
//faz decolagem
void Decolar(TAviao **Fila_Dec){

	assert(Fila_Dec);

	TAviao *prim = (*Fila_Dec)->ant;
	TAviao *aux = prim ->ant;

	aux->prox = (*Fila_Dec)->prox;
	(*Fila_Dec)->ant = aux;

	free(prim);
}

#endif



