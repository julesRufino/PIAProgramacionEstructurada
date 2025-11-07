#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>


void imprimirMenu();
void imprimirSubMenu(char *titulo);
void imprimirMenuReportes();
void menuReportes(char opcionF);


void AgregarCliente(FILE *fptr);
void ConsultarCliente(FILE *fptr);
void ModificarCliente(FILE *fptr);
void BorrarCliente(FILE *fptr);


void AgregarEmpleado(FILE *fptr);
void ConsultarEmpleado(FILE *fptr);
void ModificarEmpleado(FILE *fptr);
void BorrarEmpleado(FILE *fptr);


void AgregarServicio(FILE *fptr);
void ConsultarServicio(FILE *fptr);
void ModificarServicio(FILE *fptr);
void BorrarServicio(FILE *fptr);

#endif
