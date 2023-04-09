#include <stdio.h>

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
    int vetor[6];
    for (int i = 0; i < 6; i++)
    {
        scanf("%d", &vetor[i]);
    }
    bubble(vetor, 6);
    for (int j = 0; j < 6; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
