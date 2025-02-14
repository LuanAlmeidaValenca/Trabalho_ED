/*Discentes:
Cauan Teixeira Machado
Cézar Augusto Nascimeto Dias
Luan Almeida Valença
Maria Eduarda Mascarenhas da Silva
Paulo Henrique Melo Rugani de Souza
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no //Estrutura do no da fila
{
    int horario[4], PFPJ, preferencial;
    char nome[40];
    struct no *prox;
} No;

typedef struct fila_banco // Estrutura da fila
{
    int tamanho;
    No *primeiro;
    No *ultimo;
} Fila;

void criarFila(Fila *fila) //Inicializa fila vazia
{
    fila->tamanho = 0;
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    printf("\nFila criada com sucesso\n");
}

void imprimirFila(Fila fila) //Imprime a fila, detalhando cada elemento da estrutura no 
{
    No *no = fila.primeiro;

    if (!no)
    {
        printf("\nFila vazia\n");
        return;
    }

    printf("\n----- FILA DE CLIENTES -----\n");
    //Inicia a impressão
    while (no)
    {
        printf("----------------------------\n");
        printf("Nome: %s\n", no->nome);
        if (no->preferencial)
        {
            printf("Eh Preferencial\n");
        }
        else
        {
            printf("Nao eh preferencial\n");
        }
        if (no->PFPJ)
        {
            printf("Pessoa fisica\n");
        }
        else
        {
            printf("Pessoa juridica\n");
        }
        printf("Horario de chegada: %d%d:%d%d\n",
               no->horario[0], no->horario[1], no->horario[2], no->horario[3]);

        no = no->prox;
    }
    printf("----------------------------\n");
}

void inserirNaFila(Fila *fila, int hora[4], int PFPJ, int *ultimoHorario) //Coloca o cliente no final da fila, obedecendo o FIFO
{
    No *novo = (No *)malloc(sizeof(No));

    if (!novo)
    {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    printf("\nInsira o nome do cliente: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0; // Remove o '\n' do final

    memcpy(novo->horario, hora, 4 * sizeof(int));
    novo->PFPJ = PFPJ;

    printf("\nInsira se o cliente eh preferencial (1 para sim, 0 para nao): ");
    scanf("%d", &novo->preferencial);
    getchar();
    if (novo->preferencial != 1 && novo->preferencial != 0)
    {
        printf("\nOpcao invalida\n");
        free(novo); //Libera memoria em caso de erro
        return;
    }

    novo->prox = NULL;

    if (fila->primeiro == NULL)
    {
        fila->primeiro = novo;
        fila->ultimo = novo;
    }
    else
    {
        fila->ultimo->prox = novo;
        fila->ultimo = novo;
    }
    fila->tamanho++;

    // Atualiza o último horário da fila correspondente
    memcpy(ultimoHorario, hora, 4 * sizeof(int));

    printf("\nCliente adicionado com sucesso!\n");
}

void removerDaFila(Fila *fila) //Remove o primeiro cliente da fila
{
    if (fila->primeiro == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    No *remover = fila->primeiro;
    fila->primeiro = remover->prox;
    if (fila->primeiro == NULL)
    {
        fila->ultimo = NULL;
    }

    free(remover); //Libera a memoria alocada para o ponteiro
    fila->tamanho--;

    printf("Cliente removido com sucesso!");
}

void exibirPrevisaoFila(Fila fila) //Mostra quantas pessoas estão presentes na fila e quantas faltam para o cliente ser atendido
{
    No *no = fila.primeiro;
    int posicao = 1;

    if (!no)
    {
        printf("\nFila vazia\n");
        return;
    }

    printf("\n----- PREVISAO DE ATENDIMENTO -----\n");

    while (no)
    {
        printf("Posicao: %d\n", posicao++);
        printf("Nome: %s\n", no->nome);
        printf("Horario de chegada: %d%d:%d%d\n",
               no->horario[0], no->horario[1], no->horario[2], no->horario[3]);
        no = no->prox;
    }
    printf("----------------------------\n");
}

void verPrevisao(Fila fila, char *nome)
{//Percorre a fila linearmente até encontrar o nome (O(n))
    No *no = fila.primeiro;
    int posicao = 1;

    while (no)
    {
        if (strcmp(no->nome, nome) == 0)
        {
            printf("\nCliente encontrado!\n");
            printf("Posicao na fila: %d\n", posicao);
            printf("Horario de chegada: %d%d:%d%d\n",
                   no->horario[0], no->horario[1], no->horario[2], no->horario[3]);
            return;
        }
        no = no->prox;
        posicao++;
    }

    printf("\nCliente nao encontrado na fila.\n");
}

void dividirLista(No *fonte, No **frente, No **atras) //Função auxiliar da função de Merge
{//Divide uma lista encadeada em duas metades para o Merge Sort.
    No *rapido;
    No *lento;
    lento = fonte;
    rapido = fonte->prox;

    while (rapido != NULL)
    {
        rapido = rapido->prox;
        if (rapido != NULL)
        {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }

    *frente = fonte;
    *atras = lento->prox;
    lento->prox = NULL;
}

No *mesclarListas(No *a, No *b) //Função auxiliar da função de Merge
{
    No *resultado = NULL;

    if (a == NULL)
    {
        return b;
    }
    else if (b == NULL)
    {
        return a;
    }

    
    if ((a->horario[0] * 1000 + a->horario[1] * 100 + a->horario[2] * 10 + a->horario[3]) <=
        (b->horario[0] * 1000 + b->horario[1] * 100 + b->horario[2] * 10 + b->horario[3]))
    {
        resultado = a;
        resultado->prox = mesclarListas(a->prox, b);
    }
    else
    {
        resultado = b;
        resultado->prox = mesclarListas(a, b->prox);
    }

    return resultado;
}

void mergeSort(No **cabeca)//Ordena a lista encadeada por horário de chegada.
{//Divide a lista em duas e ordena recursivamente
    No *cabecaRef = *cabeca;
    No *a;
    No *b;

    if ((cabecaRef == NULL) || (cabecaRef->prox == NULL))
    {
        return;
    }

    dividirLista(cabecaRef, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *cabeca = mesclarListas(a, b);
}

// Função auxiliar para copiar um nó de uma fila para outra
void copiarNo(Fila *filaDestino, No *no)
{//Aloca novo nó e copia todos os dados do original.
    No *novo = (No *)malloc(sizeof(No));
    if (!novo)
    {
        printf("\nErro ao alocar memoria!\n");
        return;
    }

    // Copia os dados do nó
    memcpy(novo->horario, no->horario, 4 * sizeof(int));
    novo->PFPJ = no->PFPJ;
    novo->preferencial = no->preferencial;
    strcpy(novo->nome, no->nome);
    novo->prox = NULL;

   
    if (filaDestino->primeiro == NULL)
    {
        filaDestino->primeiro = novo;
        filaDestino->ultimo = novo;
    }
    else
    {
        filaDestino->ultimo->prox = novo;
        filaDestino->ultimo = novo;
    }
    filaDestino->tamanho++;
}

void juntarFilas(Fila *filaPF, Fila *filaPJ, Fila *filaUnificada) // Junta as Filas PF e PJ numa só para suprir a necessidade durante o almoço
{//Copia todos os nós das filas originais para a fila unificada e ordena a nova fila usando Merge Sort.
    
    No *noPF = filaPF->primeiro;
    while (noPF)
    {
        copiarNo(filaUnificada, noPF);
        noPF = noPF->prox;
    }

    
    No *noPJ = filaPJ->primeiro;
    while (noPJ)
    {
        copiarNo(filaUnificada, noPJ);
        noPJ = noPJ->prox;
    }

    
    mergeSort(&(filaUnificada->primeiro));

    
    No *temp = filaUnificada->primeiro;
    while (temp->prox != NULL)
    {
        temp = temp->prox;
    }
    filaUnificada->ultimo = temp;
}

void atender(Fila *fila, int *QPreferencial) {//Remove os clientes da fila de acordo com a regra de prioridade
    if (fila->primeiro == NULL) {
        printf("\nNao ha clientes para atender.\n");
        return;
    }

    No *atendido = NULL;
    No *anterior = NULL;
    No *atual = fila->primeiro;

    if (*QPreferencial == 3) {
        // Procura o primeiro cliente NÃO prioritário
        while (atual != NULL && atual->preferencial) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual != NULL) {
            atendido = atual;
            // Remove o cliente não prioritário da fila
            if (anterior == NULL) {
                fila->primeiro = atendido->prox;
            } else {
                anterior->prox = atendido->prox;
            }

            if (atendido->prox == NULL) {
                fila->ultimo = anterior;
            }
            *QPreferencial = 0; // Reinicia o contador
        } else {
            // Não há não prioritários, atende o próximo prioritário
            atendido = fila->primeiro;
            fila->primeiro = atendido->prox;
            if (fila->primeiro == NULL) {
                fila->ultimo = NULL;
            }
            *QPreferencial = 0; // Reinicia após atender prioritário
        }
    } else {
        // Procura o primeiro cliente PRIORITÁRIO (ignorando não prioritários à frente)
        No *anterior_prioritario = NULL;
        No *prioritario = fila->primeiro;

        while (prioritario != NULL && !prioritario->preferencial) {
            anterior_prioritario = prioritario;
            prioritario = prioritario->prox;
        }

        if (prioritario != NULL) {
            // Atende o prioritário encontrado
            atendido = prioritario;
            if (anterior_prioritario == NULL) {
                fila->primeiro = atendido->prox;
            } else {
                anterior_prioritario->prox = atendido->prox;
            }

            if (atendido->prox == NULL) {
                fila->ultimo = anterior_prioritario;
            }
            (*QPreferencial)++; // Incrementa o contador
        } else {
            // Não há prioritários, atende o primeiro cliente (não prioritário)
            atendido = fila->primeiro;
            fila->primeiro = atendido->prox;
            if (fila->primeiro == NULL) {
                fila->ultimo = NULL;
            }
            *QPreferencial = 0; // Reinicia o contador
        }
    }

    printf("\nAtendendo cliente: %s\n", atendido->nome);
    free(atendido);
    fila->tamanho--;
}


void liberarMemoria(Fila *fila)
{
    No *temp = fila->primeiro;
    while (temp != NULL)
    {
        No *proxNo = temp->prox;
        free(temp);
        temp = proxNo;
    }

    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->tamanho = 0;

    printf("\nMemoria liberada!\n");
}

int main()
{
    int hora[4], ultimoHorarioPF[4], ultimoHorarioPJ[4], ultimoHorarioGeral[4];
    int escolha = 0, escolhaFila, PFouPJ, uniaoFila = 0, QPreferencial = 0;
    Fila filaPF, filaPJ, filaUnificada;

    for (int i = 0; i < 4; i++)
    {
        ultimoHorarioPF[i] = 0;
        ultimoHorarioPJ[i] = 0;
    }

    while (escolha != 8)
    {
        char temp;

        printf("\n1 - Criar fila");
        printf("\n2 - Ver fila");
        printf("\n3 - Inserir na fila");
        printf("\n4 - Remover da fila");
        printf("\n5 - Ver previsao de atendimento");
        printf("\n6 - Atender proximo");
        printf("\n7 - Unir filas");
        printf("\n8 - Encerrar atendimento");
        printf("\n\nEscolha a opcao desejada: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
            criarFila(&filaPF);
            criarFila(&filaPJ);
            criarFila(&filaUnificada);
            break;

        case 2:
            if (uniaoFila)
            {
                imprimirFila(filaUnificada);
            }
            else
            {
                printf("\nInsira qual fila deseja imprimir (0 para PJ, 1 para PF):");
                scanf("%d", &escolhaFila);
                if (escolhaFila)
                {
                    imprimirFila(filaPF);
                }
                else
                {
                    imprimirFila(filaPJ);
                }
            }
            break;

        case 3:
            printf("\nInsira o horario de chegada do cliente (XX:XX): ");
            scanf("%1d%1d%c%1d%1d", &hora[0], &hora[1], &temp, &hora[2], &hora[3]);
            getchar();

            printf("\nInsira se o cliente eh PF ou PJ (1 para PF, 0 para PJ): ");
            scanf("%d", &PFouPJ);
            getchar();
            if (PFouPJ != 1 && PFouPJ != 0)
            {
                printf("\nOpcao invalida\n");
                return 1;
            }

            if (uniaoFila)
            {
                if ((ultimoHorarioPF[0] * 10 + ultimoHorarioPF[1]) * 60 + (ultimoHorarioPF[2] * 10 + ultimoHorarioPF[3]) < (ultimoHorarioPJ[0] * 10 + ultimoHorarioPJ[1]) * 60 + (ultimoHorarioPJ[2] * 10 + ultimoHorarioPJ[3])){
                    memcpy(ultimoHorarioGeral, ultimoHorarioPJ, 4 * sizeof(int));
                }else{
                    memcpy(ultimoHorarioGeral, ultimoHorarioPF, 4 * sizeof(int));
                }
                
                if((hora[0] * 10 + hora[1]) * 60 + (hora[2] * 10 + hora[3]) < (ultimoHorarioGeral[0] * 10 + ultimoHorarioGeral[1]) * 60 + (ultimoHorarioGeral[2] * 10 + ultimoHorarioGeral[3])){
                    printf("\nHorario de chegada invalido");
                    printf("\nChegada do cliente anterior: %d%d:%d%d", ultimoHorarioGeral[0], ultimoHorarioGeral[1], ultimoHorarioGeral[2], ultimoHorarioGeral[3]);
                    break;
                }
                inserirNaFila(&filaUnificada, hora, PFouPJ, ultimoHorarioGeral);
            }
            else
            {
                
                if (PFouPJ)
                {
                    
                    if ((hora[0] * 10 + hora[1]) * 60 + (hora[2] * 10 + hora[3]) < (ultimoHorarioPF[0] * 10 + ultimoHorarioPF[1]) * 60 + (ultimoHorarioPF[2] * 10 + ultimoHorarioPF[3]))
                    {
                        printf("\nHorario de chegada invalido");
                        printf("\nChegada do cliente anterior: %d%d:%d%d", ultimoHorarioPF[0], ultimoHorarioPF[1], ultimoHorarioPF[2], ultimoHorarioPF[3]);
                        break;
                    }
                    inserirNaFila(&filaPF, hora, PFouPJ, ultimoHorarioPF);
                }
                else
                {
                    
                    if ((hora[0] * 10 + hora[1]) * 60 + (hora[2] * 10 + hora[3]) < (ultimoHorarioPJ[0] * 10 + ultimoHorarioPJ[1]) * 60 + (ultimoHorarioPJ[2] * 10 + ultimoHorarioPJ[3]))
                    {
                        printf("\nHorario de chegada invalido");
                        printf("\nChegada do cliente anterior: %d%d:%d%d", ultimoHorarioPJ[0], ultimoHorarioPJ[1], ultimoHorarioPJ[2], ultimoHorarioPJ[3]);
                        break;
                    }
                    inserirNaFila(&filaPJ, hora, PFouPJ, ultimoHorarioPJ);
                }
            }
            break;

        case 4:
            if (uniaoFila)
            {
                removerDaFila(&filaUnificada);
            }
            else
            {
                printf("\nInsira qual fila deseja remover (0 para PJ, 1 para PF):");
                scanf("%d", &escolhaFila);
                if (escolhaFila)
                {
                    removerDaFila(&filaPF);
                }
                else
                {
                    removerDaFila(&filaPJ);
                }
            }
            break;

        case 5:
            if (uniaoFila)
            {
                char nome[40];
                printf("\nInsira o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                verPrevisao(filaUnificada, nome);
            }
            else
            {
                printf("\nInsira qual fila deseja ver a previsao (0 para PJ, 1 para PF):");
                scanf("%d", &escolhaFila);
                if (escolhaFila)
                {
                    exibirPrevisaoFila(filaPF);
                }
                else
                {
                    exibirPrevisaoFila(filaPJ);
                }
            }
            break;

        case 6:
            if (uniaoFila)
            {
                atender(&filaUnificada, &QPreferencial);
            }
            else
            {
                printf("\nInsira qual fila deseja atender (0 para PJ, 1 para PF):");
                scanf("%d", &escolhaFila);
                if (escolhaFila)
                {
                    atender(&filaPF, &QPreferencial);
                }
                else
                {
                    atender(&filaPJ, &QPreferencial);
                }
            }
            break;

        case 7:
            if (uniaoFila)
            {
                printf("Filas ja unificadas");
            }
            else
            {
                juntarFilas(&filaPF, &filaPJ, &filaUnificada);
                uniaoFila = 1;
            }
            break;

        case 8:
            liberarMemoria(&filaPF);
            liberarMemoria(&filaPJ);
            liberarMemoria(&filaUnificada);
            break;

        default:
            printf("\nOpcao invalida\n");
        }
    }

    return 0;
}