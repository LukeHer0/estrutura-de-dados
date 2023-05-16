#include <stdio.h>

#define MAX_SIZE 10

int particiona(int * vetor, int inicio, int fim)
{
    int esquerda, direita, pivot, aux;
    esquerda = inicio;
    direita = fim;
    pivot = vetor[inicio];
    while (esquerda < direita)
    {
        while(vetor[esquerda] <= pivot)
        {
            esquerda ++;
        }
        while(vetor[direita] > pivot)
        {
            direita --;
        }
        if(esquerda < direita)
        {
            aux = vetor[esquerda];
            vetor[esquerda] = vetor[direita];
            vetor[direita] = aux;
        }
    }
    vetor[inicio] = vetor[direita];
    vetor[direita] = pivot;
    return direita;
}

void quicksort(int * vetor, int inicio, int fim)
{
    int pivot;
    if (fim > inicio)
    {
        pivot = particiona(vetor, inicio, fim);
        quicksort(vetor, inicio, pivot - 1);
        quicksort (vetor, pivot + 1, fim);
    }
}

int main ()
{
    int vetor[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        scanf("%d", &vetor[i]);
    }
    quicksort(vetor, 0, MAX_SIZE);
    for (int j = 0; j < MAX_SIZE; j++)
    {
        printf("%d ", vetor[j]);
    }
    printf("\n");
    return 0;
}
