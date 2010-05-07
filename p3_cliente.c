/* #include (librerías de sockets necesarias y librerías estándar ) */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct d_envio {
			int opcion;
			int datos;
		};
/* Función principal del cliente */

int lerInteger(){
	char cadena[5];
	fgets(cadena,5,stdin);
	char * cadena2=strtok(cadena,"\n");
	return atoi(cadena2);
}

int main(int argc, char *argv[]){
		if(argc!=3)
			printf("Compruebe que clienteP3 tiene 2 argumentos (dirección,puerto)\n");
        /* Comprueba que clienteTCP tiene 4 argumentos (clienteTCP, dirección, puerto,
                 mensaje) */

        /* Creación del socket TCP */
		short port = htons(atoi(argv[2]));
		short port2=atoi(argv[2]);
		printf("p %d\n",port2);
		int socketfd;		
		if((socketfd=socket(AF_INET,SOCK_STREAM,0))<0)
			perror("problema creando o socket");

		struct sockaddr_in sin;
		sin.sin_family=AF_INET;
		sin.sin_port=0;
		sin.sin_addr.s_addr=htonl(INADDR_ANY); //inet_addr("127.0.0.1");


		if(bind(socketfd, (struct sockaddr *)&sin, sizeof(sin))==-1)
			perror("problema con bind");


        /************************************************************************************/
        /* Preparar un nombre local en un puerto cualquiera: El nombre local                */
        /* se prepara con la propia dirección de Internet y el puerto se deja a             */
        /* la elección de la máquina.*/


        /************************************************************************************/
        /* Asigna nombre local al socket: Asignación de una dirección local                 */
        /************************************************************************************/
        /* Preparar el nombre de la máquina remota: La dirección remota hay                 */
        /* que convertirla a binario con la función inet.addr y el número de                */
        /* puerto remoto hay que ponerlo en formato de red con htons.                       */
        /************************************************************************************/
		struct sockaddr_in sout;
		sout.sin_family=AF_INET;
		sout.sin_port=port;
		sout.sin_addr.s_addr=inet_addr(argv[1]);
		if(connect(socketfd,(struct sockaddr *) &sout, sizeof(sout))==-1)
			perror("problema na conexion");
        /* Establecer la conexión con el servidor */


		short acerto = 1;
		int tam=sizeof(struct d_envio);
		struct d_envio estEnvio;
		struct d_envio estRecv;
		while(acerto){
		
		estEnvio.opcion=htonl(1);

			printf("\ninserte un numero de 0 a 100\n");
			estEnvio.datos=htonl(lerInteger());
			send(socketfd,(char *)&estEnvio, tam, 0);
			recv(socketfd,(char *)&estRecv,tam,0);
			int op = ntohl(estRecv.opcion);
			int numero=ntohl(estRecv.datos);
			if(op==2){
				if(numero==0){
					printf("EXITO!, numero acertado\n");
					close(socketfd);
					exit(0);
				} else if(numero ==1)
					printf("insertaches un numero maior que o que tes que adiviñar\n");
				else if(numero==-1)
					printf("insertaches un numero menor que o que tes que adiviñar\n");
				else if(numero == -2){
					printf("FIN, maximo numero de intentos alcanado\n");
					close(socketfd);
					exit(0);
				}else
					printf("algo raro pasa xD\n");
			}
			else
				printf("erro, operacion 1 recibida\n");


		}
        /* Recibir la respuesta */
		//close(socketfd);
        /* Cerrar el socket */
}
