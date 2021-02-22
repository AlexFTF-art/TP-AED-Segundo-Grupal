/*Esta parte del proyecto estará dirigida a los diferentes profesionales que atienden y registran la
evolución de las mascotas en una base de datos de historias clínicas. El sistema deberá contar con un listado de
las mascotas que están registradas para ser atendidas ese día, para visualizarla, el veterinario deberá
identificarse en el sistema por medio de su número de matrícula y contraseña y accediendo a la opción indicada.
De esta manera el veterinario llamará por apellido y nombre a la mascota que atenderá, una vez realizada esta
tarea procede al ingreso de la evolución, en un texto de no más de 380 caracteres. Luego de realizada esta
operación la mascota debe desaparecer del listado.
Los datos de interés para el veterinario en este proceso son: Apellido y Nombres de la mascota (el
apellido corresponde al dueño o familia), DNI del dueño, Localidad, Edad (calculada con la fecha de nacimiento
registrada), Peso.
La historia clínica de la mascota es común para todos los veterinarios, por lo tanto se deberá visualizar
fecha de atentación de la misma y el nombre del veterinario que la redacto*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Types.h"

int Menu();
void IniciarSesion(Veterinario veterinarios[], int N, Veterinario &usuario);
void ListaEspera(Turno turnos[], Mascota mascotas[], int N, int N_mascota, int matricula);
void Atender(Turno turnos[], Mascota mascotas[], int N, int N_mascota, int matricula);
int calcularEdad(Fecha nacimiento) {
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);
  char fecha[10];
  strftime(fecha, 10, "%m/%y", tlocal);
  int mes = (fecha[0] - 48) * 10 + fecha[1] - 48, ano = (fecha[3] - 48) * 10 + fecha[4] + 1952;

  return ((mes < nacimiento.mes) ? ano - nacimiento.ano : ano - nacimiento.ano - 1);
}

int main() {
	int N = 0, N_turnos = 0, N_mascota = 0, opcion = Menu();
	FILE *veterinario, *mascota, *turno;
	Veterinario veterinarios[50], usuario;
	Mascota mascotas[50];
	Turno turnos[50];

  usuario.matricula = 0;
	veterinario = fopen ("Veterinarios.dat","r+b");
	if (veterinario != NULL) {
		do {				
			fread(&veterinarios[N], sizeof(Veterinario), 1, veterinario);
			N++;
		} while(!feof(veterinario));
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
		do {				
			fread(&turnos[N_turnos], sizeof(Turno), 1, turno);
			N_turnos++;
		} while(!feof(turno));
	}


	while(opcion != 4) {
		system("cls");
		switch (opcion) {
			case 1:
				if (usuario.matricula == 0) IniciarSesion(veterinarios, N, usuario);
				else printf("Ya ha ingresado al sistema.\n");
				break;
			case 2: ListaEspera(turnos, mascotas, N_turnos, N_mascota, usuario.matricula);  break;
			case 3: Atender(turnos, mascotas, N_turnos, N_mascota, usuario.matricula);      break;
			default: break;
		}
		system("pause");
		opcion = Menu();
	}
	if (N > 0) {
		rewind(veterinario);
		if (veterinario == NULL) {
			veterinario = fopen("Veterinarios.dat", "w+b");
			if (veterinario == NULL) {
				printf("Error al crear el archivo 'Veterinarios.dat'.\nTerminando programa.\n");
				exit(1);
			}
		}
		for (int i = 0; i < N; i++) fwrite(&veterinarios[i], sizeof(Veterinario), 1, veterinario);
	}
	if (N_turnos > 0) {
		rewind(turno);
		for (int i = 0; i < N_turnos; i++) fwrite(&turnos[i], sizeof(Turno), 1, turno);
	}
  fclose(veterinario);
  fclose(mascota);
  fclose(turno);
	return 0;
}

int Menu() {
	int opcion;
	do {
		system ("cls");
		printf ("Modulo Consultorio Veterinario\n=========================\n1.- Iniciar Sesi%cn\n2.- Visualizar Lista de Espera de Turnos (informe)\n3.- Registrar Evoluci%cn de la Mascota\n4.- Cerrar la aplicaci%cn.\n\nIngrese una opci%cn:\t", 162, 162, 162, 162);
		scanf("%d", &opcion);	
	} while (opcion < 0 || opcion > 4);
	return (opcion);
}

void IniciarSesion(Veterinario veterinarios[], int N, Veterinario &usuario) {
	int check, i = -1;

	do {
		check = 0;
		// Leer datos del usuario
		printf ("Introduce la matr%ccula:\t", 161);
		scanf("%d", &usuario.matricula);
		printf("\nIntroduce la Contrase%ca (DNI):\t", 164);
		scanf("%d", &usuario.dni);
		// comparar con los del archivo
		for(i=0; i < N; i++) {
			if(usuario.matricula == veterinarios[i].matricula) {
				check = 1;
				if(usuario.dni == veterinarios[i].dni) {
					strcpy(usuario.apellido_nombre, veterinarios[i].apellido_nombre);
					strcpy(usuario.telefono, veterinarios[i].telefono);
					check = 2;
					i = N;
				}
			}
		}
    system("cls");
		switch(check) {
			case 0:	printf("Usuario inexistente. Vuelva a intentarlo\n"); system("pause");	system("cls");	break;
			case 1:	printf("Contrase%ca Incorrecta. Vuelva a intentarlo\n", 164);   system("pause");	system("cls");	break;
			case 2:	printf("Inicio de sesi%cn exitoso\n", 162);                     break;
		}
	} while (check != 2);
}

void ListaEspera(Turno turnos[], Mascota mascotas[], int N, int N_mascota, int matricula) {
  if (matricula == 0) printf("Primero debe iniciar sesi%cn\n", 162);
  else {
    if (N < 1) printf("No hay turnos registrados.\n");
    else {
      printf("Lista de espera para el veterinario %d\n\n", matricula);
      for (int i = 0; i < N; i++)
        if (!turnos[i].atendido && turnos[i].matricula_veterinario == matricula) {
          Mascota aux;
          for (int j = 0; j < N_mascota; j++)
            if (mascotas[j].dni_dueno == turnos[i].dni_dueno) {
              aux = mascotas[j];
              j = N_mascota;
            }
          printf("Fecha: %d/%d/%d\nNombre y apellido: %s\nDni due%co: %d\nLocalidad: %s\nEdad: %d\nPeso: %d\n", turnos[i].fecha.dia, turnos[i].fecha.mes, turnos[i].fecha.ano, aux.nombre, aux.dni_dueno, aux.localidad, calcularEdad(aux.nacimiento), aux.peso);
        }
    }
  }
}

void Atender(Turno turnos[], Mascota mascotas[], int N, int N_mascota, int matricula) {
  if (matricula == 0) printf("Primero debe iniciar sesi%cn\n", 162);
  else {
    if (N < 1) printf("No hay turnos registrados.\n");
    else for (int i = 0; i < N; i++)
      if (!turnos[i].atendido && turnos[i].matricula_veterinario == matricula) {
        Mascota mascota;
        for (int j = 0; j < N_mascota; j++)
          if (mascotas[j].dni_dueno == turnos[i].dni_dueno) {
            mascota = mascotas[j];
            j = N_mascota;
          }
        turnos[i].atendido = true;
        _flushall();
        printf("Atendiendo a: %s\nDni due%co: %d\nEdad: %d\nPeso: %d\nDetalle: ", mascota.nombre, mascota.dni_dueno, calcularEdad(mascota.nacimiento), mascota.peso);
        gets(turnos[i].detalle);
        i = N;
      }
  }
}
