#include "util_daemon.h"
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>

#define ASCENSOR_TOPEUP 0x000001
#define ASCENSOR_TOPEDOWN 0x000002
#define ASCENSOR_SET_OUT 0x000004
#define PERSIANAS_TOPEUP 0x000010
#define PERSIANAS_TOPEDOWN 0x000020
#define PERSIANAS_SET_OUT 0x000040
#define CLIMATIZACION_ON 0x000100
#define CLIMATIZACION_AUTO 0x000200
#define ALARMA_ARMADA 0x000400
#define ALARMA_DISPARADA 0x000800
#define FONTE_ENCENDIDA 0x001000
#define FONTE_AUTO 0x002000
#define ILUMINACION_EXTERIOR 0x004000
#define ILUMINACION_COCINA 0x008000
#define ILUMINACION_BANHO 010000
#define ILUMINACION_HABITACION 0x020000
#define ILUMINACION_SALON 0x040000
#define ILUMINACION_PASILLO 0x080000
#define ILUMINACION_AUTO 0x100000
#define CHIMENEA_ON 0x200000



typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

#define BOOL(x) (!(!(x)))

#define BitSet(arg,posn) ((arg) | (1L << (posn)))
#define BitClr(arg,posn) ((arg) & ~(1L << (posn)))
#define BitTst(arg,posn) BOOL((arg) & (1L << (posn)))
#define BitFlp(arg,posn) ((arg) ^ (1L << (posn)))
int ard0;


short ilum0E = 1;
short ilum1E = 1;
short ilum2E = 1;
short ilum3E = 1;
short ilum4E = 1;
short ilum5E = 1;

short ilumEE = 1;
short fonteE = 1;
short alarmaE = 1;
short alarmaDE = 1;

short ilum0M = 1;
short ilum1M = 1;
short ilum2M = 1;
short ilum3M = 1;
short ilum4M = 1;
short ilum5M = 1;
short ilumEM = 1;
short fonteM = 0;
short alarmaM = 0;
short alarmaDM = 1;

char * devolver_get;

int b0E1=0,b0E2=0,b1E1=0,b1E2=0,b0M1=0,b0M2=0,b1M1=0,b1M2=0;

void codificarBytes(){
    b0E1=0,b0E2=0,b1E1=0,b1E2=0,b0M1=0,b0M2=0,b1M1=0,b1M2=0;
    if(ilum0M)
	b1M1=BitSet(b1M1,0);
    if(ilum1M)
	b1M1=BitSet(b1M1,1);
    if(ilum2M)
	b1M1=BitSet(b1M1,2);
    if(ilum3M)
	b1M1=BitSet(b1M1,3);
    if(ilum4M)
	b1M1=BitSet(b1M1,4);
    if(ilum4M)
	b1M1=BitSet(b1M1,5);
    if(ilumEM)
	b1M1=BitSet(b1M1,6);
    if(fonteM)
	b1M2=BitSet(b1M2,0);
    if(alarmaM)
	b1M2=BitSet(b1M2,1);
    if(alarmaDM)
	b1M2=BitSet(b1M2,2);
    if(ilum0E)
	b1E1=BitSet(b1E1,0);
    if(ilum1E)
	b1E1=BitSet(b1E1,1);
    if(ilum2E)
	b1E1=BitSet(b1E1,2);
    if(ilum3E)
	b1E1=BitSet(b1E1,3);
    if(ilum4E)
	b1E1=BitSet(b1E1,4);
    if(ilum4E)
	b1E1=BitSet(b1E1,5);
    if(ilumEE)
	b1E1=BitSet(b1E1,6);
    if(fonteE)
	b1E2=BitSet(b1E2,0);
    if(alarmaE)
	b1E2=BitSet(b1E2,1);
    if(alarmaDE)
	b1E2=BitSet(b1E2,2);
}
void actualizarEstado(int estado, int valor){


 	if(estado==ALARMA_ARMADA){
		alarmaM=0;
		alarmaE=valor;
	}else if(estado==ALARMA_DISPARADA){
		alarmaDM=0;
		alarmaDE=valor;
	}else if(estado==FONTE_ENCENDIDA){
		fonteM=0;
		fonteE=valor;
	}else if(estado==ILUMINACION_EXTERIOR){
		ilumEM=0;
		ilumEE=valor;
	}else if(estado==ILUMINACION_COCINA){
		printf("cociña %d\n",valor);
		ilum0M=0;
		ilum0E=valor;
	}else if(estado==ILUMINACION_BANHO){
		ilum1M=0;
		ilum1E=valor;
	}else if(estado==ILUMINACION_HABITACION){
		ilum2M=0;
		ilum2E=valor;
	}else if(estado==ILUMINACION_SALON){
		ilum3M=0;
		ilum3E=valor;
	}else if(estado==ILUMINACION_PASILLO){
		ilum4M=0;
		ilum4E=valor;
	}else if(estado==ILUMINACION_AUTO){
		ilum0M=1;
		ilum1M=1;
		ilum2M=1;
		ilum3M=1;
		ilum4M=1;
		//ilum5E=valor;
	}
	
	
}

void enviarGet(char ** datos, int sock){
    
    datos = malloc(4);
    *datos=0;

    if(ilum0E)
	*datos+=ILUMINACION_COCINA;

    if(ilum1E)
	*datos+=ILUMINACION_BANHO;

    if(ilum2E)
	*datos+=ILUMINACION_HABITACION;

    if(ilum3E)
	*datos+=ILUMINACION_SALON;

    if(ilum4E)
	*datos+=ILUMINACION_PASILLO;

    if(ilumEE)
	*datos+=ILUMINACION_EXTERIOR;

    if(fonteE)
	*datos+=FONTE_ENCENDIDA;

    if(alarmaE)
	*datos+=ALARMA_ARMADA;

    if(alarmaDE)
	*datos+=ALARMA_DISPARADA;

    char * out = malloc(9);
    sprintf(out,"%#x\n",*datos);
    send(sock, out, 9, 0);
    free(out);

}

/*
void setBit(int  number, int x){
 number |= 1 << x;
}
void clrBit(int * number, int x){
 &number &= ~(1 << x);
}

int vBit(int * number,int x){
	return  &number & (1 << x);
}*/

void enviarDatosArduino(){
	char * buf = malloc(sizeof(char)*15);
	//printf("enviando GM a %d\n",ard0);
	//write(ard0, "GM\n",3 );
	write(ard0,"SM",2);
	write(ard0,&b1M1,1);
	write(ard0,&b1M2,1);
	usleep(500000);
	write(ard0,"SE",2);
	write(ard0,&b1E1,1);
	write(ard0,&b1E2,1);
	usleep(500000);
	read(ard0,buf,10);
	printf("ARD: %s\n",buf);
}



int logaritmoMadeINFIC(int num){
    int cont = 0;
    while (num > 1){
	num = num >>1;
	cont++;
    }
    return cont;
}

int main(int argc, char *argv[]){





	char * device0;
	char * device1;
	
	//printf("\n enteiro maximo: %d %d\n", 0x200000, logaritmoMadeINFIC(0x200000));
	
// 	argc = 4;
// 	argv[1] = "5555";
// 	argv[2] = "/dev/tty0";
// 	argv[3] = "/dev/tty1";
	
	int porto, i;
	porto = 3300;
// 	printf("\n*DBG* argc %d", argc);
// 	for (i = 0; i < argc; i++){
// 	    printf("\n*DBG* argv[%d]: '%s'", i, argv[i]);
// 	}
	printf("\n");
// 	if (getParam(argc, argv, &porto, &device0, &device1) >= 0){
// 	}
// 	else{
// 	    printf("\nErro cos parametros. Tes que:\n./server porto device0 device1");
// 	    return -1;
// 	}
	if (argc < 4){
	    printf("\nErro cos parametros. Tes que:\n./server porto device0 device1");
	    return -1;
	} else{
	    porto = atoi(argv[1]);
	}
	printf("\n*DBG* despois de ler parametros");
    
    

        /* Creación del socket TCP */

		int socketfd;
		if ((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0) 
			perror("msg ERR: problema creando o socket");
		printf("\n*DBG* socketfd: %d\n", socketfd);
        /************************************************************************************/
        /* Preparar un nombre local en el puerto especificado: El nombre local */
        /* se prepara con la propia dirección de Internet que la sabe el sistema, */
        /* y el puerto se obtiene del parámetro recibido                                    */
        /************************************************************************************/
		short port = htons( (uint16_t) porto);

		struct sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = port; //o importante desto
		sin.sin_addr.s_addr = htonl(INADDR_ANY);

		if (bind(socketfd, (struct sockaddr *)&sin, sizeof(sin)) == -1){
		    perror("msg ERR: problema con bind");
		    exit(-1);
		}
		printf("\nProbamos abrir portos\n");
		if ((ard0 = open_port(argv[2])) <= 0){
		    return -1;
		}
		printf("\nard0 OK\n");

struct termios options; //setting the options termios

	tcgetattr(ard0,&options); //getting the current attributes of the fd


	options.c_iflag=IGNPAR;
	options.c_oflag=0;
	options.c_cflag= CS8 | CREAD | CLOCAL;
	options.c_lflag=0;
	cfsetispeed(&options,B19200); //setting the speed to 9600
	cfsetospeed(&options,B19200);
	tcsetattr(ard0,TCSANOW,&options);

	//write(ard0,"GM",2);
	//char * buf = malloc(100);
	//read(ard0,buf,14);
	/*int pp;
	for(pp=0;pp<20;pp++){
		enviarDatosArduino();
		//usleep(100000);
	}*/
	

	//exit(-1);
// 		int ard1;
// 		if (ard1 = open_port(device1) <= 0){
// 		    return -1;
// 		}
// 		printf("\nard1 OK");
		
        /* Asigna nombre local al socket: Asignación de una dirección local*/
		short b=1;
		listen(socketfd,5); // isto quedase escoitando nese socket
		//printf("entrando en bucle\n");
		while(b){
				printf("bucleee\n");
				/* Esperar el establecimiento de alguna conexión */
				    struct sockaddr_in addr;
				    int lenAd;//isto é así
				    int sock = accept(socketfd,(struct sockaddr *)&addr,&lenAd);//isto é así
				    if (sock == -1)
					    perror("msg ERR: erro coa aceptación");
				    int devolver = -2;
				    
				    //pedir datos arduinos
// 				    pedirDatosArduino(device0, &Aest0, &Amod0);
// 				    pedirDatosArduino(device1, &Aest1, &Amod1);
				    
				    char * stringOut; //a estructura que se envia
				    char * stringIn; //string de entrada
				    
				    //int tam = sizeof(char *);
				    size_t tam = TAM_MSG;
				    
				    char * rec = malloc(TAM_MSG+5); //aí vaise meter onde se
					    /* Recibir el mensaje */

				    
 				    while (1) {
					    //bucle infinito cando xa establecida a conexion
					    //printf("maxAt %d\n",maxAt);
// 					    char * rec = malloc(TAM_MSG+5); //aí vaise meter onde se
					    /* Recibir el mensaje */

					    int aux;
					    if ((aux = recv(sock, rec, TAM_MSG+5, 0 )) == 0) //mete en rec o que recibe polo socket
						    break;
					    //char * reci = malloc(TAM_MSG);
					    
					    
					    //reci = (char *)rec;
					    //printf("Tamanos: %d %d\n", strlen(reci), strlen(rec));
					    printf("\n*DBG* Mensaxe recibido: '%s'", rec);
					    //printf("%d", strlen(rec));
					    if (strlen(rec) < 1)
						continue;
					    struct mensagem mesg;
					    int tok = tokMensagemsSubStr(rec, &mesg);
					    switch (tok){
						case 1: // Peticion SET
						    printf("\n*DBG* COMANDO: '%s' | ID ESTADO: '%d' | Valor: '%d'", mesg.comando, mesg.idEstado, mesg.valor);
						    actualizarEstado(mesg.idEstado, mesg.valor);
							codificarBytes();
						    enviarDatosArduino();
						    // accionar os estados que a interface me manda
						    break;
						case 0: // Peticion GET
						    printf("\n*DBG* COMANDO: '%s'", mesg.comando);
							// conxuminar os datos
							// enviarlle á interface os datos que temos do arduin	
							// Esto acabo de metelo eu agora a maiores
							//printf("\n*DBG* Vamos a mandar un mensaxe de proba, 0xFF00FF\n");
							stringOut = malloc(9);
							stringOut = strcpy(stringOut, "0xFF00FF\0");
							char * strOut;
							enviarGet(&strOut, sock);

// 							free(stringOut);
							
							
						    break;
						default:
						    printf("msg ERR: comando errado");
					    }
					    printf("\n*DBG* return tokMensagemsSubStr %d\n", tok);
						
					    
					    
					
// 					    free(rec);
				    }
				    /* Cerrar el socket */
				    close(sock);
 				    free(rec);
		}
		close(socketfd);
	free(device1);
	free(device0);
}