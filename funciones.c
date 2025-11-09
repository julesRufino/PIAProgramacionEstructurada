#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "funciones.h"
#include "validaciones.h"
#include <stdbool.h>

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
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
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

        printf("Deseas modificar otro cliente? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void BorrarCliente(FILE *fptr)
{
    struct DatosCliente cliente, vacio = {0, "", "", "", ""};
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
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
            fwrite(&vacio, sizeof(struct DatosCliente), 1, fptr);
            fflush(fptr);
            printf("Cliente eliminado correctamente.\n");
        }

        printf("Deseas borrar otro cliente? (s/n): ");
        scanf(" %c", &continuar);
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
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
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

        printf("Deseas modificar otro empleado? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void BorrarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado, vacio = {0, "", "", "", "", ""};
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
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
            fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
            fwrite(&vacio, sizeof(struct DatosEmpleado), 1, fptr);
            fflush(fptr);
            printf("Empleado eliminado correctamente.\n");
        }

        printf("Deseas borrar otro empleado? (s/n): ");
        scanf(" %c", &continuar);
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
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
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

        printf("Deseas modificar otro servicio? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void BorrarServicio(FILE *fptr)
{
    struct DatosServicio servicio, vacio = {0, "", 0.0, ""};
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
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
            fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
            fwrite(&vacio, sizeof(struct DatosServicio), 1, fptr);
            fflush(fptr);
            printf("Servicio eliminado correctamente.\n");
        }

        printf("Deseas borrar otro servicio? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void AgregarCita(FILE *fAgenda)
{
    struct DatosAgenda agenda;
    int i = 0, encontrado = 0;

    rewind(fAgenda);

    while (fread(&agenda, sizeof(struct DatosAgenda), 1, fAgenda) == 1 && i < 100)
    {
        if (agenda.claveAgenda == 0 && encontrado == 0)
            encontrado = 1;
        else
            i++;
    }

    if (i >= 100)
    {
        printf("Archivo lleno.\n");
        return;
    }

    agenda.claveAgenda = i + 1;

    printf("=== Nueva Agenda ===\n");

    printf("Clave del cliente: ");
    scanf("%d", &agenda.claveCliente);

    printf("Clave del empleado: ");
    scanf("%d", &agenda.claveEmpleado);

    printf("Clave del servicio: ");
    scanf("%d", &agenda.claveServicio);

    printf("Fecha (dd/mm/aaaa): ");
    fflush(stdin);
    fgets(agenda.fecha, sizeof(agenda.fecha), stdin);
    agenda.fecha[strcspn(agenda.fecha, "\n")] = '\0';

    printf("Hora (hh:mm): ");
    fgets(agenda.hora, sizeof(agenda.hora), stdin);
    agenda.hora[strcspn(agenda.hora, "\n")] = '\0';

    printf("Estatus: ");
    fgets(agenda.estatus, sizeof(agenda.estatus), stdin);
    agenda.estatus[strcspn(agenda.estatus, "\n")] = '\0';

    fseek(fAgenda, i * sizeof(struct DatosAgenda), SEEK_SET);
    fwrite(&agenda, sizeof(struct DatosAgenda), 1, fAgenda);
    fflush(fAgenda);

    printf("Registro de agenda agregado con clave %d.\n", agenda.claveAgenda);
}

void ConsultarCita(FILE *fptr)
{
    struct DatosAgenda cita;
    int opcion, clave, encontrados;

    do
    {
        printf("\n--- CONSULTAR CITA ---\n");
        printf("1. Buscar por clave de agenda\n");
        printf("2. Buscar por clave de cliente\n");
        printf("3. Buscar por clave de empleado\n");
        printf("4. Buscar por clave de servicio\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        encontrados = 0;
        rewind(fptr);

        switch (opcion)
        {
        case 1:
            printf("Ingresa la clave de agenda: ");
            scanf("%d", &clave);

            if (clave < 1 || clave > 100)
            {
                printf("Clave fuera de rango.\n");
                break;
            }

            fseek(fptr, (clave - 1) * sizeof(struct DatosAgenda), SEEK_SET);
            if (fread(&cita, sizeof(struct DatosAgenda), 1, fptr) == 1 && cita.claveAgenda != 0)
            {
                printf("\n%-10s%-12s%-12s%-12s%-12s%-10s%-12s\n",
                       "Agenda", "Cliente", "Empleado", "Servicio", "Fecha", "Hora", "Estatus");
                printf("%-10d%-12d%-12d%-12d%-12s%-10s%-12s\n",
                       cita.claveAgenda, cita.claveCliente, cita.claveEmpleado, cita.claveServicio,
                       cita.fecha, cita.hora, cita.estatus);
            }
            else
            {
                printf("No se encontró la cita.\n");
            }
            break;

        case 2: // Buscar por clave de cliente
            printf("Ingresa la clave del cliente: ");
            scanf("%d", &clave);

            printf("\n%-10s%-12s%-12s%-12s%-12s%-10s%-12s\n",
                   "Agenda", "Cliente", "Empleado", "Servicio", "Fecha", "Hora", "Estatus");

            while (!feof(fptr) && fread(&cita, sizeof(struct DatosAgenda), 1, fptr) == 1)
            {
                if (cita.claveAgenda != 0 && cita.claveCliente == clave)
                {
                    printf("%-10d%-12d%-12d%-12d%-12s%-10s%-12s\n",
                           cita.claveAgenda, cita.claveCliente, cita.claveEmpleado, cita.claveServicio,
                           cita.fecha, cita.hora, cita.estatus);
                    encontrados++;
                }
            }

            if (encontrados == 0)
                printf("No se encontraron citas para ese cliente.\n");
            break;

        case 3: // Buscar por clave de empleado
            printf("Ingresa la clave del empleado: ");
            scanf("%d", &clave);

            printf("\n%-10s%-12s%-12s%-12s%-12s%-10s%-12s\n",
                   "Agenda", "Cliente", "Empleado", "Servicio", "Fecha", "Hora", "Estatus");

            while (!feof(fptr) && fread(&cita, sizeof(struct DatosAgenda), 1, fptr) == 1)
            {
                if (cita.claveAgenda != 0 && cita.claveEmpleado == clave)
                {
                    printf("%-10d%-12d%-12d%-12d%-12s%-10s%-12s\n",
                           cita.claveAgenda, cita.claveCliente, cita.claveEmpleado, cita.claveServicio,
                           cita.fecha, cita.hora, cita.estatus);
                    encontrados++;
                }
            }

            if (encontrados == 0)
                printf("No se encontraron citas para ese empleado.\n");
            break;

        case 4: // Buscar por clave de servicio
            printf("Ingresa la clave del servicio: ");
            scanf("%d", &clave);

            printf("\n%-10s%-12s%-12s%-12s%-12s%-10s%-12s\n",
                   "Agenda", "Cliente", "Empleado", "Servicio", "Fecha", "Hora", "Estatus");

            while (!feof(fptr) && fread(&cita, sizeof(struct DatosAgenda), 1, fptr) == 1)
            {
                if (cita.claveAgenda != 0 && cita.claveServicio == clave)
                {
                    printf("%-10d%-12d%-12d%-12d%-12s%-10s%-12s\n",
                           cita.claveAgenda, cita.claveCliente, cita.claveEmpleado, cita.claveServicio,
                           cita.fecha, cita.hora, cita.estatus);
                    encontrados++;
                }
            }

            if (encontrados == 0)
                printf("No se encontraron citas para ese servicio.\n");
            break;

        case 5:
            printf("Saliendo de consulta de citas...\n");
            break;
        }

    } while (opcion != 5);
}

void ModificarCita(FILE *fptr)
{
    struct DatosAgenda cita;
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        printf("Ingresa la clave de agenda a modificar: ");
        scanf("%d", &clave);

        fseek(fptr, (clave - 1) * sizeof(struct DatosAgenda), SEEK_SET);
        fread(&cita, sizeof(struct DatosAgenda), 1, fptr);

        if (cita.claveAgenda == 0)
        {
            printf("Cita no encontrada.\n");
        }
        else
        {
            printf("\nModificando cita #%d\n", cita.claveAgenda);
            fflush(stdin);
            printf("Nueva fecha (dd/mm/aaaa): ");
            gets(cita.fecha);
            printf("Nueva hora (hh:mm): ");
            gets(cita.hora);
            printf("Nuevo estatus: ");
            gets(cita.estatus);

            fseek(fptr, (clave - 1) * sizeof(struct DatosAgenda), SEEK_SET);
            fwrite(&cita, sizeof(struct DatosAgenda), 1, fptr);
            fflush(fptr);

            printf("Cita modificada correctamente.\n");
        }

        printf("Deseas modificar otra cita? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void BorrarCita(FILE *fptr)
{
    struct DatosAgenda cita, vacio = {0, 0, 0, 0, "", "", ""};
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        printf("Ingresa la clave de agenda a borrar: ");
        scanf("%d", &clave);

        fseek(fptr, (clave - 1) * sizeof(struct DatosAgenda), SEEK_SET);
        fread(&cita, sizeof(struct DatosAgenda), 1, fptr);

        if (cita.claveAgenda == 0)
        {
            printf("Cita no encontrada.\n");
        }
        else
        {
            fseek(fptr, (clave - 1) * sizeof(struct DatosAgenda), SEEK_SET);
            fwrite(&vacio, sizeof(struct DatosAgenda), 1, fptr);
            fflush(fptr);
            printf("Cita eliminada correctamente.\n");
        }

        printf("Deseas borrar otra cita? (s/n): ");
        scanf(" %c", &continuar);
    }
}

void menuReportes(char opcionF)
{
	struct DatosCliente cliente;
    struct DatosEmpleado empleado;
    struct DatosAgenda agenda;
    struct DatosServicio servicio;
	
	FILE *clientePtr, *servicioPtr, *empleadoPtr, *agendaPtr, *archivoCliente, *archivoEmpleado;
	int clave, opcion;
    char puesto[50], status[20], periodo[20], fechaVentaInicio[20], fechaVentaFin[20];
	
	switch(opcionF)
	{
		case 'a':
            do
            {
                printf("Ingrese el puesto: ");
                fflush(stdin);
                gets(puesto);
                if(validarPuesto(puesto))
                    printf("Error, ingrese un puesto valido.\n");
            }while(validarPuesto(puesto));

            empleadoPtr = fopen("empleados.dat", "r");

            printf("%-6s%-20s%-12s%-15s%-11s%-25s\n",
                    "Clave", "Nombre", "Puesto", "FechaContrat.", "Telefono", "Correo");
            
            fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
            while(!feof(empleadoPtr))
            {                

                if(strcmp(empleado.puesto, puesto) == 0)
                {
                    printf("%-6d%-20s%-12s%-15s%-11s%-25s\n",
                            empleado.clave,
                            empleado.nombre,
                            empleado.puesto,
                            empleado.fechaContratacion,
                            empleado.telefono,
                            empleado.correoElectronico);

                }
                fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
            }
            
            fclose(empleadoPtr);
            
			break;
		
		case 'b':
			//wiliam aqui va la validacion del status
			printf("Ingrese el status: ");
			fflush(stdin);
			gets(status);
			
			agendaPtr = fopen("agenda.dat", "r");
			
			fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			
			printf("%-25s%-25s%-25s\n", "Cliente", "Empleado", "Servicio");

			while(!feof(agendaPtr))
			{
				if(strcmp(agenda.estatus, status) == 0)
					imprimirListaAgenda(&agenda.claveCliente, &agenda.claveEmpleado, &agenda.claveServicio);
					
                fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			}
			
			fclose(agendaPtr);
			break;
			
		case 'c':
			printf("Ingrese el periodo: ");
			fflush(stdin);
			gets(periodo);
			
			agendaPtr = fopen("agenda.dat", "r");
			
			fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			
			printf("%-25s%-25s%-25s\n", "Cliente", "Empleado", "Servicio");

			while(!feof(agendaPtr))
			{
				if(strcmp(agenda.fecha, periodo) == 0 && strcmp(agenda.estatus, "PROGRAMADO") == 0)
					imprimirListaAgenda(&agenda.claveCliente, &agenda.claveEmpleado, &agenda.claveServicio);
                
                fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			}
			
			fclose(agendaPtr);
			break;
			
		case 'd':
			printf("Ingrese inicio del periodo de ventas (dd/mm/aaaa): ");
			fflush(stdin);
			gets(fechaVentaInicio);
			
			printf("Ingrese fin del periodo de ventas (dd/mm/aaaa): ");
			fflush(stdin);
			gets(fechaVentaFin);			
			
			agendaPtr = fopen("agenda.dat", "r");
			
			fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			
 			printf("\n%-25s%-15s%-15s\n", "Servicio", "Fecha", "Precio");
    		printf("----------------------------------------------------\n");
			
			while(!feof(agendaPtr))
			{
 			if (strcmp(agenda.estatus, "REALIZADO") == 0 && fechaEnRango(agenda.fecha, fechaVentaInicio, fechaVentaFin) == false)
                imprimirVenta(&agenda);

            fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
            
        	}
        	
        	fclose(agendaPtr);
        
			break;
			
		case 'e':
			printf("Generando archivo...");
			
			if((archivoCliente = fopen("archivoCliente.txt", "w")) == NULL || (clientePtr = fopen("clientes.dat", "r")) == NULL)
				printf("Error, hubo un problema al acceder a los archivos.\n");
			else
			{
				fread(&cliente, sizeof(struct DatosCliente), 1, clientePtr);
				
				while(!feof(clientePtr))
				{
					fprintf(archivoCliente, "%d %s %s %s %s %s\n", cliente.clave, cliente.nombre, cliente.fechaNacimiento, cliente.telefono, cliente.correoElectronico, cliente.direccion);	
					fread(&cliente, sizeof(struct DatosCliente), 1, clientePtr);

				}
				fclose(archivoCliente);
				fclose(clientePtr);
			}
			break;
		
		case 'f':
			printf("Generando archivo...");
			
			if((archivoEmpleado = fopen("archivoEmpleado.txt", "w")) == NULL || (empleadoPtr = fopen("empleados.dat", "r")) == NULL)
				printf("Error, hubo un problema al acceder a los archivos.\n");
			else
			{
				fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
				
				while(!feof(empleadoPtr))
				{
					fprintf(archivoEmpleado, "%d %s %s %s %s %s\n", empleado.clave, empleado.nombre, empleado.puesto, empleado.fechaContratacion, empleado.telefono, empleado.correoElectronico);	
					fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);

				}
				fclose(archivoEmpleado);
				fclose(empleadoPtr);
			}
			break;
			
		case 'g':
			printf("opciones de archivos a visualizar:\n");
			printf("1. Cliente\n");
			printf("2. Emppleado\n");
			scanf("%d", &opcion);
			
			switch(opcion)
			{
        case 1:
        	
            if((archivoCliente = fopen("archivoCliente.txt", "r")) == NULL)
                printf("Error al abrir archivoCliente.txt\n");
            else
            {
                printf("\n%-10s%-20s%-15s%-20s%-30s%-30s\n",
                       "Clave", "Nombre", "Nacimiento", "Tel�fono", "Correo", "Direcci�n");
                printf("---------------------------------------------------------------------------------------------------------------\n");

                fscanf(archivoCliente, "%d %s %s %s %s %s",
                       &cliente.clave,
                       cliente.nombre,
                       cliente.fechaNacimiento,
                       cliente.telefono,
                       cliente.correoElectronico,
                       cliente.direccion);

                while(!feof(archivoCliente))
                {
                    printf("%-10d%-20s%-15s%-20s%-30s%-30s\n",
                           cliente.clave,
                           cliente.nombre,
                           cliente.fechaNacimiento,
                           cliente.telefono,
                           cliente.correoElectronico,
                           cliente.direccion);

                    fscanf(archivoCliente, "%d %s %s %s %s %s",
                           &cliente.clave,
                           cliente.nombre,
                           cliente.fechaNacimiento,
                           cliente.telefono,
                           cliente.correoElectronico,
                           cliente.direccion);
                }

                fclose(archivoCliente);
            }
            break;

        case 2:
            if((archivoEmpleado = fopen("archivoEmpleado.txt", "r")) == NULL)
                printf("Error al abrir archivoEmpleado.txt\n");
            else
            {
                printf("\n%-10s%-20s%-15s%-20s%-20s%-30s\n",
                       "Clave", "Nombre", "Puesto", "Contrataci�n", "Tel�fono", "Correo");
                printf("----------------------------------------------------------------------------------------------------\n");

                fscanf(archivoEmpleado, "%d %s %s %s %s %s",
                       &empleado.clave,
                       empleado.nombre,
                       empleado.puesto,
                       empleado.fechaContratacion,
                       empleado.telefono,
                       empleado.correoElectronico);

                while(!feof(archivoEmpleado))
                {
                    printf("%-10d%-20s%-15s%-20s%-20s%-30s\n",
                           empleado.clave,
                           empleado.nombre,
                           empleado.puesto,
                           empleado.fechaContratacion,
                           empleado.telefono,
                           empleado.correoElectronico);

                    fscanf(archivoEmpleado, "%d %s %s %s %s %s",
                           &empleado.clave,
                           empleado.nombre,
                           empleado.puesto,
                           empleado.fechaContratacion,
                           empleado.telefono,
                           empleado.correoElectronico);
                }

                fclose(archivoEmpleado);
            }
            break;
			}
			
			break;
			
		case 'h':
			printf("Saliendo...");
			break;	
	}
}


void imprimirListaAgenda(int *claveCliente, int *claveEmpleado, int *claveServicio)
{
	struct DatosEmpleado empleado;
	struct DatosCliente cliente;
	struct DatosServicio servicio;
	FILE *clientePtr, *empleadoPtr, *servicioPtr;
	
		if((clientePtr = fopen("clientes.dat", "r")) == NULL || (empleadoPtr = fopen("empleados.dat", "r")) == NULL || (servicioPtr = fopen("servicios.dat", "r")) == NULL)
			printf("Error, no se pudieron abrir los archivo.\n");
		else
		{
			fseek(clientePtr, (*claveCliente - 1) * sizeof(struct DatosCliente), SEEK_SET);
			fread(&cliente, sizeof(struct DatosCliente), 1, clientePtr);
			
			fseek(empleadoPtr, (*claveEmpleado - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
			fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
			
			fseek(servicioPtr, (*claveServicio - 1) * sizeof(struct DatosServicio), SEEK_SET);
			fread(&servicio, sizeof(struct DatosServicio), 1, servicioPtr);
			
			printf("%-25s%-25s%-25s\n", cliente.nombre, empleado.nombre, servicio.descripcion);
			fclose(clientePtr);
			fclose(empleadoPtr);
			fclose(servicioPtr);
		}	
}

void imprimirVenta(struct DatosAgenda *agenda)
{
    FILE *servicioPtr;
    struct DatosServicio servicio;

    if ((servicioPtr = fopen("servicios.dat", "r")) == NULL)
        printf("Error al abrir servicios.dat\n");
    else
    {
        fseek(servicioPtr, (agenda->claveServicio - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fread(&servicio, sizeof(struct DatosServicio), 1, servicioPtr);

        printf("%-25s%-25s$%-14.2f\n", servicio.descripcion, agenda->fecha, servicio.precio);

        fclose(servicioPtr);
    }
}


