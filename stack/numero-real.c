#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64

typedef struct Stack{
    int topo;
    char itens[MAX_SIZE];
}Stack;

Stack * novo_no (Stack * no)
{
    return malloc(sizeof(Stack));
}

void empilha (Stack * pilha, char numero)
{
    pilha->topo ++;
    pilha->itens[pilha->topo] = numero;
    return;
}

char desempilha (Stack * pilha)
{
    char aux = pilha->itens[pilha->topo];
    pilha->topo --;
    return aux;
}

void printa_pilha (Stack * pilha, int tamanho)
{
    for (tamanho; tamanho >= 0; tamanho--)
    {
        printf("%c", pilha->itens[tamanho]);
    }
    printf("\n");
}

/*Stack * second_ordenation(Stack * pilha, int tamanho)
{
    Stack * aux = novo_no(aux);
    aux->topo = -1;
    if (tamanho < 0)
    {
        return aux;
    }
    for(char i = '9'; i >= '0'; i--)
    {
        if (pilha->itens[pilha->topo] == i)
        {
            empilha(aux, desempilha(pilha));
            second_ordenation(pilha, tamanho - 1);
            break;
        }
    }
}*/

Stack * ordenacao (Stack * pilha, int tamanho)
{
    for (int j = tamanho; j > 0; j--)
    {
        for(int i = tamanho; i > 0; i--)
        {
            if(pilha->itens[i] < pilha->itens[i-1])
            {
                char t = pilha->itens[i];
                pilha->itens[i] = pilha->itens[i-1];
                pilha->itens[i-1] = t;
            }
        }
    }
    return pilha;
}

void novo_numero (char * numero, int k, int w)
{
    Stack * fracionaria = novo_no(fracionaria);
    Stack * inteira = novo_no(inteira);
    fracionaria->topo = -1;
    inteira->topo = -1;
    int j = (strlen(numero) - 1); //j = posição do último número no array
    while (numero[j] != '.' && numero[j] != ',')
    {
        empilha(fracionaria, numero[j]);
        j--;
    }
    if (k >= j)
    {
        printf ("K inválido!\n");
        return;
    }
    if (w >(fracionaria->topo))
    {
        printf ("W inválido!\n");
        return;
    }
    fracionaria = ordenacao(fracionaria, fracionaria->topo);
    empilha(fracionaria, numero[j]); //empilhando a vírgula
    j--;

    //Lidando com a parte inteira:

    while(j >= 0)
    {
        empilha(inteira, numero[j]); //empilhando o primeiro número pré vírgula
        j--;
    }
    inteira = ordenacao(inteira, inteira->topo);
    
    while((inteira->topo - k) >= 0)
    {
        printf("%c", desempilha(inteira));
    }
    while((fracionaria->topo - w) >= 0)
    {
        printf("%c", desempilha(fracionaria));
    }
    printf("\n");
}

int verificacao(char * numero, int tamanho)
{
    int cont = 0;
    for(int i = 0; i < tamanho; i++)
    {
        if(numero[i] < '0' || numero[i] > '9')
        {
            if (numero[i] != '.' && numero[i] != ',')
            {
                return 0;
            }
            else
            {
                cont ++;
            }
        }
    }
    if (cont != 1)
    {
        return 0;
    }
    return 1;
}

int main()
{
    char numero[MAX_SIZE];
    int k, w;
    printf ("Insira um número real com parte inteira e parte fracionária: ");
    scanf ("%s", numero);
    if(!verificacao(numero, strlen(numero)))
    {
        printf("Número inválido!\n");
        return 0;
    }
    printf ("Insira dois número K e W: \n");
    scanf ("%d %d", &k, &w);
    novo_numero(numero, k, w);
}
