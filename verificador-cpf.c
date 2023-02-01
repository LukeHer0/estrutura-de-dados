#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int soma_dos_digitos (char cpf[], int i, int j, int verificar);
int calculo_resto (char cpf[], int digitao);
int soma_dos_digitos2 (char cpf[], int i, int j, int verificar);
int calculo_resto2 (char cpf[], int digitao);

int main()
{
    char cpf[11];
    printf ("Por favor, escreva seu CPF (use apenas números):\n");
    scanf ("%[^\n]", cpf);
    if (soma_dos_digitos (cpf, 0, 10, 0) && soma_dos_digitos2 (cpf, 0, 11, 0))
    {
        printf ("Seu CPF está correto\n");
    }
    else
    {
        printf ("Seu CPF está incorreto\n");
    }
    return 0;
}

int soma_dos_digitos (char cpf[], int i, int j, int verificar)
{
    if (i == 9)
    {
        return calculo_resto(cpf, verificar);
    }
    else
    {
        verificar += (cpf[i] - 48) * j;
        return soma_dos_digitos (cpf, i + 1, j - 1, verificar);
    }
}

int calculo_resto (char cpf[], int digitao)
{
    if ((11 - (digitao % 11)) >= 10)
    {
        if ((cpf[9] - 48) != 0)
        {
            return 0;
        }
        return 1;
    }
    else if ((cpf[9] - 48) != (11 - (digitao % 11)))
    {
        return 0;
    }
    return 1;
}

int soma_dos_digitos2 (char cpf[], int i, int j, int verificar)
{
    if (i == 10)
    {
        return calculo_resto2(cpf, verificar);
    }
    else
    {
        verificar += (cpf[i] - 48) * j;
        return soma_dos_digitos2 (cpf, i + 1, j - 1, verificar);
    }
}

int calculo_resto2 (char cpf[], int digitao)
{
    if ((11 - (digitao % 11)) >= 10)
    {
        if ((cpf[10] - 48) != 0)
        {
            return 0;
        }
        return 1;
    }
    else if ((cpf[10] - 48) != (11 - (digitao % 11)))
    {
        return 0;
    }
    return 1;
}
