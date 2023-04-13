#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 6

void selection(int *vetor, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        int menor = i;
        for(int j = i; j < tamanho; j++)
        {
            if(vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }
        int t = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = t;
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
