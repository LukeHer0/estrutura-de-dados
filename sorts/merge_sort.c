#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 10

void merge(int * vetor, int inicio, int meio, int fim)
{
    int * temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int *) malloc(tamanho * sizeof(int));
    if(temp != NULL)
    {
        for(i = 0; i < tamanho; i++)
        {
            if(!fim1 && !fim2)
            {
                if(vetor[p1] < vetor[p2])
                {
                    temp[i] = vetor[p1++];
                }
                else
                {
                    temp[i] = vetor[p2++];
                }
                if(p1 > meio)
                {
                    fim1 = 1;
                }
                if (p2 > fim)
                {
                    fim2 = 1;
                }
            }
            else
            {
                if(!fim1)
                {
                    temp[i] = vetor[p1++];
                }
                else
                {
                    temp[i] = vetor[p2++];
                }
            }
        }
        for(j = 0, k = inicio; j <tamanho; j++, k++)
        {
            vetor[k] = temp[j];
        }
    }
    free(temp);
}

void mergesort (int * vetor, int inicio, int fim)
{
    int meio;
    if (inicio < fim)
    {
        meio = floor((inicio + fim)/2);
        mergesort(vetor, inicio, meio);
        mergesort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

int main()
{
     int vetor[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        scanf("%d", &vetor[i]);
    }
    mergesort(vetor, 0, MAX_SIZE - 1);
    for (int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
