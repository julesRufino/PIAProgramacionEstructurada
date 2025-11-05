Instrucciones:

en una peluqueria se lleva el control de los servicios ofrecidos de forma manual,
pero con la finalidad de hacer mas eficiente este proceso, se ha iniciado un analisis
de los datos para poder automatizar dicha informacion.

El sistema debera permitir registrar clientes, administrar los servicios ofrecidos,
agendar citas y generar reportes, utilizando estructuras, funciones, punteros y archivos
de acceso directo para almacenar la informacion de manera permanente.

Una vez llevado a cabo el analisis, se encontro lo siguiente:

Para cada cliente se cuenta con la siguiente informacion: clave del cliente, nombre completo,
fecha de nacimiento, telefono, correo electronico y direccion (calle, numero, colonia, municipio y estado).
Se detecto que se tiene que validar:

-clave, entre 1 y 100.
-Nombre (texto y espacios).
-Fecha de nacimiento, que sea menor a fecha actual. Validar cada dato
(dia, mes y ano).
-Telefono. (que sean 10 digitos).
-Correo electronico, contenga @ y dominio (gmail.com, edu.mx, hotmail.com, etc.).

CREAR UNA ESTRUCTURA PARA DATOS DEL CLIENTE. A lo mas pueden ser 100.

Para cada empleado se cuenta con la siguiente informacion: clave del empleado, nombre completo,
puesto, fecha de contratacion, telefono, correo electronico y direccion
(calle, numero, colonia, municipio y estado). Se detecto que se tiene que validar:

-clave, entre 1 y 100.
-Nombre (texto y espacios).
-Puesto, puede ser estilista, colorista, recepcionista, coordinador o maquillador.
-Fecha de contratacion, que sea menor a fecha actual. Validar cada dato
(dia, mes y ano).
-Telefono. (que sean 10 digitos).
-Correo electronico, contenga @ y dominio (gmail.com, edu.mx, hotmail.com, etc.).

CREA UNA ESTRUCTURA PARA LOS DATOS DEL EMPLEADO. A lo mas pueden ser 100.

Para los servicios se cuenta con la siguiente informacion: clave del servicio,
descripcion, precio y duracion aproximada. Se detecto que se tiene que validar:

-Clave, entre 1 y 100.
-Descripcion (texto y espacios).
-Precio (Mayor a cero).
-Duracion aproximada, pueden ser horas y/o minutos.

Crear una estructura para los datos del servicio. A lo mas pueden ser 100.

Para la agenta se cuenta con la siguiente informacion:
clave del cliente, clave del empleado que dara el servicio, clave del servicio,
fecha, hora y status. Se detecto que se tiene que validar:

-Las claves validar que existan previamente en el archivo.
-Estatus, pueden ser: programado, realizado, cnacelado.

CREAR UNA ESTRUCTURA PARA LOS DATOS DE LA AGENDA. A lo mas pueden ser 100.

*Utilizar funciones por referencia y apuntadores para las validaciones.
*Utilizar archivos de acceso directo para guardar todos los datos.
*Elaborar funciones para optimizar el codigo.
*No incluir comentarios en el codigo.
*Elaborar tu propio archivo de cabecera.

El sistema funcionara de arcuerdo con las siguietnes pantallas:

1) clientes
2) Empleados
3) servicios
4) agenda
5) reportes
6) Salir 

opcion:
Validar que la opcion se encuentre entre 1 y 6

--CADA OPCION DEL MENU SE MANEJARA COMO UNA FUNCION--

Cuando se elija una opcion de 1 a 4, se mostrar el siguiente submenu:

A: Agregar "registros"
B: Consultar "registros"
M: Modificar "registros"
D: Borrrar "registros"
S: Salir

Descripcion:

A: Se daran de alta registros de acuerdo con la pantalla seleccionada
y a las validaciones que correspondan. Enviar mensaje de error al usuario
y tambien cuando se haya agregado el registro correctamente.

C: Se pueden consultar los datos de el o los registros seleccionados.
Muestra las opciones de busqueda de acuerdo con tu criterio (por clave, por nombre, etc.).
Si el registro consultado no existe, enviar el mensaje correspondiente.

M: Modificar registros. El usuario realizara los cambios a los datos que la logica
del sistema lo permita. Enviar mensaje si el registro no existe y tambien cuando se haya
realizado la modificacion. La busqueda del registro se realizara con las opciones que propongas.

D: Borrar registros. Se realizara el borrado logico del registro indicado por el usuario.
Enviar mensaje si el registro no existe y tambien cuando se haya realizado la baja.

S: Salir.

En cada una de las opciones, preguntar al usuario si desea realizar otra accion,
por ejemplo: si eligio la opcion A, cuando ingrese los datos para el primer registro
y que se haya dado de alta, se le preguntara si desea ingresar otro registro (utilizar el ciclo while).

para TODAS LAS VALIDACIONES, cuando se envie un mensaje de error, el texto se pondra
de color rojo y se escuchara una alerta.

Todos los archivos se abriran y cerraran desde main y se pasara el apuntador al archivo, tambien 
se manejara un apuntador a alguna de las estructuras, el cual se pasara como parametro
a la funcion.

Al seleccionar la opcion 5), se debera mostrar la siguiente pantalla:

reportes

a) Listado de empleados por puesto.
b) Lista de citas por status.
c) Listado de citas por fecha.
d) ventas por fecha.
e) Generar archivo de clientes.
f) generar archivo de empleados.
g) Mostrar archivo.
h) Salir

Opcion:
    Validar que la opcion sean de la letra "a" a la "h"

Si la respuesta es a), mostrar toda la información de los empleados (en forma tabular),
de acuerdo con el puesto indicado (Validar el puesto).

Si la respuesta es b), preguntar el estatus al usuario (validarla) e imprimir la lista 
con todos los datos (nombre del cliente, empleado y servicio).

Si la respuesta es c), preguntar el período y mostrar la información de todas las citas 
programadas que se hayan creado en esa fecha. Indicar el nombre del cliente, empleado y servicio que se realizará.

Si la respuesta es d), se le solicitará al usuario el período y se le mostrará 
el ingreso de esas fechas (servicios realizados).

Si la respuesta es e), generar el archivo de texto con toda la información

Si la respuesta es f), generar el archivo de texto con toda la información

Si la respuesta es g), preguntar si se desea abrir el archivo de clientes o 
empleados y mostrar el contenido en la pantalla (formato tabular)

Después de mostrar la información de cada una de las opciones de reportes, regresar a esta misma opción, 
solo regresará al menú principal cuando la opción sea h.

Mostrar mensajes si no hay registros de la opción seleccionada. 
Desde main validar las opciones a las que se puede ingresar (ya exista información)

Especificaciones técnicas:

· El editor que se utilizará es Dev-C.

· Uso de estructuras (struct) para representar los datos de cada elemento.

· Empleo de funciones para cada operación con sus parámetros correspondientes.

· Utilización de punteros para paso de parámetros y manipulación de estructuras.

· Uso de archivos binarios de acceso directo en todo el proyecto,
  excepto en la parte indicada, en donde se utilizarán archivos de texto.

· Implementación de menús y submenús que faciliten la navegación.

· Validaciones en todas las entradas del usuario 
  (por ejemplo, evitar claves duplicadas o registros vacíos).

· En la actividad en MSTeams, se subirá el código fuente 
  con los archivos de cabecera ne