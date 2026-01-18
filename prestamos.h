#ifndef PRESTAMOS_H
#define PRESTAMOS_H
#include "prestamos.h"
#include "estudiante.h"
#include "libros.h"

typedef struct prestamos{
	int id;
	int rut_estudiante;
	char ISBN[20];
	char fecha_prestamo[11];
	char fecha_debolucion[11];
	int estado;
	struct prestamos *sgte;
}PRESTAMOS;

void realizar_prestamo(PRESTAMOS **inicio2, int rut, const char *isbn , int id);
void ingresar_fecha (char fecha[11] );
void cargar_prestamos (PRESTAMOS **inicio2);
int contador_id (PRESTAMOS *inicio2);
PRESTAMOS* buscar_prestamo_id(PRESTAMOS *inicio, int id);
void devolver(PRESTAMOS *inicio2, int rut, ESTUDIANTES **inicio, LIBROS *inicio1);
int  mostrar_pendientes (PRESTAMOS *inicio2, int rut);
void actualizar_datos_prestamos (PRESTAMOS **inicio);
void mostrar_estudiantes_con_prestamos (PRESTAMOS *inicio2, ESTUDIANTES *inicio);
#endif
