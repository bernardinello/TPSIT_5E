#include <stdio.h>       // Standard input-output
#include <stdlib.h>      // Per l'utilizzo di certe funzioni: htonl, rand, ...
#include <sys/socket.h>  // Funzioni accept, bind, listen
#include <sys/types.h>   // Funzioni accept
#include <netinet/in.h>  // Definizione della struttura degli indirizzi 
#include <string.h>      // Funzioni per le stringhe
#include <errno.h>       // Gestione errori connessione
#include <ctype.h>       // Funzioni per classificare i caratteri
#include <unistd.h>      // Accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

// Funzione per modificare la stringa eliminando caratteri speciali e ordinandola
void modifica_stringa(char *s) {
    char temp[DIM];   // Array temporaneo per memorizzare solo le lettere
    int j = 0;       // Indice per il nuovo array temporaneo

    // Ciclo per filtrare solo le lettere dalla stringa originale
    for (int i = 0; s[i]; i++) {
        if (isalpha(s[i])) {
            temp[j++] = s[i];
        }
    }
    temp[j] = '\0'; // Termina la stringa filtrata con un carattere null

    // Ordinamento dell'array temporaneo in ordine alfabetico
    for (int i = 0; i < j; i++) {
        for (int k = i + 1; k < j; k++) {
            if (temp[i] > temp[k]) {
                char t = temp[i];
                temp[i] = temp[k];
                temp[k] = t;
            }
        }
    }

    // Copia il risultato ordinato nell'array originale
    strcpy(s, temp);
}

int main() {
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET; // Famiglia di indirizzi IPv4
    servizio.sin_addr.s_addr = htonl(INADDR_ANY); // Accetta connessioni da qualsiasi indirizzo
    servizio.sin_port = htons(SERVERPORT); // Imposta la porta del server

    int socketfd, soa, fromlen = sizeof(servizio);
    char str[DIM];

    // Creazione del socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));
    listen(socketfd, 10);

    // Ciclo infinito per accettare le connessioni
    for (;;) {
        printf("Server in ascolto.......\n");
        fflush(stdout);
        
        // Accetta una connessione
        soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);
        
        // Leggi la stringa inviata dal client
        read(soa, str, sizeof(str));
        
        // Modifica la stringa
        modifica_stringa(str);
        
        // Invia la stringa ordinata al client
        write(soa, str, strlen(str) + 1);
        
        // Chiudi la connessione
        close(soa);
    }

    close(socketfd); // Chiudi il socket del server
    return 0;
}
