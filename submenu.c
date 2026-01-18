#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "submenu.h"


void menu_estudiantes (ESTUDIANTES **inicio){
	int opes, rut_busc ,i ;
	do{
		printf("\n----------------------------------------\n");
		printf("           Gestion de Estudiantes            ");
		printf("\n----------------------------------------\n");
		printf("Opcion 1: Agregar Estudiante\n");
		printf("Opcion 2: Buscar Estudiante\n");
		printf("Opcion 3: Listar Estudiantes\n");
		printf("Opcion 0: Volver al menu principal\n");
		printf("----------------------------------------\n");
		printf("Seleccione Opcion: ");
		scanf("%d", &opes);
		getchar();
		switch (opes){
			case 0:
	        	printf("volviendo...... :/\n");
				break;
			case 1:
				Agregar_Estudiante (inicio);
				break;
			case 2:
					do{
    	                printf("ingrese rut a bucar, sin (.), ni (-), ni diguito verificador: ");
	                    i = scanf("%d",&rut_busc);
		                if(i!=1 || rut_busc < 1000000 || rut_busc >99999999 ){
		                	printf("Error, rut no valido intente otra vez\n");
	                	}	
	                }while (i!=1 || rut_busc < 1000000 || rut_busc >99999999 );
	                buscar (*inicio, rut_busc);
				break;
			case 3:
				listar_estudiantes (*inicio);
				break;
			default:
				printf("ERROR: Opcion no valida :D\n");
		}
	}while(opes!=0);	
}

void menu_libros (LIBROS **inicio1){
	int opli;
	char titu_bu[100], isbn_bu[20];
	do{
		printf("\n----------------------------------------\n");
    	printf("           Gestion de Libros            ");
    	printf("\n----------------------------------------\n");
    	printf("Opcion 1: Agregar Nuevo Libro\n");
    	printf("Opcion 2: Buscar Libro\n");
    	printf("Opcion 3: Aumentar Stock\n");
    	printf("Opcion 0: Volver al menu principal\n");
    	printf("----------------------------------------\n");
    	printf("Seleccione Opcion: ");
    	scanf("%d",& opli);
    	getchar();
    	switch(opli){
	    	case 0:
	    		printf("volviendo...........:3");
		    	break;
	    	case 1:
                agregar_nuevo_libro (inicio1);
	    		break;
	    	case 2:{
	    		printf ("Igrese titulo a buscar: ");
	    		fgets (titu_bu, 100, stdin);
	    		titu_bu[strcspn(titu_bu, "\n")] = '\0';
	    		
	    		LIBROS *en = buscar_titulo (*inicio1, titu_bu);
	    		if (en != NULL){
	    			printf ("Libro encontrado\n");
	    			printf ("ISBN: %s \n", en->ISBN);
	    			printf ("Titulo: %s \n", en->titulo);
	    			printf ("Autor: %s \n", en->autor);
	    			printf ("Categoria: %s \n", en->categoria);
	    			printf ("Stock: %d \n", en->stock);
	    			printf ("Prestados: %d \n", en->prestados );
				}else{
					printf ("ERROR: no se pudo encontrar\n");
				}
				break;
			}
	    	case 3:
	    		printf ("Ingrese ISBN a buscar: ");
	    		fgets (isbn_bu, 20, stdin);
	    		isbn_bu[strcspn(isbn_bu, "\n")] = '\0';
	    		aumentar_stock (*inicio1, isbn_bu);
	    		break;
	    	default:
	    		printf("ERROR: Opcion no valida >:(");	
	    }
	}while (opli!=0);
}

void menu_prestamo (PRESTAMOS **inicio2, ESTUDIANTES **inicio, LIBROS **inicio1){
	int oppr,rut_bu,i, id = contador_id (*inicio2);
	char ISBN_bu[20];
	do{
		printf("\n----------------------------------------\n");
		printf("           Gestion de Prestamos            ");
		printf("\n----------------------------------------\n");
		printf("Opcion 1: Realizar Prestamo\n");
		printf("Opcion 2: Devolucion de Libro\n");
		printf("Opcion 0: Volver al menu principal \n");
		printf("----------------------------------------\n");
		printf("Seleccione Opcion: ");
		scanf("%d", &oppr);
		switch(oppr){
			case 0:
				printf("volviendo...........:P");
				break;
			case 1:{
	            do{
    	            printf("ingrese rut sin (.), ni (-), ni diguito verificador del estudiante: ");
	                i = scanf("%d",&rut_bu);
	                if(i!=1 || rut_bu < 1000000 || rut_bu >99999999 ){
		                printf("Error, rut no valido intente otra vez\n");
	 	           }	
	            }while (i!=1 || rut_bu < 1000000 || rut_bu >99999999);
	            while(getchar() != '\n');
	            
	            printf ("ingrese ISBN del libro: ");
	            fgets (ISBN_bu, 20, stdin );
    	        ISBN_bu [strcspn(ISBN_bu ,"\n")]='\0';
    	        
    	        ESTUDIANTES *re = buscar ( *inicio , rut_bu );
    	        
    	        if (buscar_isbn (*inicio1, ISBN_bu)==1 && re != NULL ){
    	            printf ("ISBN y RUT detectados si existen\n");
    	            realizar_prestamo(inicio2, rut_bu, ISBN_bu, id );
    	            aumentar_prestamos (*inicio1, ISBN_bu);
    	            id++;
    	        }else{
    	            printf ("ERROR; no se a encontrado alguno de los dos\n");
		        }
		        
		        
				break;
			}
			case 2:{
				do{
    	            printf("ingrese rut sin (.), ni (-), ni diguito verificador del estudiante: ");
	                i = scanf("%d",&rut_bu);
	                if(i!=1 || rut_bu < 1000000 || rut_bu >99999999 ){
		                printf("Error, rut no valido intente otra vez\n");
	 	           }	
	            }while (i!=1 || rut_bu < 1000000 || rut_bu >99999999);
	            while(getchar() != '\n');
	            devolver(*inicio2, rut_bu, inicio, *inicio1);
				break;
			}
			default:
				printf("ERROR: Opcion no valida :V");
		}
	}while(oppr !=0);
}

void menu_reportes (ESTUDIANTES **inicio, LIBROS **inicio1, PRESTAMOS **inicio2 ){
	int opre;
	do{
		printf("\n----------------------------------------\n");
		printf("                Reportes                  ");
		printf("\n----------------------------------------\n");
		printf("Opcion 1: Libros por Categoria:\n");
		printf("Opcion 2: Alumnos con Prestamos Activos\n");
		printf("Opcion 0: Volver al menu principal \n");
		printf("\n----------------------------------------\n");
		printf("Seleccione Opcion: \n");
		scanf("%d", &opre);
		switch (opre){
			case 0:
				printf("volviendo...........:T");
				break;
			case 1:
				mostrar_libros_por_categoria(*inicio1);
				break;
			case 2:
				mostrar_estudiantes_con_prestamos (*inicio2, *inicio);
				break;
			default:
				printf("ERROR: Opcion no valida :O");
		}
	}while(opre != 0);
}
	


