#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LIN 1000

int rellenar(int **matriz,int *arreglo,int x){
	int i = 0;
	while(i<x){
		matriz[0][i] = arreglo[i+1];
		i++;
	}
}
int m,n;
int **leermatriz(){
  FILE* fp=fopen("Entrada.txt","r");
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
int main(int argc, char const *argv[])
{
	int **matriz = leermatriz();
	int **city = (int **)malloc(sizeof(int *)*10);
	for (int i = 0; i < 10; ++i)
	{
		city[i] = (int *)malloc(sizeof(int )*10);
	}

	int *arreglo1 = (int *)malloc(sizeof(int )*10);
	int *arreglo2 = (int *)malloc(sizeof(int )*10);
	for (int i = 0; i <=20; ++i)
	{
		for (int j = 0; j < matriz[0][j]; ++j)
		{
			//	city[i][j] = 0;
			//printf("%i",matriz[i][j]);
			arreglo1[j] = matriz[i+1][j];
			//printf("a%i",arreglo1[j] );
		}
		printf("\n");
	}
	for (int i = 0; i < 15 ; ++i)
	{
		printf("i=%i\n",i);
		int c = 0;
		printf("c%i\n",c);
		while(c < 10){
			printf("c%i\n",c);
			printf("arreglo1%i\n",arreglo1[c]);
			for (int j = 15 - arreglo1[c]; j > 0; --j)
			{
				printf("j %i\n",j);
				int x = 1;
				city[i][j] = matriz[i][j];
				printf("%i",city[i][j]);
			}
			c++;
		}
		
	}
	int pit = 1;
	/*
	rellenar(city,matriz,matriz[pit][1],arreglo,arreglo[0]);
	int i = 0;
	while(i<10){
		printf("%i ",matriz[0][i]);
		i++;
	}
	*/
	printf("\n");
	return 0;
}