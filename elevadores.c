#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define andares 300 //predio de 300 andares
#define corredores 3 //3 corredores 
#define elevadores_per_cor 5 //5 elevadores por corredor
#define tot_elevadores (corredores * elevadores_per_cor) // 15 elevadores no total

typedef struct Elevador
{
    char id;
    int andar;
    int corredor;
    int distancia;
}Elevador;

void inicializar (Elevador * elevadores)
{
    for (int i = 0; i < tot_elevadores; i++)
    {
        elevadores[i].id = 'A' + i;
        elevadores[i].andar = i * 20;
        elevadores[i].corredor = i % 3;
        elevadores[i].distancia = 0;
    }
}

void printador(Elevador * elevadores)
{
    char predio [andares][corredores];
    int subtrator = 0;
    for(int i = andares; i >= 0 ; i--)
    {
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

int verificador(int andar, int corredor)
{
    if(andar > 300)
    {
        return 0;
    }
    if(corredor > 2)
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

Elevador * menor_distancia (Elevador * elevadores, int andar, int corredor)
{
    int menor = INT_MAX;
    int distancia;
    Elevador * escolhido;
    for (int i = 0; i < tot_elevadores; i++)
    {
        distancia = abs(andar - elevadores[i].andar) + abs(corredor - elevadores[i].corredor);

        if(distancia < menor)
        {
            menor = distancia;
            escolhido = &elevadores[i];
        }
    }
    escolhido->andar = andar;
    escolhido->corredor = corredor;
    escolhido->distancia = menor;
    return escolhido;
}

Elevador * destino(Elevador * eleva, int index, int andar, int distancia, int novo, int chegou)
{
    char opcao;
    if(eleva[index].andar == andar || chegou == 1)
    {
        chegou = 1;
        if (novo == -1 || eleva[index].andar == novo)
        {
            eleva[index].distancia = distancia;
            eleva[index].andar = andar;
            return eleva;
        }
        else if (eleva[index].andar > novo)
        {
            if(tem_elevador(eleva, eleva[index].andar - 1, eleva[index].corredor))
            {
                eleva[index].corredor = (eleva[index].corredor + 1) % 3;
                distancia ++;
            }
            eleva[index].andar --;
            distancia++;
            printador(eleva);
            printf("Insira algum caractere para prosseguir ");
            scanf(" %c", &opcao);
            destino(eleva, index, andar, distancia, novo, chegou);
        }
        else
        {
            if(tem_elevador(eleva, eleva[index].andar + 1, eleva[index].corredor))
            {
                eleva[index].corredor = (eleva[index].corredor + 1) % 3;
                distancia ++;
            }
            eleva[index].andar ++;
            distancia++;
            printador(eleva);
            printf("Insira algum caractere para prosseguir ");
            scanf(" %c", &opcao);
            destino(eleva, index, andar, distancia, novo, chegou);
        }
    }
    else if (eleva[index].andar > andar)
    {
        if(tem_elevador(eleva, eleva[index].andar - 1, eleva[index].corredor))
        {
            eleva[index].corredor = (eleva[index].corredor + 1) % 3;
            distancia ++;
        }
        eleva[index].andar --;
        distancia++;
        printador(eleva);
        printf ("Tem outro chamado?(S/N) ");
        scanf(" %c", &opcao);
        switch(opcao)
        {
            case 'S':
                printf("Para onde? ");
                scanf("%d", &novo);
                break;
            case 'N':
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
        destino(eleva, index, andar, distancia, novo, chegou);
    }
    else
    {
        if(tem_elevador(eleva, eleva[index].andar + 1, eleva[index].corredor))
        {
            eleva[index].corredor = (eleva[index].corredor + 1) % 3;
            distancia ++;
        }
        eleva[index].andar ++;
        distancia++;
        printador(eleva);
        printf ("Tem outro chamado?(S/N) ");
        scanf(" %c", &opcao);
        switch(opcao)
        {
            case 'S':
                printf("Para onde? ");
                scanf("%d", &novo);
                break;
            case 'N':
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
        destino(eleva, index, andar, distancia, novo, chegou);
    }
}

int main()
{
    Elevador elevadores[tot_elevadores];
    inicializar(elevadores);
    printf("Este é o prédio de 300 andares. Cada letra simboliza um ID de um elevador. Eis o prédio:\n");
    printador(elevadores);
    int andar = 0, corredor = 0;
    while(andar >= 0 && corredor >= 0)
    {
        printf("Selecione o andar e o corredor que desejam chamar um elevador, respectivamente, caso queira finalizar o programa, escreva um dos dois como números negativos: ");
        scanf("%d %d", &andar, &corredor);
        if (andar >= 0 && corredor >= 0)
        {
            if (verificador(andar, corredor))
            {
                printf("Procedimento bem sucedido! O Elevador %c percorreu %d m de distância para atender o chamado! Agora o prédio está assim:\n", menor_distancia(elevadores, andar, corredor)->id, menor_distancia(elevadores, andar, corredor)->distancia);
                int k;
                for(int j = 0; j < tot_elevadores; j++)
                {
                    if(elevadores[j].id == menor_distancia(elevadores, andar, corredor)->id)
                    {
                        k = j;
                        elevadores[j].andar = menor_distancia(elevadores, andar, corredor)->andar;
                        elevadores[j].corredor = menor_distancia(elevadores, andar, corredor)->corredor;
                    }
                }
                printador(elevadores);
                printf("Para que andar deseja ir? ");
                while (tem_elevador(elevadores, andar, corredor))
                {
                    scanf("%d", &andar);
                }
                if (andar >= 0)
                {
                    if (verificador(andar, corredor))
                    {
                        printf("Procedimento bem sucedido! O Elevador %c percorreu %d m de distância para atender o chamado! Agora o prédio está assim:\n", elevadores[k].id, destino(elevadores, k, andar, 0, -1, 0)->distancia);
                        elevadores[k].andar = destino(elevadores, k, andar, 0, -1, 0)->andar;
                        elevadores[k].corredor = destino(elevadores, k, andar, 0, -1, 0)->corredor;
                        printador(elevadores);
                    }
                    else
                    {
                        printf("Algum dos números é inválido. Lembre-se que o prédio tem somente 300 andares(insira apenas um número entre 0 e 300 para o andar) e 3 corredores (insira um número entre 0 e 2 para o corredor). Por favor, tente novamente!\n"); 
                    }
                }
            }
            else 
            {
                printf("Algum dos números é inválido. Lembre-se que o prédio tem somente 300 andares(insira apenas um número entre 0 e 300 para o andar) e 3 corredores (insira um número entre 0 e 2 para o corredor). Por favor, tente novamente!\n");
            }
            printf("Agora, o elevador irá retornar para sua posição inicial:\n");
            inicializar(elevadores);
            printador(elevadores);
        }
    }
    return 0;
}
