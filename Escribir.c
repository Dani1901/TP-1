# include <stdio.h>

int escribir( ){
	FILE * archivo;
	char* users = "listaContactos.txt";//Apunta al archivo en memoria
	char user[30];
	
	archivo = fopen(users,"a");//agrega al final del archivo
	if(archivo==NULL) return -1;
		
	
	printf("Escriba el Nombre de usuario:");
	scanf(" %[^\n]",user); //Lee del teclado cosas con espacios hasta presionar enter
	
	fprintf(archivo,"%s\n",user);
	fclose(archivo);
	

	
	}
	
	
int leer2(){
	static const char users[] = "listaContactos.txt";
	FILE *file = fopen ( users, "r" );
	if ( file != NULL )
	{
		char linea [30]; //Se almacena cada linea
		while ( fgets ( linea, sizeof linea, file ) != NULL ) //Lee una linea
		{
			fputs ( linea, stdout ); //Escribe la linea en pantalla
		}
		fclose ( file );
	}
	else
	{
		perror ( users ); //Me indica el tipo de error lo transforma a mensaje
	}
	return 0;
}
	
int leer(){
	char listacont[30];
	int indicafin=0;
	FILE * archivo;
	char * users= "listaContactos.txt";
		
	archivo = fopen(users,"r");// Leer desde el .txt
	if (users==NULL)return -1;
		
	printf("Contactos: \n");
		
	indicafin=fscanf(archivo,"%[^\n]",&listacont);//Almacena el EOF en indicafin
		
	while(indicafin!=EOF){//Mientras sea diferende de EOF imprime linea por linea hasta que encuentra enter
		printf("%s\n",listacont);//Recibe puntero a la lista de contactos temporal y la imprime hasta salto de linea.
		indicafin=fscanf(archivo," %[^\n]", &listacont);
	}
	fclose(archivo);
	//Cierra el archivo	
}


int main(int argc, char *argv[]){
	
escribir();
leer();
		
	}
