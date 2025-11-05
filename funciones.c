#include <stdio.h>
#include "estructuras.h"
#include "funciones.h"

void imprimirMenu()
{
 printf("\n");
    printf("========================================\n");
    printf("           SISTEMA DE PELUQUERIA        \n");
    printf("========================================\n");
    printf("  [1] Clientes\n");
    printf("  [2] Empleados\n");
    printf("  [3] Servicios\n");
    printf("  [4] Agenda\n");
    printf("  [5] Reportes\n");
    printf("  [6] Salir\n");
    printf("========================================\n");
}

void imprimirSubMenu(char *titulo)
{
	printf("\n");
    printf("========================================\n");
    printf("        SUBMENU DE %s\n", titulo);
    printf("========================================\n");
    printf("  [A] Agregar registros\n");
    printf("  [B] Consultar registros\n");
    printf("  [M] Modificar registros\n");
    printf("  [D] Borrar registros\n");
    printf("  [S] Salir\n");
    printf("========================================\n");
}

void imprimirMenuReportes()
{
    printf("\n");
    printf("========================================\n");
    printf("              MENU DE REPORTES          \n");
    printf("========================================\n");
    printf("  [a] Listado de empleados por puesto\n");
    printf("  [b] Lista de citas por status\n");
    printf("  [c] Listado de citas por fecha\n");
    printf("  [d] Ventas por fecha\n");
    printf("  [e] Generar archivo de clientes\n");
    printf("  [f] Generar archivo de empleados\n");
    printf("  [g] Mostrar archivo\n");
    printf("  [h] Salir\n");
    printf("========================================\n");
}