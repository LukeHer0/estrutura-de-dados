#include <stdio.h>

#define MAX_SIZE 6

void bubble(int *vetor, int tamanho)
{
    for (int j = 0; j < tamanho; j++)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (vetor[i] > vetor[i + 1])
            {
                int t = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = t;
            }
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
    bubble(vetor, MAX_SIZE);
    for (int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
