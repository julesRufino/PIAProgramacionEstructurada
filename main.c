#include <stdio.h>
#include "funciones.h"
#include "validaciones.h"
#include "estructuras.h"


main()
{
    FILE *fClientes;
    FILE *fEmpleados;
    FILE *fServicios;
    FILE *fAgenda;
    int opcion=0;
    char subopcion;

    validarArchivos(&fClientes, &fEmpleados, &fServicios, &fAgenda);

    while(opcion!=6)
    {
        imprimirMenu();
        printf("Opcion: ");
        scanf("%d", &opcion);
        //validarOpcionMenu(&opcion);

        switch(opcion)
        {
            case 1:
                imprimirSubMenu("CLIENTES");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                break;
    
            case 2:
                imprimirSubMenu("EMPLEADOS");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                break;

            case 3:
                imprimirSubMenu("SERVICIOS");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                break;

            case 4:
                imprimirSubMenu("AGENDA");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                break;

            case 5:
                imprimirMenuReportes();
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenuReporte(&subopcion);
                break;
  
            case 6:
                break;
               
        }
    }
}
