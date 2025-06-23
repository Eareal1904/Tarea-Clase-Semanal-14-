#include <stdio.h>

#define TIENDAS 5
#define DIAS 7

void menu();
printf("=== MENU DE OPCIONES ===");
printf("1. Ingresar ventas.\n2. Ver totales por tienda.\n3. Ver totales por día.");
printf("\n4. Ver tienda y día con mayores ventas.\n5. Salir del programa.");
return menu;

int main() {
	int ventas[TIENDAS][DIAS];
	int totalPorTienda[TIENDAS] = {0};
	int totalPorDia[DIAS] = {0};
	int i, j;
	
	menu();
	
	// Entrada de datos
	printf("Ingrese las ventas de cada tienda por cada día:\n");
	for (i = 0; i < TIENDAS; i++) {
		printf("Tienda %d:\n", i + 1);
		for (j = 0; j < DIAS; j++) {
			printf("Día %d: ", j + 1);
			scanf("%d", &ventas[i][j]);
		}
	}
	
	// Cálculo de totales por tienda y por día
	for (i = 0; i < TIENDAS; i++) {
		for (j = 0; j < DIAS; j++) {
			totalPorTienda[i] += ventas[i][j];
			totalPorDia[j] += ventas[i][j];
		}
	}
	
	// Determinar la tienda con mayores ventas
	int maxVentasTienda = 0, tiendaMayor = 0;
	for (i = 0; i < TIENDAS; i++) {
		if (totalPorTienda[i] > maxVentasTienda) {
			maxVentasTienda = totalPorTienda[i];
			tiendaMayor = i;
		}
	}
	
	// Determinar el día con mayores ventas
	int maxVentasDia = 0, diaMayor = 0;
	for (j = 0; j < DIAS; j++) {
		if (totalPorDia[j] > maxVentasDia) {
			maxVentasDia = totalPorDia[j];
			diaMayor = j;
		}
	}
	
	// Salida de resultados
	printf("\nVentas totales por tienda:\n");
	for (i = 0; i < TIENDAS; i++) {
		printf("Tienda %d: %d\n", i + 1, totalPorTienda[i]);
	}
	
	printf("\nVentas totales por día:\n");
	for (j = 0; j < DIAS; j++) {
		printf("Día %d: %d\n", j + 1, totalPorDia[j]);
	}
	
	printf("\nLa tienda con mayores ventas es: Tienda %d con %d ventas.\n", tiendaMayor + 1, maxVentasTienda);
	printf("El día con mayores ventas es: Día %d con %d ventas.\n", diaMayor + 1, maxVentasDia);
	
	return 0;
}
