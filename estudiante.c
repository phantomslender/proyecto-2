#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "estudiante.h"

void cargar_estudiantes (ESTUDIANTES **inicio){
	FILE *archivo = fopen ("estudiantes.txt", "r");
	int cont=0, co_rut, co_anio;
	char co_prin[50], co_sen[50], co_pria[50], co_sea[50], co_carr[200];
	if (archivo == NULL){
		printf("ERROR, no se encontro estudiantes.txt, iniciando lista vacia\n");
		return;
	}
	ESTUDIANTES *nuevo;
	while (fscanf(archivo, "%d,%49[^,],%49[^,],%49[^,],%49[^,],%199[^,],%d", &co_rut, co_prin, co_sen, co_pria, co_sea, co_carr, &co_anio  )==7){
		nuevo= (ESTUDIANTES*)malloc(sizeof(ESTUDIANTES));
		if(nuevo == NULL){
			printf("ERROR: en asignasion de memoria......\n");
			fclose (archivo);
			break;
		}
		nuevo->rut = co_rut;
		strcpy(nuevo->primer_nombre, co_prin);
		strcpy(nuevo->segundo_nombre, co_sen);
		strcpy(nuevo->primer_apellido, co_pria);
		strcpy(nuevo->segundo_apellido, co_sea);
		strcpy(nuevo->carrera, co_carr);
		nuevo->anio_ingreso = co_anio;
		nuevo->sget = NULL;
		if(*inicio==NULL){
			*inicio=nuevo;
		}else{
			ESTUDIANTES *aux = *inicio;
			while(aux->sget!=NULL){
				aux=aux->sget;
			}
			aux->sget = nuevo;
		}
		cont++;
	}
	fclose (archivo);
	printf("Se cargaron %d estudiantes de manera exitosa de estudiantes.txt\n", cont);
}

int rut_existe (ESTUDIANTES *inicio, int rut){
	while (inicio != NULL){
		if (inicio->rut == rut){
			return 1;
		}
		inicio = inicio->sget;
	}
	return 0;
}

void Agregar_Estudiante (ESTUDIANTES **inicio){
	int i;
	ESTUDIANTES *nuevo = (ESTUDIANTES*)malloc(sizeof(ESTUDIANTES));
	if(nuevo == NULL){
		printf("ERROR DE MEMORIA :´( \n");
		return;
	}
	printf("\n----------------------------------------\n");
	printf("           Agregar Estudiante            ");
	printf("\n----------------------------------------\n");
	printf("ingrese primer nombre:");
	fgets(nuevo->primer_nombre, 50, stdin);
	nuevo->primer_nombre[strcspn(nuevo->primer_nombre,"\n")]='\0';
	
	printf("ingrese segundo nombre: ");
	fgets(nuevo->segundo_nombre, 50, stdin);
	nuevo->segundo_nombre[strcspn(nuevo->segundo_nombre,"\n")]='\0';
	
	printf("ingrese primer apellido: ");
	fgets(nuevo->primer_apellido, 50, stdin);
	nuevo->primer_apellido [strcspn(nuevo->primer_apellido,"\n")]='\0';
	
	printf("ingrese segundo apellido: ");
	fgets(nuevo->segundo_apellido, 50, stdin);
	nuevo->segundo_apellido[strcspn(nuevo->segundo_apellido, "\n" )]='\0';
	
	printf("ingrese carrera del estudiante: ");
	fgets(nuevo->carrera, 200, stdin);
	nuevo->carrera[strcspn(nuevo->carrera, "\n")]='\0';
	do{
    	printf("ingrese rut sin (.), ni (-), ni diguito verificador: ");
	    i = scanf("%d",&nuevo->rut);
		if(i!=1 || nuevo->rut < 1000000 || nuevo->rut >99999999 ){
			printf("Error, rut no valido intente otra vez\n");
		}
		if ((rut_existe ( *inicio, nuevo->rut))==1){
			printf("ERROR: el rut ya existe\n");
		}	
	}while (i!=1 || nuevo->rut < 1000000 || nuevo->rut >99999999 || (rut_existe ( *inicio, nuevo->rut))==1  );
	
	do{
		printf("ingrese anio de ingreso de estudiante: ");
    	scanf("%d", &nuevo->anio_ingreso);
		if (nuevo->anio_ingreso>2025 || nuevo->anio_ingreso < 1980){
			printf("Error anio no valido\n");
		}
	}while (nuevo->anio_ingreso>2025 || nuevo->anio_ingreso < 1980);
	
	getchar();
    nuevo->sget=*inicio;
	*inicio=nuevo;
}
void listar_estudiantes (ESTUDIANTES *inicio){
	ESTUDIANTES *aux = inicio;
	if (aux == NULL){
		printf("no hay estudiantes registrados\n");
		return;
	}
	printf("\n----------------------------------------\n");
	printf("           LISTA ESTUDIANTES            ");
	printf("\n----------------------------------------\n");
	printf("RUT / NOMBRE COMPLETO / CARRERA / ANIO INGRESO ");
	do{
		printf("\n%d / %s %s %s %s / %s / %d", aux->rut, aux->primer_nombre, aux->segundo_nombre, aux->primer_apellido, aux->segundo_apellido, aux->carrera, aux->anio_ingreso);
		aux=aux->sget;
	}while (aux!=NULL);
}

int contar_estudiantes (ESTUDIANTES *inicio){
	int contar=0;
	while (inicio != NULL){
		contar++;
		inicio = inicio->sget; 
	}
	return contar;
}

void transformar_en_arreglo (ESTUDIANTES *inicio, ESTUDIANTES **v ){
	int i=0;
	while (inicio != NULL){
		v[i++] = inicio;
		inicio = inicio->sget;
	}
}

void ordenar_por_rut_burbuja (ESTUDIANTES **v, int cant){
    ESTUDIANTES *aux;
    int i,j;

    for ( i = 0; i < cant - 1; i++){
        for ( j = 0; j < cant - i - 1; j++){
            if (v[j]->rut > v[j + 1]->rut){
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

ESTUDIANTES* busqueda_binaria (ESTUDIANTES **v, int n, int rut){
	int i=0, f=n-1 , m;
	while (i<=f){
		m=(i+f)/2;
		if (v[m]->rut == rut){
			return v[m];
		}else if(rut < v[m]->rut){
			f = m-1;
		}else{
			i=m+1;
		}
	}
	return NULL;
}

ESTUDIANTES* buscar (ESTUDIANTES *inicio, int rut_buscar){
	int n = contar_estudiantes (inicio);
	if (n==0){
		printf ("ERROR: no se pudo iniciar la busqueda al no haber datos 0_0\n");
		return NULL;
	}
	ESTUDIANTES **v = malloc(n * sizeof(ESTUDIANTES*));
	if (v==NULL){
		printf("ERROR EN BUSQUEDA *~*\n");
		return NULL;
	}
	transformar_en_arreglo (inicio, v );
	ordenar_por_rut_burbuja (v, n);
	ESTUDIANTES *encontrado = busqueda_binaria (v, n, rut_buscar );
	if(encontrado != NULL ){
		printf ("esudiante encontrado\n");
		printf ("rut: %d\n", encontrado->rut);
		printf ("nombre completo: %s %s %s %s\n", encontrado->primer_nombre, encontrado->segundo_nombre, encontrado->primer_apellido, encontrado->segundo_apellido );
		printf ("carrera: %s\n", encontrado->carrera);
		printf ("anio de ingreso: %d\n", encontrado->anio_ingreso);
	}else{
	    printf ("ERROR: rut no encontrado en vase de datos >_<\n");
	}
	free (v);
	return encontrado;
}

void actualizar_datos (ESTUDIANTES **inicio){
	FILE *archivo = fopen("estudiantes.txt", "w");
	ESTUDIANTES *cop = *inicio;
	if (archivo == NULL){
		printf("ERROR: no se encontro el archivo :(\n");
		return;
	}
	while (cop != NULL){
		fprintf (archivo, "%d,%s,%s,%s,%s,%s,%d\n", cop->rut, cop->primer_nombre, cop->segundo_nombre, cop->primer_apellido, cop->segundo_apellido, cop->carrera, cop->anio_ingreso);
		cop=cop->sget;
	}
	fclose(archivo);
}
