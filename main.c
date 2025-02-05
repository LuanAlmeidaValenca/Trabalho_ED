#include <stdio.h>

typedef struct no{
    int horario[4], PFPJ, preferencial;
    char nome[40];
    Cliente *prox = NULL;
} Cliente;

typedef struct fila_banco{
    int tamanho;
    Cliente *primeiro = NULL;
} Fila;

Fila criarFila(Fila *fila){
    fila = (Fila *) malloc(sizeof(Fila));
    if(fila){
        fila->tamanho = 0;    
    }
    return fila;
}

void imprimirFila(Fila *fila){
    if (Fila->tamanho == 0){
        printf("\nLista vazia\n");
    }else{
    Cliente no = lista->inicio;
        if(no){
            do{
                printf("-------------------");
                printf("\nNome: %s", no->nome);
                printf("\nPreferencia: %d", no->preferencial);
                printf("\nÉ pf ou pj: ", no->PFPJ);
                printf("\nHorário de chegada: %d%d:%d%d", cliente->horario[0],cliente->horario[1],cliente->horario[2],cliente->horario[3]);
                printf("-------------------\n");
                no = no->prox;
            }while (no->prox != NULL);    
        }
    }
}

void inserirNaFila(Fila *fila, char nome, int hora, int PFPJ, int preferencial){
        
    
}

void removerDaFila();
void verPrevisao();
void atender();
void juntarFilas();
void separarFilas();
void liberarMemoria();

int main() {
    int escolha;
    
    
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
        printf("\nEscolha a opção desejada: ");
        scanf("%d", &escolha);
        
        if(escolha < 1 && escolha > 9){
            printf("Escolha inválida, o número precisa estar entre 1 e 9");
        }
        
        switch (escolha){
            case 1 : 
                criarFila();
            break;
            
            case 2 : 
                imprimirFila();
            break;
            
            case 3 : 
                inserirNaFila();
            break;
            
            case 4 : 
                removerDaFila();
            break;
            
            case 5 : 
                verPrevisao();
            break;
            
            case 6 : 
                atender();
            break;
            
            case 7 :
                juntarFilas();
            break;
            
            case 8 : 
                separarFilas();
            break;
            
            case 9 :
                liberarMemoria();
            break;
            default : break;
        }
    }

    return 0;
}
