
typedef struct aviao{
	int id_air;
	int temp;
	int fuel;
	short int pri = 0;
	struct aviao *prox = NULL;
	struct aviao *ant = NULL;
}TAviao;

void Inserefila(TAviao **ult, int id);
void Tranplante_fila(TAviao **Prat,TAviao **Pista);
void VerificaComb_FilaEmergencia(TAviao **Prat,TAviao **Fila_Emerg);
int verifica_Pistas(TAviao *P1, TAviao *P2, TAviao *P3);
void Atualizar_Comb(TAviao **Fila);
int Verica_Aviao(TAviao **Fila);
void Plane_Menos_fuel(TAviao **Fila_Emerg, TAviao **aux_Emerg);
void Decolar(TAviao **Fila_Dec);