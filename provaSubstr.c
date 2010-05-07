#include "util_daemon.h"


int main(){

    const char * str = "SET 1234567=0";
    
    char * comando = malloc(sizeof(char)*4);
    comando = subString(str, (size_t) 0, (size_t) 4);
    comando[4] = '\0';
    
    char * idEstado = malloc(sizeof(char)*8);
    idEstado = subString(str, (size_t) 4, (size_t) 7);
    idEstado[8] = '\0';
    
    char * valor = malloc(sizeof(char)*2);
    valor = subString(str, (size_t) 12, (size_t) 1);
    valor[2] = '\0';

    printf("\nstr: %s", str);
    printf("\ncomando: '%s'", comando);
    printf("\nidEstado: '%s'", idEstado);
    printf("\nvalor: '%s'", valor);
    printf("\n");

    free(comando);
    free(idEstado);
    free(valor);

    return 0;
} 
