//Se importan las librerias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>





//Funcion que invoca si ocurre un error
void error(const char *msg) 
{
	perror(msg);
	exit(0);
}

int contar(char arreglo[]){
	int cont =0;
	while(arreglo[cont]!='\0'){
		cont ++;
	}
	
	return cont;
}

	void imprimir(char entrada[]){
	int j =0;
    for( j = 0; j<contar(entrada); j++) {
        printf("%c ", entrada[j]);
    }
}




//Funcion main
int sockets()
{	
	
	char Ip[16]; 
	char Puerto;
	
	printf("Digite la ip remota \n");
	scanf("%s",&Ip);
	
	system("color 4"); 			
	printf("Digite el número de puerto \n");
	scanf("%s",&Puerto);			
	
	//Declaracion de variables
	//printf("Paramentro de la ip--->");
	//imprimir(&Ip); 
	
	int socket1, nuevoSocket, numPuerto, pid, mensaje;   
	socklen_t clilen;
	char buffer[256];
/**
	if (argumentos < 3)
	{
		fprintf(stderr,"Los parametros de %s está equivocados\n", args[0]);
		exit(0);
	}
	**/
	numPuerto = atoi(&Puerto);
	//printf("NUMERO DE PUERTO: %i\n",numPuerto);
		
	pid = fork();
	
	//Si el id es menor a cero muestra un error en el fork
	
	if (pid < 0)
		error("ERROR en fork");
	
	//Si el id es igual a 0 se cierra el socket y se abre una nueva comunicacion
	if (pid == 0)
	{
		
		struct sockaddr_in dir_servidor;             
		struct hostent *servidor;
		
		while (1){
			sleep(2);
			
			//Se crea el socket
			socket1 = socket(AF_INET, SOCK_STREAM, 0);
			
			//Muestra error en caso de no poder crear el socket
			if (socket1 < 0) error("ERROR de apertura de socket");
			
			
			//printf("IP %s",Ip);
			
			//Obtiene la direccion ip del servidor
			servidor = gethostbyname(Ip);
			
			
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
				error("ERROR de conexión clie");
			
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
			
			
			close(socket1);
	
		}
		return 0;
	}
		
	else {  //Servidor
		
		struct sockaddr_in dir_servidor, dir_cliente;
		
		socket1 = socket(AF_INET, SOCK_STREAM, 0);
		
		//validacion en caso de no se pueda establecer el socket
		if (socket1 < 0)
			error("ERROR de apertura de socket");

		//Establece los valores del bufer a 0
		bzero((char *) &dir_servidor, sizeof(dir_servidor));
		//numPuerto obtine el numero de puerto ingresado por el usuario
		
		dir_servidor.sin_family = AF_INET;                  //Protocolo TCP
		dir_servidor.sin_addr.s_addr = INADDR_ANY;          //Representa la direccion ip
		dir_servidor.sin_port = htons(numPuerto);           //Representa el puerto

		//Verifica la conexion
		if (bind(socket1, (struct sockaddr *) &dir_servidor,sizeof(dir_servidor)) < 0)
			error("ERROR en la conexión");
		
		while(1){
			
			listen(socket1,5);
	
			//Tamaño de bytes que ocupa la direccion cliente
			clilen = sizeof(dir_cliente);
			
			nuevoSocket = accept(socket1,(struct sockaddr *) &dir_cliente, &clilen);
			if (nuevoSocket < 0)
			error("ERROR en aceptar.....");
			
			sleep (5);
			
			bzero(buffer,256);
			
			//Lee el mensaje
			mensaje = read(nuevoSocket,buffer,255);
			//Muestra el error en caso de que se produzca
			if (mensaje < 0)
				error("ERROR al leer del socket");
			
			//Muestra el mensaje recibido
			printf("Aquí está el mensaje: %s\n",buffer);
			
			close(nuevoSocket);
			
			
		}	
	}
	return 0;
}

	
	
	void Menu(){
		printf("Bienvenidos  al Sistema de comunicacion \n OPCIONES:\n 1)ENVIAR MENSAJER\n 2)LISTA DE AMIGOS \n 3)AGREGAR AMIGOS \n");
		//char* argumentos = malloc ( 21 * sizeof(char));
		//char Ip; 
		//char Puerto;
		char opcion=0;
		scanf("%c",&opcion);
			switch(opcion){
				case '1':
				/**
				printf("Digite la ip remota \n");
				scanf("%s",&Ip);
				imprimir (&Ip);
				
				printf("Digite el número de puerto \n");
				scanf("%s",&Puerto);
				imprimir (&Puerto);
				**/
				sockets();
				break;
				case '2':
				break;
				case '3':
				break;
}
	}
	
	int main () {
		
		Menu ();
		return 0;
	}


