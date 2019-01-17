#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIN 1000


typedef struct pos pos;

struct pos{
	int y;
	int x;
	int idEstado;
	int EstadoAnterior;
	char * transicion;
};
int n,m;
int **matriz;
int correlativo;//numera los estados
pos CrearEstado(int x, int y, int EstadoAnterior, char * t);
pos * agregarEstado(pos * lista, int * elementos , pos estado);
int verificarArriba(pos estado);
int verificarDerecha(pos estado);
int verificarAbajo(pos estado);
int verificarIzquierda(pos estado);
pos Arriba(pos estado,pos anterior);
pos Derecha(pos estado,pos anterior);
pos Izquierda(pos estado,pos anterior);
pos Abajo(pos estado,pos anterior);
pos * sacarElemento(pos * lista, int * elementos);
int esFinal(pos estado);
void imprimirEstado(pos estado);
int estaEstado(pos * lista, int elementos, pos estado);



pos CrearEstado(int y,int x,int EstadoAnterior,char * t){
	pos nuevoEstado;
	nuevoEstado.x = x;
	nuevoEstado.y = y;
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.EstadoAnterior = EstadoAnterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}
pos * sacarElemento(pos * lista, int * elementos){
	pos * nuevaLista = (pos *)malloc(sizeof(pos)*(*elementos-1));
	int i;
	for (i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}
pos * agregarEstado(pos * lista, int * elementos,pos estado){
	pos * nuevaLista = (pos *)malloc(sizeof(pos)*(*elementos+1));
	int i;
	for (i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}
int esFinal(pos estado){
	int suma = 0;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			suma = suma + matriz[i][j] ;
		}
	}
	if(suma == 0)
		return 1;
	return 0;
}
void Imprimir(pos estado){
	printf("idEstado:%i,X:%i,Y:%i,EstadoAnterior:%i,transicion:%s\n",estado.idEstado,estado.x,estado.y,estado.EstadoAnterior,estado.transicion);
}
int verificarArriba(pos estado){
	if(estado.y == 0){
		return 0;
	}
	if (estado.y > 0)
	{
		if(matriz[estado.y-1][estado.x] == 0){
			return 0;
		}
		if (matriz[estado.y-1][estado.x] > 0)
		{
			
			return 1;
		}
	}
}
pos Arriba(pos estado,pos anterior){
	matriz[anterior.y][anterior.x] = matriz[anterior.y][anterior.x] - 1 ; 
	return CrearEstado(estado.y-1,estado.x,estado.idEstado,"arriba");
}
int verificarDerecha(pos estado){
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

pos Derecha(pos estado,pos anterior){
	matriz[anterior.y][anterior.x] = matriz[anterior.y][anterior.x] - 1 ; 
	return CrearEstado(estado.y,estado.x+1,estado.idEstado,"derecha");
}
int verificarAbajo(pos estado){
	if(estado.y == m){
		return 0;
	}
	if (estado.y < m)
	{
		if(matriz[estado.y+1][estado.x] == 0){
			return 0;
		}
		if (matriz[estado.y+1][estado.x] > 0)
		{
			return 1;
		}
	}
}
pos Abajo(pos estado,pos anterior){
	matriz[anterior.y][anterior.x] = matriz[anterior.y][anterior.x] - 1 ; 
	return CrearEstado(estado.y+1,estado.x,estado.idEstado,"abajo");
}
int verificarIzquierda(pos estado){
	if(estado.x == 0){
		return 0;
	}
	if (estado.x > 0)
	{
		if(matriz[estado.y][estado.x-1] == 0){
			return 0;
		}
		if (matriz[estado.y][estado.x-1] > 0)
		{
			return 1;
		}	
	}
}
pos Izquierda(pos estado,pos anterior){
	matriz[anterior.y][anterior.x] = matriz[anterior.y][anterior.x] - 1 ; 
	return CrearEstado(estado.y,estado.x-1,estado.idEstado,"Izquierda");
}
int estaEstado(pos * lista, int elementos, pos estado){
	for (int i = 0; i < elementos; ++i){
		if((lista[i].x == estado.x) && (lista[i].y == estado.y))
			return 1;
	}return 0;
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
void mostrarSolucion(pos * lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].idEstado != 0){
		printf("%s\n", lista[ultimo].transicion);
		ultimo = lista[ultimo].EstadoAnterior;
	}
}
void imprimirEstado(pos estado){
	printf("X:%i,Y:%i,idEstado:%i,EstadoAnterior:%i,transicion:%s\n",estado.x,estado.y,estado.idEstado,estado.EstadoAnterior,estado.transicion);
}
void imprimirMatriz(pos estado){
	int i , j ;	
	for (i=0; i<=m; i++) {
     for (j=0; j<=n; j++) {
			printf ("%d ", matriz[i][j]);
			/*
			if(i == estado.y && j == estado.x){
				printf("X ");
			}else{
				
			}
			*/
     }
     printf("\n");
   	}
}
int main()
{
	matriz = leermatriz();
	
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	pos * abiertos = (pos *)malloc(sizeof(pos)*canAbiertos);
	pos * cerrados = (pos *)malloc(sizeof(pos)*canCerrados);
	pos estado;
	pos inicial = CrearEstado(0,4, correlativo,"X");
	pos pActual,pSiguiente,pAnterior;
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	//imprimirMatriz(pActual);
	printf("canAbiertos :%i\n",canAbiertos);
	while(canAbiertos>0){
		pActual = abiertos[0];
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados,pActual);
		//matriz[pActual.y][pActual.x] = matriz[pActual.y][pActual.x] - 1;
		imprimirMatriz(pActual);
		if(esFinal(pActual) == 1){
			printf("llegue a la solucion\n");
			mostrarSolucion(cerrados,canCerrados-1);
			return 0;
		}else{
			//transiciones
			//Arriba
			printf("el valor es arriba :%i\n",verificarArriba(pActual));
			if(verificarArriba(pActual) == 1){
				pAnterior = pActual;
				pSiguiente = Arriba(pActual,pAnterior);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}

			}
			//Derecha
			printf("el valor es derecha :%i\n",verificarDerecha(pActual));
			if(verificarDerecha(pActual) == 1){
				pAnterior = pActual;
				pSiguiente = Derecha(pActual,pAnterior);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			//Abajo
			printf("el valor es abajo :%i\n",verificarAbajo(pActual));
			if(verificarAbajo(pActual) == 1){
				pAnterior = pActual;
				pSiguiente = Abajo(pActual,pAnterior);
				if((estaEstado(abiertos,canAbiertos,pSiguiente) == 0) && (estaEstado(cerrados,canCerrados,pSiguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,pSiguiente);
				}else{
					correlativo = correlativo - 1;
				}

			}
			//Izquierda
			printf("el valor es Izquierda :%i\n",verificarIzquierda(pActual));
			if(verificarIzquierda(pActual) == 1){
				PAnterior = pActual;
				pSiguiente = Izquierda(pActual,pAnterior);
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
	
	return 0;
}
