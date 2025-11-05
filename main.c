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
                imprimirSubMenu();
                break;
    
            case 2:
                imprimirSubMenu();
                break;

            case 3:
                imprimirSubMenu();
                break;

            case 4:
                imprimirSubMenu();
                break;

            case 5:
                imprimirSubMenu();
                break;
  
            case 6:
                imprimirSubMenu();
                break;
               
        }
    }
}
