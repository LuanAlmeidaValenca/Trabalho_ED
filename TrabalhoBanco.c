#include <stdio.h>

typedef struct no{
    int horario[4], PFPJ, preferencial;
    char nome[40];
    Cliente *prox;
} Cliente;

typedef struct fila_banco{
    int tamanho;
    Cliente *primeiro;
} Fila;

Fila criarFila(Fila *fila){
    fila = (Fila *) malloc(sizeof(Fila));
    if(fila){
        fila->tamanho = 0;  
        fila->primeiro = NULL;  
    }
    return *fila;
}

void imprimirFila(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("\nFila vazia\n");
        return;
    }

    Cliente *no = fila->primeiro;
    printf("\n--- FILA DE CLIENTES ---\n");
    
    while (no != NULL) {
        printf("-------------------\n");
        printf("Nome: %s\n", no->nome);
        printf("Preferência: %d\n", no->preferencial);
        printf("É PF ou PJ: %d\n", no->PFPJ);
        printf("Horário de chegada: %d%d:%d%d\n", 
               no->horario[0], no->horario[1], no->horario[2], no->horario[3]);
        printf("-------------------\n");
        
        no = no->prox;
    }
}

void inserirNaFila(Fila *fila, char nome, int hora, int PFPJ, int preferencial){
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    strcpy(novo->nome, nome);
    memcpy(novo->horario, &hora, 4 * sizeof(int));
    novo->PFPJ = PFPJ;
    novo->preferencial = preferencial;
    novo->prox = NULL;
    
    if (fila->primeiro == NULL) {
        fila->primeiro = novo;
    } else {
        Cliente *temp = fila->primeiro;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }

    fila->tamanho++;
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
