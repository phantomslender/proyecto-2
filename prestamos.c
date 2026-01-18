#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prestamos.h"
#include "estudiante.h"
#include "libros.h"
void cargar_prestamos (PRESTAMOS **inicio2){
	FILE *archivo = fopen ("prestamos.txt", "r");
	int id_cop, rut_cop, estado, con=0;
	char ISBN_cop[20], fechapre_co[11], fechaent_co[11];
	if (archivo == NULL){
		printf("ERROR: no se encontro prestamos.txt, iniciando lista vacia\n");
		return;
	}
	PRESTAMOS *nuevo;
	while (fscanf(archivo, "%d,%d,%19[^,],%10[^,],%10[^,],%d", &id_cop, &rut_cop, ISBN_cop, fechapre_co, fechaent_co, &estado)==6){
		nuevo = (PRESTAMOS*)malloc(sizeof(PRESTAMOS));
		if(nuevo == NULL){
			printf("ERROR: en asignasion de memoria......\n");
			fclose (archivo);
			break;
		}
		nuevo->id = id_cop;
		nuevo->rut_estudiante = rut_cop;
		strcpy(nuevo->ISBN , ISBN_cop);
		strcpy(nuevo->fecha_prestamo , fechapre_co);
		strcpy(nuevo->fecha_debolucion, fechaent_co );
		nuevo->estado =estado;
		nuevo->sgte = NULL;
		if (*inicio2 == NULL){
			*inicio2 = nuevo;
		}else{
			PRESTAMOS *aux = *inicio2;
			while (aux->sgte != NULL){
				aux = aux->sgte;
			}
			aux->sgte = nuevo;
		}
		con++;
	}
	fclose (archivo);
	printf("Se cargaron %d datos de prestamos de manera exitosa de prestamos.txt\n", con);
}

void realizar_prestamo(PRESTAMOS **inicio2, int rut, const char *isbn, int id ){
	PRESTAMOS *nuevo = (PRESTAMOS*)malloc(sizeof(PRESTAMOS));
	if (nuevo == NULL){
		printf("ERROR DE MEMORIA :´( \n");
		return;
	}
	printf("\n----------------------------------------\n");
	printf("           Realizando Prestamo            ");
	printf("\n----------------------------------------\n");
	nuevo->id = id;
	nuevo->rut_estudiante = rut;
	nuevo->estado = 0;
	printf ("ingrese fecha del prestamo en formato (DD-MM-AAAA): \n");
	ingresar_fecha (nuevo->fecha_prestamo );
	printf("ingrese fecha de devolucion esperada en formato (DD-MM-AAAA): ");
	ingresar_fecha (nuevo->fecha_debolucion );
	strcpy(nuevo->ISBN , isbn);
	nuevo->sgte = *inicio2;
	*inicio2 = nuevo;
}

void ingresar_fecha (char fecha[11] ){
	int val=0;
	do{
	    fgets (fecha, 11, stdin);
	    fecha[strcspn(fecha, "\n")] = '\0';
	    
	    if (strlen(fecha) == 10 && fecha[2] == '-' && fecha[5] == '-'){
	    	val=1;
		}else{
			printf("ERROR: LA FECHA NO ESTA BIEN ESCRITA\n");
		}
	}while (val==0);
	
}

int contador_id (PRESTAMOS *inicio2){
	int cont = 0;
	while (inicio2 != NULL){
		cont++;
		inicio2 = inicio2->sgte;
	}
	return cont;
}

int  mostrar_pendientes (PRESTAMOS *inicio2, int rut){
	int cont=0;
	while (inicio2 != NULL){
		if (inicio2->rut_estudiante == rut && inicio2->estado == 0){
			printf ("ID: %d, ISBN: %s, FECHA DEL PRESTAMO: %s, FECHA DE ENTREGA: %s\n", inicio2->id, inicio2->ISBN, inicio2->fecha_prestamo, inicio2->fecha_debolucion);
			cont++;
		}
		inicio2 = inicio2->sgte;
	}
	return cont;
}

void devolver(PRESTAMOS *inicio2, int rut, ESTUDIANTES **inicio, LIBROS *inicio1){
    ESTUDIANTES *re;
    PRESTAMOS *p;
    LIBROS *l;
    int can, id_cam;

    re = buscar(*inicio, rut);
    if (re == NULL){
        printf("ERROR: el RUT no existe\n");
        return;
    }

    printf("RUT detectado, estudiante valido\n");

    can = mostrar_pendientes(inicio2, rut);
    if (can == 0){
        printf("El estudiante no tiene prestamos pendientes\n");
        return;
    }

    printf("\nEl estudiante debe %d libros\n", can);

    printf("Ingrese ID del prestamo a devolver: ");
    scanf("%d", &id_cam);
    getchar();

    p = buscar_prestamo_id(inicio2, id_cam);
    if (p == NULL){
        printf("ERROR: prestamo no encontrado o ya devuelto\n");
        return;
    }
    p->estado = 1;

    l = buscar_libro_ISBN(inicio1, p->ISBN);
    if (l != NULL){
        l->prestados --;
    }

    printf("Libro devuelto correctamente\n");
}

PRESTAMOS* buscar_prestamo_id(PRESTAMOS *inicio, int id){
	while (inicio != NULL){
		if (inicio->id == id && inicio->estado == 0){
			return inicio;
		}
		inicio = inicio->sgte;
	}
	return NULL;
}
void actualizar_datos_prestamos (PRESTAMOS **inicio){
	FILE *archivo = fopen("prestamos.txt", "w");
	PRESTAMOS *cop = *inicio;
	if (archivo == NULL){
		printf("ERROR: no se encontro el archivo :(\n");
		return;
	}
	while (cop != NULL){
		fprintf (archivo, "%d,%d,%s,%s,%s,%d\n", cop->id, cop->rut_estudiante, cop->ISBN, cop->fecha_prestamo, cop->fecha_debolucion, cop->estado );
		cop=cop->sgte  ;
	}
	fclose(archivo);
}

void mostrar_estudiantes_con_prestamos (PRESTAMOS *inicio2, ESTUDIANTES *inicio){
	while (inicio2 != NULL){
		if (inicio2->estado == 0){
			printf ("ESTUDIANTE CON PRESTAMOS ACTIVOS\n");
			buscar (inicio, inicio2->rut_estudiante);
		}
		inicio2 = inicio2->sgte;
	}
}
