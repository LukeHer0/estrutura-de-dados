#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 6

void selection(int *vetor, int tamanho)
{
    int menor = INT_MAX;
    int k;
    for(int i = 0; i < tamanho; i++)
    {
        for(int j = i; j < tamanho; j++)
        {
            if(vetor[j] < menor)
            {
                menor = vetor[j];
                k = j;
            }
        }
        vetor[k] = vetor[i];
        vetor[i] = menor;
        menor = INT_MAX;
    }
}

int main()
{
    int vetor[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        scanf("%d", &vetor[i]);
    }
    selection(vetor, MAX_SIZE);
    for(int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
