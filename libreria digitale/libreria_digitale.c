#include <windows.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIBRI 38
typedef struct 
{
    char titolo[100];
    char autore[100];
    int anno;
    float prezzo;
    char genere[100];
}Libro;
typedef enum {
    ADVENTURE,
    DYSTOPIAN,
    FANTASY,
    GOTHIC,
    HISTORICAL_FICTION,
    LITERARY_FICTION,
    MEMOIR,
    MODERNIST,
    MYSTERY,
    PHILOSOPHICAL,
    POETRY,
    ROMANCE,
    MAGICAL_REALISM,
    EXISTENTIALIST,
    PLAY,
    SCIENCE_FICTION,
    CATEGORY_COUNT //serve per contare il numero di categorie
}Categoria;
void leggiFile()
{

}
int main(int argc,char *argv[])
{
    
    Libro libreria[MAX_LIBRI];
    return 0;
}