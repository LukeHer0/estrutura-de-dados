#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int so_letras (char nome[]);
int maiusculo (char nome[]);
int caractere (char nome[]);

int main()
{
    char nome[50];
    printf ("Por favor, escreva seu nome seguindo as seguintes regras:\n-Use apenas letras\n-Seu nome deve ter no mínimo 1 caractere\n-A primeira letra do seu nome deve iniciar com letra maiúscula\n");
    fgets (nome, 50, stdin);
    if (!so_letras(nome) && !caractere(nome) && !maiusculo (nome))
    {
        printf ("Parabéns, seu nome é válido!\n");
    }
    return 0;
}

int so_letras (char nome[])
{
    int i;
    for (i = 0; i < (strlen(nome) - 1); i++)
    {
        if ((nome[i] >= 65 && nome[i] <= 90) || (nome[i] >= 97 && nome[i] <= 122) || (nome[i] == 32))
        {}
        else 
        {
            printf ("Apenas letras, espertinhe!\n");
            return 1;
        }
    }
    return 0;
}

int maiusculo (char nome[])
{
    if (nome[0] < 65 || nome[0] > 90)
    {
        printf ("Por favor, inicie seu nome com letra maiúscula!\n");
        return 1;
    }
    return 0;
}

int caractere (char nome[])
{
    if (nome[0] == '\n')
    {
        printf ("Seu nome tem que ter ao menos 1 caractere!\n");
        return 1;
    }
    return 0;
}
