//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LIN 1000

//Variables
int n, m, correlativo;


//Funciones y Estructuras
typedef struct posicion posicion;
typedef struct p p;

/* Estructura para almacenar los datos respecto a la posicion de Spiderman*/
struct posicion{
	int x;
	int y;
	int idEstado;
	int estadoAnterior;
	char * movimiento;
	int **ciudad;
	int altura;
};
<<<<<<< Updated upstream
typedef struct p p;
=======

/* Estructura para almacenar los datos respecto a la posicion de Spiderman al jugar de manera automática, trabaja con los datos
x e y como coordenadas*/
>>>>>>> Stashed changes
struct p{
	int x;
	int y;
};


int verificarArriba(posicion estado,int **matriz);
int verificarDerecha(posicion estado,int **matriz);
int verificarAbajo(posicion estado,int **matriz);
int verificarIzquierda(posicion estado,int **matriz);
posicion Arriba(posicion estado,int **nuevaCiudad);
posicion Derecha(posicion estado,int **nuevaCiudad);
posicion Izquierda(posicion estado,int **nuevaCiudad);
posicion Abajo(posicion estado,int **nuevaCiudad);

<<<<<<< Updated upstream
int correlativo;
=======

/*Entrada: recibe los valores que funcionan como las coordenadas de la posisción, una variable del tipo entero para guardar el 
           estado anterior, un puntero a entero que almacena las transiciones realizadas, la matriz de la ciudad y la altura 
           correspondiente de cada edificio
  Salida:  un nuevo estado.
  Objetivo: Generar un nuevo estado de trabajo para hacer el problema mas próximo a nuestras herramientas
            */
>>>>>>> Stashed changes
posicion CrearEstado(int x, int y, int anterior, char * t,int **ciudad,int altura){
	posicion nuevoEstado;
	nuevoEstado.x = x;
	nuevoEstado.y = y;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.movimiento = t;
	nuevoEstado.ciudad = ciudad;
	nuevoEstado.altura = altura;
	correlativo = correlativo + 1;
	return nuevoEstado;
}
posicion * agregarEstado(posicion * lista, int * elementos, posicion estado){
	posicion * nuevaLista = (posicion *)malloc(sizeof(posicion)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}
posicion * sacarElemento(posicion * lista, int * elementos){
	posicion * nuevaLista = (posicion *)malloc(sizeof(posicion)*(*elementos-1));
	int i;
	for (i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}
int esFinal(posicion estado,int **matriz){
	//printf("la matris es matriz[%i][%i] = %i\n",estado.y,estado.x,matriz[estado.y][estado.x]);
	int suma = 0;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			suma = suma + matriz[i][j];
			//printf("suma es %i\n",suma);
		}
	}
	if(suma == 0){
		return 1;
	}else{
		return 0;
	}
}
int verificarArriba(posicion estado,int **matriz){
	if(estado.y == 0){
		return 0;
	}
	if (estado.y > 0)
	{
		if(matriz[estado.y-1][estado.x] == 0){
			return 0;
		}
		else if (matriz[estado.y-1][estado.x] > 0)
		{
			return 1;
		}
	}
		
}
posicion Arriba(posicion estado,int **nuevaCiudad){
	return CrearEstado(estado.x,estado.y-1,estado.idEstado,"arriba",nuevaCiudad,nuevaCiudad[estado.y][estado.x]);
}

int verificarDerecha(posicion estado,int **matriz){
	if(estado.x == m){
		return 0;
	}
	if (estado.x < m)
	{
		if(matriz[estado.y][estado.x+1] == 0){
			return 0;
		} 
		else if (matriz[estado.y][estado.x+1] > 0)
		{
			return 1;
		}
	}
}

posicion Derecha(posicion estado,int **nuevaCiudad){
	return CrearEstado(estado.x+1,estado.y,estado.idEstado,"derecha",nuevaCiudad,nuevaCiudad[estado.y][estado.x]);
}
int verificarAbajo(posicion estado,int **matriz){
	if(estado.y == m){
		return 0;
	}
	if (estado.y < m)
	{
		if(matriz[estado.y+1][estado.x] == 0){
			return 0;
		}
		else if (matriz[estado.y+1][estado.x] > 0)
		{
			return 1;
		}
	}
}
posicion Abajo(posicion estado,int **nuevaCiudad){
	return CrearEstado(estado.x,estado.y+1,estado.idEstado,"abajo",nuevaCiudad,nuevaCiudad[estado.y][estado.x]);
}
int verificarIzquierda(posicion estado,int **matriz){
	if(estado.x == 0){
		return 0;
	}
	if (estado.x > 0)
	{
		if(matriz[estado.y][estado.x-1] == 0){
			return 0;
		}
		else if (matriz[estado.y][estado.x-1] > 0)
		{
			return 1;
		}	
	}
}
posicion Izquierda(posicion estado,int **nuevaCiudad){
	return CrearEstado(estado.x-1,estado.y,estado.idEstado,"Izquierda",nuevaCiudad,nuevaCiudad[estado.y][estado.x]);
}
int estaEstado(posicion * lista, int elementos, posicion estado){
	for (int i = 0; i < elementos; ++i){
		if((lista[i].x == estado.x) && (lista[i].y == estado.y) && (lista[i].ciudad[estado.y][estado.x] == estado.ciudad[estado.y][estado.x]) && lista[i].idEstado == estado.idEstado)
			return 1;
	}return 0;
}
void mostrarSolucion(posicion * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].movimiento);
		ultimo = lista[ultimo].estadoAnterior;
		printf("el valor de ultimo es :%i\n",ultimo);  
	}
}
void imprimirEstado(posicion estado){
	printf("X:%i,Y:%i,idEstado:%i,EstadoAnterior:%i,movimiento:%s,AE:%i\n",estado.x,estado.y,estado.idEstado,estado.estadoAnterior,estado.movimiento,estado.ciudad[estado.y][estado.x]);
}
int numero;

int mf,nf;
void filas(int **PistasFilas,int numero,int **matriz){
	int contador = 0 , contadorAnterior = 0 , o = 1;
	int i,j;
	for(i = 0 ; i < numero ; i++){
		for (j = 0; j < numero; ++j)
		{
			if(matriz[i][j] > 0){
				contador++;
				if(j==numero-1){
					if(matriz[i][numero-1] > 0){
						j++;
					}
					j++;
				}
			}
			if(matriz[i][j+1] > 0 && j<numero){
				contador = contador ;	
			}
			else if(contador != 0){
					PistasFilas[mf][0] = contador;
					contador = 0;
			}
		}
		mf++;
	}
	nf = 1;
	mf = 0;
	int x,y;
	for( x = 0 ; x < numero ; x++){
		for (y = 0; y < numero; ++y)
		{
			printf("matriz[%i][%i] == %i\n",x,y,matriz[x][y]);
			/*if(matriz[x][y] == 0){
				y++;
			}*/
			if(matriz[x][y] > 0){
				PistasFilas[mf][nf] = matriz[x][y];
				nf++;
			}
		}
		nf=1;
		mf++;
	}
}
int nc,mc;
void columnas(int **PistasColumnas,int numero,int **matriz){
	int contador = 0 , contadorAnterior = 0 , o = 1;
	int i,j;
	mc = 0;
	for(i = 0 ; i < numero ; i++){
		int h = 0;
		for (j = 0; j < numero; ++j)
		{
			printf("matriz[%i][%i] == %i\n",j,i,matriz[j][i]);
			/*if(matriz[j][i] == 0){
				contador = 0;
			}*/
			if(matriz[j][i] == 0){
				contador = 0;
			}
			if(matriz[j][i] > 0 ){
				contador++;
				if(j<numero-1){
					if(matriz[j+1][i] > 0 ){
						contador = contador;
					}else{

						PistasColumnas[mc][h] = contador;
						contador = 0;
						h++;
					}
				}
			}
			if(contador == 0){
				PistasColumnas[mc][0] = 0;
			}
		}
		mc++;
	}
		
}

int **leermatriz(){
  FILE* fp=fopen("matriz.txt","r");
   char linea[MAX_LIN], *p;
   int val;
   int **matriz= (int **) calloc(1000, sizeof(int *)) ;
   m=-1;
   while (fgets(linea, MAX_LIN, fp)!=NULL) {
     m=m+1;
     //printf("La linea es : %s\n", linea);
     matriz[m] = (int *) calloc(MAX_LIN, sizeof(int));
     p = strtok(linea," ");
     n=-1;
     while(p != NULL) {
       n=n+1;
       sscanf(p,"%d",&val);
       //printf("%d\n",val);
       matriz[m][n] = val;
       p=strtok(NULL," ");
     }

    }
  	return matriz;
}
int imprimirMatriz1(int **matriz , int posx ,int posy){
	for (int i = 0; i < m+1; ++i)
	{
		for (int j = 0; j < m+1; ++j)
		{
			if(i == posy && j == posx){
				printf("X ");
			}else{
				printf("%i ",matriz[i][j]);
			}
		}
		printf("\n");
	}
}
int imprimirMatriz2(int **matriz , int posx ,int posy){
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			if(i == posy && j == posx){
				printf("X ");
			}else{
				printf("%i ",matriz[i][j]);
			}
		}
		printf("\n");
	}
}
int verificarMovimiento(int **matriz,p pos){
	int suma = 0;
	if(pos.y == 0){
		suma = suma;
	}else{
		if(matriz[pos.y-1][pos.x] > 0){
			suma++;
		}else{
			suma = suma;
		}
	}
	if(pos.x == m){
		suma = suma;
	}else{
		if(matriz[pos.y][pos.x+1] > 0){
			suma++;
		}else{
			suma = suma;
    	}																		
	}
	if(pos.y == m){
		suma = suma;
	}else{
		if(matriz[pos.y+1][pos.x] > 0){
			suma++;
		}else{
			suma = suma;
		}
	}
	if(pos.x == 0){
		if(matriz[pos.y][pos.x-1] > 0){
			suma++;
		}else{
			suma = suma;
		}
	}
	printf("suma es : %i \n",suma);
	if(suma > 0){
		return 1;
	}else{
		return 0;
	}
}
int movimientosManual(int **matriz,p pos){
	FILE *registro;
 	registro = fopen("registroLab.txt", "a");
	int n;
	printf("pos X = %i , pos Y = %i\n",pos.x,pos.y);
	printf("\n");
	imprimirMatriz1(matriz,pos.x,pos.y);
	printf("\n\n\n\n\n\n");
	printf("1 NORTE\n");
	printf("2 ESTE ->\n");
	printf("3 SUR \n");
	printf("4 OESTE <-\n");
	scanf("%i",&n);
	printf("el n es :%i\n",n);
	switch(n){
		//arriba
		case 1:
			system("clear");
			if(pos.y == 0 ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.y-1][pos.x] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int N = 'N';
				fputc(N,registro);
				fclose(registro);
				matriz[pos.y][pos.x] = matriz[pos.y][pos.x] - 1;
				pos.y--;
				movimientosManual(matriz,pos);
			}
			return 1;
		break;
		case 2:
			system("clear");
			if(pos.x == m ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.y][pos.x+1] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int E = 'E';
				fputc(E,registro);
				fclose(registro);
				matriz[pos.y][pos.x] = matriz[pos.y][pos.x] - 1;
				pos.x++;
				movimientosManual(matriz,pos);
			}
			return 2;
		break;
		case 3:
			system("clear");
			if(pos.y == m ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.y+1][pos.x] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int S = 'S';
				fputc(S,registro);
				fclose(registro);
				matriz[pos.y][pos.x] = matriz[pos.y][pos.x] - 1;
				pos.y++;
				movimientosManual(matriz,pos);
				
			}
			return 3;
		break;
		case 4:
			system("clear");
			if(pos.x == 0 ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.y][pos.x-1] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int O = 'O';
				fputc(O,registro);
				fclose(registro);
				matriz[pos.y][pos.x] = matriz[pos.y][pos.x] - 1;
				pos.x--;
				movimientosManual(matriz,pos);
				
			}
			return 4;
		break;
		default:
			system("clear");
			printf("MOVIMIENTO INVALIDO\n");
			movimientosManual(matriz,pos);
		break;
	}
}
int **copiarMatriz(int **matriz){
	int **nuevaMatriz;
	nuevaMatriz = (int **)malloc(sizeof(int * )*m);
	int i , j ;
	for (i = 0; i <= m; ++i)
	{
		nuevaMatriz[i] = ( int * )malloc(sizeof(int)*m);
	}
	for (i = 0; i <= m; ++i)
	{
		for ( j = 0; j <= m; ++j)
		{
			nuevaMatriz[i][j] = matriz[i][j]; 
		}
	}
	return nuevaMatriz;
}
int automatico(int **matriz,p pos){
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	int **Nciudad;
	posicion * abiertos = (posicion *)malloc(sizeof(posicion)*canAbiertos);
	posicion * cerrados = (posicion *)malloc(sizeof(posicion)*canCerrados);
	posicion estado;
	posicion inicial = CrearEstado(pos.x,pos.y, correlativo,"X",matriz,matriz[pos.y][pos.x]);
	posicion pActual,pSiguiente,pAnterior;
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	printf("canAbiertos :%i\n",canAbiertos);
	while(canAbiertos > 0){
		pActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados,pActual);
		pActual.ciudad[pActual.y][pActual.x] = pActual.ciudad[pActual.y][pActual.x] - 1;
		printf("X:%i,Y:%i,idEstado:%i,EstadoAnterior:%i,movimiento:%s,AE:%i\n",pActual.x,pActual.y,pActual.idEstado,pActual.estadoAnterior,pActual.movimiento,pActual.ciudad[pActual.y][pActual.x]);
		imprimirMatriz2(pActual.ciudad,pActual.x,pActual.y);
		printf("esFinal %i\n",esFinal(pActual,pActual.ciudad));
		printf("la canCerrados es %i\n",canCerrados);
		printf("la canAbiertos es %i\n",canAbiertos);
		if(esFinal(pActual,pActual.ciudad) == 1){
			printf("llegue a la solucion\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{
			//movimientoes
			//Arriba
			
			printf("el valor es arriba :%i\n",verificarArriba(pActual,pActual.ciudad));
			if(verificarArriba(pActual,pActual.ciudad) == 1){
				Nciudad = copiarMatriz(pActual.ciudad);
				/*
				if(Nciudad[pActual.y][pActual.x] > 0){
					Nciudad[pActual.y][pActual.x] = Nciudad[pActual.y][pActual.x] - 1;
				}*/
				pAnterior = pActual;
				pSiguiente = Arriba(pActual,Nciudad);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
					correlativo = correlativo + 1;
				}else{
					correlativo = correlativo - 1;
				}
			}
			//Derecha
			printf("el valor es derecha :%i\n",verificarDerecha(pActual,pActual.ciudad));
			if(verificarDerecha(pActual,pActual.ciudad) == 1){
				Nciudad = copiarMatriz(pActual.ciudad);
				pAnterior = pActual;
				/*
				if(Nciudad[pActual.y][pActual.x] > 0){
					Nciudad[pActual.y][pActual.x] = Nciudad[pActual.y][pActual.x] - 1;
				}*/
				pSiguiente = Derecha(pActual,Nciudad);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
					correlativo = correlativo + 1;
				}else{
					correlativo = correlativo - 1;
				}
			}
			//Abajo
			printf("el valor es abajo :%i\n",verificarAbajo(pActual,pActual.ciudad));
			if(verificarAbajo(pActual,pActual.ciudad) == 1){
				Nciudad = copiarMatriz(pActual.ciudad);
				pAnterior = pActual;
				/*
				if(Nciudad[pActual.y][pActual.x] > 0){
					Nciudad[pActual.y][pActual.x] = Nciudad[pActual.y][pActual.x] - 1;
				}*/
				pSiguiente = Abajo(pActual,Nciudad);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
					correlativo = correlativo + 1;
				}else{
					correlativo = correlativo - 1;
				}

			}
			//Izquierda
			printf("el valor es Izquierda :%i\n",verificarIzquierda(pActual,pActual.ciudad));
			if(verificarIzquierda(pActual,pActual.ciudad) == 1){
				Nciudad = copiarMatriz(pActual.ciudad);
				pAnterior = pActual;
				/*
				if(Nciudad[pActual.y][pActual.x] > 0){
					Nciudad[pActual.y][pActual.x] = Nciudad[pActual.y][pActual.x] - 1;
				}*/
				pSiguiente = Izquierda(pActual,Nciudad);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
					correlativo = correlativo + 1;
				}else{
					correlativo = correlativo - 1;
				}
			}

		}
		
	}
	/*
	printf("ABIERTOS:");
	for (int i = 0; i < canAbiertos; ++i)
	{
		imprimirEstado(abiertos[i]);
	}


	printf("\nCERRADOS:");
	for (int i = 0; i < canCerrados; ++i)
	{
		imprimirEstado(cerrados[i]);
	}
	printf("\n\n");
	*/

}

int main(){
	system("clear");
	int **matriz1 = leermatriz();
	int **matriz2 = leermatriz();
	p pos;
	pos.x = 5;
	pos.y = 0;
	correlativo = 0;
<<<<<<< Updated upstream
=======
	FILE *registro;
	registro = fopen("registroLab.txt", "w");
	fclose(registro);
	pos.x = 5;
	pos.y = 0;
	correlativo = 0;
>>>>>>> Stashed changes
	int posx = 0;
	int posy = 5;
	int Menu = 1;
	int opcion;
	int proceso;
	int k = 1;
	while(Menu = 1){
		printf("Menu de procesos:\n");
		printf("1 generar mapa por entrada\n");
		printf("2 generar el proceso inverso \n");
		printf("3 salir\n");
		proceso = getchar();
		proceso = proceso%48;
		switch(proceso){
			case 1:
				system("clear");
<<<<<<< Updated upstream
				printf("hola en esto momentos spiderman recorrera la ciudad\n");
				automatico(matriz1,pos);
				Menu = 2;
			break;
			case 2:
				system("clear");
				movimientosManual(matriz2,pos);
=======
				printf("Hola, en este momento se generará el mapa de la ciudad\n");
				printf("Menu:\n");


				//agregar matriz por entrada



				printf("1 modo automatico\n");
				printf("2 modo manual\n");
				printf("3 salir\n");
				scanf("%i",&opcion);
				switch(opcion){
					case 1:
						system("clear");
						printf("Spiderman recorrerá la ciudad\n");
//						automatico(matriz1,pos);
						Menu = 2;
					break;
					case 2:
						system("clear");
//						movimientosManual(matriz2,pos);
					break;
					case 3:
						Menu = 2;
					break;
					default:
    				break;
				}
			break;
			case 2:
				system("clear");
				printf("Hola, en este momento se generará el mapa de la ciudad\n");
				printf("Menu:\n");
				printf("1 modo automatico\n");
				printf("2 modo manual\n");
				printf("3 salir\n");
				scanf("%i",&opcion);
				switch(opcion){
					case 1:
						system("clear");
						printf("Spiderman recorrerá la ciudad\n");
						automatico(matriz1,pos);
						Menu = 2;
					break;
					case 2:
						system("clear");
						movimientosManual(matriz2,pos);
					break;
					case 3:
						Menu = 2;
					break;
					default:
    				break;
				}
>>>>>>> Stashed changes
			break;
			case 3:
				Menu = 2;
				return 0;
			break;
			default: 
				Menu = 2;
		}
<<<<<<< Updated upstream
	}
	//imprimirMatriz(matriz,pos.x,pos.y);
	//movimientosManual(matriz,pos);
	/*while(movimientosManual(matriz,pos)<5){
		system("clear");	
	}

	/*
	int **PistasFilas;
	PistasFilas = (int **)malloc(sizeof(int * ) * numero);
	for(int i = 0; i < (numero); ++i)
	{
		PistasFilas[i] = (int *)malloc(sizeof(int ));
	}
	/* 
	arreglo dinamico doble que almacenara las pistas por columnas
	int **PistasColumnas;
	PistasColumnas = (int **)malloc(sizeof(int * ) * numero);
	for(int i = 0; i < (numero); ++i)
	{
		PistasColumnas[i] = (int *)malloc(sizeof(int ));
	}
	filas(PistasFilas,numero,matriz);
	for(int k = 0; k < numero; k++){
		for (int i = 0; i <= PistasFilas[k][0]; ++i)
		{
			printf("%i ",PistasFilas[k][i]);
		}
		printf("\n");
	}


	/*
	columnas(PistasColumnas,numero,matriz);
	for(int k = 0; k < numero; k++){
		for (int i = 0; i < numero; ++i)
		{
			printf("%i\n",PistasColumnas[k][i]);
		}
	} */ 	     	

=======
	}	     	
>>>>>>> Stashed changes
	return 0;
}