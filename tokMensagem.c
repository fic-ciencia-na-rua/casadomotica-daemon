#include "util_daemon.h"

// int tokMensagem (char * msgIn, struct mensagem *m){
// /*	recibimos un string que decomponhemos no mensaxe tokenizado, na estructura esa
// 	return 0 - temos un GET
// 	return 1 - temos un SET
// 	return -1 - erro na mensagem
// */
// 	
// 	//tokenizamos co espazo:
// 	char * msgNovo = malloc(strlen(msgIn));
// 	msgNovo = strtok(msgIn, " "); //así temo o comando
// 
// 	m->comando = malloc(TAM_COMANDO);
// 	m->comando = strncpy(m->comando, msgNovo, TAM_COMANDO);
// 	
// 	if (strncmp(m->comando, "GET", TAM_COMANDO) == 0) {
// 	    return 0;
// 	}
// 	else{
// 	    if (strncmp(m->comando, "SET", TAM_COMANDO) == 0){
// 		    msgNovo = strtok(NULL, " "); //agora comando aponta a string[4] o idestado
// 		    msgNovo = strtok(msgNovo, "="); //agora temos 000
// 		    
// 		    char * strIdEstado = malloc(TAM_IDESTADO);
// 		    strIdEstado = strncpy(strIdEstado, msgNovo, TAM_IDESTADO); //copiamos o id
// 		    
// 		    msgNovo = strtok(NULL, "="); //agora apuntamos a string[8] o valor para o estado
// 		    
// 		    char * charValor = malloc(TAM_VALOR);
// 		    charValor = strncpy(charValor, msgNovo, TAM_VALOR);
// 		    
// 		    //pasamos os valores de strings aos valores enteiros
// 		    m->idEstado = atoi(strIdEstado);
// 		    m->valor = atoi(charValor);
// 		    
// 		    //liberamos a memoria ocupa polas 
// 		    free( (void *) strIdEstado);
// 		    free( (void *) charValor);
// 		    return 1;
// 	    }
// 	    else{ //erro na mensaxe
// 		return -1;
// 	    }
// 	}
// }



int tokMensagemsSubStr (char * msgIn, struct mensagem *m){
/*	recibimos un string que decomponhemos no mensaxe tokenizado, na estructura esa
	return 0 - temos un GET
	return 1 - temos un SET
	return -1 - erro na mensagem
*/
	//tokenizamos co espazo:
	msgIn[TAM_MSG] = '\0';
	char * msgNovo = malloc(TAM_MSG);
	//msgNovo = strtok(msgIn, " "); //así temo o comando
	
	m->comando = malloc(TAM_COMANDO);
	msgNovo = subString(msgIn, (size_t) 0, (size_t) TAM_COMANDO-1);
// 	printf("\n*DBG* msgNovo: '%s'", msgNovo);
	//msgNovo[TAM_COMANDO] = '\0';
	m->comando = strncpy(m->comando, msgNovo, TAM_COMANDO-1);
// 	printf("\n*DBG* comando: '%s'\n", m->comando);
	
	if (strncmp(m->comando, "GET", TAM_COMANDO-1) == 0) {
// 	    printf("\n*DBG* comando: '%s'\n", m->comando);
	    return 0;
	}
	else{
	    if (strncmp(m->comando, "SET", TAM_COMANDO) == 0){
// 		    msgNovo = strtok(NULL, " "); //agora comando aponta a string[4] o idestado
// 		    msgNovo = strtok(msgNovo, "="); //agora temos 000
// 		    printf("\n*DBG* comando: '%s'\n", m->comando);
		    msgNovo = subString(msgIn, (size_t) TAM_COMANDO, (size_t) TAM_IDESTADO);
		    //msgNovo[TAM_IDESTADO] = '\0';
		    char * strIdEstado = malloc(TAM_IDESTADO);
		    strIdEstado = strncpy(strIdEstado, msgNovo, TAM_IDESTADO); //copiamos o id
// 		    printf("\n*DBG* IdEstado: '%s'\n", strIdEstado);
// 		    msgNovo = strtok(NULL, "="); //agora apuntamos a string[8] o valor para o estado

		    msgNovo = subString(msgIn, (size_t) TAM_COMANDO + TAM_IDESTADO + 1, (size_t) TAM_VALOR-1);
		    //msgNovo[TAM_VALOR] = '\0';
		    
		    char * charValor = malloc(TAM_VALOR);
		    charValor = strncpy(charValor, msgNovo, TAM_VALOR);
		    
// 		    printf("\n*DBG* Valor: '%s'\n", charValor);
		    //pasamos os valores de strings aos valores enteiros
		    m->idEstado = atoi(strIdEstado);
		    m->valor = atoi(charValor);
		    
		    //liberamos a memoria ocupada polas 
		    free(strIdEstado);
		    free(charValor);
		    free(msgNovo);
		    return 1;
	    }
	    else{ //erro na mensaxe
		return -1;
	    }
	}
}



int getParam(int argc, char * const argv[], int *porto, char ** nomDevice0, char ** nomDevice1){
    
	if (argc >= 4){
	    printf("*DBG* argc: %d", argc);
	    *porto = atoi(argv[1]);
	    printf("\n*DBG* porto: '%d'", *porto);
	    
	    int tam[4];
	    tam[2]= strlen(argv[2]);
	    printf("\n tam2: %d", tam[2]);
	    * nomDevice0 = malloc(tam[2]+1);
	    * nomDevice0 = strncpy(* nomDevice0, argv[2], tam[2]);
	    * nomDevice0[tam[2]] = '\0';
	    printf("\n*DBG* device: '%s'", * nomDevice0);
	    
	    tam[3] = strlen(argv[3]);
	    
	    printf("\n tam3: %d", tam[3]);
	    
	    * nomDevice1 = malloc(tam[3]+1);
	    * nomDevice1 = strncpy(* nomDevice1, argv[3], tam[3]);
	    * nomDevice1[tam[4]] = '\0';
	    printf("\n*DBG* device: '%s'", *nomDevice1);
	    return 0;
	}
	else{
	    return -1;
	}
}