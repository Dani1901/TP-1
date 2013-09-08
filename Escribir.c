#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int escribir( ){
	FILE * archivo;
	char* users = "listaContactos.txt";//Apunta al archivo en memoria
	char user[30];
	char ip[30];
	char puerto[30];
	
	archivo = fopen(users,"a");//agrega al final del archivo
	if(archivo==NULL) return -1;
		
	
	printf("Escriba el Nombre de usuario:");
	scanf(" %[^\n]",user); //Lee del teclado cosas con espacios hasta presionar enter
	printf("Escriba el ip:");
	scanf(" %[^\n]",ip);
	printf("Escriba el puerto:");
	scanf(" %[^\n]",puerto);
	
	fprintf(archivo,"%s\n",user);
	fprintf(archivo,"%s\n",ip);
	fprintf(archivo,"%s\n",puerto);
	fclose(archivo);
	

	
	}
	
	

	
int contar(char arreglo[]){
	int cont =0;
	while(arreglo[cont]!='\0'){
		cont ++;
	}
	
	return cont;
}

int Comparar(char arreglo1[],char arreglo2[]){
	int x = contar(arreglo1);
	int y = contar(arreglo2);
	int cont=0;
	if (x!= y){
		//printf("falso0");
		return 1;	
	}
         	 		
	while(cont!=x-1){
		printf("%c, %c",arreglo1[cont],arreglo2[cont] );
		if (arreglo1[cont]==arreglo2[cont]){
			cont++;
			printf("Si ");
		}
		else{
			//printf("falso");
		return 1;
		}
	}
		//printf("verdadero");
		return 0;
		
	}
	

	 
	
 int lee(char usuario[]){
	 FILE *archivo;
		
        char caracteres[30];
        static char user[30];
        static char ip[30];
        static char puerto[30];
		int i=0;
        archivo = fopen("listaContactos.txt","r");
 
        if (archivo == NULL)
                exit(1);
 
        printf("\nEl contenido del archivo de prueba es \n\n");
        while (feof(archivo) == 0)
        {
                fgets(caracteres,30,archivo);
				printf("%s",caracteres);
                if(((Comparar(caracteres,usuario))==0)||(i>0)){
					if(i==0){strcpy(user,caracteres);
					printf("ajjajaja","%s",user);}
					if(i==1)strcpy(caracteres,ip);
					if(i==2)strcpy(caracteres,puerto);
					}i++;
        }
 
        fclose(archivo);
        return 0;
	 
	 
	 
	 }
 




int main(int argc, char *argv[]){
	//char usuario[30];
	//printf("Para: ");
	//scanf("%c",&usuario);

	//escribir();
	/*******************************************/
	char user[30];
	printf("Introduzca usuario :");
	scanf("%s",&user);
	lee(user);
	
        
			
	}
