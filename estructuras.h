#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct DatosCliente
{
	int clave;
	char nombre[100];
	char fechaNacimiento[20];
	char telefono[20];
	char correoElectronico[100];
};


struct DatosEmpleado
{
	int clave;
	char nombre[100];
	char puesto[50];
	char fechaContratacion[20];
	char telefono[20];
	char correoElectronico[100];
};


struct DatosServicio
{
	int clave;
	char descripcion[200];
	float precio;
	char duracion[50];
};


struct DatosAgenda
{
	int claveCliente;
	int claveEmpleado;
	int claveServicio;
	char fecha[20];
	char hora[10];
	char estatus[20];
};


#endif
