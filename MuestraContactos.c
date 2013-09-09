#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Funcion para mostrar todos los contactos
int muestra( ){
	 FILE *archivo;//Es un buffer que almacena la dirección del archivo
        char caracteres[30];
        archivo = fopen("listaContactos.txt","r");//Almacena la dirección del archivo
        if (archivo == NULL)
                exit(1);
 
        
        while (feof(archivo) == 0)//Mientras que no sea el final del documento
        {
        fgets(caracteres,30,archivo);//Toma caracter por caracter del archivo y lo almacena en caracteres
        if(feof(archivo) == 0)
		printf("%s",caracteres);
               
        }
        fclose(archivo);//Cierra el documento
        return 0;
	 
	 }
 




/************************************************************************************************************/
int main(int argc, char *argv[]){
muestra();
}
