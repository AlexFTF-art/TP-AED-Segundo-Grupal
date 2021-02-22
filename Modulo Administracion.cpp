/*La gerencia del centro veterinario es la encargada de realizar el alta de los veterinarios que trabajan
en la instituci�n, as� como tambi�n de los empleados que realizan la registraci�n de los turnos y mascotas.
Es el �rea encargada desea visualizar las atenciones realizadas por los profesionales seg�n el mes.
Para incentivar a los veterinarios, la gerencia otorga un bono mensual al profesional que haya
registrado la mayor cantidad de turnos en ese periodo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Types.h"

int Menu();
void RegistrarVeterinario (Veterinario veterinarios[], int &N);
void RegistrarAsistente (Usuario usuarios[], int &N);
void ListarAtenciones (Turno turnos[], int N, int N_turnos);
void Ranking (Turno turnos[], int N, int N_turnos);

int main() {
	int N = 0, N_usuarios = 0, N_turnos = 0, opcion = Menu();
	FILE *veterinario, *usuario, *turno;
	Veterinario veterinarios[50];
	Usuario usuarios[50];
	Turno turnos[50];

	veterinario = fopen ("Veterinarios.dat", "r+b");
	if (veterinario != NULL) {
		do {				
			fread(&veterinarios[N], sizeof(Veterinario), 1, veterinario);
			N++;
		} while(!feof(veterinario));
	}

	usuario = fopen ("Usuarios.dat", "r+b");
	if (usuario != NULL) {
		do {				
			fread(&usuarios[N_usuarios], sizeof(Usuario), 1, usuario);
			N_usuarios++;
		} while(!feof(usuario));
	}

	turno = fopen("Turnos.dat", "r+b");
	if (turno != NULL) {
		do {
			fread(&turnos[N_turnos], sizeof(Turno), 1, turno);
			N_turnos++;
		} while(!feof(turno));
	}


	while(opcion != 5) {
		system("cls");
		switch (opcion){
			case 1: RegistrarVeterinario(veterinarios, N);		break;
			case 2: RegistrarAsistente(usuarios, N_usuarios);	break;
			case 3: ListarAtenciones(turnos, N, N_turnos);		break;
			case 4: Ranking(turnos, N, N_turnos); 						break;
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
	fclose(veterinario);
	if (N_usuarios > 0) {
		rewind(usuario);
		if (usuario == NULL) {
			usuario = fopen("Usuarios.dat", "w+b");
			if (usuario == NULL) {
				printf("Error al crear el archivo 'Usuarios.dat'.\nTerminando programa.\n");
				exit(1);
			}
		}
		for (int i = 0; i < N_usuarios; i++) fwrite(&usuarios[i], sizeof(Usuario), 1, usuario);
	}
	fclose(usuario);
	return 0;
}

int Menu() {
	int opcion;
	do {
		system ("cls");
		printf ("Modulo del Administraci%cn\n=========================\n 1.- Registrar Veterinario\n 2.- Registrar Usuario Asistente\n 3.- Atenciones por Veterinarios\n 4.- Ranking de Veterinarios por Atenciones\n 5.- Salir de la Aplicaci%cn.\n\nElige una Opcion:\t", 162, 162);
		scanf("%d", &opcion);	
	} while (opcion < 0 || opcion > 5);
	return (opcion);
}

void RegistrarVeterinario (Veterinario veterinarios[], int &N) {
	Veterinario veterinario;

	_flushall();
	printf ("Ingrese el Apellido y Nombre del Veterinario: ");
	gets(veterinario.apellido_nombre);
	printf("\nIngrese el DNI del Veterinario: ");
	scanf("%d", &veterinario.dni);
	printf ("\nIngrese su Numero de Matricula: ");
	scanf("%d", &veterinario.matricula);
	_flushall();
	printf("\nIngrese el Telefono del Veterinario: ");
	gets(veterinario.telefono);
	veterinarios[N] = veterinario;
	N++;
	system("cls");
	printf("Veterinario registrado exitosamente.\nVolviendo al Men%c principal.\n", 163);
}

void RegistrarAsistente (Usuario usuarios[], int &N) {
	Usuario user;
	char aux[50], aux1[50];
	int check = 0, minus = 0, mayus = 0, digit = 0, i, letras, temp, respuesta = 0;
	_flushall();
	do {
		printf("Bienvenido al Sistema de Creaci%cn de Cuentas\n--------------------------------------------", 162);
		printf("\nIngrese un Nombre de Usuario que debe: \n-\tTener entre 6 y 10 caracteres\n-\tIniciar con min%cscula", 163);
		printf("\n-\tTener al menos 2 may%csculas\n-\tTener como m%cximo 3 d%cgitos\n\n", 163, 160, 161);
		gets(user.usuario);
		for(i = 0; i < N; i++) if(strcmp(user.usuario, usuarios[i].usuario)) check=1;
		letras = strlen(user.usuario);
		if(check == 0) {
			if(letras < 11 && letras > 5) {
				if(user.usuario[0]>96 && isalpha(user.usuario[0])) {
					for(i=1; i < letras; i++) {
						if(isalpha(user.usuario[i]) && user.usuario[i]<91) mayus++;
						else {
							if(isdigit(user.usuario[i])) digit++;
							else if(!isalpha(user.usuario[i]) && user.usuario[i]!=33 && user.usuario[i]!=45 && user.usuario[i]!=47 && user.usuario[i]!=42 && user.usuario[i]!=43 && user.usuario[i]!=63 && user.usuario[i]!=168 && user.usuario[i]!=173) {
								check = 5;
								i = letras;
							}
						}
					}
					if(mayus<2 || digit>3) check=4;	
				} else check=3;
			} else check=2;
		}
		if(check!=0) {
			printf("\nEl nombre de usuario Ingresado no es v%clido. Vuelva a intentarlo", 160);
			switch(check) {
				case 1:	printf("\nC%cdigo de error %d:\tEl nombre de usuario ya est%c en uso\n", 162, check, 160);	break;
				case 2:	printf("\nC%cdigo de error %d:\tEl nombre de usuario posee una cantidad no permitida de caracteres\n", 162, check);	break;
				case 3:	printf("\nC%cdigo de error %d:\tEl nombre de usuario debe iniciar con una letra min%cscula\n", 162, check, 163);	break;
				case 4:	printf("\nC%cdigo de error %d:\tEl nombre de usuario posee menos may%csculas y/o m%cs d%cgitos de los requeridos\n", 162, check, 163, 160, 161);	break;
				case 5:	printf("\nC%cdigo de error %d:\tEl nombre de usuario contiene caracteres no permitidos\n", 162, check);	break;
			}
			system("pause");
		}
		system("cls");
	} while(check!=0);
	do {
		printf("Sistema de Creaci%cn de Cuentas\n-------------------------------", 162);
		printf("\nUsuario:\t%s\n", user.usuario);
		check=0;	minus=0;	mayus=0; digit=0;
		printf("\nIngrese una contrase%ca. Requisitos: \n-\tTener entre 6 y 32 caracteres\n-\tTener al menos una min%cscula, una may%cscula y un d%cgito", 164, 163, 163, 161);
		printf("\n-\tNo contener caracteres de puntuaci%cn\n-\tTener como m%cximo 3 d%cgitos consecutivos\n-\tNo contener 2 letras alfab%cticamente consecutivas\n\n", 162, 160, 161, 130);
		gets(user.contrasena);
		letras=strlen(user.contrasena);
		if(letras>5 && letras<33) {
			strcpy(aux, user.contrasena);
			strupr(aux);
			for(i=0; i<letras; i++) {
				if(isalpha(user.contrasena[i])) {
					if(user.contrasena[i]<91) mayus+=2;
					else minus+=2;
				}	else {
					if(isdigit(user.contrasena[i])) {
						digit += 2;
						if(i > 1) {
							int a, b, c;
							a=user.contrasena[i-2];
							b=user.contrasena[i-1];
							c=user.contrasena[i];
							if((a-b==1 && b-c==1)||(a-b==-1 && b-c==-1)) check=3;
						}
					}	else check=5;
				}
				if(i>0 && aux[i-1]<91 && aux[i-1]>64 && aux[i]<91 && aux[i]>64) {
					int a = aux[i-1], b = aux[i];
					if(abs(a-b)==1) check=4;	
				}
				if(check!=0) i=letras;	
			}
			if(digit==0 || minus==0 || mayus==0) check=2;	
		} else check=1;							
		if(check!=0) {
			printf("\nLa Contrase%ca Ingresada no es v%clida. Vuelva a intentarlo", 164, 160);
			switch(check) {
				case 1:	printf("\nC%cdigo de error %d:\tLa Contrase%ca posee una cantidad no permitida de caracteres\n", 162, check, 164);	break;
				case 2:	printf("\nC%cdigo de error %d:\tLa Contrase%ca debe contener al menos una min%cscula, una may%cscula y un d%cgito\n", 162, check, 164, 163, 163, 161);	break;
				case 3:	printf("\nC%cdigo de error %d:\tLa Contrase%ca contiene 3 d%cgitos sucesivos\n", 162, check, 164, 161);	break;
				case 4:	printf("\nC%cdigo de error %d:\tLa Contrase%ca posee 2 letras sucesivas\n", 162, check, 164);	break;
				case 5:	printf("\nC%cdigo de error %d:\tLa Contrase%ca contiene caracteres no permitidos\n", 162, check, 164);	break;
			}
			system("pause");	system("cls");
		}
	} while(check!=0);
	system("cls");
	printf("Sistema de Creaci%cn de Cuentas\n-------------------------------", 162);
	printf("\nUsuario:\t%s\n", user.usuario);
	printf ("Ingrese el nombre y apellido: ");
	gets(user.apellido_nombre);
	usuarios[N] = user;
	N++;
	system("cls");
	printf("Usuario asistente registrado exitosamente.\nVolviendo al Men%c principal.\n", 163);
}

void ListarAtenciones (Turno turnos[], int N, int N_turnos) {
	Turno resultado[N][N_turnos];
	if (N_turnos < 1) printf("No se encontraron atenciones registradas.\n");
	else {
		int atenciones[N], veterinarios = 0, mes, ano;
		printf("Ingrese el mes del cual desea conocer el ranking:\t");
		scanf("%d", &mes);
		printf("Ingrese el a%co del cual desea conocer el ranking:\t", 164);
		scanf("%d", &ano);
		for (int i = 0; i < N; i++) atenciones[i] = 0;
		for (int i = 0; i < N_turnos; i++) {
			if (turnos[i].fecha.mes == mes && turnos[i].fecha.ano == ano && turnos[i].atendido) {
				int indice_veterinario = -1;
				for (int j = 0; j < veterinarios; j++) if (turnos[i].matricula_veterinario == resultado[0][0].matricula_veterinario) indice_veterinario = j;
				if (indice_veterinario > -1) {
					resultado[indice_veterinario][atenciones[indice_veterinario]] = turnos[i];
					atenciones[indice_veterinario]++;
				} else {
					resultado[veterinarios][0] = turnos[i];
					veterinarios++;
				}
			}
		}
		for (int i = 0; i < veterinarios; i++) {
			printf("Veterinario: %d\n\n", resultado[i][0].matricula_veterinario);
			for (int j = 0; j < atenciones[i]; i++) {
				printf("Turno:\t\t%d/%d/%d\n", resultado[i][j].fecha.dia, resultado[i][j].fecha.mes, resultado[i][j].fecha.ano);
				printf("DNI due%co:\t%d\n", 163, resultado[i][j].dni_dueno);
				printf("Detalle:\t%s\n---------------------------------\n", resultado[i][j].detalle);
			}
			printf("\n\n==================================================\n\n");
		}
	}
}

void Ranking (Turno turnos[], int N, int N_turnos) {
	if (N < 1) printf("No se encontraron atenciones registradas.\n");
	else {
		int rank[N][N_turnos], veterinarios = 0, mes;
		printf("Ingrese el mes del cual desea conocer el ranking:\t");
		scanf("%d", &mes);
		for (int i = 0; i < N_turnos; i++) {
			if (turnos[i].fecha.mes == mes) {
				bool b = false;
				for (int j = 0; j < veterinarios; j++)
					if (rank[j][0] == turnos[i].matricula_veterinario) {
						rank[j][1]++;
						b = true;
						j = veterinarios;
					}
				if (!b) {
					rank[veterinarios][0] = turnos[i].matricula_veterinario;
					rank[veterinarios][1] = 1;
					veterinarios++;
				}
			}
		}
		int indice = 0;
		for (int i = 1; i < veterinarios; i++) if (rank[i][1] > rank[i][1]) indice = i;
		printf("El veterinario con la mayor cantidad de atenciones fue %d, con un total de %d.\n\n", rank[indice][0], rank[indice][1]);
	}
}
