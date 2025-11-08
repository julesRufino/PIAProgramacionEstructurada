#include <stdio.h>
#include <string.h>
#include "validaciones.h"
#include "estructuras.h"

void validarArchivos(FILE **fClientes, FILE **fEmpleados, FILE **fServicios, FILE **fAgenda)
{
    int i;

    if ((*fClientes = fopen("clientes.dat", "r+")) == NULL)
    {
        printf("Archivo 'clientes.dat' no encontrado. Creando nuevo archivo...\n");
        *fClientes = fopen("clientes.dat", "w+");
        if (*fClientes == NULL)
            printf("ERROR al crear el archivo 'clientes.dat'.\n");
        else
        {
            struct DatosCliente vacio = {0, "", "", "", ""};
            for (i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosCliente), 1, *fClientes);
            printf("Archivo 'clientes.dat' creado exitosamente.\n");
        }
    }

 
    if ((*fEmpleados = fopen("empleados.dat", "r+")) == NULL)
    {
        printf("Archivo 'empleados.dat' no encontrado. Creando nuevo archivo...\n");
        *fEmpleados = fopen("empleados.dat", "w+");
        if (*fEmpleados == NULL)
            printf("ERROR al crear el archivo 'empleados.dat'.\n");
        else
        {
            struct DatosEmpleado vacio = {0, "", "", "", "", ""};
            for (i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosEmpleado), 1, *fEmpleados);
            printf("Archivo 'empleados.dat' creado exitosamente.\n");
        }
    }

    if ((*fServicios = fopen("servicios.dat", "r+")) == NULL)
    {
        printf("Archivo 'servicios.dat' no encontrado. Creando nuevo archivo...\n");
        *fServicios = fopen("servicios.dat", "w+");
        if (*fServicios == NULL)
            printf("ERROR al crear el archivo 'servicios.dat'.\n");
        else
        {
            struct DatosServicio vacio = {0, "", 0.0, ""};
            for (i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosServicio), 1, *fServicios);
            printf("Archivo 'servicios.dat' creado exitosamente.\n");
        }
    }

   
    if ((*fAgenda = fopen("agenda.dat", "r+")) == NULL)
    {
        printf("Archivo 'agenda.dat' no encontrado. Creando nuevo archivo...\n");
        *fAgenda = fopen("agenda.dat", "w+");
        if (*fAgenda == NULL)
            printf("ERROR al crear el archivo 'agenda.dat'.\n");
        else
        {
            struct DatosAgenda vacio = {0, 0, 0, 0, "", "", ""};
            for (i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosAgenda), 1, *fAgenda);
            printf("Archivo 'agenda.dat' creado exitosamente.\n");
        }
    }
}

bool validarPuesto(char *puestoF)
{
	bool verificacion = false;

	if(strcmp(puestoF, "ESTILISTA") != 0 && strcmp(puestoF, "COLORISTA") != 0 && strcmp(puestoF, "RECEPCIONISTA") != 0 && strcmp(puestoF, "COORDINADOR") != 0 && strcmp(puestoF, "MAQUILLADOR") != 0)
		verificacion = true;

	return verificacion;
}
