#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include "estructuras.h"

void imprimirMenu();
void imprimirSubMenu(char *);
void imprimirMenuReportes();
void menuReportes(char opcion);
void imprimirListaAgenda(int *, int *, int *);
void imprimirVenta(struct DatosAgenda *);

void AgregarCliente(FILE *);
void ConsultarCliente(FILE *);
void ModificarCliente(FILE *);
void BorrarCliente(FILE *);

void AgregarEmpleado(FILE *);
void ConsultarEmpleado(FILE *);
void ModificarEmpleado(FILE *);
void BorrarEmpleado(FILE *);

void AgregarServicio(FILE *);
void ConsultarServicio(FILE *);
void ModificarServicio(FILE *);
void BorrarServicio(FILE *);

void AgregarCita(FILE *);
void ConsultarCita(FILE *);
void ModificarCita(FILE *);
void BorrarCita(FILE *);

#endif
