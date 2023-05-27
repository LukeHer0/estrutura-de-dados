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

typedef struct Elevador
{
    char id;
    int andar;
    int corredor;
    int distancia;
    Estado estado;
}Elevador;

void entrada(Elevador * elevadores);

void inicializar (Elevador * elevadores)
{
    for (int i = 0; i < tot_elevadores; i++)
    {
        elevadores[i].id = 'A' + i;
        elevadores[i].andar = i * 20;
        elevadores[i].corredor = i % 3;
        elevadores[i].distancia = 0;
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

Elevador * menor_distancia (Elevador * elevadores, int andar)
{
    int menor = INT_MAX;
    int distancia;
    Elevador * escolhido;
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
            escolhido = &elevadores[i];
        }
    }
    return escolhido;
}

void chegada(Elevador elevadores[], int index, int destino, int distancia)
{
    if (elevadores[index].andar == destino)
    {
        elevadores[index].estado = PARADO;
        printf("Procedimento bem sucessido! O elevador %c percorreu %dm no total e chegou no andar %d!\n", elevadores[index].id, distancia, destino);
        return;
    }
    if(tem_elevador(elevadores, elevadores[index].andar + 1, elevadores[index].corredor) && elevadores[index].estado == SUBINDO)
    {
        distancia ++;
        if(elevadores[index].corredor != 2)
        {
            elevadores[index].corredor = (elevadores[index].corredor + 1) % 3;
        }
        else 
        {
            elevadores[index].corredor = elevadores[index].corredor - 1;
        }
        entrada(elevadores);
        chegada(elevadores, index, destino, distancia);
    }
    if(tem_elevador(elevadores, elevadores[index].andar - 1, elevadores[index].corredor) && elevadores[index].estado == DESCENDO)
    {
        distancia ++;
        if(elevadores[index].corredor != 2)
        {
            elevadores[index].corredor = (elevadores[index].corredor + 1) % 3;
        }
        else 
        {
            elevadores[index].corredor = elevadores[index].corredor - 1;
        }
        entrada(elevadores);
        chegada(elevadores, index, destino, distancia);
    }
    else if (elevadores[index].andar > destino)
    {
        elevadores[index].estado = DESCENDO;
        elevadores[index].andar --;
        distancia ++;
        entrada(elevadores);
        chegada(elevadores, index, destino, distancia);
    }
    else if (elevadores[index].andar < destino)
    {
        elevadores[index].estado = SUBINDO;
        elevadores[index].andar ++;
        distancia ++;
        entrada(elevadores);
        chegada(elevadores, index, destino, distancia);
    }
}

void movimento(Elevador elevadores[], int index, int andar, int destino, int distancia)
{
    if (elevadores[index].andar == andar)
    {
        elevadores[index].distancia = distancia;
        printf("Procedimento bem sucessido! O elevador %c percorreu %dm para atender o chamado no andar %d!\n", elevadores[index].id, distancia, andar);
        chegada(elevadores, index, destino, elevadores[index].distancia);
        return;
    }
    else if (elevadores[index].andar > andar)
    {
        elevadores[index].estado = DESCENDO;
        elevadores[index].andar --;
        distancia ++;
        entrada(elevadores);
        movimento(elevadores, index, andar, destino, distancia);
    }
    else
    {
        elevadores[index].estado = SUBINDO;
        elevadores[index].andar ++;
        distancia ++;
        entrada(elevadores);
        movimento(elevadores, index, andar, destino, distancia);
    }
}

void entrada(Elevador * elevadores)
{
    char opcao;
    printf("Tem chamado?(S/N) ");
    scanf(" %c", &opcao);
    int andar = -1, destino = -1, k;
    switch(opcao)
    {
        case 'S':
        {   
            while(!verificador(andar) || !verificador(destino))
            {
                printf("Em qual andar o elevador está sendo chamado e qual o destino? (0 a 300) ");
                scanf("%d %d", &andar, &destino);
            }
            for(int j = 0; j < tot_elevadores; j++)
            {
                if(elevadores[j].id == menor_distancia(elevadores, andar)->id)
                {
                    k = j;
                }
            }
            movimento(elevadores, k, andar, destino, 0);
        }
        break;
        case 'N':
        {
            printador(elevadores);
            return;
        }
        default:
        {
            printf("Opção inválida, por favor insira apenas S ou N\n");
            return entrada(elevadores);
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
