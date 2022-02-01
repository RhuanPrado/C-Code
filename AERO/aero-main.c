#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "aero.h"


/* 1°carregar filas de aterrisagem
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
 *  Fila Emergencia	|                     |		             Decolar
 *     ()()() ->    V __________________  
 *			pista3______________________----------------------------->
 *
 *
 *
 *
 */




int main(){

int tempo , tempInsere , tempPista , tempHangar , tempDecola , tempComb, tempVer, tempAte, TempFimDecolagem, decolar; 
int instante = 0, id = 0, flagPista = 0, flag_P3 = 0, flag_decol = 0;
int qtd = 0, i = 0;
tempo = tempInsere = tempPista = tempHangar = tempDecola = tempComb = tempVer = tempAte = TempFimDecolagem = decolar =time(NULL);
tempo += 1440;

TAviao *Prat_1 = NULL, *Prat_2 = NULL, *Prat_Emerg = NULL, *Pista_1 = NULL, *Pista_2 = NULL, *Pista_3 = NULL, *Hangar = NULL, *Fila_Dec = NULL, *aux_Emerg = NULL;


do{
//atualiza o tempo
instante = time(NULL);

//1°carregar filas de aterrisagem
//a cada 60s insere uma quantidade de avioes de 1 a 3
if((tempInsere+60) == instante){	
	
	qtd = (rand()%ENT)+1;
	

	for(i = 0; i < qtd; i++){
		id++;
		if((id%2) != 0){
		   Inserefila( &Prat_1, id);
		}else{
		   Inserefila( &Prat_2, id);
		}
	}
	tempInsere = time(NULL);
}
//atualiza o tempo
instante = time(NULL);

//------------------------ATUALIZAR COMBUSTIVEL------------------------------------
//a cada 3s atualiza combustivel das prateleiras
if((tempComb+5) == instante){
	Atualizar_Comb(&Prat_1);
	Atualizar_Comb(&Prat_2);
	Atualizar_Comb(&Prat_Emerg);
	tempComb = time(NULL);
}


//atualiza o tempo
instante = time(NULL);
//2°ver quais aviões tem prioridade(emergencia) passar pra fila de emergência
//3°verificar quais pistas estão livres
//verifica a cada 1s quais pistas então livres e se algum avião caiu.
if( tempVer+1 == instante){
	VerificaComb_FilaEmergencia(&Prat_1, &Prat_Emerg);
	VerificaComb_FilaEmergencia(&Prat_2, &Prat_Emerg);
	flagPista = verifica_Pistas(Pista_1, Pista_2, Pista_3);
	flag_Av = Verica_Aviao(&Prat_1)+Verica_Aviao(&Prat_2)+Verica_Aviao(&Prat_Emerg);
	tempVerP = time(NULL);
}

//atualiza o tempo
instante = time(NULL);

//5°passar aviões da aterrisagem para o hangar
// passagem dos aviões das pistas para o Hangar
if(tempHangar+10 == instante){
	if((Pista_3 != NULL)&&(flag_P3 == 1)){
		Tranplante_fila(&Pista_3, &Hangar);
		flag_P3 = 0;
	}
	if(Prat_1 != NULL)
		Tranplante_fila(&Pista_1, &Hangar);
	if(Prat_2 != NULL)
		Tranplante_fila(&Pista_2, &Hangar);

	tempHangar = time(NULL);
}

//atualiza o tempo
instante = time(NULL);

//4°aterrisar aviões na pista 1 e 2 caso tiver emergencia de um avião pousar na pista 3 
//  se houver mais que 1 parar filas e colocar aviões com emergencia nas pista 1 ou 2.
//aterrisagem
if(tempAte+1 == instante){
	if((Prat_1 != NULL)||(Prat_2 != NULL)||(Prat_Emerg != NULL)){
		
		if(Pista_3 == NULL){
			if(Prat_Emerg != NULL){
				Plane_Menos_fuel(&Prat_Emerg, &aux_Emerg);
				Tranplante_fila(&aux_Emerg, &Pista_3);
				flag_P3 = 1;
				aux_Emerg = NULL;
			}
		 }else{
			if(Pista_1 == NULL){
				if(Prat_Emerg != NULL){
				Plane_Menos_fuel(&Prat_Emerg, &aux_Emerg);
				Tranplante_fila(&aux_Emerg, &Pista_1);
				aux_Emerg = NULL;
				}	
			}else{
				if(Pista_2 == NULL){ 
					if(Prat_Emerg != NULL){
					Plane_Menos_fuel(&Prat_Emerg, &aux_Emerg);
					Tranplante_fila(&Prat_Emerg, &Pista_2);
					aux_Emerg = NULL;
					}
				}
			}
		}
		if(Pista_1 == NULL){
			Tranplante_fila(&Prat_1, &Pista_1);
		 }
		if(Pista_2 == NULL){
			Tranplante_fila(&Prat_2, &Pista_2);
		 }	
	}
	tempAte = time(NULL);
}

//atualiza o tempo
instante = time(NULL);

//passagem do Hangar para a Fila de Decolagem
if(tempDecola+20 == instante){
	if(Hangar != NULL)
	Tranplante_fila(&Hangar, &Fila_Dec);

	tempDecola = time(NULL);
}

//atualiza o tempo
instante = time(NULL);

//6°verificar se a pista de decolagem está livre
//e coloca na pista de decolagem
if(TempFimDecolagem+1 == instante){
	if((Fila_Dec != NULL)&&(flag_P3 == 0)){
		Tranplante_fila(&Fila_Dec, &Pista_3);
		flag_decol = 1;
	}
	TempFimDecolagem = time(NULL);
}

if(decolar+5 = instante){
	if((Pista_3 != NULL)&&(flag_decol == 1)){
		Decolar(&Fila_Dec);
		flag_decol = 0;
	}
	decolar = time(NULL);
}

//atualiza o tempo
instante = time(NULL);


}while(tempo != instante);

printf("\nterminouuuuu!!!!!!!!\n");

return 0;
}

