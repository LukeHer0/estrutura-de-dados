#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define andares 300 //predio de 300 andares
#define corredores 3 //3 corredores 
#define elevadores_per_cor 5 //5 elevadores por corredor
#define tot_elevadores (corredores * elevadores_per_cor) // 15 elevadores no total

typedef enum Estado{
    PARADO,
    SUBINDO,
    DESCENDO
}Estado;

typedef enum Direcao{
    INDO,
    LEVANDO
}Direcao;

typedef struct Elevador
{
    char id;
    int andar;
    int corredor;
    Estado estado;
}Elevador;

typedef struct Chamadas
{
    int andar;
    int destino;
    Elevador * elevador;
    Direcao direcao;
    struct Chamadas * prox;
}Chamadas;

void entrada(Elevador * elevadores);

void inicializar (Elevador * elevadores)
{
    for (int i = 0; i < tot_elevadores; i++)
    {
        elevadores[i].id = 'A' + i;
        elevadores[i].andar = i * 20;
        elevadores[i].corredor = i % 3;
        elevadores[i].estado = PARADO;
    }
}

void printador(Elevador * elevadores)
{
    char predio [andares][corredores];
    int subtrator = 0;
    for(int i = andares; i >= 0 ; i--)
    {
        printf("%d. ", i);
        for(int j = 0; j < corredores; j++)
        {
            for(int k = 0; k < tot_elevadores; k++)
            {
                if(elevadores[k].andar == i && elevadores[k].corredor == j)
                {
                    printf("%c ", elevadores[k].id);
                    subtrator = 1;
                }
            }
            //j += subtrator;
            subtrator = 0;
            if (j == corredores)
            {}
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int verificador(int andar)
{
    if(andar < 0 || andar > 300)
    {
        return 0;
    }
    return 1;
}

void printa_lista (Chamadas * lista)
{
    while (lista != NULL)
    {
        printf("%d %d\n", lista->andar, lista->destino);
        lista = lista->prox;
    }
}

Elevador * menor_distancia (Elevador * elevadores, int andar)
{
    int menor = INT_MAX;
    int distancia;
    int k;
    for (int i = 0; i < tot_elevadores; i++)
    {
        if(elevadores[i].andar < andar && elevadores[i].estado == DESCENDO)
        {
            i ++;
        }
        else if(elevadores[i].andar > andar && elevadores[i].estado == SUBINDO)
        {
            i++;
        }

        distancia = abs(andar - elevadores[i].andar);

        if(distancia < menor)
        {
            menor = distancia;
            k = i;
        }
    }
    return elevadores + k;
}

int tem_elevador(Elevador * elevadores, int andar, int corredor)
{
    for (int i = 0; i < tot_elevadores; i++)
    {
        if(elevadores[i].andar == andar && elevadores[i].corredor == corredor)
        {
            return 1;
        }
    }
    return 0;
}

Chamadas * aloca_espaco()
{
    return malloc(sizeof(Chamadas));
}

Chamadas * inserir (Chamadas * lista, Elevador * elevadores, int andar, int destino)
{
    Chamadas * aux = aloca_espaco();
    Chamadas * percorre = lista;
    if (!lista)
    {
        lista = aux;
        lista->andar = andar;
        lista->destino = destino;
        lista->elevador = menor_distancia(elevadores, andar);
        lista->direcao = INDO;
        lista->prox = NULL;
    }
    else
    {
        while(percorre->prox != NULL)
        {
            percorre = percorre->prox;
        }
        aux->andar = andar;
        aux->destino = destino;
        aux->elevador = menor_distancia(elevadores, andar);
        aux->direcao = INDO;
        aux->prox = NULL;
        percorre->prox = aux;
    }
    return lista;
}

Chamadas * remover (Chamadas * lista, Chamadas * alvo)
{
    Chamadas * aux = lista;
    Chamadas * aux2 = NULL;
    if(lista == NULL)
    {
        puts("primeiro");
        return NULL;
    }
    else if (lista == alvo)
    {
        puts("segundo");
        lista = lista->prox;
        aux = NULL;
        return lista;
    }
    else
    {
        puts("terceiro");
        while(aux->prox != alvo)
        {
            aux = aux->prox;
        }
        aux2 = aux->prox;
        aux->prox = aux->prox->prox;
        free(aux2);
        return lista; 
    }
}

int movimento(Direcao * direcao, Elevador * elevadores, int andar, int destino)
{
    if(*direcao == INDO)
    {
        if(elevadores->andar == andar)
        {
            elevadores->estado = PARADO;
            *direcao = LEVANDO;
            printf("O elevador %c chegou no andar %d!\n", elevadores->id, elevadores->andar);
        }
        else if(elevadores->andar > andar)
        {
            elevadores->andar --;
            elevadores->estado = DESCENDO;
        }
        else if (elevadores->andar < andar)
        {
            elevadores->andar ++;
            elevadores->estado = SUBINDO;
        }
    }
    else if(*direcao == LEVANDO)
    {
        if(elevadores->andar == destino)
        {
            elevadores->estado = PARADO;
            return 1;
        }
        else if(tem_elevador(elevadores, elevadores->andar + 1, elevadores->corredor) && elevadores->estado == SUBINDO)
        {
            if(elevadores->corredor != 2)
            {
                elevadores->corredor = (elevadores->corredor + 1) % 3;
            }
            else 
            {
                elevadores->corredor = elevadores->corredor - 1;
            }
        }
        else if(tem_elevador(elevadores, elevadores->andar - 1, elevadores->corredor) && elevadores->estado == DESCENDO)
        {
            if(elevadores->corredor != 2)
            {
                elevadores->corredor = (elevadores->corredor + 1) % 3;
            }
            else 
            {
                elevadores->corredor = elevadores->corredor - 1;
            }
        }
        else if(elevadores->andar > destino)
        {
            elevadores->andar --;
            elevadores->estado = DESCENDO;
        }
        else if(elevadores->andar < destino)
        {
            elevadores->andar ++;
            elevadores->estado = SUBINDO;
        }
        
    }
    return 0;
}

void conferidor_lista (Elevador * elevadores, Chamadas * lista)
{
    Chamadas * percorre = lista;
    Chamadas * aux = NULL;
    if(lista == NULL)
    {
        return;
    }
    else 
    {
        while (percorre != NULL)
        {
            aux = percorre->prox;
            if (movimento(&(percorre->direcao), percorre->elevador, percorre->andar, percorre->destino))
            {
                lista = remover(lista, percorre);
            }
            percorre = aux;
        }
    }
}

void entrada(Elevador * elevadores)
{
    char opcao;
    Chamadas * lista = NULL;
    while (1)
    {
        printf("Tem chamado?(S/Outra letra) ");
        scanf(" %c", &opcao);
        int andar = -1, destino = -1;
        switch(opcao)
        {
            case 'S':
            {   
                while(!verificador(andar) || !verificador(destino))
                {
                    printf("Em qual andar o elevador está sendo chamado e qual o destino? (0 a 300) ");
                    scanf("%d %d", &andar, &destino);
                }
                lista = inserir(lista, elevadores, andar, destino);
                break;
            }
            default:
            {
                conferidor_lista(elevadores, lista);
                printador(elevadores);
                break;
            }
        }
    }
}

int main()
{
    Elevador elevadores[tot_elevadores];
    inicializar(elevadores);
    printf("Este é o prédio de 300 andares. Cada letra simboliza um ID de um elevador. Eis o prédio:\n");
    printador(elevadores);
    entrada(elevadores);
    return 0;
}
