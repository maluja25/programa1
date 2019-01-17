#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LIN 1000


typedef struct posicion posicion;

struct posicion{
	int x;
	int y;
	int idEstado;
	int estadoAnterior;
	char * movimiento;
};

typedef struct p p;
struct p{
	int x;
	int y;
};

int n,m;
int verificarArriba(posicion estado,int **matriz);
int verificarDerecha(posicion estado,int **matriz);
int verificarAbajo(posicion estado,int **matriz);
int verificarIzquierda(posicion estado,int **matriz);
posicion Arriba(posicion estado);
posicion Derecha(posicion estado);
posicion Izquierda(posicion estado);
posicion Abajo(posicion estado);

int correlativo;
posicion CrearEstado(int x, int y, int anterior, char * t){
	posicion nuevoEstado;
	nuevoEstado.x = x;
	nuevoEstado.y = y;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.movimiento = t;
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
posicion Arriba(posicion estado){
	return CrearEstado(estado.x,estado.y-1,estado.idEstado,"arriba");
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

posicion Derecha(posicion estado){
	return CrearEstado(estado.x+1,estado.y,estado.idEstado,"derecha");
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
posicion Abajo(posicion estado){
	return CrearEstado(estado.x,estado.y+1,estado.idEstado,"abajo");
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
posicion Izquierda(posicion estado){
	return CrearEstado(estado.x-1,estado.y,estado.idEstado,"Izquierda");
}
int estaEstado(posicion * lista, int elementos, posicion estado){
	for (int i = 0; i < elementos; ++i){
		if((lista[i].x == estado.x) && (lista[i].y == estado.y))
			return 1;
	}return 0;
}
void mostrarSolucion(posicion * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].movimiento);
		ultimo = lista[ultimo].estadoAnterior;
	}
}
void imprimirEstado(posicion estado){
	printf("X:%i,Y:%i,idEstado:%i,EstadoAnterior:%i,movimiento:%s\n",estado.x,estado.y,estado.idEstado,estado.estadoAnterior,estado.movimiento);
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
  FILE* fp=fopen("matriz1.txt","r");
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
int imprimirMatriz(int **matriz , int posx ,int posy){
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			if(i == posx && j == posy){
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
	if(pos.x == 0){
		suma = suma;
	}else{
		if(matriz[pos.x-1][pos.y] > 0){
			suma++;
		}else{
			suma = suma;
		}
	}
	if(pos.y == m){
		suma = suma;
	}else{
		if(matriz[pos.x][pos.y+1] > 0){
			suma++;
		}else{
			suma = suma;
    	}																		
	}
	if(pos.x == m){
		suma = suma;
	}else{
		if(matriz[pos.x+1][pos.y] > 0){
			suma++;
		}else{
			suma = suma;
		}
	}
	if(pos.y == 0){
		if(matriz[pos.x][pos.y-1] > 0){
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
	printf("posx%i , posy=%i\n",pos.x,pos.y);
	imprimirMatriz(matriz,pos.x,pos.y);
	printf("\n\n\n\n\n\n");
	printf("1 Arriba\n");
	printf("2 Derecha\n");
	printf("3 Abajo\n");
	printf("4 Izquierda\n");
	scanf("%i",&n);
	printf("el n es :%i\n",n);
	switch(n){
		//arriba
		case 1:
			system("clear");
			if(pos.x == 0 ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.x-1][pos.y] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int N = 'N';
				fputc(N,registro);
				fclose(registro);
				matriz[pos.x-1][pos.y] = matriz[pos.x-1][pos.y] - 1;
				pos.x--;
				movimientosManual(matriz,pos);
			}
			return 1;
		break;
		case 2:
			system("clear");
			if(pos.y == m ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.x][pos.y+1] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int E = 'E';
				fputc(E,registro);
				fclose(registro);
				matriz[pos.x][pos.y+1] = matriz[pos.x][pos.y+1] - 1;
				pos.y++;
				movimientosManual(matriz,pos);
			}
			return 2;
		break;
		case 3:
			system("clear");
			if(pos.x == m ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.x+1][pos.y] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int S = 'S';
				fputc(S,registro);
				fclose(registro);
				matriz[pos.x + 1][pos.y] = matriz[pos.x + 1][pos.y] - 1;
				pos.x++;
				movimientosManual(matriz,pos);
				
			}
			return 3;
		break;
		case 4:
			system("clear");
			if(pos.y == 0 ){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			if(matriz[pos.x][pos.y-1] == 0){
				printf("MOVIMIENTO INVALIDO\n");
				movimientosManual(matriz,pos);
			}
			else{
				int O = 'O';
				fputc(O,registro);
				fclose(registro);
				matriz[pos.x][pos.y-1] = matriz[pos.x][pos.y-1] - 1;
				pos.y--;
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
int automatico(int **matriz,p pos){
	FILE* Mov ;
	int canAbiertos = 0;
	int canCerrados = 0;
	posicion * abiertos = (posicion *)malloc(sizeof(posicion)*canAbiertos);
	posicion * cerrados = (posicion *)malloc(sizeof(posicion)*canCerrados);
	posicion estado;
	posicion inicial = CrearEstado(pos.y,pos.x, correlativo,"X");
	posicion pActual,pSiguiente;
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	printf("canAbiertos :%i\n",canAbiertos);
	while(canAbiertos > 0){
		Mov = fopen("MovAutomaticos.txt","a");
		pActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados,pActual);
		imprimirMatriz(matriz,pActual.y,pActual.x);
		printf("esFinal %i\n",esFinal(pActual,matriz));
		if(esFinal(pActual,matriz) == 1){
			printf("llegue a la solucion\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{
			//movimientoes
			//Arriba
			printf("el valor es arriba :%i\n",verificarArriba(pActual,matriz));
			if(verificarArriba(pActual,matriz) == 1){
				if(matriz[pActual.y][pActual.x] > 0){
					matriz[pActual.y][pActual.x] = matriz[pActual.y][pActual.x] - 1;
				}
				pSiguiente = Arriba(pActual);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}

			}
			//Derecha
			printf("el valor es derecha :%i\n",verificarDerecha(pActual,matriz));
			if(verificarDerecha(pActual,matriz) == 1){
				if(matriz[pActual.y][pActual.x] > 0){
					matriz[pActual.y][pActual.x] = matriz[pActual.y][pActual.x] - 1;
				}
				pSiguiente = Derecha(pActual);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//Abajo
			printf("el valor es abajo :%i\n",verificarAbajo(pActual,matriz));
			if(verificarAbajo(pActual,matriz) == 1){
				pSiguiente = Abajo(pActual);
				if(matriz[pActual.y][pActual.x] > 0){
					matriz[pActual.y][pActual.x] = matriz[pActual.y][pActual.x] - 1;
				}
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}

			}
			//Izquierda
			printf("el valor es Izquierda :%i\n",verificarIzquierda(pActual,matriz));
			if(verificarIzquierda(pActual,matriz) == 1){
				pSiguiente = Izquierda(pActual);
				if(matriz[pActual.y][pActual.x] > 0){
					matriz[pActual.y][pActual.x] = matriz[pActual.y][pActual.x] - 1;
				}
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}

			}

		}
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
	} 




}

int main(){
	int **matriz1 = leermatriz();
	int **matriz2 = leermatriz();
	p pos;
	pos.x = 0;
	pos.y = 2;
	correlativo = 0;
	FILE *registro;
	registro = fopen("registroLab.txt", "w");
	fclose(registro);

	int posx = 0;
	int posy = 2;
	int Menu = 1;
	int opcion;
	int k = 1;
	while(Menu = 1){
		printf("Menu\n");
		printf("1 modo automatico\n");
		printf("2 modo manual\n");
		printf("3 salir\n");
		scanf("%i",&opcion);
		switch(opcion){
			case 1:
				system("clear");
				printf("hola en esto momentos spiderman recorrera la ciudad\n");
				automatico(matriz1,pos);
				return 0;
				Menu = 2;
			break;
			case 2:
				system("clear");
				while(k = 1){
					if(verificarMovimiento(matriz2,pos) == 0){
						k = 2;
					}else{
						k = 1;
					}
					printf("K es = %i\n",k);
					movimientosManual(matriz2,pos);
				}
			break;
			case 3:
				Menu = 2;
			break;
		}
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
	return 0;
}