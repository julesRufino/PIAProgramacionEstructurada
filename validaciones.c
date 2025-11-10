#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "validaciones.h"
#include "estructuras.h"

void printError(const char *mensaje)
{
    printf("\033[1;31m");   
    printf("ERROR: %s\n", mensaje);
    printf("\033[0m");      
    printf("\a");           
    fflush(stdout);         
}

bool validarSN(char opcion)
{
	bool validacion = false;
	
	if(opcion != 'S' && opcion != 's' && opcion != 'n' && opcion != 'N')
	{
		validacion = true;
		printError("Error, ingrese opciones validas (s/n)\n");
	}
	
	return validacion;
}

bool validarOpcion3(int opcion)
{
	bool validacion = false;
	
	if(opcion < 1 || opcion > 3)
	{
		validacion = true;
		printError("Opcion fuera de rango (1-3).\n");
	}
	
	return validacion;
}

bool validarOpcionMenu(int opcion)
{
	bool validacion = false; 
	
    if(opcion < 1 || opcion > 6)
    {
        validacion = true;
        printError("Opcion del menu fuera de rango (1-6).\n");
    }
        
	return validacion;
}

bool validarSubmenu(char subopcion)
{
	bool validacion = false;
	
    subopcion = toupper(subopcion);
    
    if(subopcion != 'A' && subopcion != 'B' && subopcion != 'M' && subopcion != 'D' && subopcion != 'S')
    {
        validacion = true;
        printError("Subopcion invalida. Use A, B, M, D o S.\n");
    }
	
	return validacion;
}

bool ValidarSubmenuReporte(char subopcion)
{
	bool validacion = false;
    subopcion = tolower(subopcion);
    
    if(subopcion != 'a' && subopcion != 'b' && subopcion != 'c' && subopcion != 'd' &&
       subopcion != 'e' && subopcion != 'f' && subopcion != 'g' && subopcion != 'h')
       {
        validacion = true;
        printError("Subopcion invalida. Use a, b, c, d, e, f, g o h.\n");
       }

    return validacion;
}

void validarArchivos(FILE **fClientes, FILE **fEmpleados, FILE **fServicios, FILE **fAgenda)
{
    int i;

    if((*fClientes = fopen("clientes.dat", "r+")) == NULL)
    {
        printError("Archivo 'clientes.dat' no encontrado. Creando nuevo archivo...\n");
        *fClientes = fopen("clientes.dat", "w+");
        if(*fClientes == NULL)
            printError("al crear el archivo 'clientes.dat'.\n");
        else
        {
            struct DatosCliente vacio = {0, "", "", "", "", "", "", "", "", ""};
            for(i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosCliente), 1, *fClientes);
            printf("Archivo 'clientes.dat' creado exitosamente.\n");
        }
    }

    if((*fEmpleados = fopen("empleados.dat", "r+")) == NULL)
    {
        printError("Archivo 'empleados.dat' no encontrado. Creando nuevo archivo...\n");
        *fEmpleados = fopen("empleados.dat", "w+");
        if(*fEmpleados == NULL)
            printError("al crear el archivo 'empleados.dat'.\n");
        else
        {
            struct DatosEmpleado vacio = {0, "", "", "", "", "", "", "", "", "", ""};
            for(i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosEmpleado), 1, *fEmpleados);
            printf("Archivo 'empleados.dat' creado exitosamente.\n");
        }
    }

    if((*fServicios = fopen("servicios.dat", "r+")) == NULL)
    {
        printError("Archivo 'servicios.dat' no encontrado. Creando nuevo archivo...\n");
        *fServicios = fopen("servicios.dat", "w+");
        if(*fServicios == NULL)
            printError("al crear el archivo 'servicios.dat'.\n");
        else
        {
            struct DatosServicio vacio = {0, "", 0.0, ""};
            for(i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosServicio), 1, *fServicios);
            printf("Archivo 'servicios.dat' creado exitosamente.\n");
        }
    }

    if((*fAgenda = fopen("agenda.dat", "r+")) == NULL)
    {
        printError("Archivo 'agenda.dat' no encontrado. Creando nuevo archivo...\n");
        *fAgenda = fopen("agenda.dat", "w+");
        if(*fAgenda == NULL)
            printError("al crear el archivo 'agenda.dat'.\n");
        else
        {
            struct DatosAgenda vacio = {0, 0, 0, 0, "", "", ""};
            for(i = 0; i < 100; i++)
                fwrite(&vacio, sizeof(struct DatosAgenda), 1, *fAgenda);
            printf("Archivo 'agenda.dat' creado exitosamente.\n");
        }
    }
}

bool validarPuesto(char *puestoF)
{
    bool verificacion = false;

    int i = 0;
    char puestoUpper[20];
    strcpy(puestoUpper, puestoF);
    
    while(puestoUpper[i] != '\0')
    {
        puestoUpper[i] = toupper(puestoUpper[i]);
        i++;
    }

    if(strcmp(puestoUpper, "ESTILISTA") != 0 && strcmp(puestoUpper, "COLORISTA") != 0 && 
       strcmp(puestoUpper, "RECEPCIONISTA") != 0 && strcmp(puestoUpper, "COORDINADOR") != 0 && 
       strcmp(puestoUpper, "MAQUILLADOR") != 0)
       {
        verificacion = true;
        printError("Puesto invalido. Use ESTILISTA, COLORISTA, RECEPCIONISTA, COORDINADOR o MAQUILLADOR.\n");
       }

    return verificacion;
}

bool fechaEnRango(char *fecha, char *inicio, char *fin)
{
    bool verificacion = false;
    int d, m, a;
    int di, mi, ai;
    int df, mf, af;

    sscanf(fecha, "%d/%d/%d", &d, &m, &a);
    sscanf(inicio, "%d/%d/%d", &di, &mi, &ai);
    sscanf(fin, "%d/%d/%d", &df, &mf, &af);

    long f = a * 10000 + m * 100 + d;
    long fi = ai * 10000 + mi * 100 + di;
    long ff = af * 10000 + mf * 100 + df;

    if(f < fi || f > ff)
    {
        verificacion = true;
        printError("Fecha fuera de rango.\n");
    }
        
    return verificacion;
}

bool validarClave(int clave)
{
	bool validacion = false;
	
    if(clave < 1 || clave > 100)
    {
        validacion = true;
        printError("Clave fuera de rango (1-100).\n");
    }
    
    return validacion;
}

bool validarCadena(char *cadena)
{
	bool validacion = false;
    int i = 0;
    
    if(strlen(cadena) == 0)
    {
        validacion = true;
        printError("Cadena vacia.\n");
    }
        
    while(cadena[i] != '\0')
    {
        if(!isalpha(cadena[i]) && !isspace(cadena[i]))
        {
            validacion = true;
            printError("Cadena contiene caracteres invalidos (solo letras y espacios).\n");
        }
        i++;
    }
    
    return validacion;
}

bool validarTelefono(char *telefono)
{
	bool validacion = false;
	
    int i = 0;
    
    if(strlen(telefono) != 10)
    {
        validacion = true;
        printError("Telefono debe tener 10 digitos.\n");
    }
        
    while(telefono[i] != '\0')
    {
        if(!isdigit(telefono[i]))
        {
            validacion = true;
            printError("Telefono contiene caracteres invalidos\n");
        }
        i++;
    }
    
    return validacion;
}

bool validarCorreo(char *correo)
{
	bool validacion = false;
    int i, cantidad_arrobas = 0;
    int longitud_cadena;
    bool punto_despues_arroba = false;
    
    longitud_cadena = strlen(correo);
    
    if(longitud_cadena < 5)
        validacion = true;
        
    for(i = 0; correo[i] != '\0'; i++)
    {
        if(!isalpha(correo[i]) && !isdigit(correo[i]) &&
           correo[i] != '.' && correo[i] != '-' && correo[i] != '_' && correo[i] != '@')
            validacion = true;
        
        if(correo[i] == '@')
            cantidad_arrobas++;
        
        if(cantidad_arrobas == 1 && correo[i] == '.')
            punto_despues_arroba = true;
    }
    
    if(cantidad_arrobas != 1 || correo[longitud_cadena-1] == '.' || !punto_despues_arroba)
        validacion = true;
        
    if (validacion)
        printError("Correo electronico no valido.\n");
    return validacion;
}

bool validarNumero(char *numero)
{
	bool validacion = false;
    int i = 0;
    
    if(strlen(numero) == 0)
    {
        validacion = true;
        printError("Numero vacio.\n");
    }
        
    while(numero[i] != '\0')
    {
        if(!isdigit(numero[i]))
        {
            validacion = true;
            printError("Numero contiene caracteres invalidos (solo digitos).\n");
        }
        i++;
    }
    
    return validacion;
}

bool validarFecha(char *fecha)
{
	bool validacion = false;
    int dia, mes, anio;
    int dia_actual, mes_actual, anio_actual;
    int dias_por_mes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int i;
    
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    dia_actual = tm_info->tm_mday;
    mes_actual = tm_info->tm_mon + 1;
    anio_actual = tm_info->tm_year + 1900;
    
    if(strlen(fecha) != 10)
        validacion = true;
    
    if(fecha[2] != '/' || fecha[5] != '/')
        validacion = true;
    
    for(i = 0; i < 10; i++)
    {
        if(i != 2 && i != 5 && !isdigit(fecha[i]))
            validacion = true;
    }
    
    dia = (fecha[0] - '0') * 10 + (fecha[1] - '0');
    mes = (fecha[3] - '0') * 10 + (fecha[4] - '0');
    anio = (fecha[6] - '0') * 1000 + (fecha[7] - '0') * 100 + 
           (fecha[8] - '0') * 10 + (fecha[9] - '0');
    
    if(anio < 1900 || anio > anio_actual)
        validacion = true;
    
    if(mes < 1 || mes > 12)
        validacion = true;

    if(mes == 2)
    {
        if((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
            dias_por_mes[1] = 29;
        else
            dias_por_mes[1] = 28;
    }
    
    if(dia < 1 || dia > dias_por_mes[mes-1])
        validacion = true;
      
    if(anio > anio_actual)
        validacion = true;
    else if(anio == anio_actual)
    {
        if(mes > mes_actual)
            validacion = true;
        else if(mes == mes_actual && dia > dia_actual)
            validacion = true;
    }
    if(validacion)
        printError("Fecha no valida.\n");
    return validacion;
}

bool validarPrecio(float precio)
{
	bool validacion = false;
	 
    if(precio <= 0)
    {
        validacion = true;
        printError("Precio debe ser mayor que cero.\n");
    }
        
    return validacion;
}

bool validarEstatus(char *estatus)
{
	bool validacion = false;
	
    char estatusUpper[20];
    strcpy(estatusUpper, estatus);
    int i = 0;

    while(estatusUpper[i] != '\0')
    {
        estatusUpper[i] = toupper(estatusUpper[i]);
        i++;
    }
    
    if(strcmp(estatusUpper, "PROGRAMADO") != 0 && strcmp(estatusUpper, "REALIZADO") != 0 && 
       strcmp(estatusUpper, "CANCELADO") != 0)
       {
        validacion = true;
        printError("Estatus invalido. Use PROGRAMADO, REALIZADO o CANCELADO.\n");
       }
        
    return validacion;
}
