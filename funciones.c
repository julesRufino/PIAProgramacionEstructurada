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

            if (cliente.clave == 0 || cliente.activo == 0)
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
                printf("Direccion: %s %d, %s, %s, %s\n",
                       cliente.calle, cliente.numero,
                       cliente.colonia, cliente.municipio, cliente.estado);
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

    if (cliente.clave == 0 || cliente.activo == 0)
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

    if (cliente.clave == 0 || cliente.activo == 0)
    {
        printf("Cliente no encontrado.\n");
    }
    else
    {
        cliente.activo = 0;
        fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
        fwrite(&cliente, sizeof(struct DatosCliente), 1, fptr);
        fflush(fptr);
        printf("Cliente eliminado correctamente.\n");
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
