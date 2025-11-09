#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "validaciones.h"
#include "estructuras.h"

bool validarOpcionMenu(int opcion)
{
    if(opcion < 1 || opcion > 6)
        return true;
    else
        return false;
}

bool validarSubmenu(char subopcion)
{
    subopcion = toupper(subopcion);
    
    if(subopcion != 'A' && subopcion != 'B' && subopcion != 'M' && subopcion != 'D' && subopcion != 'S')
        return true;
    else
        return false;
}

void validarArchivos(FILE **fClientes, FILE **fEmpleados, FILE **fServicios, FILE **fAgenda)
{
    int i;

    if((*fClientes = fopen("clientes.dat", "r+")) == NULL)
    {
        printf("Archivo 'clientes.dat' no encontrado. Creando nuevo archivo...\n");
        *fClientes = fopen("clientes.dat", "w+");
        if(*fClientes == NULL)
            printf("ERROR al crear el archivo 'clientes.dat'.\n");
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
        printf("Archivo 'empleados.dat' no encontrado. Creando nuevo archivo...\n");
        *fEmpleados = fopen("empleados.dat", "w+");
        if(*fEmpleados == NULL)
            printf("ERROR al crear el archivo 'empleados.dat'.\n");
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
        printf("Archivo 'servicios.dat' no encontrado. Creando nuevo archivo...\n");
        *fServicios = fopen("servicios.dat", "w+");
        if(*fServicios == NULL)
            printf("ERROR al crear el archivo 'servicios.dat'.\n");
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
        printf("Archivo 'agenda.dat' no encontrado. Creando nuevo archivo...\n");
        *fAgenda = fopen("agenda.dat", "w+");
        if(*fAgenda == NULL)
            printf("ERROR al crear el archivo 'agenda.dat'.\n");
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

    // Convertir a mayúsculas para validación
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
        verificacion = true;

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
        verificacion = true;
        
    return verificacion;
}

bool validarClave(int clave)
{
    if(clave < 1 || clave > 100)
        return true;
    else
        return false;
}

bool validarCadena(char *cadena)
{
    int i = 0;
    
    if(strlen(cadena) == 0)
        return true;
        
    while(cadena[i] != '\0')
    {
        if(!isalpha(cadena[i]) && !isspace(cadena[i]))
            return true;
        i++;
    }
    
    return false;
}

bool validarTelefono(char *telefono)
{
    int i = 0;
    
    if(strlen(telefono) != 10)
        return true;
        
    while(telefono[i] != '\0')
    {
        if(!isdigit(telefono[i]))
            return true;
        i++;
    }
    
    return false;
}

bool validarCorreo(char *correo)
{
    int i, cantidad_arrobas = 0;
    int longitud_cadena;
    bool punto_despues_arroba = false;
    
    longitud_cadena = strlen(correo);
    
    if(longitud_cadena < 5)
        return true;
        
    for(i = 0; correo[i] != '\0'; i++)
    {
        if(!isalpha(correo[i]) && !isdigit(correo[i]) &&
           correo[i] != '.' && correo[i] != '-' && correo[i] != '_' && correo[i] != '@')
            return true;
        
        if(correo[i] == '@')
            cantidad_arrobas++;
        
        if(cantidad_arrobas == 1 && correo[i] == '.')
            punto_despues_arroba = true;
    }
    
    if(cantidad_arrobas != 1 || correo[longitud_cadena-1] == '.' || !punto_despues_arroba)
        return true;
    
    return false;
}

bool validarNumero(char *numero)
{
    int i = 0;
    
    if(strlen(numero) == 0)
        return true;
        
    while(numero[i] != '\0')
    {
        if(!isdigit(numero[i]))
            return true;
        i++;
    }
    
    return false;
}

bool validarFecha(char *fecha)
{
    int dia, mes, anio;
    int dia_actual, mes_actual, anio_actual;
    int dias_por_mes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    dia_actual = tm_info->tm_mday;
    mes_actual = tm_info->tm_mon + 1;
    anio_actual = tm_info->tm_year + 1900;
    
    if(strlen(fecha) != 10)
        return true;
    
    if(fecha[2] != '/' || fecha[5] != '/')
        return true;
    
    for(int i = 0; i < 10; i++)
    {
        if(i != 2 && i != 5 && !isdigit(fecha[i]))
            return true;
    }
    
    dia = (fecha[0] - '0') * 10 + (fecha[1] - '0');
    mes = (fecha[3] - '0') * 10 + (fecha[4] - '0');
    anio = (fecha[6] - '0') * 1000 + (fecha[7] - '0') * 100 + 
           (fecha[8] - '0') * 10 + (fecha[9] - '0');
    
    if(anio < 1900 || anio > anio_actual)
        return true;
    
    if(mes < 1 || mes > 12)
        return true;

    if(mes == 2)
    {
        if((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
            dias_por_mes[1] = 29;
        else
            dias_por_mes[1] = 28;
    }
    
    if(dia < 1 || dia > dias_por_mes[mes-1])
        return true;
      
    if(anio > anio_actual)
        return true;
    else if(anio == anio_actual)
    {
        if(mes > mes_actual)
            return true;
        else if(mes == mes_actual && dia > dia_actual)
            return true;
    }
    
    return false;
}

bool validarPrecio(float precio)
{
    if(precio <= 0)
        return true;
    else
        return false;
}

bool validarEstatus(char *estatus)
{
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
        return true;
    else
        return false;
}
