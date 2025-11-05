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
	char colonia[100];
	char municipio[100];
	char estado[100];
	int activo;
};


struct DatosEmpleado
{
	int clave;
	char nombre[100];
	char puesto[50];
	char fechaContratacion[20];
	char telefono[20];
	char correoElectronico[100];
	char calle[100];
	int numero;
	char colonia[100];
	char municipio[100];
	char estado[100];
	int activo;
};


struct DatosServicio
{
	int clave;
	char descripcion[200];
	float precio;
	char duracion[50];
	int activo;
};


struct DatosAgenda
{
	int claveCliente;
	int claveEmpleado;
	int claveServicio;
	char fecha[20];
	char hora[10];
	char estatus[20];
	int activo;
};


#endif
