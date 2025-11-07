#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"
#include "validaciones.h"

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

void AgregarCliente(FILE *fptr)
{
    struct DatosCliente cliente;
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        do
        {
            printf("Ingresa la clave del cliente (1-100): ");
            scanf("%d", &clave);
        } while (/*validarPositivo(clave)*/ 0); // temporalmente omitido

        fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
        fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

        if (cliente.clave != 0)
        {
            printf("Esa clave ya existe.\n");
        }
        else
        {
            fflush(stdin);
            printf("Nombre del cliente: ");
            gets(cliente.nombre);

            printf("Fecha de nacimiento (dd/mm/aaaa): ");
            gets(cliente.fechaNacimiento);

            printf("Telefono: ");
            gets(cliente.telefono);

            printf("Correo electronico: ");
            gets(cliente.correoElectronico);


            cliente.clave = clave;

            fseek(fptr, (cliente.clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
            fwrite(&cliente, sizeof(struct DatosCliente), 1, fptr);
            fflush(fptr);

            printf("Cliente agregado correctamente.\n");
        }

        printf("Deseas agregar otro cliente? (s/n): ");
        scanf(" %c", &continuar);
    }
}


void ConsultarCliente(FILE *fptr)
{
    struct DatosCliente cliente;
    int opcion, clave, contador=1, encontrados=0;
    char nombreBuscado[50];

    do
    {
        printf("\n--- CONSULTAR CLIENTE ---\n");
        printf("1. Buscar por clave\n");
        printf("2. Buscar por nombre\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            printf("Ingresa la clave del cliente a consultar: ");
            scanf("%d", &clave);
            fflush(stdin);

            fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
            fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

            if (cliente.clave == 0)
            {
                printf("Cliente no encontrado.\n");
            }
            else
            {
                printf("\n--- Datos del Cliente ---\n");
                printf("Clave: %d\n", cliente.clave);
                printf("Nombre: %s\n", cliente.nombre);
                printf("Fecha de nacimiento: %s\n", cliente.fechaNacimiento);
                printf("Telefono: %s\n", cliente.telefono);
                printf("Correo: %s\n", cliente.correoElectronico);
                printf("--------------------------\n");
            }
            break;

        case 2:
            printf("Ingresa parte del nombre del cliente a buscar: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = 0; 

            rewind(fptr);

            while (!feof(fptr) && contador < 100)
            {
                fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

                if (strstr(cliente.nombre, nombreBuscado) != NULL)
                {
                    printf("\n---Coincidencia %d ---\n", contador);
                    printf("Clave: %d\n", cliente.clave);
                    printf("Nombre: %s\n", cliente.nombre);
                    printf("Fecha de nacimiento: %s\n", cliente.fechaNacimiento);
                    printf("Telefono: %s\n", cliente.telefono);
                    printf("Correo: %s\n", cliente.correoElectronico);
                    printf("--------------------------\n");
                    encontrados++;
                }

                contador++;
            }

            if (encontrados == 0)
            {
                printf("No se encontraron coincidencias.\n");
            }

            break;

        case 3:
            printf("Saliendo de consulta.\n");
            break;
        }

    } while (opcion != 3);
}

void ModificarCliente(FILE *fptr)
{
    struct DatosCliente cliente;
    int clave;

    printf("Ingresa la clave del cliente a modificar: ");
    scanf("%d", &clave);

    fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
    fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

    if (cliente.clave == 0)
    {
        printf("Cliente no encontrado.\n");
    }
    else
    {
        printf("\nModificando datos del cliente '%s'\n", cliente.nombre);
        fflush(stdin);

        printf("Nuevo nombre: ");
        gets(cliente.nombre);
        printf("Nueva fecha de nacimiento: ");
        gets(cliente.fechaNacimiento);
        printf("Nuevo telefono: ");
        gets(cliente.telefono);
        printf("Nuevo correo: ");
        gets(cliente.correoElectronico);

        fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
        fwrite(&cliente, sizeof(struct DatosCliente), 1, fptr);
        fflush(fptr);

        printf("Cliente modificado correctamente.\n");
    }
}


void BorrarCliente(FILE *fptr)
{
    struct DatosCliente cliente;
    int clave;

    printf("Ingresa la clave del cliente a borrar: ");
    scanf("%d", &clave);

    fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
    fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

    if (cliente.clave == 0)
    {
        printf("Cliente no encontrado.\n");
    }
    else
    {

        fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
        fwrite(&cliente, sizeof(struct DatosCliente), 1, fptr);
        fflush(fptr);
        printf("Cliente eliminado correctamente.\n");
    }
}


void AgregarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado;
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        do
        {
            printf("Ingresa la clave del empleado (1-100): ");
            scanf("%d", &clave);
        } while (/*validarPositivo(clave)*/ 0);

        fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
        fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

        if (empleado.clave != 0)
        {
            printf("Esa clave ya existe.\n");
        }
        else
        {
            fflush(stdin);
            printf("Nombre del empleado: ");
            gets(empleado.nombre);
            printf("Puesto: ");
            gets(empleado.puesto);
            printf("Fecha de contratacion (dd/mm/aaaa): ");
            gets(empleado.fechaContratacion);
            printf("Telefono: ");
            gets(empleado.telefono);
            printf("Correo electronico: ");
            gets(empleado.correoElectronico);

            empleado.clave = clave;

            fseek(fptr, (empleado.clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
            fwrite(&empleado, sizeof(struct DatosEmpleado), 1, fptr);
            fflush(fptr);

            printf("Empleado agregado correctamente.\n");
        }

        printf("Deseas agregar otro empleado? (s/n): ");
        scanf(" %c", &continuar);
    }
}


void ConsultarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado;
    int opcion, clave, contador = 1, encontrados = 0;
    char nombreBuscado[50];

    do
    {
        printf("\n--- CONSULTAR EMPLEADO ---\n");
        printf("1. Buscar por clave\n");
        printf("2. Buscar por nombre\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            printf("Ingresa la clave del empleado a consultar: ");
            scanf("%d", &clave);
            fflush(stdin);

            fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
            fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

            if (empleado.clave == 0)
            {
                printf("Empleado no encontrado.\n");
            }
            else
            {
                printf("\n--- Datos del Empleado ---\n");
                printf("Clave: %d\n", empleado.clave);
                printf("Nombre: %s\n", empleado.nombre);
                printf("Puesto: %s\n", empleado.puesto);
                printf("Fecha de contratacion: %s\n", empleado.fechaContratacion);
                printf("Telefono: %s\n", empleado.telefono);
                printf("Correo: %s\n", empleado.correoElectronico);
                printf("--------------------------\n");
            }
            break;

        case 2:
            printf("Ingresa parte del nombre del empleado a buscar: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

            rewind(fptr);

            while (!feof(fptr) && contador < 100)
            {
                fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

                if (strstr(empleado.nombre, nombreBuscado) != NULL)
                {
                    printf("\n--- Coincidencia %d ---\n", contador);
                    printf("Clave: %d\n", empleado.clave);
                    printf("Nombre: %s\n", empleado.nombre);
                    printf("Puesto: %s\n", empleado.puesto);
                    printf("Fecha de contratacion: %s\n", empleado.fechaContratacion);
                    printf("Telefono: %s\n", empleado.telefono);
                    printf("Correo: %s\n", empleado.correoElectronico);
                    printf("--------------------------\n");
                    encontrados++;
                }
                contador++;
            }

            if (encontrados == 0)
                printf("No se encontraron coincidencias.\n");

            break;

        case 3:
            printf("Saliendo de consulta.\n");
            break;
        }

    } while (opcion != 3);
}


void ModificarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado;
    int clave;

    printf("Ingresa la clave del empleado a modificar: ");
    scanf("%d", &clave);

    fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
    fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

    if (empleado.clave == 0)
    {
        printf("Empleado no encontrado.\n");
    }
    else
    {
        printf("\nModificando datos del empleado '%s'\n", empleado.nombre);
        fflush(stdin);

        printf("Nuevo nombre: ");
        gets(empleado.nombre);
        printf("Nuevo puesto: ");
        gets(empleado.puesto);
        printf("Nueva fecha de contratacion: ");
        gets(empleado.fechaContratacion);
        printf("Nuevo telefono: ");
        gets(empleado.telefono);
        printf("Nuevo correo: ");
        gets(empleado.correoElectronico);

        fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
        fwrite(&empleado, sizeof(struct DatosEmpleado), 1, fptr);
        fflush(fptr);

        printf("Empleado modificado correctamente.\n");
    }
}


void BorrarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado;
    int clave;

    printf("Ingresa la clave del empleado a borrar: ");
    scanf("%d", &clave);

    fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
    fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

    if (empleado.clave == 0)
    {
        printf("Empleado no encontrado.\n");
    }
    else
    {
        memset(&empleado, 0, sizeof(struct DatosEmpleado));
        fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
        fwrite(&empleado, sizeof(struct DatosEmpleado), 1, fptr);
        fflush(fptr);
        printf("Empleado eliminado correctamente.\n");
    }
}


void AgregarServicio(FILE *fptr)
{
    struct DatosServicio servicio;
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        do
        {
            printf("Ingresa la clave del servicio (1-100): ");
            scanf("%d", &clave);
        } while (/*validarPositivo(clave)*/ 0);

        fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

        if (servicio.clave != 0)
        {
            printf("Esa clave ya existe.\n");
        }
        else
        {
            fflush(stdin);
            printf("Descripcion del servicio: ");
            gets(servicio.descripcion);
            printf("Precio: ");
            scanf("%f", &servicio.precio);
            fflush(stdin);
            printf("Duracion (ej. '30min', '1h'): ");
            gets(servicio.duracion);

            servicio.clave = clave;

            fseek(fptr, (servicio.clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
            fwrite(&servicio, sizeof(struct DatosServicio), 1, fptr);
            fflush(fptr);

            printf("Servicio agregado correctamente.\n");
        }

        printf("Deseas agregar otro servicio? (s/n): ");
        scanf(" %c", &continuar);
    }
}


void ConsultarServicio(FILE *fptr)
{
    struct DatosServicio servicio;
    int opcion, clave, contador = 1, encontrados = 0;
    char descripcionBuscada[50];

    do
    {
        printf("\n--- CONSULTAR SERVICIO ---\n");
        printf("1. Buscar por clave\n");
        printf("2. Buscar por descripcion\n");
        printf("3. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            printf("Ingresa la clave del servicio a consultar: ");
            scanf("%d", &clave);
            fflush(stdin);

            fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
            fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

            if (servicio.clave == 0)
            {
                printf("Servicio no encontrado.\n");
            }
            else
            {
                printf("\n--- Datos del Servicio ---\n");
                printf("Clave: %d\n", servicio.clave);
                printf("Descripcion: %s\n", servicio.descripcion);
                printf("Precio: %.2f\n", servicio.precio);
                printf("Duracion: %s\n", servicio.duracion);
                printf("--------------------------\n");
            }
            break;

        case 2:
            printf("Ingresa parte de la descripcion del servicio a buscar: ");
            fgets(descripcionBuscada, sizeof(descripcionBuscada), stdin);
            descripcionBuscada[strcspn(descripcionBuscada, "\n")] = 0;

            rewind(fptr);

            while (!feof(fptr) && contador < 100)
            {
                fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

                if (strstr(servicio.descripcion, descripcionBuscada) != NULL)
                {
                    printf("\n--- Coincidencia %d ---\n", contador);
                    printf("Clave: %d\n", servicio.clave);
                    printf("Descripcion: %s\n", servicio.descripcion);
                    printf("Precio: %.2f\n", servicio.precio);
                    printf("Duracion: %s\n", servicio.duracion);
                    printf("--------------------------\n");
                    encontrados++;
                }
                contador++;
            }

            if (encontrados == 0)
                printf("No se encontraron coincidencias.\n");

            break;

        case 3:
            printf("Saliendo de consulta.\n");
            break;
        }

    } while (opcion != 3);
}


void ModificarServicio(FILE *fptr)
{
    struct DatosServicio servicio;
    int clave;

    printf("Ingresa la clave del servicio a modificar: ");
    scanf("%d", &clave);

    fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
    fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

    if (servicio.clave == 0)
    {
        printf("Servicio no encontrado.\n");
    }
    else
    {
        printf("\nModificando datos del servicio '%s'\n", servicio.descripcion);
        fflush(stdin);

        printf("Nueva descripcion: ");
        gets(servicio.descripcion);
        printf("Nuevo precio: ");
        scanf("%f", &servicio.precio);
        fflush(stdin);
        printf("Nueva duracion: ");
        gets(servicio.duracion);

        fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fwrite(&servicio, sizeof(struct DatosServicio), 1, fptr);
        fflush(fptr);

        printf("Servicio modificado correctamente.\n");
    }
}


void BorrarServicio(FILE *fptr)
{
    struct DatosServicio servicio;
    int clave;

    printf("Ingresa la clave del servicio a borrar: ");
    scanf("%d", &clave);

    fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
    fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

    if (servicio.clave == 0)
    {
        printf("Servicio no encontrado.\n");
    }
    else
    {
        memset(&servicio, 0, sizeof(struct DatosServicio));
        fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fwrite(&servicio, sizeof(struct DatosServicio), 1, fptr);
        fflush(fptr);
        printf("Servicio eliminado correctamente.\n");
    }
}

void menuReportes(char opcionF)
{
	struct datosCliente cliente;
	
	int clave;
	
	switch(opcionF)
	{
		case 'a':
			break;
		
		case 'b':
			break;	
	}
}
