#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int tem_espaco (char numero[]);
int real (char numero[]);
int inteiro (char numero[]);
int natural (char numero[]);

int main()
{
    char numero[20];
    printf ("Por favor, digite um número:\n");
    fgets (numero, 50, stdin);
    if (numero[0] == '\n' || numero[0] == ' ' || numero[0] == '/')
    {
        printf ("Por favor, digite um número\n");
        return 0;
    }
    if (tem_espaco(numero))
    {
        printf ("Por favor, digite apenas um número!\n");
    }
    else if (real(numero))
    {
        printf ("Real\n");
    }
    else if (inteiro(numero))
    {
        printf ("Inteiro\n");
    }
    else if (natural(numero))
    {
        printf ("Natural\n");
    }
    else 
    {
        printf ("Erro: tipo não identificado\n");
    }
    return 0;
}

int tem_espaco (char numero[])
{
    int i;
    for (i = 0; i < strlen(numero) - 1; i++)
    {
        if (numero[i] == ' ')
        {
            return 1;
        }
    }
    return 0;
}

int real (char numero[]) //não inclui frações
{
    int i, numerador, denominador;
    for (i = 0; i < strlen(numero) - 1; i++)
    {
        if (numero[i] == '.')
        {
            return 1;
        }
    }
    return 0;
}

int inteiro (char numero[])
{
    if (numero[0] == '-')
    {
        return 1;
    }
    return 0;
}

int natural (char numero[])
{
    int i;
    for (i = 0; i < strlen(numero) - 1; i++)
    {
        if (numero[i] < '0' || numero[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}
