#include <stdio.h>

#define MAX_SIZE 9

void troca(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void bin (int *vetor, int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        while(vetor[i] != i)
        {
            troca(&vetor[i], &vetor[vetor[i]]);
        }
    }
}

int main()
{
    int vetor[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        scanf("%d", &vetor[i]);
    }
    bin(vetor, MAX_SIZE);
    for (int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    return 0;
}
