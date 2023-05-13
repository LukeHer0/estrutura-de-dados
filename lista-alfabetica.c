#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define NAME_SIZE 40
#define QUEUE 104

void valorando(char fila[][NAME_SIZE])
{
    for (int i = 0; i < QUEUE; i++)
    {
        fila[i][0] = '\0';
    }
    return;
}

void printa_fila(char fila[][NAME_SIZE])
{
    for (int i = 0; i < QUEUE; i++)
    {
        printf("%d. ", (i + 1));
        for(int j = 0; fila[i][j] != '\0'; j++)
        {
            printf("%c", fila[i][j]);
        }
        printf("\n");
    }
}

void printa_sem_gap(char fila[][NAME_SIZE])
{
    for (int i = 0; i < QUEUE; i++)
    {
        if(fila[i][0] != '\0')
        {
            printf(" %d. ", (i + 1));
        }
        for(int j = 0; fila[i][j] != '\0'; j++)
        {
            if(fila[i][0] != '\0')
            {
                printf("%c", fila[i][j]);
            }
        }
    }
    printf("\n");
}

int verificacao(char * nome)
{
    if(nome[0] == ' ')
    {
        return 0;
    }
    for (int i = 0; nome[i] != '\0'; i++)
    {
        if ((nome[i] < 'A' || nome[i] > 'Z') && nome[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

void deletar(char fila[][NAME_SIZE])
{
    int posicao;
    printf("Em que posição está o nome que você quer deletar? ");
    scanf(" %d", &posicao);
    posicao -= 1;
    if (fila[posicao][0] != '\0')
    {
        printf("%s foi deletadx!\n", fila[posicao]);
        strcpy(fila[posicao], fila[posicao + 1]);
        strcpy(fila[posicao + 1], "\0");
    }
    else
    {
        printf("Não há nenhum nome nessa posição!\n");
    }
}

int tem_gap(char fila[][NAME_SIZE])
{
    for (int i = 0; i < QUEUE; i++)
    {
        if(fila[i][0] == '\0')
        {
            return 1;
        }
    }
    return 0;
}

int comparalfa(char * nome, char * word)
{
    for (int i = 0; i < strlen(nome); i++)
    {
        if (nome[i] < word[i])
        {
            return 0;
        }
        else if (nome[i] > word[i])
        {
            return 1;
        }
    }
    return 0;
}

int procura_gap (char fila[][NAME_SIZE])
{
    for(int i = QUEUE; i >= 0; i--)
    {
        if (fila[i][0] == '\0')
        {
            return i;
        }
    }
}

void puxa_cima(char fila[][NAME_SIZE], int posicao)
{
    char aux[NAME_SIZE];
    for(int i = posicao; i < QUEUE; i++)
    {
        strcpy(aux, fila[i]);
        strcpy(fila[i], fila[i + 1]);
        strcpy(fila[i + 1], aux);
    }
}

void inserir(char fila[][NAME_SIZE], char * nome, int lugar)
{
    char aux[NAME_SIZE];
    int posicao = ((nome[0] - 'A') * (QUEUE / ALPHABET_SIZE)) + lugar;
    if (verificacao(nome))
    {
        if(!tem_gap(fila))
        {
            printf("A lista está cheia!\n");
        }
        else if(fila[posicao][0] == '\0')
        {
            strcpy(fila[posicao], nome);
        }
        
        else if (comparalfa(nome, fila[posicao]) && posicao < (QUEUE - 1))
        {
            inserir(fila, nome, lugar + 1);
        }
        else if (!comparalfa(nome, fila[posicao]) && posicao < (QUEUE - 1))
        {
            strcpy(aux, fila[posicao]);
            strcpy(fila[posicao], nome);
            strcpy(nome, aux);
            inserir(fila, nome, lugar + 1);
        }
        else if (comparalfa(nome, fila[posicao]))
        {
            puxa_cima(fila, procura_gap(fila));
            inserir(fila, nome, lugar);
        }
        else 
        {
            strcpy(fila[procura_gap(fila)], nome);
        }
    }
    else 
    {
        printf("Nome inválido. Por favor, use apenas letras maiúsculas e não dê espaço antes da primeira letra!\n");
    }
    return;
}

int main()
{
    printf("Inserir nomes apenas com letras maiúsculas!\n");
    char fila[QUEUE][NAME_SIZE];
    valorando(fila); //representando os espaços por "\0"
    int opcao = 3;
    while(opcao != 0)
    {
        char nome[NAME_SIZE];
        printf("Selecione uma opção:\n\t0 - Finalizar e mostrar a lista\n\t1- Inserir\n\t2- Deletar\n\t3- Mostrar a lista sem gap\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            printa_fila(fila);
            return 0;
            break;
        case 1:
            scanf(" %[^\n]", nome);
            inserir(fila, nome, 0);
            printa_fila(fila);
            break;
        case 2:
            deletar(fila);
            printa_fila(fila);
            break;
        case 3:
            printa_sem_gap(fila);
            break;
        default:
            printf("Número inválido!\n");
            break;
        }
    }
    return 0;
}
