#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore
{
    int chave;
    struct Arvore *esq;
    struct Arvore *dir;
}Arvore;

Arvore *aloca_memoria()
{
    return malloc(sizeof(Arvore));
}

int teste(Arvore *no)
{
    if(no->esq == NULL && no->dir == NULL)
    {
        return 1;
    }
    else
    {
        return 0;    
    }
}

Arvore *inserir(Arvore *no, int num)
{
    if (no == NULL)
    {
        no = aloca_memoria();
        no->chave = num;
        no->esq = NULL;
        no->dir = NULL;
        return no;
    }
    else 
    {
        if (num < no->chave)
        {
            no->esq = inserir(no->esq, num);
        }
        else
        {
            no->dir = inserir(no->dir, num);
        }
        return no;
    }
}

void display(Arvore *no)
{
    if(no)
    {
        printf("%d(", no->chave);
        display(no->esq);
        display(no->dir);
        printf(")");
    }
    
}

void loopscan(Arvore *no)
{
  int num;
  scanf("%d", &num);
  if (num == -10)
  {
        display(no);
        return;
  }
  else
  {
      no = inserir (no, num);
      loopscan(no);
  }
}

int main()
{
  Arvore *no = NULL;
  loopscan(no);
  return 0;
}
