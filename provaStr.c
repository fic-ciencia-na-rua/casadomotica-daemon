#include </home/braisarias/FIC/ciencia na rua/daemon/util_daemon.h>

int main(){
    struct mensagem mesg;
    //char * stringOut;
	//strncpy(stringIn, "GET 1234567=0", TAM_MSG);
	//strncpy(stringIn, "SET 1234567=0", TAM_MSG);
	    
	    char * stringIn = (char *) malloc(TAM_MSG);
	    strncpy(stringIn, "SET 1234567=0", TAM_MSG);
	    
	    switch (tokMensagem(stringIn, &mesg)){
		case 1:
		    printf("\n*DBG* COMANDO: '%s' | ID ESTADO: '%d' | Valor: '%d'", mesg.comando, mesg.idEstado, mesg.valor);
		    break;
		case 0:
		    printf("\n*DBG* COMANDO: '%s'", mesg.comando);
		    break;
		default:
		    printf("msg ERR: comando errado");
	    }
	    free (stringIn);
	    printf("\n");
	    return 0;
}
