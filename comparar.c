#include <string.h>
# include <stdio.h>


void imprimir(char ar1[]){
int x=strlen(ar1);
int i=0;
for(i;i<x;i++){
	printf("%c",ar1[i]);}
}

int contar(char arreglo[]){
	int cont =0;
	while(arreglo[cont]!='\0'){
		cont ++;
	}
	return cont;
}

int Comparar(char arr1[],char arr2[]){
	int x=strlen(arr1);
	int y=strlen(arr2);
	int cont=0; 
	if(x!=y-1){
		//printf("falso1");
		return 0;
	}
	else{
		while(cont+1!=x){
			if (arr1[cont]!=arr2[cont]){
				//printf("falso2");
				return 0;
							
			}cont++;
		} printf("es verdadero");
		return 1;
				
	}
}


/***********************************************************************************************************/


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
 
        
        while (feof(archivo) == 0)
        {
                fgets(caracteres,30,archivo);
                if(((Comparar(usuario,caracteres))==1)||(i>0)){
					if(i==0)strcpy(user,caracteres);
					imprimir(user);
					if(i==1)strcpy(ip,caracteres);
					imprimir(ip);
					if(i==2){strcpy(puerto,caracteres);
					i==0;
					imprimir(puerto);
					break;}
					
					i++;
					}
        }
        fclose(archivo);
        return 0;
	 
	 }
 




/************************************************************************************************************/
main(){
char var1[30];
char var2[30];
scanf("%s",&var1);
lee(var1);
//escribir();


}
