#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>    

// Definisce le costanti per le dimensioni massime
#define MAX_LEN 100                   // Lunghezza massima per titoli, autori e generi
#define MAX_LIBRI 100                 // Numero massimo di libri
#define MAX_CATEGORIE 50              // Numero massimo di categorie
#define MAX_LIBRI_PER_CATEGORIA 50    // Numero massimo di libri per categoria

// Struttura per rappresentare un libro
typedef struct {
    char titolo[MAX_LEN];     
    char autore[MAX_LEN];    
    int anno;                 
    float prezzo;             
    char genere[MAX_LEN];     
} Libro;

// Struttura per rappresentare una categoria di libri
typedef struct {
    char nome[MAX_LEN];                  // Nome della categoria
    Libro libri[MAX_LIBRI_PER_CATEGORIA]; // Array di libri appartenenti alla categoria
    int numLibri;                        // Numero di libri nella categoria
} Categoria;

// Array globale delle categorie di libri
Categoria categorie[MAX_CATEGORIE]; // Array per contenere tutte le categorie
int numCategorie = 0;                 // Contatore per il numero di categorie esistenti

// Funzione per rimuovere eventuali newline o spazi finali da una stringa
void rimuoviNewline(char* str) {
    size_t len = strlen(str); // Calcola la lunghezza della stringa di input

    // Se l'ultimo carattere è un carattere di nuova riga
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0'; // Sostituisce il newline con un terminatore di stringa
    }

    // Rimuovi eventuali spazi finali
    while (len > 0 && (str[len - 1] == ' ')) {
        str[--len] = '\0'; // Riduce la lunghezza della stringa, sostituendo gli spazi finali con il terminatore
    }

    // Inizializza una variabile per individuare l'inizio della stringa
    size_t start = 0;

    // Rimuovi eventuali spazi iniziali
    while (str[start] == ' ') {
        start++; // Incrementa l'indice di partenza per saltare gli spazi iniziali
    }

    // Se ci sono spazi iniziali da rimuovere
    if (start > 0) {
        // Sposta la stringa a sinistra, sovrascrivendo gli spazi iniziali
        memmove(str, str + start, len - start + 1); // Copia la parte rimanente della stringa
    }
}

// Funzione per trovare la categoria in base al nome
int trovaCategoria(char* nome) {
    for (int i = 0; i < numCategorie; i++) {
        rimuoviNewline(categorie[i].nome); // Pulisce il nome della categoria
        rimuoviNewline(nome); // Pulisce il nome passato come parametro
        if (strcmp(categorie[i].nome, nome) == 0) // Confronta i nomi
        { 
            return i; // Ritorna l'indice della categoria trovata
        }
    }
    return -1; // Ritorna -1 se la categoria non è trovata
}

// Funzione per aggiungere un libro a una categoria
void aggiungiLibroACategoria(Libro libro) {
    int indiceCategoria = trovaCategoria(libro.genere); // Trova l'indice della categoria del libro

    if (indiceCategoria == -1) {
        // Se la categoria non esiste, creala
        if(numCategorie >= MAX_CATEGORIE) { // Controlla se ci sono già troppe categorie
            return; // Non aggiunge il libro se si supera il limite
        }
        // Copia il nome del genere nella nuova categoria
        strcpy(categorie[numCategorie].nome, libro.genere);
        categorie[numCategorie].libri[0] = libro; // Aggiunge il libro come primo nella nuova categoria
        categorie[numCategorie].numLibri = 1; // Incrementa il numero di libri nella categoria
        numCategorie++; // Incrementa il numero totale di categorie
    } else {
        // Se la categoria esiste, aggiungi il libro
        Categoria* cat = &categorie[indiceCategoria]; // Ottiene un puntatore alla categoria esistente
        cat->libri[cat->numLibri++] = libro; // Aggiunge il libro all'array e incrementa il conteggio
    }
}

// Funzione per leggere i libri da un file CSV e aggiungerli alle categorie
int leggiLibriDaCSV(char* nomeFile) {
    FILE* file = fopen(nomeFile, "r"); // Apre il file in lettura
    if (!file) {
        printf("Errore nell'aprire il file\n"); // Stampa un errore se il file non può essere aperto
        return -1; // Ritorna -1 in caso di errore
    }

    char buffer[256]; // Buffer per leggere le righe dal file
    int i = 0; // Contatore per il numero di libri letti
    fgets(buffer, sizeof(buffer), file); // Ignora la prima riga (intestazione del CSV)

    while (fgets(buffer, sizeof(buffer), file)) { // Legge ogni riga del file
        rimuoviNewline(buffer); // Pulisce la riga letta

        Libro libro; // Crea un nuovo libro
        char* token = strtok(buffer, ","); // Estrae il titolo (token)
        if (token != NULL) {
            strcpy(libro.titolo, token); // Copia il titolo nel libro
        }
        token = strtok(NULL, ","); // Estrae l'autore
        if (token != NULL) {
            strcpy(libro.autore, token); // Copia l'autore nel libro
        }
        token = strtok(NULL, ","); // Estrae l'anno
        if (token != NULL) {
            libro.anno = atoi(token); // Converte l'anno da stringa a intero
        }
        token = strtok(NULL, ","); // Estrae il prezzo
        if (token != NULL) {
            libro.prezzo = atof(token); // Converte il prezzo da stringa a float
        }
        token = strtok(NULL, ","); // Estrae il genere
        if (token != NULL) {
            strcpy(libro.genere, token); // Copia il genere nel libro
        }

        // Aggiungi il libro alla categoria appropriata
        aggiungiLibroACategoria(libro); // Aggiunge il libro alla categoria
        i++; // Incrementa il contatore dei libri letti
    }

    fclose(file); // Chiude il file
    return i; // Ritorna il numero di libri letti
}

// Funzione per stampare i libri di una categoria
void stampaLibriCategoria(Categoria* categoria) {
    printf("Categoria: %s\n", categoria->nome); // Stampa il nome della categoria
    for (int i = 0; i < categoria->numLibri; i++) { // Cicla attraverso i libri nella categoria
        Libro* libro = &categoria->libri[i]; // Ottiene il puntatore al libro corrente
        // Stampa le informazioni del libro
        printf("Titolo: %s, Autore: %s, Anno: %d, Prezzo: %.2f\n", libro->titolo, libro->autore, libro->anno, libro->prezzo);
    }
}

// Funzione per stampare tutti i libri organizzati per categorie
void stampaTutteLeCategorie() {
    for (int i = 0; i < numCategorie; i++) { // Cicla attraverso tutte le categorie
        stampaLibriCategoria(&categorie[i]); // Stampa i libri della categoria corrente
        printf("\n"); // Stampa una riga vuota tra le categorie
    }
}

// Funzione per cercare un libro per titolo
int cercaLibroPerTitolo(char* titolo) {
    for (int i = 0; i < numCategorie; i++) { // Cicla attraverso tutte le categorie
        for (int j = 0; j < categorie[i].numLibri; j++) { // Cicla attraverso i libri nella categoria
            if (strcmp(categorie[i].libri[j].titolo, titolo) == 0) { // Confronta il titolo del libro
                // Stampa le informazioni del libro trovato
                printf("Libro trovato: Titolo: %s, Autore: %s, Anno: %d, Prezzo: %.2f, Categoria: %s\n",
                    categorie[i].libri[j].titolo, categorie[i].libri[j].autore,
                    categorie[i].libri[j].anno, categorie[i].libri[j].prezzo,
                    categorie[i].nome);
                return 1; // Libro trovato, ritorna 1
            }
        }
    }
    return 0; // Libro non trovato, ritorna 0
}

// Funzione per cercare libri per categoria
int cercaLibriPerCategoria(char* nomeCategoria) {
    rimuoviNewline(nomeCategoria); // Pulisce il nome della categoria
    int indiceCategoria = trovaCategoria(nomeCategoria); // Trova l'indice della categoria
    if (indiceCategoria != -1) { // Se la categoria è trovata
        stampaLibriCategoria(&categorie[indiceCategoria]); // Stampa i libri della categoria
        return 1; // Categoria trovata, ritorna 1
    } else {
        return 0; // Categoria non trovata, ritorna 0
    }
}

// Funzione principale
int main(int argc, char *argv[]) {
    char nomeFile[] = "libri.csv"; // Nome del file CSV contenente i libri

    int numLibri = leggiLibriDaCSV(nomeFile); // Legge i libri dal file

    if (numLibri > 0) { // Se sono stati letti libri
        printf("Libri letti e organizzati in categorie:\n");
        stampaTutteLeCategorie(); // Stampa tutte le categorie e i loro libri
    } else {
        printf("Nessun libro trovato o errore nel file.\n"); // Messaggio di errore
    }

    // Cerca un libro per titolo
    char titoloDaCercare[MAX_LEN];
    while (1) {
        printf("\nInserisci il titolo del libro da cercare: ");
        fgets(titoloDaCercare, MAX_LEN, stdin); // Legge il titolo da input
        rimuoviNewline(titoloDaCercare); // Pulisce il titolo

        // Cerca il libro per titolo
        if (cercaLibroPerTitolo(titoloDaCercare) == 0) {
            printf("Libro con titolo \"%s\" non trovato. Riprova.\n", titoloDaCercare); // Messaggio se non trovato
        } else {
            break; // Esci dal ciclo se il libro è trovato
        }
    }

    // Cerca libri per categoria
    char categoriaDaCercare[MAX_LEN];
    while (1) {
        printf("\nInserisci il nome della categoria da cercare: ");
        fgets(categoriaDaCercare, MAX_LEN, stdin); // Legge la categoria da input
        rimuoviNewline(categoriaDaCercare); // Pulisce il nome della categoria

        // Cerca la categoria
        if (cercaLibriPerCategoria(categoriaDaCercare) == 0) {
            printf("Categoria \"%s\" non trovata. Riprova.\n", categoriaDaCercare); // Messaggio se non trovata
        } else {
            break; // Esci dal ciclo se la categoria è trovata
        }
    }

    return 0; // Termina il programma
}
