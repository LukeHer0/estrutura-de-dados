#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int leitura (int lista[])
{
    int i;
    int cont = 0;
    for (i = 0; i < 4; i++)
    {
        scanf ("%d", &lista[i]);
        if (lista[i] == -1000)
        {
            break;
        }
        cont += 1;
    }
    return cont;
}

void inicio (int lista[], int tamanho)
{
    int i;
    for (i = (tamanho - 1); i >= 0; i--)
    {
        lista[i + 1] = lista[i];
    }
    scanf ("%d", &lista[0]);
}

void final (int lista[], int tamanho)
{
    scanf("%d", &lista[tamanho]);
}

void printar (int lista[], int tamanho)
{
    for (int i = 0; i <= tamanho; i++)
    {
        printf ("%d\n", lista[i]);
    }
}

void bubblesort(int lista[], int tamanho)
{
    int x;
    for (int i = 0; i <= tamanho; i++)
    {
        for (int j = 0; j <= tamanho; j++)
        if (lista[i] < lista[j])
        {
            x = lista[i];
            lista[i] = lista[j];
            lista[j] = x;
        }
    }
}

int main()
{
    int lista[5];
    printf ("Insira 4 números para sua lista, caso queira menos, insira -1000\n");
    int tamanho = leitura(lista);
    printf ("Aonde você quer inserir o número?\n");
    printf ("a. Início\n");
    printf ("b. Inserir e ordenar a lista\n");
    printf ("c. Final\n");
    char opcao;
    scanf (" %c", &opcao);
    switch(opcao)
    {
        case 'a':
            inicio(lista, tamanho);
            break;
        case 'b':
            final(lista, tamanho);
            bubblesort(lista, tamanho);
            break;
        case 'c':
            final(lista, tamanho);
            break;
        default:
            break;
    }
    printf("\n");
    printar (lista, tamanho);
    return 0;
}
