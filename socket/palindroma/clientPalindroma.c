#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define DIM 1024
#define SERVERPORT 1313

int main(int argc, char **argv) {
    struct sockaddr_in servizio;
    int socketfd;
    char str[DIM]; // dove verrà memorizzata la stringa da inviare al server

    int palindroma = 0; // variabile che dirà se è palindroma oppure no

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY); 
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // Verifico se la connessione è andata a buon fine
    if (connect(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore connessione");
        exit(EXIT_FAILURE);
    }

    // Faccio inserire stringa all'utente
    printf("Inserisci la stringa: ");
    scanf("%s", str);

    // Scrivo al server la stringa inserita dall'utente
    write(socketfd, str, sizeof(str));

    // Leggo dal server se la stringa è palindroma
    read(socketfd, &palindroma, sizeof(int));

    printf("palindromo = %d\n", palindroma);
    if (palindroma) {
        printf("La stringa inserita è palindroma\n");
    } else {
        printf("La stringa inserita non è palindroma\n");
    }

    // Chiudo la connessione 
    close(socketfd);
    return 0;
}
