//Se importan las librerias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//Funcion que invoca si ocurre un error
void error(const char *msg) 
{
	perror(msg);
	exit(0);
}

//Funcion main recibe ip 
int main(int argc, char *argv[]) {
	//Declaracion de variables
	int socket1, numPuerto, mensaje;
	struct sockaddr_in dir_servidor;             
	struct hostent *servidor;
	char buffer[256];
	
	//Error que se muestra cuando los parametros son equivocados
	if (argc < 3)
	{
	fprintf(stderr,"Los parametros de %s está equivocados\n", argv[0]);
	exit(0);
	}
	
	//Se guarda el numero de puerto
	numPuerto = atoi(argv[2]);
	
	//Se crea el socket
	socket1 = socket(AF_INET, SOCK_STREAM, 0);
	
	//Muestra error en caso de no poder crear el socket
	if (socket1 < 0) error("ERROR de apertura de socket");
	
	//Obtiene la direccion ip del servidor
	servidor = gethostbyname(argv[1]);
	
	//Si el servidor es nulo ,muestra el error 
	if (servidor == NULL)
	{
		fprintf(stderr,"ERROR, no hay host \n");
		exit(0);
	}
	
	//Restablece el valor del buffer a 0
	bzero((char *) &dir_servidor, sizeof(dir_servidor));
	
	dir_servidor.sin_family = AF_INET;                  //Protocolo TCP
    
    //Copia la direccion
	bcopy((char *)servidor->h_addr,(char*)&dir_servidor.sin_addr.s_addr,servidor->h_length);
	
	dir_servidor.sin_port = htons(numPuerto);           //Representa el numero de puerto
	
	//Verifica que pueda establecer la conexion
	if (connect(socket1,(struct sockaddr *)&dir_servidor,sizeof(dir_servidor)) < 0) 
		error("ERROR de conexión");
	
	printf("Por favor, introduzca el mensaje:");
	
	//Relleno con ceros
	bzero(buffer,256);
	
	//Lee el mensaje desde la entrada estandar
	fgets(buffer,255,stdin);
	
	//Solicita escribir un mensaje
	mensaje = write(socket1,buffer,strlen(buffer));
	
	//Si se produce un error al escribir el msj, se muestra el error
	if (mensaje < 0)
		error("ERROR al escribir en socket");
	
	//Relleno con ceros
	bzero(buffer,256);
	//Lee el mensaje
	mensaje = read(socket1,buffer,255);
	
	//Si se produce un error al leer el msj, se muestra el error
	if (mensaje < 0)
		error("ERROR al leer del socket");

	printf("%s\n",buffer);
	close(socket1);
	return 0;
}
