#include <stdio.h>
#include <stdlib.h>


struct Fecha {
	int dia, mes, ano;
};

struct Mascota {
	char nombre[60], domicilio[60], localidad[60], telefono[25];
	int dni_dueno;
	float peso;
	Fecha nacimiento;
};

struct Veterinario {
	char apellido_nombre[60], telefono[25];
	int matricula, dni;
};

struct Turno {
	int matricula_veterinario, dni_dueno;
	char detalle[380];
	Fecha fecha;
	bool atendido;
};

struct Usuario {
	char usuario[10], contrasena[10], apellido_nombre[60];
};
