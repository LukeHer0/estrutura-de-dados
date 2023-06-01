#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int chave;
    struct No * esq;
    struct No * dir;
}No;

No * initialize()
{
    return malloc(sizeof(No));
}

No * inserir (No * tree, int chave)
{
    if (tree == NULL)
    {
        tree = initialize();
        tree->chave = chave;
        tree->esq = NULL;
        tree->dir = NULL;
        return tree;
    }
    else 
    {
        if (chave > tree->chave)
        {
            tree->dir = inserir(tree->dir, chave);
        }
        else if (chave < tree->chave)
        {
            tree->esq = inserir(tree->esq, chave);
        }
        return tree;
    }
}

No * busca (No * tree, int chave)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree->chave == chave)
    {
        return tree;
    }
    else if(chave > tree->chave)
    {
        busca(tree->dir, chave);
    }
    else if (chave < tree->chave)
    {
        busca(tree->esq, chave);
    }
}

int contagem (No * tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    return contagem(tree->esq) + 1 + contagem(tree->dir);
    }

void printador(No * tree)
{
    if(tree != NULL)
    {
        printf("%d", tree->chave);
        printf("(");
        printador(tree->esq);
        printador(tree->dir);
        printf(")");
    }
}

No * busca_aux (No * raiz, int chave, No ** pai)
{
    No * atual = raiz;
    *pai = NULL;
    while(atual)
    {
        if (atual->chave == chave)
        {
            return (atual);
        }
        *pai = atual;
        if(chave < atual->chave)
        {
            atual = atual->esq;
        }
        else 
        {
            atual = atual->dir;
        }
    }
    return (NULL);
}

No * remover (No * tree, int chave)
{
    No * pai;
    No * no; 
    No * p;
    No * q;
    no = busca_aux(tree, chave, &pai);
    if(no == NULL)
    {
        return tree;
    }
    if (!no->esq || !no->dir)
    {
        if(!no->esq)
        {
            q = no->dir;
        }
        else 
        {
            q = no->esq;
        }
    }
    else
    {
        p = no;
        q = no->esq;
        while (q->dir)
        {
            p = q;
            q = q->dir;
        }
        if (p != no)
        {
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }
    if (!pai)
    {
        free(no);
        return q;
    }
    if (chave < pai->chave)
    {
        pai->esq = q;
    }
    else 
    {
        pai->dir = q;
    }
    free(no);
    return tree;
}

int main()
{
    No * tree = NULL;
    int i = 0;
    int chave;
    int opcao;
    while(1)
    {
        printf("O que deseja fazer?\n\t0 - Inserir\n\t1 - Buscar\n\t2 - Contagem\n\t3 - Remover\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 0:
            {
                printf("Insira um nó: ");
                scanf("%d", &chave);
                tree = inserir(tree, chave);
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
            case 2:
            {
                printf("A árvore possui %d nós!\n", contagem(tree));
                break;
            }
            case 3:
            {
                printf("Qual nó você deseja remover? ");
                scanf("%d", &chave);
                remover(tree, chave);
                printador(tree);
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
