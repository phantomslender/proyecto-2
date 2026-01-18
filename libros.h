#ifndef LIBROS_H
#define LIBROS_H

typedef struct libro{
	char ISBN[20];
	char titulo[100];
	char categoria[50];
	int stock;
	int prestados;
	char autor[100];
	struct libro *sgte;
}LIBROS;
LIBROS* buscar_libro_ISBN(LIBROS *inicio, char isbn[]);
void agregar_nuevo_libro (LIBROS **inicio1);
void cargar_libros(LIBROS **inicio1);
int existe_isbn (LIBROS *inicio1, const char *isbn );
LIBROS* buscar_titulo (LIBROS *inicio1, const char *titulo_bus);
int strcmp_insensible(const char *a, const char *b);
void aumentar_stock (LIBROS *inicio1, const char *isbn);
void actualizar_datos_libros (LIBROS **inicio);
int buscar_isbn (LIBROS *inicio1, const char *isbn);
int validar_stock (LIBROS *inicio);
void aumentar_prestamos (LIBROS *inicio1, const char *isbn);
int contar_libros(LIBROS *inicio1);
void lista_a_arreglo(LIBROS *inicio1, LIBROS **v);
void burbuja(LIBROS **v, int n);
void mostrar_libros_por_categoria(LIBROS *inicio1);
#endif
