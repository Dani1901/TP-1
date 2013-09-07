//Se importan las librerias
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void comunicacion(int);

//Funcion que se invoca cuando ocurre un error
void error(const char *msg)             
{
	perror(msg);                         
	exit(1);
}

//Funcion main
int main(int argc, char *argv[])
{
	//Declaracion de variables
	int socket1, nuevoSocket, numPuerto, pid;   
	socklen_t clilen;
	struct sockaddr_in dir_servidor, dir_cliente;      //Reserva espacio en memoria
	

    //Verifica que exista un numero de puerto
	if (argc < 2)
	{
		fprintf(stderr,"ERROR, no hay ningún puerto\n");
		exit(1);
	}
	//Se crea define el socket
	socket1 = socket(AF_INET, SOCK_STREAM, 0);
	
	//validacion en caso de no se pueda establecer el socket
	if (socket1 < 0)
		error("ERROR de apertura de socket");

    //Establece los valores del bufer a 0
	bzero((char *) &dir_servidor, sizeof(dir_servidor));
	//numPuerto obtine el numero de puerto ingresado por el usuario
	numPuerto = atoi(argv[1]);
	
	dir_servidor.sin_family = AF_INET;                  //Protocolo TCP
	dir_servidor.sin_addr.s_addr = INADDR_ANY;          //Representa la direccion ip
	dir_servidor.sin_port = htons(numPuerto);           //Representa el puerto

	//Verifica la conexion
	if (bind(socket1, (struct sockaddr *) &dir_servidor,sizeof(dir_servidor)) < 0)
		error("ERROR en la conexión");
	
	//Habilita al socket a recibir peticiones seran almacenadas en una cola
	listen(socket1,5);
	
	//Tamaño de bytes que ocupa la direccion cliente
	clilen = sizeof(dir_cliente);

    //Se crea un ciclo infinito para que el servidor quede en espera de peticiones
	while (1)
	{
		//Acepta las solicitudes que esten en la cola
		nuevoSocket = accept(socket1,(struct sockaddr *) &dir_cliente, &clilen);
		
		//Valida que no exista error en aceptar 
		if (nuevoSocket < 0)
			error("ERROR en aceptar");
		
		//Se le asigna un id de proceso al fork
		pid = fork();
		//Si el id es menor a cero muestra un error en el fork
		if (pid < 0)
			error("ERROR en fork");
		
		//Si el id es igual a 0 se cierra el socket y se abre una nueva comunicacion
		if (pid == 0)
		{
			close(socket1);
			comunicacion(nuevoSocket);
			exit(0);
		}
		
		else
		// Si es mayor a 0 se cierra la comunicacion
			close(nuevoSocket);
	}
	close(socket1);
	return 0;
}

//Se encarga de las comunicaciones despues de establecida la conexion
void comunicacion (int sock)
{
	//Declaracion de variables
	int mensaje;
	char buffer[256];       
	
	//Rellena con ceros
	bzero(buffer,256);
	
	//Lee el mensaje
	mensaje = read(sock,buffer,255);
	
	//Muestra el error en caso de que se produzca
	if (mensaje < 0)
		error("ERROR al leer del socket");
	
	//Muestra el mensaje recibido
	printf("Aquí está el mensaje: %s\n",buffer);
	mensaje = write(sock,"Tengo el mensaje",18);
	
	
	//Si no puede leer el msj muestra el error
	if (mensaje < 0)
		error("ERROR al escribir en el socket");
	
	}

