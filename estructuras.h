#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct DatosCliente
{
	int clave;
	char nombre[100];
	char fechaNacimiento[20];
	char telefono[20];
	char correoElectronico[100];
	char calle[100];
	int numero;
};


struct DatosEmpleado
{
	int clave;
	char nombre[100];
	char puesto[10];
	char fechaContratacion[20];
	char telefono[20];
	char correoElectronico[100];
};


struct DatosServicio
{
	int clave;
	char descripcion[200];
	float precio;
	char duracion[10];
};


struct DatosAgenda
{
	int claveCliente;
	int claveEmpleado;
	int claveServicio;
	char fecha[20];
	char hora[10];
	char estatus[10];
};


#endif
