#include <stdio.h>

#define MAX_SIZE 6

void insertion (int *vetor, int tamanho)
{
    for (int j = 1; j < tamanho; j++)
    {
        int k = vetor[j];
        int i = j - 1;

        while (i >= 0 && vetor[i] > k)
        {
            vetor[i + 1] = vetor[i];
            i = i - 1;
        }
        vetor[i + 1] = k;
    }
}

int main()
{
    int vetor[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        scanf("%d", &vetor[i]);
    }
    insertion(vetor, MAX_SIZE);
    for (int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
