#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define DIM 1024
int SoloLettere(char *stringa)
{
    for(int i=0;i<strlen(stringa);i++)
    {
        if(!isalpha(stringa[i])) // se il carattere non è una lettera restituisce 0
        {
            return 0;
        }
    }
    return 1; //restituisce 1 se sono tutte lettere.
}
int ContaLettere(char *stringa,char lettera)
{
    int contatore=0;
    for(int i=0;i<strlen(stringa);i++)
    {
        if(tolower(*stringa)==tolower(lettera))
        {
            contatore++;
        }
    }
    return contatore;
}
void PariDispari(char *stringa)
{
    char pari[strlen(stringa)];
    char dispari[strlen(stringa)];
    int indicePari=0,indiceDispari=0;
    for(int i=0;i<strlen(stringa);i++)
    {
        if(i%2==0)
        {
            dispari[indiceDispari]=stringa[i]; //posizione numeri pari
            indiceDispari++;
        }
        else 
        {
            pari[indicePari]=stringa[i]; //posizione numeri pari
            indicePari++;
            
        }
    }
    pari[indicePari] = '\0';   // Terminazione stringa
    dispari[indiceDispari] = '\0'; // Terminazione stringa
    printf("Posizione pari %s\n",pari);
    printf("Posizione dispari %s\n",dispari);
}


int ContieneDoppie(char *stringa)
{
    for(int i=0;i<strlen(stringa)-1;i++)
    {
        if(tolower(stringa[i])==tolower(stringa[i+1]))
        {
            return  1; //se trova doppie ritorna 1
        }
    }
    return  0; //se non le trova ritorna 0
}
int ContaVocali(char *stringa)
{
    int contatore=0;
    for(int i=0;i<strlen(stringa);i++)
    {
        char car=tolower(stringa[i]);
        if(car=='a'||car=='e'||car=='i'||car=='o'||car=='u')
        {
            contatore++;
        }
    }
    return contatore;
}
int ContaConsonanti(char *stringa)
{
    int contatore=0;
    for(int i=0;i<strlen(stringa);i++)
    {
        char car=tolower(stringa[i]);
        if(!(car=='a'||car=='e'||car=='i'||car=='o'||car=='u'))
        {
            contatore++;
        }
    }
    return contatore;
}
void Lunghezza(char stringa1[],char stringa2[])
{
    if(strlen(stringa1)>strlen(stringa2))
    {
        printf("La prima stringa è piu grande della seconda\n");
    }
    else if(strlen(stringa1)<strlen(stringa2))
    {
        printf("La seconda stringa è più grande della prima\n");
    }
    else 
    {
        printf("Le due stringhe sono uguali\n");
    }
}
void LettereEntrambe(char * stringa1, char stringa2[])
{
	//controlla che non ci sia due volte la stessa frase 
    char ripetute[strlen(stringa1)];
    int flag=0;
    int cont=0;

    for(int i=0; i<strlen(stringa1);i++)
    {
        flag=0;
        for(int h=0; h<strlen(stringa1);h++)
        {
            if(ripetute[h]==stringa1[i])
                flag=1;
        }
        if(flag==0)
        {
            for(int j=0; j<strlen(stringa2);j++)
                if(stringa1[i]==stringa2[j])
                {
                    printf("La lettera %c compare in entrambi\n",stringa1[i]);
                    ripetute[cont++]=stringa1[i];
                    break;
                }
        }
    }   
}
int main()
{
    char stringa[DIM];
    char stringa2[DIM];
    char lettera;
    printf("Inserisci la frase\n");
    scanf("%s",stringa);
    if(SoloLettere(stringa)==1)
    {
        printf("La stringa inserita contiene solo lettere\n");
    }
    else 
    {
        printf("La stringa inserita non contiene solo lettere\n");
    }
    PariDispari(stringa);
    if(ContieneDoppie(stringa)==1)
    {
        printf("Ci sono doppie\n");
    }
    printf("Inserisci un'altra stringa\n");
    scanf("%s",stringa2);
    Lunghezza(stringa,stringa2);
    LettereEntrambe(stringa,stringa2);
    int vocali1=ContaVocali(stringa);
    int vocali2=ContaVocali(stringa2);
    int consonanti1=ContaConsonanti(stringa);
    int consonanti2=ContaConsonanti(stringa2);
    if(vocali1>vocali2)
    {
        printf("La prima stringa ha più vocali rispetto alla seconda\n");
    }
    else if(vocali1<vocali2)
    {
        printf("La seconda stringa ha più vocali rispetto alla prima\n");
    }
    else 
    {
        printf("Le due stringhe hanno lo stesso numero di vocali\n");
    }
    if(consonanti1>consonanti2)
    {
        printf("La prima stringa ha più consonanti rispetto alla seconda\n");
    }
    else if(consonanti1<consonanti2)
    {
        printf("La seconda stringa ha più consonanti rispetto alla prima\n");
    }
    else 
    {
        printf("Le due stringhe hanno lo stesso numero di consonanti\n");
    }
    
    
    return 0;
    
}
