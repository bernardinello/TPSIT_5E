#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 3

typedef struct {
    char modelloAuto[50];
    char marca[50];
    int cilindrata;
    float prezzo;
    int anno_Immatricolazione;
} Auto;

void Stampa(Auto concessionaria[]) {
    for(int i = 0; i < DIM; i++) {
        printf("Modello: %s - Marca: %s - Cilindrata: %d - Prezzo: %.2f - Anno Immatricolazione: %d\n",
               concessionaria[i].modelloAuto,
               concessionaria[i].marca,
               concessionaria[i].cilindrata,
               concessionaria[i].prezzo,
               concessionaria[i].anno_Immatricolazione);
    }
}

void confronto_prezzi(Auto concessionaria[]) {
    float prezzoMax = concessionaria[0].prezzo;
    float prezzoMin = concessionaria[0].prezzo;
    char modelloMax[50], modelloMin[50];

    strcpy(modelloMax, concessionaria[0].modelloAuto);
    strcpy(modelloMin, concessionaria[0].modelloAuto);

    for(int i = 1; i < DIM; i++) {
        if(concessionaria[i].prezzo > prezzoMax) {
            prezzoMax = concessionaria[i].prezzo;
            strcpy(modelloMax, concessionaria[i].modelloAuto);
        }
        if(concessionaria[i].prezzo < prezzoMin) {
            prezzoMin = concessionaria[i].prezzo;
            strcpy(modelloMin, concessionaria[i].modelloAuto);
        }
    }

    printf("Prezzo più alto: %.2f (Modello: %s)\n", prezzoMax, modelloMax);
    printf("Prezzo più basso: %.2f (Modello: %s)\n", prezzoMin, modelloMin);
}

void ordina_per_anno(Auto concessionaria[]) {
    for(int i = 0; i < DIM - 1; i++) {
        for(int j = i + 1; j < DIM; j++) {
            if(concessionaria[i].anno_Immatricolazione > concessionaria[j].anno_Immatricolazione) {
                Auto temp = concessionaria[i];
                concessionaria[i] = concessionaria[j];
                concessionaria[j] = temp;
            }
        }
    }
}

void visualizza_auto_per_prezzo(Auto concessionaria[], float prezzo) {
    printf("Auto con prezzo superiore a %.2f:\n", prezzo);
    for(int i = 0; i < DIM; i++) {
        if(concessionaria[i].prezzo > prezzo) {
            printf("%s - %s\n", concessionaria[i].modelloAuto, concessionaria[i].marca);
        }
    }
}

int main(int argc, char *argv[]) {
    Auto a1 = {"modello 1", "marca 1", 80, 506.24, 2006};
    Auto a2 = {"modello 2", "marca 2", 60, 450.00, 2008};
    Auto a3 = {"modello 3", "marca 3", 75, 650.24, 2005};
    
    Auto concessionaria[DIM] = {a1, a2, a3};

    // Stampa tutte le auto
    printf("Elenco delle auto:\n");
    Stampa(concessionaria);
    
    // Confronto prezzi
    printf("\nConfronto prezzi:\n");
    confronto_prezzi(concessionaria);
    
    // Ordinamento per anno di immatricolazione
    printf("\nAuto ordinate per anno di immatricolazione:\n");
    ordina_per_anno(concessionaria);
    Stampa(concessionaria);
    
    // Visualizzazione auto per prezzo
    float prezzoScelto;
    printf("\nInserisci un prezzo per visualizzare le auto superiori a tale prezzo: ");
    scanf("%f", &prezzoScelto);
    visualizza_auto_per_prezzo(concessionaria, prezzoScelto);
    
    return 0;
}
