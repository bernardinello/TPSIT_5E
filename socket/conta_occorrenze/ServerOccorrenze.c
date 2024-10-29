#include <stdio.h>       // std in-out
#include <stdlib.h>      // per htonl, htons, ...
#include <sys/socket.h>  // funzioni accept, bind, listen
#include <sys/types.h>   // funzioni accept
#include <netinet/in.h>  // struttura degli indirizzi
#include <string.h>      // funzioni stringhe
#include <unistd.h>      // API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

int main() {
    struct sockaddr_in servizio;
    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);
    
    int socketfd, soa, fromlen = sizeof(servizio);
    char str[DIM];
    char carattere;
    
    // Creazione del socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    

    // Bind del socket
    bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));
       

    // Inizio ad ascoltare le richieste
    listen(socketfd, 10);

    for (;;) {
        printf("\n\nServer in ascolto...");
        fflush(stdout);
        
        // Accetta la connessione
        soa = accept(socketfd, (struct sockaddr*)&servizio, &fromlen);
        

        // Leggi la stringa e il carattere dal client
        read(soa, str, sizeof(str));
        read(soa, &carattere, sizeof(char));

        // Conta le occorrenze del carattere nella stringa
        int count = 0;
        for (int i = 0; str[i] != '\0' && i < DIM; i++) {
            if (str[i] == carattere) {
                count++;
            }
        }

        // Stampa il risultato
        printf("Stringa ricevuta: '%s', Carattere: '%c', Occorrenze: %d\n", str, carattere, count);

        // Invia il conteggio al client
        write(soa, &count, sizeof(int));

        // Chiudi il socket del client
        close(soa);
    }
    
    // Chiudi il socket del server
    close(socketfd);
    return 0;
}
