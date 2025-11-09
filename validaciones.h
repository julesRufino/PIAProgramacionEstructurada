#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stdio.h>
#include <stdbool.h>

void validarArchivos(FILE **fClientes, FILE **fEmpleados, FILE **fServicios, FILE **fAgenda);
bool validarPuesto(char *puesto);
bool fechaEnRango(char *fecha, char *inicio, char *fin);
bool validarOpcionMenu(int opcion);
bool validarSubmenu(char subopcion);
bool validarClave(int clave);
bool validarEstatus(char *estatus);
bool validarCadena(char *cadena);
bool validarTelefono(char *telefono);
bool validarCorreo(char *correo);
bool validarNumero(char *numero);
bool validarFecha(char *fecha);
bool validarPrecio(float precio);

#endif
