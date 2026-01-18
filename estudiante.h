#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

typedef struct estudiante{
	int rut;
	char primer_nombre[50];
	char segundo_nombre[50];
	char primer_apellido[50];
	char segundo_apellido[50];
	char carrera[200];
	int anio_ingreso;
	struct estudiante *sget;
}ESTUDIANTES;

void Agregar_Estudiante (ESTUDIANTES **inicio);
void listar_estudiantes (ESTUDIANTES *inicio);
void cargar_estudiantes (ESTUDIANTES **inicio);
int contar_estudiantes (ESTUDIANTES *inicio);
void transformar_en_arreglo (ESTUDIANTES *inicio, ESTUDIANTES **v );
void ordenar_por_rut_burbuja (ESTUDIANTES **v, int cant);
ESTUDIANTES* busqueda_binaria (ESTUDIANTES **v, int n, int rut);
ESTUDIANTES* buscar (ESTUDIANTES *inicio, int rut_buscar);
void actualizar_datos (ESTUDIANTES **inicio);
int rut_existe (ESTUDIANTES *inicio, int rut);

#endif
