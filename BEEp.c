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
	int **ciudad;
	int altura;
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
posicion Arriba(posicion estado,int **nuevaCiudad);
posicion Derecha(posicion estado,int **nuevaCiudad);
posicion Izquierda(posicion estado,int **nuevaCiudad);
posicion Abajo(posicion estado,int **nuevaCiudad);
int correlativo;
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
	if(estado.x == m-1){
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
	if(estado.y == m-1){
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
	/*
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if(i == estado.y && j == estado.x){
				printf("X ");
			}else{
				printf("%i ",estado.ciudad[i][j]);
			}
		}
		printf("\n");
	}
	*/
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
int imprimirMatriz(int **matriz , int posx ,int posy){
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
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
int **copiarMatriz(int **matriz){
	int **nuevaMatriz;
	nuevaMatriz = (int **)malloc(sizeof(int * )*m);
	int i , j ;
	for (i = 0; i < m; ++i)
	{
		nuevaMatriz[i] = ( int * )malloc(sizeof(int)*m);
	}
	for (i = 0; i < m; ++i)
	{
		for ( j = 0; j < m; ++j)
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
		imprimirMatriz(pActual.ciudad,pActual.x,pActual.y);
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

int main(){
	int **matriz2 = leermatriz();
	p pos;
	pos.x = 5;
	pos.y = 0;
	correlativo = 0;
	automatico(matriz2,pos);
	free(matriz2);    	
	return 0;
}