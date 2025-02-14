#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define previsao = 5;

/*A FAZER:
Implementar atendimento, mostrar previsão para atendimento de acordo com o cliente.
CORREÇÃO OPCIONAL:
O armazenamento de ultimoHorario[] no case 3, esta sendo usado tanto para a fila Fisica quanto Juridica,
porem, as duas filas independem uma da outra quanto a chegada, pode ser interessante criar um array para 
salvar o ultimo horario de cada lista 
PS: Se for implementar a função de atendimento, pode fazer ela do zero, se n achar nada que tem nela
pertinente, apague dboa, era so um teste q eu tava fazendo
Pode ser uma boa revisar partes do codigo para garantir q ele ta de acordo com o q foi pedido no pdf
ASS: Luan
*/


typedef struct no
{
    int horario[4], PFPJ, preferencial;
    char nome[40];
    struct no *prox;
} No;

typedef struct fila_banco
{
    int tamanho;
    No *primeiro;
    No *ultimo;
} Fila;

void criarFila(Fila *fila)
{
    fila->tamanho = 0;
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    printf("\nFila criada com sucesso\n");
}

void imprimirFila(Fila fila)
{
    No *no = fila.primeiro;

    if (!no)
    {
        printf("\nFila vazia\n");
        return;
    }

    printf("\n----- FILA DE CLIENTES -----\n");

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

void inserirNaFila(Fila *fila, int hora[4] /*, char *nome, int PFPJ, int preferencial*/)
{
    No *novo = (No *)malloc(sizeof(No));

    if (!novo)
    {
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
    if (novo->preferencial != 1 && novo->preferencial != 0)
    {
        printf("\nOpcao invalida\n");
        free(novo);
        return;
    }

    novo->prox = NULL;

    if (fila->primeiro == NULL)
    { // Se a fila estiver vazia
        fila->primeiro = novo;
        fila->ultimo = novo;
    }
    else
    {
        fila->ultimo->prox = novo;
        fila->ultimo = novo;
    }
    fila->tamanho++;

    /*
    strcpy(novo->nome, nome);
    memcpy(novo->horario, hora, 4 * sizeof(int));
    novo->PFPJ = PFPJ;
    novo->preferencial = preferencial;
    novo->prox = NULL;
    */

    printf("\nCliente adicionado com sucesso!\n");
}

void removerDaFila(Fila *fila)
{
    if (fila->primeiro == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    No *remover = fila->primeiro;
    fila->primeiro = remover->prox;
    if (fila->primeiro == NULL)
    { // caso a lista fique vazia, atualiza o ultimo
        fila->ultimo = NULL;
    }

    free(remover);
    fila->tamanho--;

    printf("Cliente removido com sucesso!");
}

void verPrevisao();

void atender(Fila *fila, int uniao, int QPreferencial)
{
    int filaEscolhida;

    if (!uniao)
    {
        printf("\n Insira qual fila deseja atender no momento (0 para PJ, 1 para PF): ");
        scanf("%d", &filaEscolhida);
        if (filaEscolhida)
        {
            if (QPreferencial <= 3)
            {
                removerDaFila(filaPF);
                return QPreferencial++;
            }
            else
            {
                removerDaFila(filaPF);
                return QPreferencial = 0;
            }
        }
        else
        {
            removerDaFila(filaPJ);
        }
    }
}


void juntarFilas(Fila *filaPF, Fila *filaPJ, Fila *filaUnificada)
{
    if (filaPF->primeiro != NULL)
    {
        filaUnificada->primeiro = filaPF->primeiro;
        filaUnificada->ultimo = filaPF->ultimo;
    }

    if (filaPJ->primeiro != NULL)
    {
        if (filaUnificada->primeiro == NULL)
        {
            filaUnificada->primeiro = filaPJ->primeiro;
        }
        else
        {
            filaUnificada->ultimo->prox = filaPJ->primeiro;
        }
        filaUnificada->ultimo = filaPJ->ultimo;
    }
}

void liberarMemoria(Fila *filaPF, Fila *filaPJ, Fila *filaUnificada)
{
    No *temp = filaPF->primeiro;
    while (temp != NULL)
    {
        No *proxNo = temp->prox;
        free(temp);
        temp = proxNo;
    }

    filaPF->primeiro = NULL;
    filaPF->ultimo = NULL;
    filaPF->tamanho = 0;

    No *temp2 = filaPJ->primeiro;
    while (temp2 != NULL)
    {
        No *proxNo = temp2->prox;
        free(temp2);
        temp2 = proxNo;
    }

    filaPJ->primeiro = NULL;
    filaPJ->ultimo = NULL;
    filaPJ->tamanho = 0;

    No *temp3 = filaUnificada->primeiro;
    while (temp3 != NULL)
    {
        No *proxNo = temp3->prox;
        free(temp3);
        temp3 = proxNo;
    }

    filaUnificada->primeiro = NULL;
    filaUnificada->ultimo = NULL;
    filaUnificada->tamanho = 0;

    printf("\nMemória liberada!\n");
}

// cauan

// MERGE SORT

void dividirLista(No *fonte, No **frente, No **atras)
{
    No *rapido;
    No *lento;
    lento = fonte;
    rapido = fonte->prox;

    while (rapido != NULL)
    {
        rapido = rapido->prox;
        if(rapido != NULL){
            lento = lento -> prox;
            rapido = rapido->prox;
        }
    }

    *frente = fonte;
    *atras = lento->prox;
    lento->prox = NULL;
}

No *mesclarListas(No *a, No *b)
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

    if (a->horario <= b->horario)
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

void mergeSort(No** cabeca){
    No *cabecaRef = *cabeca;
    No *a;
    No *b;

    if ((cabecaRef == NULL) || (cabecaRef->prox) == NULL){
        return;
    }

    dividirLista(cabecaRef,a,b);

    mergeSort(&a);
    mergeSort(&b);

    *cabeca = mesclarListas(a, b);

}

int main()
{
    int hora[4], ultimoHorario[4];
    int escolha = 0, escolhaFila, PFouPJ, uniaoFila = 0;
    Fila filaPF, filaPJ, filaUnificada;

    for (int i = 0; i < 4; i++)
    {
        ultimoHorario[i] = 0;
    }

    while (escolha != 8)
    {

        char temp;

        printf("\n1 - Criar fila");
        printf("\n2 - Ver fila");
        printf("\n3 - Inserir na fila");
        printf("\n4 - Remover da fila");
        printf("\n5 - Ver previsão de atendimento");
        printf("\n6 - Atender próximo");
        printf("\n7 - Unir filas");
        printf("\n8 - Encerrar atendimento");
        printf("\n\nEscolha a opção desejada: ");
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
            if (uniaoFila){
                imprimirFila(filaUnificada);
            }else{
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
            // Esse if verifica se o horario de chegada do cliente condiz com o horario do anterior
            if ((hora[0] * 10 + hora[1]) * 60 + (hora[2] * 10 + hora[3]) < (ultimoHorario[0] * 10 + ultimoHorario[1]) * 60 + (ultimoHorario[2] * 10 + ultimoHorario[3]))
            {
                printf("\nHorario de chegada invalido");
                printf("\nChegada do cliente anterior: %d%d:%d%d", ultimoHorario[0], ultimoHorario[1], ultimoHorario[2], ultimoHorario[3]);
                break;
            }
            memcpy(ultimoHorario, hora, 4 * sizeof(int));

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
                inserirNaFila(&filaUnificada, hora);
            }
            else
            {
                if (PFouPJ)
                {
                    inserirNaFila(&filaPF, hora /*, nome, PFouPJ, preferencial*/);
                }
                else
                {
                    inserirNaFila(&filaPJ, hora /*, nome, PFouPJ, preferencial*/);
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
            // verPrevisao();
            break;

        case 6:
            // atender();
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
                mergeSort(&filaUnificada);
            }
            break;

        case 8:
            liberarMemoria(&filaPF, &filaPJ, &filaUnificada);
            break;
        default:
            printf("\nOpção inválida\n");
        }
    }

    return 0;
}