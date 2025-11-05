#include <stdio.h>
#include "estructurasPeluqueria.h"
#include "funcionesPeluqueria.h"

void imprimirMenu()
{
	printf("--------Menu--------\n");
	printf("1) Clientes\n");
	printf("2) Empleados\n");
	printf("3) Servicios\n");
	printf("4) Agenda\n");
	printf("5) Reportes\n");
	printf("6) Salir\n");
}

void imprimirSubMenu()
{
	printf("--------Sub Menu--------\n");
	printf("A: Agregar \"registros\"\n");
	printf("B: Consultar \"registros\"\n");
	printf("M: Modificar \"registros\"\n");
	printf("D: Borrrar \"registros\"\n");
	printf("S: Salir\n");
}
