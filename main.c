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
    int opcion = 0;
    char subopcion;

    validarArchivos(&fClientes, &fEmpleados, &fServicios, &fAgenda);

    while (opcion != 6)
    {
        
        do
        {
            imprimirMenu();
            printf("Opcion: ");
            fflush(stdin);
            scanf("%d", &opcion);
        }while(validarOpcionMenu(opcion));

        switch (opcion)
        {
        case 1:
            do
            {
                do
                {
                    imprimirSubMenu("CLIENTES");
                    printf("Opcion: ");
                    fflush(stdin);
                    scanf(" %c", &subopcion);
                }while(validarSubmenu(subopcion));
               

                switch (subopcion)
                {
                case 'A':
                    AgregarCliente(fClientes);
                    break;
                case 'B':
                    ConsultarCliente(fClientes);
                    break;
                case 'M':
                    ModificarCliente(fClientes);
                    break;
                case 'D':
                    BorrarCliente(fClientes);
                    break;
                case 'S':
                    printf("Saliendo del submenu CLIENTES...\n");
                    break;
                }
            } while (subopcion != 'S');
            break;

        case 2:
            do
            {
                do
                {
                    imprimirSubMenu("EMPLEADOS");
                    printf("Opcion: ");
                    fflush(stdin);
                    scanf(" %c", &subopcion);
                }while(validarSubmenu(subopcion));

                switch (subopcion)
                {
                case 'A':
                    AgregarEmpleado(fEmpleados);
                    break;
                case 'B':
                    ConsultarEmpleado(fEmpleados);
                    break;
                case 'M':
                    ModificarEmpleado(fEmpleados);
                    break;
                case 'D':
                    BorrarEmpleado(fEmpleados);
                    break;
                case 'S':
                    printf("Saliendo del submenu EMPLEADOS...\n");
                    break;
                }
            } while (subopcion != 'S');
            break;

        case 3:
            do
            {
                do
                {
                    imprimirSubMenu("SERVICIOS");
                    printf("Opcion: ");
                    fflush(stdin);
                    scanf(" %c", &subopcion);
                }while(validarSubmenu(subopcion));

                switch (subopcion)
                {
                case 'A':
                    AgregarServicio(fServicios);
                    break;
                case 'B':
                    ConsultarServicio(fServicios);
                    break;
                case 'M':
                    ModificarServicio(fServicios);
                    break;
                case 'D':
                    BorrarServicio(fServicios);
                    break;
                case 'S':
                    printf("Saliendo del submenu SERVICIOS...\n");
                    break;
                }
            } while (subopcion != 'S');
            break;

        case 4:
            do
            {
                do
                {
                    imprimirSubMenu("AGENDA");
                    printf("Opcion: ");
                    fflush(stdin);
                    scanf(" %c", &subopcion);
                }while(validarSubmenu(subopcion));

                switch (subopcion)
                {
                case 'A':
                    AgregarCita(fAgenda);
                    break;
                case 'B':
                    ConsultarCita(fAgenda);
                    break;
                case 'M':
                    ModificarCita(fAgenda);
                    break;
                case 'D':
                   BorrarCita(fAgenda);
                    break;
                case 'S':
                    printf("Saliendo del submenu AGENDA...\n");
                    break;
                }
            } while (subopcion != 'S');
            break;

        case 5:
            do
            {
                do
                {
                    imprimirMenuReportes();
                    printf("Opcion: ");
                    fflush(stdin);
                    scanf(" %c", &subopcion);
                }while(ValidarSubmenuReporte(subopcion));
                
                menuReportes(subopcion);
                if (subopcion == 'h')
                    printf("Saliendo del submenu REPORTES...\n");
            } while (subopcion != 'h');
            break;

        case 6:
            printf("Saliendo del programa...\n");
            break;
        }
    }

    fclose(fClientes);
    fclose(fEmpleados);
    fclose(fServicios);
    fclose(fAgenda);

}
