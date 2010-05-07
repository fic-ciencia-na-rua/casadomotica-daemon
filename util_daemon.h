#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include<string.h>
#include<stdlib.h>

#define TAM_MSG 14
#define TAM_COMANDO 4
#define TAM_IDESTADO 7
#define TAM_VALOR 2


struct mensagem{
			char * comando;
			int idEstado;
			int valor;
		};

// int tokMensagem (char * msgIn, struct mensagem *m);
char * subString(const char* str, size_t begin, size_t len);
int tokMensagemsSubStr (char * msgIn, struct mensagem *m);
int open_port(const char * portoSerie);
