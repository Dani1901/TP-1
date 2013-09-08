//Se importan las librerias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <wait.h>

//Funcion que invoca si ocurre un error
void error(const char *msg) 
{
	perror(msg);
	exit(0);
}

//Funcion main
int main(int argumentos, char *args[])
{
	//Declaracion de variables
	int socket1, nuevoSocket, numPuerto, pid, mensaje, Estado;   
	socklen_t clilen;
	char buffer[256];

	if (argumentos < 3)
	{
		fprintf(stderr,"Los parametros de %s está equivocados\n", args[0]);
		exit(0);
	}
	
	numPuerto = atoi(args[2]);
	
	pid = fork();
	
	//Si el id es menor a cero muestra un error en el fork
	
	if (pid < 0)
		error("ERROR en fork");
	
	//Si el id es igual a 0 se cierra el socket y se abre una nueva comunicacion
	if (pid == 0)
	{
		printf("Entre a cliente \n");
		struct sockaddr_in dir_servidor;             
		struct hostent *servidor;
		
		while (1){
			
			//Se crea el socket
			socket1 = socket(AF_INET, SOCK_STREAM, 0);
			
			//Muestra error en caso de no poder crear el socket
			if (socket1 < 0) error("ERROR de apertura de socket");
			
			//Obtiene la direccion ip del servidor
			servidor = gethostbyname(args[1]);
			
			//Si el servidor es nulo ,muestra el error 
			if (servidor == NULL)
			{
				fprintf(stderr,"ERROR, no hay host \n");
				exit(0);
			}
			
			//Rellena con 0
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
			//sleep (1);
		}
		return 0;
	}
		
	else {  //Servidor
		struct sockaddr_in dir_servidor, dir_cliente;
		
		socket1 = socket(AF_INET, SOCK_STREAM, 0);
		printf("Entre a servidor \n");
		//validacion en caso de no se pueda establecer el socket
		if (socket1 < 0)
			error("ERROR de apertura de socket");

		//Establece los valores del bufer a 0
		bzero((char *) &dir_servidor, sizeof(dir_servidor));
		//numPuerto obtine el numero de puerto ingresado por el usuario
		
		dir_servidor.sin_family = AF_INET;                  //Protocolo TCP
		dir_servidor.sin_addr.s_addr = inet_addr ("192.168.16.3");          //Representa la direccion ip
		dir_servidor.sin_port = htons(numPuerto);           //Representa el puerto

		//Verifica la conexion
		if (bind(socket1, (struct sockaddr *) &dir_servidor,sizeof(dir_servidor)) < 0)
			error("ERROR en la conexión");
		
		while(1){
			
			listen(socket1,5);
	
			//Tamaño de bytes que ocupa la direccion cliente
			clilen = sizeof(dir_cliente);
			
			printf ("Hasta aui creo estar bn \n");
			nuevoSocket = accept(socket1,(struct sockaddr *) &dir_cliente, &clilen);
			if (nuevoSocket < 0)
			error("ERROR en aceptar.....");
			sleep (2);
			bzero(buffer,256);
	
			//Lee el mensaje
			mensaje = read(socket1,buffer,255);
			//Muestra el error en caso de que se produzca
			if (mensaje < 0)
				error("ERROR al leer del socket");
			
			//Muestra el mensaje recibido
			printf("Aquí está el mensaje: %s\n",buffer);
			mensaje = write(socket1,"Tengo el mensaje",18);
			
			//Si no puede leer el msj muestra el error
			if (mensaje < 0)
				error("ERROR al escribir en el socket");
			
			close(nuevoSocket);
			close(socket1);
			
		}	
	}
	return 0;
}
