#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("el ql rico\n");
	int h = 100;
	int count = 1;
	int lista[count];
	printf("modificado\n");
	printf("holaaaaa lol\n");
	printf("listo\n");
<<<<<<< HEAD
<<<<<<< HEAD
	printf("no descargue nada\n");
=======
	printf("el ql rico\n");
>>>>>>> master
=======

>>>>>>> master
	for (int i = 0; i < count; ++i)
	{
		printf("el h es :%i\n",h);
		if(h%2 == 0){
			h = h / 2;
			lista[i] = h;
			if(h == 1){
				lista[i + 1] = 1;
				printf("el h es :%i\n",h);
				count = count;
				return 0;	
			}else{
				count++;
			}
		}if(h%2 !=0){
			h = 3*h + 1;
			lista[i] = h;
			count++;
		}
	}

	return 0;
}
