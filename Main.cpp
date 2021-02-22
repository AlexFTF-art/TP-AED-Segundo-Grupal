#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"
#include "Modulo Administracion.h"
#include "Modulo Consultorio.h"
#include "Modulo Recepcion.h"

int MainMenu();

int main() {
  int opcion = MainMenu();
  
	while(opcion != 4) {
		system("cls");
		switch (opcion) {
			case 1: Administracion(); break;
			case 2: Recepcion();      break;
			case 3: Consultorio();    break;
			default: break;
		}
		system("pause");
		opcion = MainMenu();
	}
  system("cls");
  printf("Saliendo. . .\n");
  system("pause");
  return 0;
}


int MainMenu() {
	int opcion;
	do {
		system ("cls");
		printf ("Gestor Veterinario\n=========================\n1.- M%cdulo Administraci%cn\n2.- M%cdulo Recepci%cn\n3.- M%cdulo Consultorio\n4.- Cerrar la aplicaci%cn.\n\nIngrese una opci%cn:\t", 162, 162, 162, 162, 162, 162, 162);
		scanf("%d", &opcion);	
	} while (opcion < 0 || opcion > 4);
	return (opcion);
}
