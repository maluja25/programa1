#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIN 1000




int m ,n ;
int ** crearTablero(int ** posiciones){
	int ** t = (int **)malloc(sizeof(int*)*m);//Se reserva memoria para un tablero de 4 filas
	//Se reserva memoria para todo, con un inicio en 0 para ellas.
	for (int i = 0; i < m; ++i){
		t[i] = (int *)malloc(sizeof(int)*m);//Se reserva memoria para que cada fila posea 4 elementos
		for(int j=0; j< m; j++){
			t[i][j] = 0;
		}
	}
	//Se colocan los 1's correspondientes en cada posición
	for (int i = 0; i < 4; ++i){
		//Se recorren las 4 posiciones, donde la fila corresponde a la posición en 0
		//y la columna a la posición en 1.
		t[posiciones[i][0]][posiciones[i][1]] = 1;
	}
	return t;
}

/*
Función que agrega un elemento a una lista de elementos
Entrada: El conjunto de elementos a donde debo agregar el nuevo elemento
				(Cada elemento es una matriz de enteros, por lo que debe ser una lista de matrices)
			La cantidad de elementos que posee este conjunto (Se pasa por referencia)
			El nuevo elemento a agregar (Una matriz de enteros)
Salida: Un nuevo conjunto de elementos
*/
int *** agregarSolucion(int *** conjunto, int * cantElementos, int ** solucion){
	//Se crea el nuevo conjunto de soluciones
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos+1));
	for (int i = 0; i < *cantElementos+1; ++i){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*m);
		for (int j = 0; j < m; ++j){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*m);
		}
	}
	//Se copian las soluciones existentes
	for (int numSolucion = 0; numSolucion < *cantElementos; ++numSolucion){
		for(int ejeX = 0; ejeX < m; ejeX ++){
			for (int ejeY = 0; ejeY < m; ++ejeY){
				conjuntoNuevo[numSolucion][ejeX][ejeY] = conjunto[numSolucion][ejeX][ejeY];
			}
		}
	}
	//Se agrega la nueva solución
	for (int ejeXSol = 0; ejeXSol < m; ++ejeXSol){
		for (int ejeYSol = 0; ejeYSol < m; ++ejeYSol){
			conjuntoNuevo[*cantElementos][ejeXSol][ejeYSol] = solucion[ejeXSol][ejeYSol];
		}
	}
	*cantElementos = *cantElementos+1;//Se actualiza la cantidad de elementos
	free(conjunto);//Se libera memoria del conjunto de soluciones que ya no se utilizará
	return conjuntoNuevo;
}
/*
Función que elimina un elmento a una lista de elementos
Entrada: El conjunto de elementos a donde debo agregar el nuevo elemento
				(Cada elemento es una matriz de enteros, por lo que debe ser una lista de matrices)
			La cantidad de elementos que posee este conjunto (Se pasa por referencia)
			La posición del elemento a eliminar
Salida: Un nuevo conjunto de elementos
*/
int *** eliminarSolucion(int *** conjunto, int * cantElementos, int posSolEliminar){
	//Se crea el nuevo conjunto de soluciones
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos-1));
	for (int i = 0; i < *cantElementos-1; ++i){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*m);
		for (int j = 0; j < m; ++j){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*m);
		}
	}
	//Se copian las soluciones existentes, excepto aquel que hay que eliminar
	int contNuevaLista = 0;//Este contador corresponde a la lista nueva
	int contAntiguaLista = 0;
	while(contAntiguaLista < *cantElementos){
		//printf("\tComparando: %d con %d\n", contAntiguaLista, posSolEliminar);
		//Acá se verifica que no sea la solución a eliminar
		if(posSolEliminar != contAntiguaLista){
			//printf("\t\tDistintos, se mantiene\n");
			for(int ejeX = 0; ejeX < m; ejeX ++){
				for (int ejeY = 0; ejeY < m; ++ejeY){
					conjuntoNuevo[contNuevaLista][ejeX][ejeY] = conjunto[contAntiguaLista][ejeX][ejeY];
				}
			}//Si se agrega, se aumenta el contador de la nueva lista
			contNuevaLista++;
		}
		else{
			//printf("\t\tcontAntiguaLista eliminado\n");
		}//Siempre se debe avanzar el contador de la lista antigua
		contAntiguaLista++;
	}
	*cantElementos = *cantElementos-1;//Se actualiza la cantidad de elementos
	free(conjunto);//Se libera memoria del conjunto de soluciones que ya no se utilizará
	return conjuntoNuevo;
}
/*
Función que imprime por pantalla un tablero en específico.
Entrada: Matriz de números enteros
*/
void imprimir(int ** t){
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < m; ++j){
			printf("%d ", t[i][j]);
		}
		printf("\n");
	}
	return;
}
/*
Función que imprime una lista de tableros
Entrada: Lista de matrices de enteros
*/
void imprimirSoluciones(int *** soluciones, int cantidadSoluciones){
	for(int nSol = 0; nSol < cantidadSoluciones; nSol ++){
		printf("Solucion N=%d\n", nSol);
		for (int i = 0; i < m; ++i){
			for (int j = 0; j < m; ++j){
				printf("%d ", soluciones[nSol][i][j]);
			}
			printf("\n");
		}
	}
	return;	
}

int **leermatriz(){
  FILE* fp=fopen("Entrada.txt","r");
   char linea[MAX_LIN], *p;
   int val;
   int **matriz= (int **) calloc(1000, sizeof(int *)) ;
   m=-1;
   while (fgets(linea, MAX_LIN, fp)!=NULL) {
     m=m+1;
     printf("La linea es : %s\n", linea);
     matriz[m] = (int *) calloc(MAX_LIN, sizeof(int));
     p = strtok(linea," ");
     n=-1;
     while(p != NULL) {
       n=n+1;
       sscanf(p,"%d",&val);
       printf("%d\n",val);
       matriz[m][n] = val;
       p=strtok(NULL," ");
     }
    }
  	return matriz;
}
int main(){
	int **matriz = leermatriz();
	int cantidadSoluciones = 0;
	//arreglo que almacenara todos los posibles tableros a crear.
	int *** conjuntoSoluciones = (int ***)malloc(sizeof(int**)*cantidadSoluciones);
	imprimirSoluciones(conjuntoSoluciones, cantidadSoluciones);




	return 0;
}