
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

char ip[16];
char puerto[30];
char IP [16];
int Menu();

// Copia la ip para eliminar el \0 
void copiar(char ar1[], char ar2[]){
int x=strlen(ar1);
int i=0;
while(i<x-1){
	 ar2[i] = ar1[i];
	 i++;
	 }
}

//Funcion que invoca si ocurre un error
void error(const char *msg) 
{
	perror(msg);
	exit(0);
}


	int lee(char usuario[]){
	 FILE *archivo;
		
        char caracteres[30];
        //static char user[30];
       
		int i=0;
        archivo = fopen("listaContactos.txt","r");
 
        if (archivo == NULL)
                exit(1);
 
        int existe;
        while (feof(archivo) == 0)
        {
                fgets(caracteres,30,archivo);
                if(((Comparar(usuario,caracteres))==1)||(i>0)){
					//if(i==0)strcpy(user,caracteres);
					if(i==1)strcpy(ip,caracteres);
					if(i==2){strcpy(puerto,caracteres);
					i=0;
					existe = 1;
					break;}
					
					i++;
					}
					
        }
        
        
        if (existe != 1) {
        printf("El contacto no se encuentra, por favor agregue \n");
        existe = 0;
        Menu ();
        }
        
        fclose(archivo);
        return 0;
	 
	 }


int sockets()
{	
	char Usuario [30];
	
	printf("Digite el usuario \n");
	scanf("%s",&Usuario);			
		
	lee(Usuario);
	
	int socket1, nuevoSocket, numPuerto, pid, mensaje;   
	socklen_t clilen;
	char buffer[1024]; // Tamaño del mensaje
	
	numPuerto = atoi(puerto);
	
	pid = fork();
	
	//Si el id es igual a 0 se cierra el socket y se abre una nueva comunicacion
	if (pid == 0) // La parte del sockect que envía
	{
		
		struct sockaddr_in dir_servidor;             
		struct hostent *servidor;
		
		while (1){
			
			sleep (1);
			//Se crea el socket
			socket1 = socket(AF_INET, SOCK_STREAM, 0);
			
			//Muestra error en caso de no poder crear el socket
			if (socket1 < 0) error("ERROR de apertura de socket");
			
			
			//Obtiene la direccion ip del servidor
			
			copiar (ip, IP);
			servidor = gethostbyname(IP);
			
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
			
			printf("\033[34m Yo: ");
			
			
			//Relleno con ceros
			bzero(buffer,1024);
			
			//Lee el mensaje desde la entrada estandar
			fgets(buffer,1023,stdin);
			
						
			//Solicita escribir un mensaje
			mensaje = write(socket1,buffer,strlen(buffer));
			//Si se produce un error al escribir el msj, se muestra el error
			if (mensaje < 0)
				error("ERROR al escribir en socket");
			
			if (strcmp(buffer,"salir\n")==0){
				printf ("\033[31m Conversacion finalizada\n");
				sleep(2);
				break;
			}
			
			//Relleno con ceros
			bzero(buffer,1024);
			//Lee el mensaje
			mensaje = read(socket1,buffer,1023);
			
			//Si se produce un error al leer el msj, se muestra el error
			if (mensaje < 0)
				error("ERROR al leer del socket");
				
			printf("%s", buffer);
			
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
			
						
			bzero(buffer,256);
			sleep (3);
			//Lee el mensaje
			mensaje = read(nuevoSocket,buffer,255);
			//Muestra el error en caso de que se produzca
			if (mensaje < 0)
				error("ERROR al leer del socket");
			
			if (strcmp(buffer,"salir\n")==0){
				printf ("\033[33m Conversacion finalizada\n");
				sleep(2);
				//break;
			}
			
			else{
				//Muestra el mensaje recibido
				printf("\033[32m %s:  %s\n",Usuario, buffer);
				
				mensaje= write (nuevoSocket,"",1);
				if (mensaje< 0)
				error("ERROR al escribir del socket");
			}
				
				close(nuevoSocket);
		}	
	}
	return 0;
}

//Funcion para mostrar todos los contactos
int muestra( ){
	FILE *archivo;//Es un buffer que almacena la dirección del archivo
    char caracteres[30];
    archivo = fopen("listaContactos.txt","r");//Almacena la dirección del archivo
    
    if (archivo == NULL)   exit(1);
     
    while (feof(archivo) == 0) {     //Mientras que no sea el final del documento
        fgets(caracteres,30,archivo);//Toma caracter por caracter del archivo y lo almacena en caracteres
        
        if(feof(archivo) == 0)
		printf("%s",caracteres);       
        }
        fclose(archivo);//Cierra el documento
        
        return 0;
	 
	 }
 
 
 
 
	int Comparar(char arr1[],char arr2[]){
		int x=strlen(arr1);
		int y=strlen(arr2);
		int cont=0; 
		if(x!=y-1){
			return 0; // No se encuentra
		}
		else{
			while(cont+1!=x){
				if (arr1[cont]!=arr2[cont]){
					//No se encuentra
				return 0;
								
				}cont++;
			} 
			return 1; // El contacto se encuentra
					
		}
	}
	//Método para validar si el contacto que se desea agregar ya esta registrado 
	int ValidaContacto(char usuario[]){
		
		FILE *archivo;
		
        char caracteres[30];
        archivo = fopen("listaContactos.txt","r");
 
        if (archivo == NULL)
                exit(1);
                
        while (feof(archivo) == 0)
        {
                fgets(caracteres,30,archivo);
                if((Comparar(usuario,caracteres))==1){
					printf("\nEl contacto ya se encuentra registrado. \n \n");
					return 0;
					}
					}
        
        fclose(archivo);
        return 1;
		}
	
	int Escribir( ){
		FILE * archivo;
		char* users = "listaContactos.txt";//Apunta al archivo en memoria
		char user[30];
		char ip[30];
		char puerto[30];
		
		archivo = fopen(users,"a");//agrega al final del archivo
		if(archivo==NULL) return -1;
			
		
		printf("Escriba el Nombre de usuario:");
		scanf(" %[^\n]",user); //Lee del teclado cosas con espacios hasta presionar enter
		if(!ValidaContacto(user))Menu();
		printf("Escriba el ip:");
		scanf(" %[^\n]",ip);
		printf("Escriba el puerto:");
		scanf(" %[^\n]",puerto);
		
		fprintf(archivo,"%s\n",user);
		fprintf(archivo,"%s\n",ip);
		fprintf(archivo,"%s\n",puerto);
		fclose(archivo);
		
	return 0;
		
		}




		
	int Menu(){
		printf("\033[0m Bienvenidos  al Sistema de comunicacion \n OPCIONES:\n 1)ENVIAR MENSAJES\n 2)LISTA DE AMIGOS \n 3)AGREGAR AMIGOS \n");
		
		int salir=0;
		int opcion;
		while(salir==0){
			opcion=-1;
			
			
			fflush(stdin);
			scanf("%d",&opcion);
			
			if (opcion==1){
				sockets();
			Menu();}
			else if (opcion==2){muestra();
			muestra();
			Menu();}
			else if (opcion==3){Escribir();
			Menu();
			}
			else exit(0);
		}
			return 0;
		
		}
	
	
	int main () {
		
		Menu ();
		return 0;
	}

