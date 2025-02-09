#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int horario[4], PFPJ, preferencial;
    char nome[40];
    struct no *prox;
} No;

typedef struct fila_banco{
    int tamanho;
    No *primeiro;
} Fila;

void criarFila(Fila *fila){
        fila->tamanho = 0;  
        fila->primeiro = NULL;  
        printf("\nFila criada com sucesso\n");
}

void imprimirFila(Fila fila) {
    No *no = fila.primeiro;   

    if (!no){
        printf("\nFila vazia\n");
    }
    
    printf("\n----- FILA DE CLIENTES -----\n");
    
    while (no) {
        printf("----------------------------\n");
        printf("Nome: %s\n", no->nome);
        if(no->preferencial){
            printf("Eh Preferencial\n");
        }else{
            printf("Nao eh preferencial\n");
        }
        if(no->PFPJ){
            printf("Pessoa fisica\n");
        }else{
            printf("Pessoa juridica\n'");
        }
        printf("Horario de chegada: %d%d:%d%d\n", 
               no->horario[0], no->horario[1], no->horario[2], no->horario[3]);
        
        no = no->prox;
    }
    printf("----------------------------\n");
}


void inserirNaFila(Fila *fila, char *nome, int hora[4], int PFPJ, int preferencial){
    No *aux, *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    strcpy(novo->nome, nome);
    memcpy(novo->horario, hora, 4 * sizeof(int));
    novo->PFPJ = PFPJ;
    novo->preferencial = preferencial;
    novo->prox = NULL;
    
    if (fila->primeiro == NULL) {
        fila->primeiro = novo;
    } else {
        aux = fila->primeiro;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    fila->tamanho++;
    printf("\nCliente adicionado com sucesso\n");
}

void removerDaFila(Fila *fila){
    if (fila->primeiro == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *temp = fila->primeiro;
    fila->primeiro = fila->primeiro->prox;
    free(temp);
    fila->tamanho--;
}

void verPrevisao();
void atender();
void juntarFilas();
void separarFilas();

void liberarMemoria(Fila *fila) {
    No *temp = fila->primeiro;
    while (temp != NULL) {
        No *remover = temp;
        temp = temp->prox;
        free(remover);
    }
    fila->tamanho = 0;
    fila->primeiro = NULL;
    printf("\nMemoria liberada!\n");
}

int main() {
    int escolha = 0, hora[4], PFouPJ, preferencial;
    Fila fila;
    char nome[30];
    
    while(escolha != 9){
        
        printf("\n1 - Criar fila");
        printf("\n2 - Ver fila");
        printf("\n3 - Inserir na fila");
        printf("\n4 - Remover da fila");
        printf("\n5 - Ver previsão de atendimento");
        printf("\n6 - Atender próximo");
        printf("\n7 - Unir filas");
        printf("\n8 - Separar filas");
        printf("\n9 - Encerrar atendimento");
        printf("\n\nEscolha a opção desejada: ");
        scanf("%d", &escolha);
        getchar();
        
        switch (escolha){
            case 1: 
                criarFila(&fila);
            break;
            
            case 2: 
                imprimirFila(fila);
            break;
            
            case 3: 
                printf("\nInsira o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                printf("\nInsira o horario de chegada do cliente (Sem ':'): ");
                scanf("%1d%1d%1d%1d", &hora[0], &hora[1], &hora[2], &hora[3]);
                getchar();
                printf("\nInsira se o cliente eh PF ou PJ (1 para PF, 0 para PJ): ");
                scanf("%d", &PFouPJ);
                getchar();
                if(PFouPJ != 1 && PFouPJ != 0){
                    printf("\nOpcao invalida\n");
                    break;
                }
                printf("\nInsira se o cliente eh preferencial (1 para sim, 0 para nao): ");
                scanf("%d", &preferencial);
                getchar();
                if(preferencial != 1 && preferencial != 0){
                    printf("\nOpcao invalida\n");
                    break;
                }
                inserirNaFila(&fila, nome, hora, PFouPJ, preferencial);
            break;
            
            case 4: 
                removerDaFila(&fila);
            break;
            
            case 5: 
                //verPrevisao();
            break;
            
            case 6: 
                //atender();
            break;
            
            case 7:
                //juntarFilas();
            break;
            
            case 8: 
                //separarFilas();
            break;
            
            case 9:
                liberarMemoria(&fila);
            break;
            default:
            printf("\nOpção inválida\n");
        }
    }

    return 0;
}
