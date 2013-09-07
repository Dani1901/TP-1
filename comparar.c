# include <stdio.h>


int contar(char arreglo[]){
	int cont =0;
	while(arreglo[cont]!='\0'){
		cont ++;
	}
	
	return cont;
}

int Comparar(char arreglo1[],char arreglo2[]){
	int cont=0;
	int x = contar(arreglo1);
	int y = contar(arreglo2);
	if (x!= y){
		
		return 1;	
	}
        char* ptr1=arreglo1;
	char* ptr2=arreglo2; 	 		
	while(*ptr1!='\0'){
	
		if (*ptr1==*ptr2){
			++ptr1;
			++ptr2;
		}
		else{
		
		return 1;
		}
	}
	
		return 0;
	
	}
/*void Menu(){
printf("Bienvenidos  al Sistema de comunicacion \n OPCIONES:\n 1)ENVIAR MENSAJER\n 2)LISTA DE AMIGOS \n 3)AGREGAR AMIGOS \n");
int opcion=0;
scanf("%i",&opcion);
	switch(opcion){
		case '1':
		case '2':
		case '3':

	}
	
}*/

void main(){
char a[]="welcome";
char b[]="welcome";

}



