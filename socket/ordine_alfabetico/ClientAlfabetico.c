#include <stdio.h>       // Standard input-output
#include <stdlib.h>      // Per l'utilizzo di certe funzioni: htonl, rand, ...
#include <sys/socket.h>  // Funzioni accept, bind, listen
#include <sys/types.h>   // Funzioni accept
#include <netinet/in.h>  // Definizione della struttura degli indirizzi 
#include <string.h>      // Funzioni per le stringhe
#include <errno.h>       // Gestione errori connessione
#include <unistd.h>      // Accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

int main(int argc, char **argv) {
    struct sockaddr_in servizio;
    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); //  La funzione htonl accetta un numero a 32 bit in ordine di byte host e restituisce un numero a 32 bit nell'ordine dei byte di rete usato nelle reti TCP/IP (la famiglia di indirizzi AF_INET o AF_INET6).
    servizio.sin_port=htons(SERVERPORT);       //La funzione htons accetta un numero a 16 bit nell'ordine dei byte host e restituisce un numero a 16 bit nell'ordine dei byte di rete usato nelle reti TCP/IP (la famiglia di indirizzi AF_INET o AF_INET6).

    char str1[DIM];
    int socketfd;

    // Creazione del socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    // Connessione al server
    connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio));

    printf("Inserisci la stringa da elaborare: ");
    scanf("%s", str1); // Legge la stringa dal client

    // Invia la stringa al server
    write(socketfd, str1, sizeof(str1));

    // Leggi la risposta dal server
    read(socketfd, str1, sizeof(str1));

    // Stampa la stringa ordinata ricevuta dal server
    printf("Stringa ordinata: %s\n", str1);

    close(socketfd); // Chiudi il socket
    return 0;
}
