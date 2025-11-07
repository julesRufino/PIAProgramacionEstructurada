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
                switch(subopcion)
                {
                    case 'A':
                        //AgregarCliente(fClientes);
                        break;
                    case 'B':
                        //ConsultarCliente(fClientes);
                        break;
                    case 'M':
                        //ModificarCliente(fClientes);
                        break;
                    case 'D':
                        //BorrarCliente(fClientes);
                        break;
                    case 'S':
                        break;
                }

                break;
    
            case 2:
                imprimirSubMenu("EMPLEADOS");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                switch(subopcion)
                {
                    case 'A':
                        //AgregarEmpleado(fEmpleados);
                        break;
                    case 'B':
                        //ConsultarEmpleado(fEmpleados);
                        break;
                    case 'M':
                        //ModificarEmpleado(fEmpleados);
                        break;
                    case 'D':
                        //BorrarEmpleado(fEmpleados);
                        break;
                    case 'S':
                        break;
                }

                break;

            case 3:
                imprimirSubMenu("SERVICIOS");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                switch(subopcion)
                {
                    case 'A':
                        //AgregarServicio(fServicios);
                        break;
                    case 'B':
                        //ConsultarServicio(fServicios);
                        break;
                    case 'M':
                        //ModificarServicio(fServicios);
                        break;
                    case 'D':
                        //BorrarServicio(fServicios);
                        break;
                    case 'S':
                        break;
                }
                break;

            case 4:
                imprimirSubMenu("AGENDA");
                printf("Opcion: ");
                scanf(" %c", &subopcion);
                //ValidarSubmenu(&subopcion);
                switch(subopcion)
                {
                    case 'A':
                        //AgregarCita(fAgenda);
                        break;
                    case 'B':
                        //ConsultarCita(fAgenda);
                        break;
                    case 'M':
                        //ModificarCita(fAgenda);
                        break;
                    case 'D':
                        //BorrarCita(fAgenda);
                        break;
                    case 'S':
                        break;
                }
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
    fclose(fClientes);
    fclose(fEmpleados);
    fclose(fServicios);
    fclose(fAgenda);
}
