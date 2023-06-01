#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int chave;
    No * son;
    No * bro;
}No;

No * novoNo (int chave)
{
    No * novo = (No*)malloc(sizeof(No));
    novo->son = NULL;
    novo->bro = NULL;
    novo->chave = chave;
    return novo;
}

No * inicializa (int chave)
{
    return novoNo(chave);
}

void printador (No * tree)
{
    if(tree == NULL)
    {
        return;
    }
    printf("%d(", tree->chave);
    No * p = tree->son;
    while (p)
    {
        printador(p);
        p = p->bro;
    }
    printf(")");
}

int inserir (No * tree, int chave, int pai)
{
    No * father = busca(pai, tree);
    if(!father)
    {
        return 0;
    }
    No * filho = novoNo(chave);
    No * p = father->son;
    if(!p)
    {
        father->son = filho;
    }
    else 
    {
        while(p->bro)
        {
            p = p->bro;
            p->bro = filho;
        }
    }
    return 1;
}

No * busca (No * tree, int chave)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if(tree->chave == chave)
    {
        return tree;
    }
    No * p = tree->son;
    while (p)
    {
        No * resp = busca(chave, p);
        if(resp)
        {
            return resp;
        }
        p = p->bro;
    }
    return NULL;
}

int main()
{
    No * tree;
    int chave, opcao, pai;
    printf("Insira o primeiro elemento da árvore: ");
    scanf("%d", &chave);
    tree = inicializa(chave);
    while (1)
    {
        printf("O que deseja fazer?\n\t0 - Inserir\n\t1 - Buscar\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 0:
            {
                printf("Insira um nó: ");
                scanf("%d", &chave);
                printf("Filho de quem? ");
                scanf("%d", &pai);
                tree = inserir(tree, chave, pai);
                printador(tree);
                printf("\n");
                break;
            }
            case 1:
            {
                printf("Qual chave você gostaria de fazer a busca? ");
                scanf("%d", &chave);
                printador(busca(tree, chave));
                printf("\n");
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return 0;
}
