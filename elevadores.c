#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define andares 300 //predio de 300 andares
#define corredores 3 //3 corredores 
#define elevadores_per_cor 5 //5 elevadores por corredor
#define tot_elevadores (corredores * elevadores_per_cor) // 15 elevadores no total

typedef enum Estado{
    PARADO,
    SUBINDO,
    DESCENDO
}Estado;

typedef enum Direcao{
    INDO,
    LEVANDO
}Direcao;

typedef struct Elevador
{
    char id;
    int andar;
    int corredor;
    Estado estado;
}Elevador;

typedef struct Chamadas
{
    int andar;
    int destino;
    Elevador * elevador;
    Direcao direcao;
    struct Chamadas * prox;
}Chamadas;

int contador = 0;
int movimento(Direcao * direcao, Elevador ** elevador, int andar, int destino, Elevador todos[]);

void inicializar (Elevador * elevadores)
{
    for (int i = 0; i < tot_elevadores; i++)
    {
        elevadores[i].id = 'A' + i;
        elevadores[i].andar = i * 20;
        elevadores[i].corredor = i % 3;
        elevadores[i].estado = PARADO;
    }
}

void printador(Elevador * elevadores)
{
    int subtrator = 0;
    for(int i = andares; i >= 0 ; i--)
    {
        printf("%d. ", i);
        for(int j = 0; j < corredores; j++)
        {
            for(int k = 0; k < tot_elevadores; k++)
            {
                if(elevadores[k].andar == i && elevadores[k].corredor == j)
                {
                    printf("%c ", elevadores[k].id);
                    subtrator = 1;
                }
            }
            //j += subtrator;
            subtrator = 0;
            if (j == corredores)
            {}
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int verificador(int andar)
{
    if(andar < 0 || andar > andares)
    {
        return 0;
    }
    return 1;
}

void displayElevadores(Elevador * elevadores)
{
    //Display da situação atual dos elevadores
    for (int i = 0; i < tot_elevadores; i++){
        printf("Elevador %c: Andar: %d Corredor: %d Estado: %s\n", elevadores[i].id ,elevadores[i].andar, elevadores[i].corredor+1, elevadores[i].estado == PARADO?"PARADO":"MOVIMENTO");
    }
    puts("");
}

void printa_lista (Chamadas * lista)
{
    Chamadas * aux = lista;
    while (aux != NULL)
    {
        printf("%d %d\n", aux->andar, aux->destino);
        aux = aux->prox;
    }
}

Elevador * menor_distancia (Elevador * elevadores, int andar)
{
    int menor = INT_MAX;
    int distancia;
    int k;
    for (int i = 0; i < tot_elevadores; i++)
    {
        if(elevadores[i].estado == PARADO)
        {
            distancia = abs(andar - elevadores[i].andar);

            if(distancia < menor)
            {
                menor = distancia;
                k = i;
            }
        }
    }
    return elevadores + k;
}

int tem_elevador(Elevador * elevadores, int andar, int corredor)
{
    for (int i = 0; i < tot_elevadores; i++)
    {
        if(elevadores[i].andar == andar && elevadores[i].corredor == corredor)
        {
            return 1;
        }
    }
    return 0;
}

Chamadas * aloca_espaco()
{
    return malloc(sizeof(Chamadas));
}

Chamadas * inserir (Chamadas * lista, Elevador * elevadores, int andar, int destino)
{
    contador++;
    Chamadas * aux = aloca_espaco();
    Chamadas * percorre = lista;
    if (!lista)
    {
        lista = aux;
        lista->andar = andar;
        lista->destino = destino;
        lista->elevador = menor_distancia(elevadores, andar);
        lista->direcao = INDO;
        lista->prox = NULL;
    }
    else
    {
        while(percorre->prox != NULL)
        {
            percorre = percorre->prox;
        }
        aux->andar = andar;
        aux->destino = destino;
        aux->elevador = menor_distancia(elevadores, andar);
        aux->direcao = INDO;
        aux->prox = NULL;
        percorre->prox = aux;
    }
    return lista;
}

Chamadas * inserir_espera (Chamadas * lista, Elevador * elevadores, int andar, int destino)
{
    Chamadas * aux = aloca_espaco();
    Chamadas * percorre = lista;
    if (!lista)
    {
        lista = aux;
        lista->andar = andar;
        lista->destino = destino;
        lista->elevador = NULL;
        lista->direcao = INDO;
        lista->prox = NULL;
    }
    else
    {
        while(percorre->prox != NULL)
        {
            percorre = percorre->prox;
        }
        aux->andar = andar;
        aux->destino = destino;
        aux->elevador = NULL;
        aux->direcao = INDO;
        aux->prox = NULL;
        percorre->prox = aux;
    }
    return lista;
}

Chamadas * remover (Chamadas * lista, Chamadas * alvo)
{
    contador --;
    Chamadas * aux = lista;
    Chamadas * aux2 = NULL;
    if(lista == NULL)
    {
        return NULL;
    }
    else if (lista == alvo)
    {
        lista = lista->prox;
        aux = NULL;
        return lista;
    }
    else
    {
        while(aux->prox != alvo)
        {
            aux = aux->prox;
        }
        aux2 = aux->prox;
        aux->prox = aux->prox->prox;
        free(aux2);
        return lista; 
    }
}

Chamadas * inclusor (Chamadas * lista, Chamadas ** espera, Elevador * elevadores)
{
    contador++;
    Chamadas * aux = lista;
    while(aux->prox)
    {
        aux = aux->prox;
    }
    aux->prox = aloca_espaco();
    aux->prox->andar = (*espera)->andar;
    aux->prox->destino = (*espera)->destino;
    aux->prox->direcao = (*espera)->direcao;
    aux->prox->elevador = menor_distancia(elevadores, (*espera)->andar);
    aux->prox->prox = NULL;

    Chamadas * aux2 = (*espera);
    (*espera) = (*espera)->prox;
    free(aux2);

    return lista;
}

int tem_parado (Elevador * elevadores)
{
    for(int i = 0; i < tot_elevadores; i++)
    {
        if(elevadores[i].estado == PARADO)
        {
            return 1;
        }
    }
    return 0;
}

int caminho_livre(Elevador * elevadores, int andar, int corredor)
{
    int a[] = {0, 1, 2};
    int b[] = {0,0,0};
    for(int i = 0; i < tot_elevadores; i++)
    {
        if(elevadores[i].andar == andar)
        {
            for(int j = 0; j < corredores; j++)
            {
                if(elevadores[i].corredor == a[j])
                {
                    b[j] = 1;
                }
            }
        }
    }
    for(int k = 0; k < 3; k++)
    {
        if(b[k] == 0)
        {
            return k > corredor;
        }
    }
    return -1;
}

void procura_bloqueio(Elevador * elevadores)
{
    int p;
    Direcao temporario = INDO;
    for(int i = 0; i <= andares; i++)
    {
        int contador = 0;
        for(int j = 0; j < corredores; j++)
        {
            for(int k = 0; k < tot_elevadores; k++)
            {
                if(elevadores[k].andar == i && elevadores[k].corredor == j && elevadores[k].estado == PARADO)
                {
                    contador ++;
                    p = k;
                }
            }
        }
        if(contador == 3) 
        {
            if(elevadores[p].andar >= andares/2)
            {
                Elevador * aux = &(elevadores[p]); 
                movimento(&temporario, &(aux), ((*(elevadores + p)).andar) - 2, -1, elevadores);
                movimento(&temporario, &(aux), ((*(elevadores + p)).andar) - 2, -1, elevadores);
            }
            else
            {
                Elevador * aux = &(elevadores[p]); 
                movimento(&temporario, &(aux), ((*(elevadores + p)).andar) + 2, -1, elevadores);
                movimento(&temporario, &(aux), ((*(elevadores + p)).andar) + 2, -1, elevadores);
            }
            elevadores[p].estado = PARADO;
        }
    }
}

int movimento(Direcao * direcao, Elevador ** elevador, int andar, int destino, Elevador todos[])
{
    if(*direcao == INDO)
    {
        if((*elevador)->andar == andar)
        {
            *direcao = LEVANDO;
            printf("\nO elevador %c chegou no andar %d!\n\n", (*elevador)->id, (*elevador)->andar);
        }
        else if((*elevador)->andar > andar)
        {
            if(tem_elevador(todos, ((*elevador)->andar - 1), (*elevador)->corredor) && (*elevador)->estado == DESCENDO)
            {
                if(caminho_livre(todos, (*elevador)->andar - 1, (*elevador)->corredor))
                {
                    (*elevador)->corredor++;
                }
                else
                {
                    (*elevador)->corredor--;
                }
                return 0;
            }
            (*elevador)->andar --;
            (*elevador)->estado = DESCENDO;
        }
        else if ((*elevador)->andar < andar)
        {
            if(tem_elevador(todos, ((*elevador)->andar + 1), (*elevador)->corredor) && (*elevador)->estado == SUBINDO)
            {
                if(caminho_livre(todos, (*elevador)->andar + 1, (*elevador)->corredor))
                {
                    (*elevador)->corredor++;
                }
                else
                {
                    (*elevador)->corredor--;
                }
                return 0;
            }
            (*elevador)->andar ++;
            (*elevador)->estado = SUBINDO;
        }
    }
    else if(*direcao == LEVANDO)
    {
        if((*elevador)->andar == destino)
        {
            (*elevador)->estado = PARADO;
            printf("\nO elevador %c chegou ao seu destino no andar %d!\n\n", (*elevador)->id, (*elevador)->andar);
            return 1;
        }
        else if((*elevador)->andar > destino)
        {
            if(tem_elevador(todos, ((*elevador)->andar - 1), (*elevador)->corredor) && (*elevador)->estado == DESCENDO)
            {
                if(caminho_livre(todos, (*elevador)->andar - 1, (*elevador)->corredor))
                {
                    (*elevador)->corredor++;
                }
                else
                {
                    (*elevador)->corredor--;
                }
                return 0;
            }
            (*elevador)->andar --;
            (*elevador)->estado = DESCENDO;
        }
        else if((*elevador)->andar < destino)
        {
            if(tem_elevador(todos, ((*elevador)->andar + 1), (*elevador)->corredor) && (*elevador)->estado == SUBINDO)
            {
                if(caminho_livre(todos, (*elevador)->andar + 1, (*elevador)->corredor))
                {
                    (*elevador)->corredor++;
                }
                else
                {
                    (*elevador)->corredor--;
                }
                return 0;
            }
            (*elevador)->andar ++;
            (*elevador)->estado = SUBINDO;
        }
        
    }
    return 0;
}

Chamadas * conferidor_lista (Elevador * elevadores, Chamadas * lista)
{
    Chamadas * percorre = lista;
    Chamadas * aux = NULL;
    procura_bloqueio(elevadores);
    if(lista == NULL)
    {
        return NULL;
    }
    else 
    {
        while (percorre != NULL)
        {
            if (movimento(&(percorre->direcao), &(percorre->elevador), percorre->andar, percorre->destino, elevadores))
            {
                lista = remover(lista, percorre);
            }
            percorre = percorre->prox;
        }
    }
    return lista;
}

int tamanho (Chamadas * lista)
{
    Chamadas * aux = lista;
    int i = 0;
    while (aux)
    {
        i++;
        aux = aux->prox;
    }
    return i;
}

void entrada(Elevador * elevadores)
{
    char opcao;
    Chamadas * lista = NULL;
    Chamadas * espera = NULL;
    while (1)
    {
        printf("Tem chamado?(S/P/Outra letra) ");
        scanf(" %c", &opcao);
        int andar = -1, destino = -1;
        switch(opcao)
        {
            case 'S':
            {   
                while(!verificador(andar) || !verificador(destino))
                {
                    printf("Em qual andar o elevador está sendo chamado e qual o destino? (0 a 300) ");
                    scanf("%d %d", &andar, &destino);
                }
                if (espera != NULL && tamanho(lista) < tot_elevadores)
                {
                    lista = inclusor(lista, &espera, elevadores);
                    espera = inserir_espera(espera, elevadores, andar, destino);
                }
                else if(tamanho(lista) < tot_elevadores)
                {
                    lista = inserir(lista, elevadores, andar, destino);
                }
                else 
                {
                    espera = inserir_espera(espera, elevadores, andar, destino);
                }
                lista = conferidor_lista(elevadores, lista);
                displayElevadores(elevadores);
                break;
            }
            case 'P':
            {
                lista = conferidor_lista(elevadores, lista);
                printador(elevadores);
                break;
            }
            case 'L':
                printa_lista(lista);
                break;
            case 'E':
                printa_lista(espera);
                break;
            default:
            {
                if (espera != NULL && tamanho(lista) < tot_elevadores)
                {
                    lista = inclusor(lista, &espera, elevadores);
                }
                lista = conferidor_lista(elevadores, lista);
                displayElevadores(elevadores);
                break;
            }
        }
    }
}

int main()
{
    Elevador elevadores[tot_elevadores];
    inicializar(elevadores);
    printf("Este é o prédio de 300 andares. Cada letra simboliza um ID de um elevador. Eis o prédio:\n");
    printador(elevadores);
    entrada(elevadores);
    return 0;
}
