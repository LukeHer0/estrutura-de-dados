#include <stdio.h>

#define MAX_SIZE 10

void shellsort (int * vetor, int tamanho)
{
    int i, j, h, aux;
    h = 1;
    while(h < tamanho/3)
    {
        h = 3 * h + 1;
    }
    while(h > 0)
    {
        for (int i = h; i < tamanho; i++)
        {
            aux = vetor[i];
            j = i;

            while (j >= h && aux < vetor[j - h])
            {
                vetor[j] = vetor[j - h];
                j = j - h;
            }
            vetor[j] = aux;
        }
        h = (h - 1)/3;
    }
}

int main()
{
    int vetor[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        scanf("%d", &vetor[i]);
    }
    shellsort(vetor, MAX_SIZE);
    for (int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
