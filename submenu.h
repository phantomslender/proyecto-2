#ifndef SUBMENU_H
#define SUBMENU_H

#include "estudiante.h"
#include "libros.h"
#include "prestamos.h"

void menu_estudiantes (ESTUDIANTES **inicio);
void menu_libros (LIBROS **inicio1);
void menu_prestamo (PRESTAMOS **inicio2, ESTUDIANTES **inicio, LIBROS **inicio1);
void menu_reportes (ESTUDIANTES **inicio, LIBROS **inicio1, PRESTAMOS **inicio2 );

#endif
