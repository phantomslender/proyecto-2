#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libros.h"

LIBROS* buscar_libro_ISBN(LIBROS *inicio, char isbn[]){
    while (inicio != NULL){
        if (strcmp(inicio->ISBN, isbn) == 0){
            return inicio;
        }
        inicio = inicio->sgte;
    }
    return NULL;
}

void cargar_libros(LIBROS **inicio1){
	FILE *archivo = fopen ("libros.txt", "r");
	char isbn_cop[20], titu_cop[100], aut_cop[100], cat_cop[50];
	int stock_cop, prest_cop, cont=0;
	if (archivo==NULL){
		printf("ERROR: no se encontro libros.txt, iniciando lista vacia\n");
		return;
	}
	LIBROS *nuevo;
	while (fscanf(archivo, "%19[^,],%99[^,],%99[^,],%49[^,],%d,%d", isbn_cop, titu_cop, aut_cop, cat_cop, &stock_cop, &prest_cop)==6){
		nuevo = (LIBROS*)malloc(sizeof(LIBROS));
		if(nuevo == NULL){
			printf("ERROR: en asignasion de memoria......\n");
			fclose (archivo);
			break;
		}
		strcpy(nuevo->ISBN, isbn_cop);
		strcpy(nuevo->titulo, titu_cop);
		strcpy(nuevo->autor, aut_cop);
		strcpy(nuevo->categoria, cat_cop);
		nuevo->stock = stock_cop;
		nuevo->prestados = prest_cop;
		nuevo->sgte = NULL;
		if(*inicio1==NULL){
			*inicio1=nuevo;
		}else{
			LIBROS *aux= *inicio1;
			while (aux->sgte !=NULL){
				aux=aux->sgte; 
			}
			aux->sgte = nuevo;
		}
		cont++;
	}
	fclose(archivo);
	printf("Se cargaron %d libros de manera exitosa de libros.txt\n", cont);
}

int existe_isbn (LIBROS *inicio1, const char *isbn ){
	while (inicio1 != NULL){
		if (strcmp(inicio1->ISBN, isbn)==0){
			return 1;
		}
		inicio1 = inicio1->sgte;
	}
	return 0;
}
void agregar_nuevo_libro (LIBROS **inicio1){
	LIBROS *nuevo = (LIBROS*)malloc(sizeof(LIBROS));
	if (nuevo == NULL){
		printf ("ERROR DE MEMORIA 1983\n");
		return;
	}
	printf("\n----------------------------------------\n");
	printf("           Agregar Nuevo Libro            ");
	printf("\n----------------------------------------\n");
	
	do{
		printf ("ingrese ISBN del libro: ");
	    fgets (nuevo->ISBN, 20, stdin );
    	nuevo->ISBN [strcspn(nuevo->ISBN ,"\n")]='\0';
    	if ((existe_isbn (*inicio1, nuevo->ISBN ))== 1){
    		printf ("ERROR: este isbn ya exite intente otra vez...\n");
		}
	}while ((existe_isbn (*inicio1, nuevo->ISBN ))== 1);
	
	printf("ingrese titulo del libro: ");
	fgets(nuevo->titulo, 100, stdin);
	nuevo->titulo  [strcspn(nuevo->titulo  ,"\n")]='\0';
	
	printf ("ingrese autor del libro: ");
	fgets (nuevo->autor, 100, stdin);
	nuevo->autor   [strcspn(nuevo->autor   ,"\n")]='\0';
	
	printf("ingrese categoria del libro: ");
	fgets(nuevo->categoria, 50, stdin);
	nuevo->categoria  [strcspn(nuevo->categoria   ,"\n")]='\0';
	do{
		printf("ingrese stock del libro: ");
	    scanf("%d", & nuevo->stock );
	
	    printf("ingrese cantidad prestada del libro: ");
	    scanf ("%d", &nuevo->prestados );
	}while (nuevo->stock <= 0 || nuevo->prestados < 0 || nuevo->prestados > nuevo->stock);
	
	getchar();
	
	nuevo->sgte = *inicio1;
	*inicio1 = nuevo;		
}

LIBROS* buscar_titulo (LIBROS *inicio1, const char *titulo_bus){

	while (inicio1 != NULL){
		if (strcmp_insensible( inicio1->titulo, titulo_bus)==0){
			return inicio1;
		}
		inicio1 = inicio1->sgte;
	}
	return NULL;
}

int strcmp_insensible(const char *a, const char *b){
    while (*a && *b){
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)){
            return tolower((unsigned char)*a) - tolower((unsigned char)*b);
        }
        a++;
        b++;
    }
    return *a - *b;
}


void aumentar_stock (LIBROS *inicio1, const char *isbn){
	LIBROS *aux = inicio1;
	int c;
	
	while (aux != NULL){
		if (strcmp(aux->ISBN, isbn)== 0){
			printf ("Libro encontrado: %s \n", aux->titulo);
			printf ("Stock actual: %d \n", aux->stock);
			do{ 
			    printf ("Ingrese cantida a aumentar el stock: ");
			    scanf("%d", &c);
			    if (c<=0){
			    	printf ("ERROR: no se permite cantidad menor o igual a 0\n");
			    }
	    	}while (c<=0);
	    	aux->stock = aux->stock + c;
	    	printf ("STOCK actual %d\n", aux->stock );
	    	return;
	    }
	    aux = aux->sgte;
	}
	printf("ERROR: No se encontró el libro con ISBN %s\n", isbn);
}
void aumentar_prestamos (LIBROS *inicio1, const char *isbn){
	LIBROS *aux = inicio1;
	int c;
	
	while (aux != NULL){
		if (strcmp(aux->ISBN, isbn)== 0){
	    	aux->prestados++;
	    	return;
	    }
	    aux = aux->sgte;
	}
}
int buscar_isbn (LIBROS *inicio1, const char *isbn){
	LIBROS *aux = inicio1;
	int c;
	
	while (aux != NULL){
		if (strcmp(aux->ISBN, isbn)== 0){
			printf ("Libro encontrado: %s \n", aux->titulo);
			printf ("Stock actual: %d \n", aux->stock);
			if (aux->stock - aux->prestados <=0){
				printf ("todas las copias estan ocupadas\n");
				return 0;
			}
			return 1;
	    }
	    aux = aux->sgte;
	}
	printf("ERROR: No se encontró el libro con ISBN %s\n", isbn);
	return 0;
}

void actualizar_datos_libros (LIBROS **inicio){
	FILE *archivo = fopen("libros.txt", "w");
	LIBROS *cop = *inicio;
	if (archivo == NULL){
		printf("ERROR: no se encontro el archivo :(\n");
		return;
	}
	while (cop != NULL){
		fprintf (archivo, "%s,%s,%s,%s,%d,%d\n", cop->ISBN, cop->titulo, cop->autor, cop->categoria, cop->stock, cop->prestados );
		cop=cop->sgte ;
	}
	fclose(archivo);
}

int validar_stock (LIBROS *inicio){
	return inicio->stock - inicio->prestados;
}

int contar_libros(LIBROS *inicio1){
	int c = 0;
	while (inicio1 != NULL){
		c++;
		inicio1 = inicio1->sgte;
	}
	return c;
}

void lista_a_arreglo(LIBROS *inicio1, LIBROS **v){
	int i = 0;
	while (inicio1 != NULL){
		v[i++] = inicio1;
		inicio1 = inicio1->sgte;
	}
}

void burbuja(LIBROS **v, int n){
	LIBROS *tmp;
	int i, j;

	for (i = 0; i < n - 1; i++){
		for (j = 0; j < n - 1 - i; j++){
			if (strcmp(v[j]->categoria, v[j + 1]->categoria) > 0){
				tmp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = tmp;
			}
		}
	}
}

void mostrar_libros_por_categoria(LIBROS *inicio1){
	int n = contar_libros(inicio1), i;
	if (n == 0){
		printf("No hay libros registrados\n");
		return;
	}

	LIBROS **v = malloc(n * sizeof(LIBROS*));
	if (v == NULL){
		printf("ERROR de memoria\n");
		return;
	}

	lista_a_arreglo(inicio1, v);
	burbuja(v, n);

	printf("\n--- Libros ordenados por categoria ---\n");
	for ( i = 0; i < n; i++){
		printf("Categoria: %s\n", v[i]->categoria);
		printf("Titulo: %s\n", v[i]->titulo);
		printf("Autor: %s\n", v[i]->autor);
		printf("Stock: %d | Prestados: %d\n\n",
		v[i]->stock, v[i]->prestados);
	}

	free(v);
}
