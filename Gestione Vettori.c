#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUM 50

void VisualizzaArray(int array[],int numArray)
{
    printf("Elementi dell'array:\n");
    for(int i=0;i<numArray;i++)
    {
        printf("%d\n",array[i]);
        
    }
    
}

void InvertiArray(int array[],int numArray)
{
    printf("Array Invertito:\n");
    for(int i=numArray-1;i>=0;i--)
    {
        printf("%d\n",array[i]);
    }
}
void SommaMedia(int array[],int numArray)
{
    int somma=0;
    for(int i=0;i<numArray;i++)
    {
        somma=somma+array[i];
    }
    float media=(float) somma/numArray;
    printf("Somma: %d\n", somma);      // Stampa la somma
    printf("Media: %.2f\n", media); //stampa la media
}
void StampaPari(int array[],int numArray)
{
    printf("Numeri pari nell'array\n");
    for(int i=0;i<numArray;i++)
    {
        if(array[i]%2==0)
        {
            printf("%d\n",array[i]);
        }
    }
}
void StampaDispari(int array[],int numArray)
{
    printf("Numeri dispari nell'array\n");
    for(int i=0;i<numArray;i++)
    {
        if(array[i]%2 != 0)
        {
            printf("%d\n",array[i]);
        }
    }
}
int cercaNumero(int array[],int numArray)
{
    int numero;
    printf("Inserisci il numero da cercare\n");
    scanf("%d",&numero);
    int trovato=0;
    for(int i=0;i<numArray;i++)
    {
        if(array[i]==numero)
        {
            printf("Numero trovato in posizione %d\n", i);
            trovato=1;
            return i;
        }
    }
    if(!trovato) //numero non trovato
    {
         printf("Numero non trovato.\n"); 
    }
    return -1;
}
void EliminaNumero(int array[],int *numArray)
{
    int indiceEliminato;
    indiceEliminato=cercaNumero(array,*numArray);
    if(indiceEliminato!=-1) //numero trovato
    {
        for(int i=indiceEliminato;i<*numArray;i++)
        {
            array[i]=array[i+1];
        }
        (*numArray)--;
    }
}
void alternaArray(int array[],int numArray)
{
    for(int i=0;i<numArray-1;i++)
    {
        int temp=array[i]; //inserisco in temp la prima posizione dell'array
        array[i]=array[i+1];
        array[i+1]=temp;
        i++;
    }
}
void BubbleSort(int array[],int numArray)
{
    for(int i=0;i<numArray;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(array[i]<array[j])
            {
                int temp=array[i]; //salvo l'elemento che devo scalare (più piccolo)
                array[i]=array[j]; //scambio il numero più piccolo con quello più grande
                array[j]=temp; 
            }
        }
    }
}
int main()
{
    int array[MAX_NUM];
    int n;
    int sceltaMenu;
    srand(time(0)); //serve a generare i numeri casualmente
    printf("Inserisci la dimensione dell'array (max %d): ",MAX_NUM);
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        array[i]=rand()%100; //genera numeri casuali tra 0 e 99
    }
    do {
        printf("\nMenu:\n");
        printf("1) Visualizza array\n");
        printf("2) Visualizza array invertito\n");
        printf("3) Somma e media degli elementi\n");
        printf("4) Visualizza numeri pari\n");
        printf("5) Visualizza numeri dispari\n");
        printf("6) Cerca un numero\n");
        printf("7) Elimina un elemento\n");
        printf("8) Alterna array\n");
        printf("9) Ordina array\n");
        printf("0) Esci\n");
        printf("Scelta: ");
        scanf("%d", &sceltaMenu);
        switch(sceltaMenu)
        {
            case 1:
            VisualizzaArray(array,n);
            break;
            case 2:
               InvertiArray(array, n);
                break;
            case 3:
                SommaMedia(array, n);
                break;
            case 4:
                StampaPari(array, n);
                break;
            case 5:
                StampaDispari(array, n);
                break;
            case 6:
                cercaNumero(array, n);
                break;
            case 7:
                EliminaNumero(array, &n);
                break;
            case 8:
               alternaArray(array, n);
                break;
            case 9:
               BubbleSort(array,n);
                break;
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    }while(sceltaMenu!=0);

    return 0;
}
