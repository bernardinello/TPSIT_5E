#include <stdio.h>       // std in-out
#include <stdlib.h>      // per htonl, htons, ...
#include <sys/socket.h>  // funzioni accept + bind + listen
#include <sys/types.h>   // funzioni accept
#include <netinet/in.h>  // definiscono la struttura degli indirizzi 
#include <string.h>      // funzioni stringhe
#include <unistd.h>      // API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

int Palindroma(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0; // non è palindroma
        }
    }
    return 1; // è palindroma
}

int main() {
    struct sockaddr_in servizio; // record con i dati del server e del client
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    
    int socketfd, soa, fromlen = sizeof(servizio);
    char str[DIM];
    
    // Creazione del socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        exit(EXIT_FAILURE);
    }
    
    // Binding del socket
    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore binding");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
    
    // Inizio ad ascoltare le richieste
    listen(socketfd, 10);

    for (;;) {
        printf("Server in ascolto.....\n");
        fflush(stdout);
        
        // Accetta la connessione
        soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);
        if (soa < 0) {
            perror("Errore in accept");
            continue; // continua a cercare connessioni
        }

        // Leggi la stringa dal client
        read(soa, str, sizeof(str));
        int palindromo = Palindroma(str);
        
        // Stampa il risultato in modo chiaro
        if (palindromo) {
            printf("La stringa '%s' è palindroma.\n", str);
        } else {
            printf("La stringa '%s' non è palindroma.\n", str);
        }
        
        // Invia il risultato al client
        write(soa, &palindromo, sizeof(int));
        close(soa); // chiudi il socket per il client
    }
    
    close(socketfd); // chiudi il socket del server
    return 0;
}
