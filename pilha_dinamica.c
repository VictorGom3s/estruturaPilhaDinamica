#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* -----------------------------------------------------------------------------
Pilha dinamica

Author: Victor Gomes Sampaio

Github: @VictorGom3s
------------------------------------------------------------------------------*/

typedef struct pilha{
        int topo;
        int dado;
        struct pilha *prox; ;
} Tno_ls;



int inicializa (Tno_ls **p);
int empilha  (Tno_ls **p, int info);
int desempilha  (Tno_ls **p);
int estado(Tno_ls *p);
int listar(Tno_ls *p);
int obter_topo(Tno_ls *p, int *dado);
int transfere(Tno_ls *p, Tno_ls **p2);

/* ----------------------------------------------------------------------------- */

int main(void)
{

	int info;
	int erro; /* valor de erro retornado pelas funcoes */
	Tno_ls *s, *s2;
	inicializa(&s);
    inicializa(&s2);
	int q;  /* receber a opcao do usuario */
	do {
	    printf("1 -> Inicializa \n");
		printf("2 -> Insere\n");
		printf("3 -> Remove\n");
		printf("4 -> Verifica Estado de Vazio\n");
		printf("5 -> Lista \n");
		printf("6 -> Obter Topo \n");
		printf("7 -> Transferir para outra pilha \n");
		printf("8 -> Listar pilha 2! \n:");
		printf("9 -> Sair \n:");
		scanf("%d", &q);     /* Ler a opcao do usuario */
		switch(q) {
			case 1: erro=inicializa (&s);
                    printf("\nInicializacao realizada com sucesso !\n");
                    printf("\nPilha VAZIA \n");           
					break;
			case 2: printf("Dado para insercao: ");
                    scanf("%d",&info);
                    erro=empilha(&s,info);
                    if (erro==1)
                       printf("\nPilha cheia. Overflow\n");
			        break;
            case 3: erro=desempilha(&s);
                    if (erro==1)
                       printf("\nPilha Vazia. Underflow\n");
                    if(erro == 0) printf("\nRemocao realizada com sucesso!\n");
                    break;
			case 4: erro=estado(s);
                    if (erro == 0)
			           printf("\nA pilha esta vazia.\n");
                    if (erro == 2)
			           printf("\nA pilha esta em condicoes de uso\n");
                    if(erro == 1){
                        printf("\nPilha com apenas 1 item.\n");
                    }
					break;
            case 5: erro= listar(s);
			        if (erro == 1)
			           printf("\nA pilha esta vazia.\n");
					break;
			case 6: erro=obter_topo(s, &info);
		        	if (erro == 0)
                    {
                       printf("Dado no topo: %d\n", info);
                    }else
                       printf("Pilha vazia. Sem topo\n");
					break;
			case 7: erro= transfere(s, &s2);
		        	if (erro == 0)
                    {
                       printf("Transferencia realizada\n");
                       listar(s2);
                    }
                    else
                       printf("erro na transferencia");
					break;
            case 8: erro= listar(s2);
			        if (erro == 1)
			           printf("\nA pilha esta vazia.\n");
					break;
			case 9: break;
			default: printf("\n\n Opcao nao valida");
		}
		getchar();    /* Limpa o buffer de entrada */
	} while ((q != 9) );
}

/* ---------------------------------------------------------------------- */

int inicializa(Tno_ls **p){
    *p = NULL;
    return 0;
}

/* ---------------------------------------------------------------------- */

int empilha  (Tno_ls **p, int info){
    Tno_ls *celula_nova, *percorre;

    celula_nova = (Tno_ls*)malloc(sizeof(Tno_ls));
    celula_nova->dado = info;
    celula_nova->prox = NULL;

    if((*p) == NULL){
        /* lista vazia */
        (*p) = celula_nova;
        return 0;
    }else{
        percorre = (*p);
        (*p) = celula_nova;
        (*p)->prox = percorre;
        return 0;
    }
}

/* --------------------------------------------------------------------------- */

int desempilha  (Tno_ls **p){
    Tno_ls *percorre = (*p), *aux;
    int erro = estado(*p);

    if(erro == 0){
        //Lista vazia
        return 1;
    }else if(erro == 1){
        //Lista com apenas 1 item
        inicializa(p);
    }
    else{
        //lista com 2 ou mais itens
        aux = percorre;
        percorre = percorre->prox;
        free(aux);
        (*p) = percorre;
        return 0;
    }
    return 0;  
}

/* --------------------------------------------------------------------------- */

int estado(Tno_ls *p){
    if(p == NULL){
        return 0;
    }else if(p->prox == NULL){
        return 1;
    }
    else{
        return 2;
    }
}

/* -------------------------------------------------------------------- */

int listar(Tno_ls *p){
    Tno_ls *percorre = p;

    if(percorre == NULL){
        //Lista vazia
        return 1;
    }else{
        printf("\nTOPO ->");
        while(percorre->prox != NULL){
            printf(" %d ->", percorre->dado);
            percorre = percorre->prox;
        }
        printf(" %d\n", percorre->dado);
        return 0;
    }
}
 /* ------------------------------------------------------------------- */
int obter_topo(Tno_ls *p, int *dado){
 if(p == NULL){ // Lista vazia
    return 1;
 }
    *dado = p->dado;
    return 0;
}
/* ------------------------------------------------------------------- */
int transfere(Tno_ls *p, Tno_ls **p2){
    Tno_ls *percorre = p;
    Tno_ls *pilhaAux;
    inicializa(&pilhaAux);
    Tno_ls **percorre2 = &pilhaAux;

    int erro = estado(p);
    
    if (erro >= 1) {        
        while(percorre->prox != NULL){
            empilha(&pilhaAux, percorre->dado);
            percorre = percorre->prox;
        }
        empilha(&pilhaAux, percorre->dado);
        printf("\nTransferindo: 50%%\n");
        printf("\nLista da pilha auxiliar\n");
        listar(pilhaAux);

        while((*percorre2)->prox != NULL){
            empilha(p2, (*percorre2)->dado);
            (*percorre2) = (*percorre2)->prox;
        }
        empilha(p2, (*percorre2)->dado);
        printf("\nTransferindo: 100%%\n");
        return 0;      
    }
    return 1;
}

