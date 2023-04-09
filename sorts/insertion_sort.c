#include <stdio.h>

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
    int vetor[6];
    for (int i = 0; i < 6; i++)
    {
        scanf("%d", &vetor[i]);
    }
    insertion(vetor, 6);
    for (int j = 0; j < 6; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
