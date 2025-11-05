#include <stdio.h>

struct datosCliente
{
	int clave;
	char nombre[100];
	char fechaNacimiento[100];
	char telefono[20];
	char correoElectronico[100];
};

struct datosEmpleado
{
	int clave;
	char nombre[100];
	char puesto[50];
	char fechaContratacion[100];
	char telefono[20];
	char correoElectronico[100];
};

struct datosServicio
{
	int clave;
	char descripcion[200];
	float precio;
	char duracion[100];
};

struct datosAgenda
{
	int clave;
	char estatus[50];
};


