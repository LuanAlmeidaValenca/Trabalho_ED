#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define previsao = 5;

/*A FAZER:
Implementar atendimento, ordenar fila, mostrar previsão para atendimento de acordo com o cliente,
merge das filas, unir as filas
OPCIONAL, mudança no case 3 para ter mais de uma variavel de ultimoHorario[4]
(sendo 1 para PF e outro para PJ)
*/
/*
Sugestões para organização das filas:
Manter uma fila para PF e outra para PJ, não necessáriamente ordenada, e fazer checagem de prioridade
de atendimento durante a execução da função atender
*/

typedef struct no{
    int horario[4], PFPJ, preferencial;
    char nome[40];
    struct no *prox;
} No;

typedef struct fila_banco{
    int tamanho;
    No *primeiro;
    No *ultimo;
} Fila;

void criarFila(Fila *fila){
        fila->tamanho = 0;  
        fila->primeiro = NULL;  
        fila->ultimo = NULL;
        printf("\nFila criada com sucesso\n");
}

void imprimirFila(Fila fila) {
    No *no = fila.primeiro;   

    if (!no){
        printf("\nFila vazia\n");
        return;
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
            printf("Pessoa juridica\n");
        }
        printf("Horario de chegada: %d%d:%d%d\n", 
               no->horario[0], no->horario[1], no->horario[2], no->horario[3]);
        
        no = no->prox;
    }
    printf("----------------------------\n");
}


void inserirNaFila(Fila *filaPF, Fila *filaPJ, int hora[4]/*, char *nome, int PFPJ, int preferencial*/){
    No *aux, *novo = (No *)malloc(sizeof(No));

    if (!novo) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    printf("\nInsira o nome do cliente: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);

    memcpy(novo->horario, hora, 4 * sizeof(int));
    getchar();

    printf("\nInsira se o cliente eh preferencial (1 para sim, 0 para nao): ");
    scanf("%d", &novo->preferencial);
    getchar();
    if(novo->preferencial != 1 && novo->preferencial != 0){
        printf("\nOpcao invalida\n");
        free(novo);
        return;
    }

    printf("\nInsira se o cliente eh PF ou PJ (1 para PF, 0 para PJ): ");
    scanf("%d", &novo->PFPJ);
    getchar();
    if(novo->PFPJ != 1 && novo->PFPJ != 0){
        printf("\nOpcao invalida\n");
        return;
    }
    if(novo->PFPJ == 1){
        novo->prox = NULL;

        if (filaPF->primeiro == NULL) { // Se a fila estiver vazia
            filaPF->primeiro = novo;
            filaPF->ultimo = novo;
        } else {
            filaPF->ultimo->prox = novo;
            filaPF->ultimo = novo; 
        }
        filaPF->tamanho++;
    } else{
        if (filaPJ->primeiro == NULL) { // Se a fila estiver vazia
            filaPJ->primeiro = novo;
            filaPJ->ultimo = novo;
        } else {
            filaPJ->ultimo->prox = novo;
            filaPJ->ultimo = novo; 
        }
        filaPJ->tamanho++;
    }

    /*
    strcpy(novo->nome, nome);
    memcpy(novo->horario, hora, 4 * sizeof(int));
    novo->PFPJ = PFPJ;
    novo->preferencial = preferencial;
    novo->prox = NULL;
    */

    printf("\nCliente adicionado com sucesso!\n");
}

void removerDaFila(Fila *fila){
    if (fila->primeiro == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *remover = fila->primeiro;
    fila->primeiro = remover->prox;
    if (fila->primeiro == NULL){ // caso a lista fique vazia, atualiza o ultimo
        fila->ultimo = NULL;
    }

    free(remover);
    fila->tamanho--;

    printf("Cliente removido com sucesso!");
}

void ordenarFila(Fila *filaPF, Fila *filaPJ, int qntdPreferencial){
    if(filaPF->tamanho == 0){
        printf("Lista vazia");
        return;
    }

    No* temp = filaPF;
    do{

    }while (temp);
    
    
}

void verPrevisao();

void atender(Fila *filaPF, Fila *filaPJ, int uniao){
    int filaEscolhida;

    if(!uniao){
        printf("\n Insira qual fila deseja atender no momento (0 para PJ, 1 para PF): ");
        scanf("%d", &filaEscolhida);
        if (filaEscolhida){
            
        }
    }
}

int juntarFilas(int uniao){

    return uniao; //caso o procedimento seja bem sucedido
}
void separarFilas();

void liberarMemoria(Fila *filaPF, Fila *filaPJ) {
    No *temp = filaPF->primeiro;
    while (temp != NULL) {
        No *proxNo = temp->prox;
        free(temp);
        temp = proxNo;
    }

    filaPF->primeiro = NULL;
    filaPF->ultimo = NULL;
    filaPF->tamanho = 0;

    No *temp2 = filaPJ->primeiro;
    while (temp2 != NULL) {
        No *proxNo = temp2->prox;
        free(temp2);
        temp2 = proxNo;
    }

    filaPJ->primeiro = NULL;
    filaPJ->ultimo = NULL;
    filaPJ->tamanho = 0;

    printf("\nMemória liberada!\n");
}

int main() {
    int hora[4], ultimoHorario[4];
    int escolha = 0, escolhaFila, PFouPJ, preferencial, preferencialAtendido = 0, uniaoFila;
    char nome[30];
    Fila filaPF, filaPJ;

    for(int i = 0; i < 4; i++){
        ultimoHorario[i] = 0;
    }
    
    while(escolha != 9){

        char temp;
        
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
                criarFila(&filaPF);
                criarFila(&filaPJ);
            break;
            
            case 2: 
                printf("\nInsira qual fila deseja imprimir (0 para PJ, 1 para PF):");
                scanf("%d", &escolhaFila);
                if(escolhaFila){
                    imprimirFila(filaPF);
                }else{
                    imprimirFila(filaPJ);
                }
            break;
            
            case 3: 
                printf("\nInsira o horario de chegada do cliente (XX:XX): ");
                scanf("%1d%1d%c%1d%1d", &hora[0], &hora[1], &temp , &hora[2], &hora[3]);
                getchar();
                // Esse if verifica se o horario de chegada do cliente condiz com o horario do anterior 
                if ((hora[0] * 10 + hora[1]) * 60 + (hora[2] * 10 + hora[3]) < (ultimoHorario[0] * 10 + ultimoHorario[1]) * 60 + (ultimoHorario[2] * 10 + ultimoHorario[3])) {
                    printf("\nHorario de chegada invalido");
                    printf("\nChegada do cliente anterior: %d%d:%d%d", ultimoHorario[0], ultimoHorario[1], ultimoHorario[2], ultimoHorario[3]);
                    break;
                }
                memcpy(ultimoHorario, hora, 4 * sizeof(int));
                
                inserirNaFila(&filaPF, &filaPJ, hora/*, nome, PFouPJ, preferencial*/);
            break;
            
            case 4: 
                removerDaFila(&filaPF);
                removerDaFila(&filaPJ);
            break;
            
            case 5: 
                //verPrevisao();
            break;
            
            case 6: 
                //atender();
            break;
            
            case 7:
                //juntarFilas(uniaoFila);
            break;
            
            case 8: 
                //separarFilas();
            break;
            
            case 9:
                liberarMemoria(&filaPF, &filaPJ);
            break;
            default:
            printf("\nOpção inválida\n");
        }
    }

    return 0;
}