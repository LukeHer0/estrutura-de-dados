#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void leitura (int conjunto[], char nome);
void interseccionar (int a[], int b[]);
void complementar (int a[], int b[]);
void unir (int a[], int b[]);

int main()
{
    int conjuntoa[10], conjuntob[10];
    printf ("(Caso deseje ter menos de 10 elementos, favor colocar o elemento -1000 para partir para o próximo passo)\n");
    leitura (conjuntoa, 'a');
    leitura (conjuntob, 'b');
    int uniao [20];
    printf ("União: ");
    unir (conjuntoa, conjuntob);
    printf ("Intersecção: ");
    interseccionar (conjuntoa, conjuntob);
    printf ("Complemento: ");
    complementar (conjuntoa, conjuntob);
    return 0;
}

void leitura (int conjunto[], char nome)
{
    int i;
    printf ("escreva o conjunto %c: ", nome);
    for (i = 0; i < 10; i++)
    {
        scanf ("%d", &conjunto[i]);
        if (conjunto[i] == -1000)
        {
            for (;i < 10; i++)
            {
                conjunto[i] = -1000;
            }
        }
    }
}

void unir (int a[], int b[])
{
    int i, j;
    int uniao[20];
    for (i = 0; i < 10; i++)
    {
        uniao[i] = a[i];
    }
    for (i = 0; i < 10; i++)
    {
        uniao[10 + i] = b[i];
    }
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (uniao[i] == uniao[j] && j != i)
            {
                uniao[i] = -1000;
            }
        }
        if (uniao[i] != -1000)
        {
            printf ("%d ", uniao[i]);
        }
    }
    printf ("\n");
}

void interseccionar (int a[], int b[])
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j= 0; j < 10; j++)
        {
            if (a[i] == b[j] && a[i] != -1000)
            {
                printf ("%d ", a[i]);
            } 
        }
    }
    printf ("\n");
}

void complementar (int a[], int b[])
{
    int i, j;
    for (j = 0; j < 10; j++)
    {
        if (b[j] == -1000)
        {
            break;
        } 
        for (i = 0; i < 10; i++)
        {
            if (b[j] == a[i])
            {
                break;
            }
            else if (a[i] == -1000)
            {
                printf ("%d ", b[j]);
                break;
            }
        }
    }
    printf ("\n");
}
