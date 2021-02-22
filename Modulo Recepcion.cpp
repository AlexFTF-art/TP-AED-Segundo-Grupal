/*M�dulo Recepci�n:
Este m�dulo satisface las necesidades del personal que asiste a los veterinarios en la atenci�n al
p�blico. Desde aqu� se hace ingreso de las mascotas, y la registraci�n de los turnos.
Esta aplicaci�n debe permitir obtener un informe de las mascotas atendidos en determinada fecha
por un determinado veterinario.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

int Menu();
void IniciarSesion(Usuario usuarios[], int N, Usuario &usuario);
void RegistrarMascota(Mascota mascotas[], int &N);
void RegistrarTurno(Turno turnos[], int &N);
void ListarAtenciones(Turno turnos[], int N);

int main() {
	FILE *usuario, *mascota, *turno;
	int opcion = Menu(), N = 0, N_mascota = 0, N_turno = 0;
	bool user_logged = false;
	Usuario usuarios[50], user;
	Mascota mascotas[50];
	Turno turnos[50];

	usuario = fopen("Usuarios.dat", "r+b");
	if (usuario != NULL) {
		do {				
			fread(&usuarios[N], sizeof(Usuario), 1, usuario);
			N++;
		} while(!feof(usuario));
	}
	mascota = fopen("Mascotas.dat", "r+b");
	if (mascota != NULL) {
		do {
			fread(&mascotas[N_mascota], sizeof(Mascota), 1, mascota);
			N_mascota++;
		} while(!feof(mascota));
	}
	turno = fopen("Turnos.dat", "r+b");
	if (turno != NULL) {
		rewind(turno);
		fread(&turnos[N_turno], sizeof(Turno), 1, turno);
		N_turno++;
		while(!feof(turno)) {				
			fread(&turnos[N_turno], sizeof(Turno), 1, turno);
			N_turno++;
		}
	}


	while (opcion != 5) {
		system("cls");
		switch (opcion) {
			case 1: 
				if (N < 1) printf("No se encuentran Usuarios en el Sistema. Por favor registre un nuevo usuario\n");
				else if (!user_logged) {
					IniciarSesion(usuarios, N, user);
					user_logged = true;
				} else printf("Ya ha ingresado al sistema.\n");
				break;
			case 2:
				if (user_logged) RegistrarMascota(mascotas, N_mascota);
				else printf("Primero debe iniciar sesi%cn.\n", 162);
				break;
			case 3:
				if (user_logged) RegistrarTurno(turnos, N_turno);
				else printf("Primero debe iniciar sesi%cn.\n", 162);
				break;
			case 4:
				if (user_logged) ListarAtenciones(turnos,N);
				else printf("Primero debe iniciar sesi%cn.\n", 162);
				break;
			default: printf("Saliendo del m%cdulo Recepci%cn", 162, 162); break;
		}
		system("pause");
		opcion = Menu();
	}
	if (N > 0) {
		rewind(usuario);
		if (usuario == NULL) {
			usuario = fopen("Usuarios.dat", "w+b");
			if (usuario == NULL) {
				printf("Error al crear el archivo 'Usuarios.dat'.\nTerminando programa.\n");
				exit(1);
			}
		}
		for (int i = 0; i < N; i++) fwrite(&usuarios[i], sizeof(Usuario), 1, usuario);
	}
	fclose(usuario);
	if (N_mascota > 0) {
		rewind(mascota);
		if (mascota == NULL) {
			mascota = fopen("Mascota.dat", "w+b");
			if (mascota == NULL) {
				printf("Error al crear el archivo 'Mascota.dat'.\nTerminando programa.\n");
				exit(1);
			}
		}
		for (int i = 0; i < N_mascota; i++) fwrite(&mascota[i], sizeof(Mascota), 1, mascota);
	}
	fclose(mascota);
	if (N_turno > 0) {
		rewind(turno);
		if (turno == NULL) {
			turno = fopen("Turnos.dat", "w+b");
			if (turno == NULL) {
				printf("Error al crear el archivo 'Turnos.dat'.\nTerminando programa.\n");
				exit(1);
			}
		}
		for (int i = 0; i < N_turno; i++) fwrite(&turnos[i], sizeof(Turno), 1, turno);
	}
	fclose(turno);
	return 0;
}

int Menu() {
	int opcion;	
	do {
		system ("cls");
		printf ("Modulo del Asistente\n=========================\n 1.- Iniciar Sesi%cn\n 2.- Registrar Mascota\n 3.- Registrar Turno\n 4.- Listado de Atenciones por Veterinario y Fecha\n 5.- Salir del M%cdulo.\n\nElige una Opcion:\t", 162, 162);
		scanf("%d", &opcion);	
	} while (opcion < 0 || opcion > 5);
	return (opcion);
}

void IniciarSesion(Usuario usuarios[], int N, Usuario &usuario) {
	system ("cls");
	int check, i = -1, temp = 0;
	_flushall();
	do {
		check = 0;
		// Leer datos del usuario
		printf ("Introduce el Usuario:\t\t");
		gets(usuario.usuario);
		printf("\nIntroduce la Contrase%ca:\t", 164);
		gets(usuario.contrasena);
		
		// comparar con los del archivo
		for(i=0; i < N; i++) {
			temp = strcmp(usuario.usuario, usuarios[i].usuario);
			if(temp == 0) {
				check = 1;
				temp= strcmp(usuario.contrasena, usuarios[i].contrasena);
				if(temp == 0) {
					check = 2;
					strcpy(usuario.apellido_nombre, usuarios[i].apellido_nombre);
					i = N;
				}
			}
		}
		switch(check) {
			case 0:	system("cls");
				printf("Nombre de Usuario inexistente. Vuelva a intentarlo\n");
				break;
			case 1:	system("cls");
				printf("Contrase%ca Incorrecta. Vuelva a intentarlo\n", 164);
				break;
			case 2:	system("cls");
				printf("Inicio de sesi%cn exitoso\n", 162);
				break;
		}
	} while (check != 2);
}

void RegistrarMascota(Mascota mascotas[], int &N) {
	Mascota mascota;

	_flushall();
	printf ("Introduce el nombre de la Mascota: ");
	gets(mascota.nombre);
	printf ("Introduce el domicilio de la Mascota: ");
	gets(mascota.domicilio);
	printf ("Introduce la localidad de la Mascota: ");
	gets(mascota.localidad);
	printf ("Introduce el telefono de la Mascota: ");
	gets(mascota.telefono);
	printf ("Introduce el dni del due%co de la Mascota: ", 164);
	scanf("%d", &mascota.dni_dueno);
	printf ("Introduce el peso de la Mascota: ");
	scanf("%f", &mascota.peso);
	printf ("Fecha de nacimiento de la Mascota\nDia: ");
	scanf("%d", &mascota.nacimiento.dia);
	printf ("Mes: ");
	scanf("%d", &mascota.nacimiento.mes);
	printf ("A%co: ", 164);
	scanf("%d", &mascota.nacimiento.ano);
	mascotas[N] = mascota;
	N++;
	system("cls");
	printf("Mascota registrada exitosamente.\nVolviendo al Men%c principal.\n", 163);
}

void RegistrarTurno(Turno turnos[], int &N) {
	Turno turno;

	_flushall();
	printf("Ingrese la Fecha");
	printf("\nDia: ");
	scanf("%d", &turno.fecha.dia);
	printf("Mes: ");
	scanf("%d", &turno.fecha.mes);
	printf("A%co", 164);
	scanf("%d", &turno.fecha.ano);
	printf("Ingrese la Matricula del veterinario: ");
	scanf("%i", &turno.matricula_veterinario);
	printf("Ingrese el DNI del Due%co: ", 164);
	scanf("%i", &turno.dni_dueno);
	turno.atendido = false;
	turnos[N] = turno;
	N++;
	system("cls");
	printf("Turno registrado exitosamente.\nVolviendo al Men%c principal.\n", 163);
}

void ListarAtenciones(Turno turnos[], int N) {
	Fecha fecha;
	Turno resultado[10];
	int matricula, n = 0;

	printf("Ingrese la matricula del veterinario a buscar: ");
	scanf("%d", &matricula);
	printf("Ingrese la fecha");
	printf ("\nDia: ");
	scanf("%d", &fecha.dia);
	printf ("\nMes: ");
	scanf("%d", &fecha.mes);
	printf ("\nA%co: ", 164);
	scanf("%d", &fecha.ano);

	for (int i = 0; i < N; i++) {
		if (turnos[i].atendido && turnos[i].matricula_veterinario == matricula && turnos[i].fecha.ano == fecha.ano && turnos[i].fecha.mes == fecha.mes && turnos[i].fecha.dia == fecha.dia) {
			resultado[n] = turnos[i];
			n++;
		}
	}
	if (n < 1) printf("\nNo se encontraron resultados.\n");
	else {
		printf("\nTurnos del veterinario con mat. %d, en la fecha %d/%d/%d\n", matricula, fecha.dia, fecha.mes, fecha.ano);
		for (int i = 0; i < n; i++) printf("\n- Dni del due%co: %d", 164, resultado[i].dni_dueno);
	}
	system("pause");
}
