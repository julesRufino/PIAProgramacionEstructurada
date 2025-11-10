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
        } while (validarClave(clave));

        fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
        fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

        if (cliente.clave != 0)
        {
            printError("Esa clave ya existe.\n");
        }
        else
        {
            fflush(stdin);
            
            do
            {
                printf("Nombre del cliente: ");
                gets(cliente.nombre);
            } while (validarCadena(cliente.nombre));
            
            do
            {
                printf("Fecha de nacimiento (dd/mm/aaaa): ");
                gets(cliente.fechaNacimiento);
            } while (validarFecha(cliente.fechaNacimiento));

            do
            {
                printf("Telefono: ");
                gets(cliente.telefono);
            } while (validarTelefono(cliente.telefono));

            do
            {
                printf("Correo electronico: ");
                gets(cliente.correoElectronico);
            } while (validarCorreo(cliente.correoElectronico));

            do
            {
                printf("Calle: ");
                gets(cliente.calle);
            } while (validarCadena(cliente.calle));

            do
            {
                printf("Numero: ");
                gets(cliente.numero);
            } while (validarNumero(cliente.numero));

            do
            {
                printf("Colonia: ");
                gets(cliente.colonia);
            } while (validarCadena(cliente.colonia));

            do
            {
                printf("Municipio: ");
                gets(cliente.municipio);
            } while (validarCadena(cliente.municipio));

            do
            {
                printf("Estado: ");
                gets(cliente.estado);
            } while (validarCadena(cliente.estado));

            cliente.clave = clave;

            fseek(fptr, (cliente.clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
            fwrite(&cliente, sizeof(struct DatosCliente), 1, fptr);
            fflush(fptr);

            printf("Cliente agregado correctamente.\n");
        }

		do{
			printf("Deseas agregar otro cliente? (s/n): ");
	        fflush(stdin);
	        scanf(" %c", &continuar);
		}while(validarSN(continuar));
    }
}

void ConsultarCliente(FILE *fptr)
{
    struct DatosCliente cliente;
    int opcion, clave, contador = 1, encontrados = 0;
    char nombreBuscado[50];

    do
    {
        printf("\n--- CONSULTAR CLIENTE ---\n");
        printf("1. Buscar por clave\n");
        printf("2. Buscar por nombre\n");
        printf("3. Salir\n");
		do{
			printf("Selecciona una opcion: ");
	        scanf("%d", &opcion);
	        fflush(stdin);
		}while(validarOpcion3(opcion));

        switch (opcion)
        {
        case 1:
	        do
	        {
	            printf("Ingresa la clave del cliente a consultar: ");
	            scanf("%d", &clave);
	        } while (validarClave(clave));

            fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
            fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

            if (cliente.clave == 0)
            {
                printError("Cliente no encontrado.\n");
            }
            else
            {
                printf("\n--- Datos del Cliente ---\n");
                printf("Clave: %d\n", cliente.clave);
                printf("Nombre: %s\n", cliente.nombre);
                printf("Fecha de nacimiento: %s\n", cliente.fechaNacimiento);
                printf("Telefono: %s\n", cliente.telefono);
                printf("Correo: %s\n", cliente.correoElectronico);
                printf("Direccion: %s %s, %s, %s, %s\n", cliente.calle, cliente.numero, cliente.colonia, cliente.municipio, cliente.estado);
                printf("--------------------------\n");
            }
            break;

        case 2:
            printf("Ingresa parte del nombre del cliente a buscar: ");
            fflush(stdin);
            gets(nombreBuscado);

            rewind(fptr);

            while (!feof(fptr) && contador <= 100)
            {
                fread(&cliente, sizeof(struct DatosCliente), 1, fptr);

                if (cliente.clave != 0 && strstr(cliente.nombre, nombreBuscado) != NULL)
                {
                    printf("\n--- Coincidencia %d ---\n", contador);
                    printf("Clave: %d\n", cliente.clave);
                    printf("Nombre: %s\n", cliente.nombre);
                    printf("Fecha de nacimiento: %s\n", cliente.fechaNacimiento);
                    printf("Telefono: %s\n", cliente.telefono);
                    printf("Correo: %s\n", cliente.correoElectronico);
                    printf("Direccion: %s %s, %s, %s, %s\n", cliente.calle, cliente.numero, cliente.colonia, cliente.municipio, cliente.estado);
                    printf("--------------------------\n");
                    encontrados++;
                    contador++;
                }
            }

            if (encontrados == 0)
            {
                printError("No se encontraron coincidencias.\n");
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

            do
            {
                printf("Nuevo nombre: ");
                gets(cliente.nombre);
                if (validarCadena(cliente.nombre))
                    printf("Error: Nombre no valido.\n");
            } while (validarCadena(cliente.nombre));

            do
            {
                printf("Nueva fecha de nacimiento: ");
                gets(cliente.fechaNacimiento);
                if (validarFecha(cliente.fechaNacimiento))
                    printf("Error: Fecha no valida.\n");
            } while (validarFecha(cliente.fechaNacimiento));

            do
            {
                printf("Nuevo telefono: ");
                gets(cliente.telefono);
                if (validarTelefono(cliente.telefono))
                    printf("Error: Telefono no valido.\n");
            } while (validarTelefono(cliente.telefono));

            do
            {
                printf("Nuevo correo: ");
                gets(cliente.correoElectronico);
                if (validarCorreo(cliente.correoElectronico))
                    printf("Error: Correo no valido.\n");
            } while (validarCorreo(cliente.correoElectronico));

            fseek(fptr, (clave - 1) * sizeof(struct DatosCliente), SEEK_SET);
            fwrite(&cliente, sizeof(struct DatosCliente), 1, fptr);
            fflush(fptr);

            printf("Cliente modificado correctamente.\n");
        }
		do
		{
			printf("Deseas modificar otro cliente? (s/n): ");
	        scanf(" %c", &continuar);
		}while(validarSN(continuar));
    }
}

void BorrarCliente(FILE *fptr)
{
    struct DatosCliente cliente, vacio = {0, "", "", "", "", "", "", "", "", ""};
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        do
		{
	        printf("Ingresa la clave del cliente a borrar: ");
	        scanf("%d", &clave);	
		}while(validarClave(clave));

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

		do
		{
			printf("Deseas borrar otro cliente? (s/n): ");
	        scanf(" %c", &continuar);
		}while(validarSN(continuar));
    }
}

void AgregarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado;
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
            printf("Ingresa la clave del empleado (1-100): ");
            scanf("%d", &clave);
            if (validarClave(clave))
                printError("Clave fuera de rango (1-100).\n");

        fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
        fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

        if (empleado.clave != 0)
        {
            printError("Esa clave ya existe.\n");
        }
        else
        {
            fflush(stdin);
            
            do
            {
                printf("Nombre del empleado: ");
                gets(empleado.nombre);
                if (validarCadena(empleado.nombre))
                    printf("Error: Nombre no valido.\n");
            } while (validarCadena(empleado.nombre));

            do
            {
                printf("Puesto (ESTILISTA, COLORISTA, RECEPCIONISTA, COORDINADOR, MAQUILLADOR): ");
                gets(empleado.puesto);
                if (validarPuesto(empleado.puesto))
                    printf("Error: Puesto no valido.\n");
            } while (validarPuesto(empleado.puesto));

            do
            {
                printf("Fecha de contratacion (dd/mm/aaaa): ");
                gets(empleado.fechaContratacion);
                if (validarFecha(empleado.fechaContratacion))
                    printf("Error: Fecha no valida.\n");
            } while (validarFecha(empleado.fechaContratacion));

            do
            {
                printf("Telefono: ");
                gets(empleado.telefono);
                if (validarTelefono(empleado.telefono))
                    printf("Error: Telefono no valido.\n");
            } while (validarTelefono(empleado.telefono));

            do
            {
                printf("Correo electronico: ");
                gets(empleado.correoElectronico);
                if (validarCorreo(empleado.correoElectronico))
                    printf("Error: Correo no valido.\n");
            } while (validarCorreo(empleado.correoElectronico));

            empleado.clave = clave;

            fseek(fptr, (empleado.clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
            fwrite(&empleado, sizeof(struct DatosEmpleado), 1, fptr);
            fflush(fptr);

            printf("Empleado agregado correctamente.\n");
        }

        do
        {
        	printf("Deseas agregar otro empleado? (s/n): ");
        	scanf(" %c", &continuar);
		}while(validarSN(continuar));
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
		do{
			printf("Selecciona una opcion: ");
	        scanf("%d", &opcion);
	        fflush(stdin);
		}while(validarOpcion3(opcion));

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
                printError("Empleado no encontrado.\n");
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
            fflush(stdin);
            gets(nombreBuscado);

            rewind(fptr);
			contador = 1;
            while (!feof(fptr) && contador <= 100)
            {
                fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

                if (empleado.clave != 0 && strstr(empleado.nombre, nombreBuscado) != NULL)
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
                    contador++;
                }
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
            printError("Empleado no encontrado.\n");
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

        do
        {
        	printf("Deseas modificar otro empleado? (s/n): ");
        	scanf(" %c", &continuar);
		}while(validarSN(continuar));
    }
}

void BorrarEmpleado(FILE *fptr)
{
    struct DatosEmpleado empleado, vacio = {0, "", "", "", "", "", "", "", "", "", ""};
    int clave;
    char continuar = 's';

    while (continuar != 'n' && continuar != 'N')
    {
        do
        {
        	printf("Ingresa la clave del empleado a borrar: ");
        	scanf("%d", &clave);
		}while(validarClave(clave));

        fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
        fread(&empleado, sizeof(struct DatosEmpleado), 1, fptr);

        if (empleado.clave == 0)
        {
            printError("Empleado no encontrado.\n");
        }
        else
        {
            fseek(fptr, (clave - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
            fwrite(&vacio, sizeof(struct DatosEmpleado), 1, fptr);
            fflush(fptr);
            printf("Empleado eliminado correctamente.\n");
        }

        do
        {
        	printf("Deseas borrar otro empleado? (s/n): ");
        	scanf(" %c", &continuar);
		}while(validarSN(continuar));
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
        } while (validarClave(clave));

        fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

        if (servicio.clave != 0)
        {
            printError("Esa clave ya existe.\n");
        }
        else
        {
            fflush(stdin);
            
            do
            {
                printf("Descripcion del servicio: ");
                fflush(stdin);
                gets(servicio.descripcion);
                
                if (validarCadena(servicio.descripcion))
                    printError("Descripcion no valida.\n");
            } while (validarCadena(servicio.descripcion));
            
            do
            {
                printf("Precio: ");
                scanf("%f", &servicio.precio);
            } while (validarPrecio(servicio.precio));
            
            fflush(stdin);
            printf("Duracion (ej. '30min', '1h'): ");
            gets(servicio.duracion);

            servicio.clave = clave;

            fseek(fptr, (servicio.clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
            fwrite(&servicio, sizeof(struct DatosServicio), 1, fptr);
            fflush(fptr);

            printf("Servicio agregado correctamente.\n");
        }

       	do{
       		
       		printf("Deseas agregar otro servicio? (s/n): ");
       		scanf(" %c", &continuar);
		}while(validarSN(continuar));
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
		do
		{
			printf("Selecciona una opcion: ");
	        scanf("%d", &opcion);
	        fflush(stdin);

		}while(validarOpcion3(opcion));
		
        switch (opcion)
        {
        case 1:
       		do
       		{
       			printf("Ingresa la clave del servicio a consultar: ");
            	scanf("%d", &clave);
            	fflush(stdin);
			}while(validarClave(clave));

            fseek(fptr, (clave - 1) * sizeof(struct DatosServicio), SEEK_SET);
            fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

            if (servicio.clave == 0)
            {
                printError("Servicio no encontrado.\n");
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
            fflush(stdin);
            gets(descripcionBuscada);

            rewind(fptr);
            
			contador = 1;
            while (!feof(fptr) && contador <= 100)
            {
                fread(&servicio, sizeof(struct DatosServicio), 1, fptr);

                if (servicio.clave != 0 && strstr(servicio.descripcion, descripcionBuscada) != NULL)
                {
                    printf("\n--- Coincidencia %d ---\n", contador);
                    printf("Clave: %d\n", servicio.clave);
                    printf("Descripcion: %s\n", servicio.descripcion);
                    printf("Precio: %.2f\n", servicio.precio);
                    printf("Duracion: %s\n", servicio.duracion);
                    printf("--------------------------\n");
                    encontrados++;
                    contador++;
                }
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

void AgregarCita(FILE *fptr)
{
    struct DatosAgenda agenda;
    int i = 0, encontrado = 0;

    rewind(fptr);

    while (fread(&agenda, sizeof(struct DatosAgenda), 1, fptr) == 1 && i < 100)
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

    printf("=== Nueva Cita ===\n");

    printf("Clave del cliente: ");
    scanf("%d", &agenda.claveCliente);

    printf("Clave del empleado: ");
    scanf("%d", &agenda.claveEmpleado);

    printf("Clave del servicio: ");
    scanf("%d", &agenda.claveServicio);

    do
    {
        printf("Fecha (dd/mm/aaaa): ");
        fflush(stdin);
        gets(agenda.fecha);
        if (validarFecha(agenda.fecha))
            printf("Error: Fecha no valida.\n");
    } while (validarFecha(agenda.fecha));

    printf("Hora (hh:mm): ");
    gets(agenda.hora);

    do
    {
        printf("Estatus (PROGRAMADO, REALIZADO, CANCELADO): ");
        gets(agenda.estatus);
        if (validarEstatus(agenda.estatus))
            printf("Error: Estatus no valido.\n");
    } while (validarEstatus(agenda.estatus));

    fseek(fptr, i * sizeof(struct DatosAgenda), SEEK_SET);
    fwrite(&agenda, sizeof(struct DatosAgenda), 1, fptr);
    fflush(fptr);

    printf("Cita agregada con clave %d.\n", agenda.claveAgenda);
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

            fseek(fptr, (clave - 1) * sizeof(struct DatosAgenda), SEEK_SET);
            fread(&cita, sizeof(struct DatosAgenda), 1, fptr);

            if (cita.claveAgenda != 0)
            {
                printf("\n--- Datos de la Cita ---\n");
                printf("Clave Agenda: %d\n", cita.claveAgenda);
                printf("Clave Cliente: %d\n", cita.claveCliente);
                printf("Clave Empleado: %d\n", cita.claveEmpleado);
                printf("Clave Servicio: %d\n", cita.claveServicio);
                printf("Fecha: %s\n", cita.fecha);
                printf("Hora: %s\n", cita.hora);
                printf("Estatus: %s\n", cita.estatus);
                printf("--------------------------\n");
            }
            else
                printf("Cita no encontrada.\n");
            break;

        case 2:
            printf("Ingresa la clave del cliente: ");
            scanf("%d", &clave);

            printf("\n--- Citas del Cliente %d ---\n", clave);

            while (fread(&cita, sizeof(struct DatosAgenda), 1, fptr))
            {
                if (cita.claveAgenda != 0 && cita.claveCliente == clave)
                {
                    printf("Agenda: %d | Fecha: %s | Hora: %s | Estatus: %s\n",
                           cita.claveAgenda, cita.fecha, cita.hora, cita.estatus);
                    encontrados++;
                }
            }

            if (encontrados == 0)
                printf("No se encontraron citas para ese cliente.\n");
            break;

        case 3:
            printf("Ingresa la clave del empleado: ");
            scanf("%d", &clave);

            printf("\n--- Citas del Empleado %d ---\n", clave);

            while (fread(&cita, sizeof(struct DatosAgenda), 1, fptr))
            {
                if (cita.claveAgenda != 0 && cita.claveEmpleado == clave)
                {
                    printf("Agenda: %d | Fecha: %s | Hora: %s | Estatus: %s\n",
                           cita.claveAgenda, cita.fecha, cita.hora, cita.estatus);
                    encontrados++;
                }
            }

            if (encontrados == 0)
                printf("No se encontraron citas para ese empleado.\n");
            break;

        case 4:
            printf("Ingresa la clave del servicio: ");
            scanf("%d", &clave);

            printf("\n--- Citas del Servicio %d ---\n", clave);

            while (fread(&cita, sizeof(struct DatosAgenda), 1, fptr))
            {
                if (cita.claveAgenda != 0 && cita.claveServicio == clave)
                {
                    printf("Agenda: %d | Fecha: %s | Hora: %s | Estatus: %s\n",
                           cita.claveAgenda, cita.fecha, cita.hora, cita.estatus);
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
            printf("Cita no encontrada.\n");
        else
        {
            printf("\nModificando cita #%d\n", cita.claveAgenda);
            fflush(stdin);
            
            do
            {
                printf("Nueva fecha (dd/mm/aaaa): ");
                gets(cita.fecha);
                if (validarFecha(cita.fecha))
                    printf("Error: Fecha no valida.\n");
            } while (validarFecha(cita.fecha));
            
            printf("Nueva hora (hh:mm): ");
            gets(cita.hora);
            
            do
            {
                printf("Nuevo estatus: ");
                gets(cita.estatus);
                if (validarEstatus(cita.estatus))
                    printf("Error: Estatus no valido.\n");
            } while (validarEstatus(cita.estatus));

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
            printf("Cita no encontrada.\n");
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
	int contador;
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
                    printf("Error: Puesto no valido.\n");
            } while(validarPuesto(puesto));

            empleadoPtr = fopen("empleados.dat", "r");

            printf("\n%-6s%-20s%-12s%-15s%-11s%-25s\n",
                    "Clave", "Nombre", "Puesto", "FechaContrat.", "Telefono", "Correo");
            printf("----------------------------------------------------------------------------\n");
            
			fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
            
            contador = 1;
            while(!feof(empleadoPtr) && contador <= 100)
            {
                if(empleado.clave != 0 && strcmp(empleado.puesto, puesto) == 0)
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
                contador++;

            }
            
            fclose(empleadoPtr);
            break;
        
        case 'b':
            do
            {
                printf("Ingrese el status (PROGRAMADO, REALIZADO, CANCELADO): ");
                fflush(stdin);
                gets(status);
                if(validarEstatus(status))
                    printf("Error: Status no valido.\n");
            } while(validarEstatus(status));
            
            agendaPtr = fopen("agenda.dat", "r");
            
            printf("\n%-25s%-25s%-25s\n", "Cliente", "Empleado", "Servicio");
            printf("------------------------------------------------------------------------\n");
			
			fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			
			contador=1;
			
            while(!feof(agendaPtr))
            {
                if(agenda.claveAgenda != 0 && strcmp(agenda.estatus, status) == 0)
                    imprimirListaAgenda(&agenda.claveCliente, &agenda.claveEmpleado, &agenda.claveServicio);
                fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
                contador++;
            }
            
            fclose(agendaPtr);
            break;
            
        case 'c':
            do
            {
                printf("Ingrese la fecha (dd/mm/aaaa): ");
                fflush(stdin);
                gets(periodo);
                if(validarFecha(periodo))
                    printf("Error: Fecha no valida.\n");
            } while(validarFecha(periodo));
            
            agendaPtr = fopen("agenda.dat", "r");
            
            printf("\n%-25s%-25s%-25s\n", "Cliente", "Empleado", "Servicio");
            printf("------------------------------------------------------------------------\n");

			fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
			contador=1;
            while(!feof(agendaPtr) && contador<=100)
            {
                if(agenda.claveAgenda != 0 && strcmp(agenda.fecha, periodo) == 0 && strcmp(agenda.estatus, "PROGRAMADO") == 0)
                    imprimirListaAgenda(&agenda.claveCliente, &agenda.claveEmpleado, &agenda.claveServicio);
                fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
                
                contador++;

            }
            
            fclose(agendaPtr);
            break;
            
        case 'd':
            do
            {
                printf("Ingrese inicio del periodo de ventas (dd/mm/aaaa): ");
                fflush(stdin);
                gets(fechaVentaInicio);
                if(validarFecha(fechaVentaInicio))
                    printf("Error: Fecha no valida.\n");
            } while(validarFecha(fechaVentaInicio));
            
            do
            {
                printf("Ingrese fin del periodo de ventas (dd/mm/aaaa): ");
                fflush(stdin);
                gets(fechaVentaFin);
                if(validarFecha(fechaVentaFin))
                    printf("Error: Fecha no valida.\n");
            } while(validarFecha(fechaVentaFin));
            
            agendaPtr = fopen("agenda.dat", "r");
            
            printf("\n%-25s%-15s%-15s\n", "Servicio", "Fecha", "Precio");
            printf("----------------------------------------------------\n");
            
            fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
            
            contador= 1;
            while(!feof(agendaPtr) && contador <= 100)
            {
                if (agenda.claveAgenda != 0 && strcmp(agenda.estatus, "REALIZADO") == 0 && 
                    !fechaEnRango(agenda.fecha, fechaVentaInicio, fechaVentaFin))
                    imprimirVenta(&agenda);
                    
            	fread(&agenda, sizeof(struct DatosAgenda), 1, agendaPtr);
            	contador++;
            }
            
            fclose(agendaPtr);
            break;
            
        case 'e':
            printf("Generando archivo de clientes...\n");
            
            if((archivoCliente = fopen("archivoCliente.txt", "w")) == NULL || (clientePtr = fopen("clientes.dat", "r")) == NULL)
                printf("Error al acceder a los archivos.\n");
            else
            {
            	
            	fread(&cliente, sizeof(struct DatosCliente), 1, clientePtr);
            	
            	contador=1;
            	
                while(!feof(clientePtr) && contador <= 100)
                {
                    if(cliente.clave != 0)
                    {
                        fprintf(archivoCliente, "%d %s %s %s %s %s %s %s %s %s\n", 
                                cliente.clave, cliente.nombre, cliente.fechaNacimiento, 
                                cliente.telefono, cliente.correoElectronico, cliente.calle,
                                cliente.numero, cliente.colonia, cliente.municipio, cliente.estado);
                    }
                    
                	fread(&cliente, sizeof(struct DatosCliente), 1, clientePtr);
                	contador++;
                }
                fclose(archivoCliente);
                fclose(clientePtr);
                printf("Archivo generado exitosamente.\n");
            }
            break;
        
        case 'f':
            printf("Generando archivo de empleados...\n");
            
            if((archivoEmpleado = fopen("archivoEmpleado.txt", "w")) == NULL || (empleadoPtr = fopen("empleados.dat", "r")) == NULL)
                printf("Error al acceder a los archivos.\n");
            else
            {
            	fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
            	contador=1;
                while(!feof(empleadoPtr) && contador<=100)
                {
                    if(empleado.clave != 0)
                    {
                        fprintf(archivoEmpleado, "%d %s %s %s %s %s %s %s %s %s %s\n", 
                                empleado.clave, empleado.nombre, empleado.puesto, 
                                empleado.fechaContratacion, empleado.telefono, empleado.correoElectronico,
                                empleado.calle, empleado.numero, empleado.colonia, empleado.municipio, empleado.estado);
                    }
                    
                    fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
                    contador++;
                }
                fclose(archivoEmpleado);
                fclose(empleadoPtr);
                printf("Archivo generado exitosamente.\n");
            }
            break;
            
        case 'g':
            printf("Opciones de archivos a visualizar:\n");
            printf("1. Cliente\n");
            printf("2. Empleado\n");
            printf("Selecciona una opcion: ");
            scanf("%d", &opcion);
            
            switch(opcion)
            {
                case 1:
                    if((archivoCliente = fopen("archivoCliente.txt", "r")) == NULL)
                        printf("Error al abrir archivoCliente.txt\n");
                    else
                    {
                        printf("\n%-10s%-20s%-15s%-20s%-30s%-30s\n",
                               "Clave", "Nombre", "Nacimiento", "Telefono", "Correo", "Direccion");
                        printf("---------------------------------------------------------------------------------------------------------------\n");
                        
						fscanf(archivoCliente, "%d %s %s %s %s %s %s %s %s %s",
                               &cliente.clave, cliente.nombre, cliente.fechaNacimiento,
                               cliente.telefono, cliente.correoElectronico, cliente.calle,
                               cliente.numero, cliente.colonia, cliente.municipio, cliente.estado);
                        
                        contador=1;
                        while(!feof(archivoCliente) && contador<=100)
                        {
                            printf("%-10d%-20s%-15s%-20s%-30s%-30s\n",
                                   cliente.clave, cliente.nombre, cliente.fechaNacimiento,
                                   cliente.telefono, cliente.correoElectronico, cliente.calle);
                                   
	                        fscanf(archivoCliente, "%d %s %s %s %s %s %s %s %s %s",
	                               &cliente.clave, cliente.nombre, cliente.fechaNacimiento,
	                               cliente.telefono, cliente.correoElectronico, cliente.calle,
	                               cliente.numero, cliente.colonia, cliente.municipio, cliente.estado);
	                        contador++;
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
                               "Clave", "Nombre", "Puesto", "Contratacion", "Telefono", "Correo");
                        printf("----------------------------------------------------------------------------------------------------\n");
                        
						fscanf(archivoEmpleado, "%d %s %s %s %s %s %s %s %s %s %s",
                               &empleado.clave, empleado.nombre, empleado.puesto,
                               empleado.fechaContratacion, empleado.telefono, empleado.correoElectronico,
                               empleado.calle, empleado.numero, empleado.colonia, empleado.municipio, empleado.estado);
                               
                        while(!feof(archivoEmpleado))
                        {
                            printf("%-10d%-20s%-15s%-20s%-20s%-30s\n",
                                   empleado.clave, empleado.nombre, empleado.puesto,
                                   empleado.fechaContratacion, empleado.telefono, empleado.correoElectronico);
                            fscanf(archivoEmpleado, "%d %s %s %s %s %s %s %s %s %s %s",
                               &empleado.clave, empleado.nombre, empleado.puesto,
                               empleado.fechaContratacion, empleado.telefono, empleado.correoElectronico,
                               empleado.calle, empleado.numero, empleado.colonia, empleado.municipio, empleado.estado);
                        }
                        fclose(archivoEmpleado);
                    }
                    break;
            }
            break;
            
        case 'h':
            printf("Saliendo de reportes...\n");
            break;
    }
}

void imprimirListaAgenda(int *claveCliente, int *claveEmpleado, int *claveServicio)
{
    struct DatosEmpleado empleado;
    struct DatosCliente cliente;
    struct DatosServicio servicio;
    FILE *clientePtr, *empleadoPtr, *servicioPtr;
    
    if((clientePtr = fopen("clientes.dat", "r")) == NULL || 
       (empleadoPtr = fopen("empleados.dat", "r")) == NULL || 
       (servicioPtr = fopen("servicios.dat", "r")) == NULL)
        printf("Error al abrir los archivos.\n");
    else
    {
        fseek(clientePtr, (*claveCliente - 1) * sizeof(struct DatosCliente), SEEK_SET);
        fread(&cliente, sizeof(struct DatosCliente), 1, clientePtr);
        
        fseek(empleadoPtr, (*claveEmpleado - 1) * sizeof(struct DatosEmpleado), SEEK_SET);
        fread(&empleado, sizeof(struct DatosEmpleado), 1, empleadoPtr);
        
        fseek(servicioPtr, (*claveServicio - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fread(&servicio, sizeof(struct DatosServicio), 1, servicioPtr);
        
        if(cliente.clave != 0 && empleado.clave != 0 && servicio.clave != 0)
        {
            printf("%-25s%-25s%-25s\n", cliente.nombre, empleado.nombre, servicio.descripcion);
        }
        
        fclose(clientePtr);
        fclose(empleadoPtr);
        fclose(servicioPtr);
    }
}

void imprimirVenta(struct DatosAgenda *agenda)
{
    FILE *servicioPtr;
    struct DatosServicio servicio;

    if((servicioPtr = fopen("servicios.dat", "r")) == NULL)
        printf("Error al abrir servicios.dat\n");
    else
    {
        fseek(servicioPtr, (agenda->claveServicio - 1) * sizeof(struct DatosServicio), SEEK_SET);
        fread(&servicio, sizeof(struct DatosServicio), 1, servicioPtr);

        if(servicio.clave != 0)
        {
            printf("%-25s%-15s$%-14.2f\n", servicio.descripcion, agenda->fecha, servicio.precio);
        }

        fclose(servicioPtr);
    }
}
