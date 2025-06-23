#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TIENDA 100
#define MAX_DIA 100

int leerEnteroSeguro(const char* mensaje) {
    int valor;
    char entrada[100];
    while (1) {
        printf("%s", mensaje);
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            if (sscanf(entrada, "%d", &valor) == 1 && valor >= 0) break;
        }
        printf("Entrada invalida. Intente de nuevo.\n");
    }
    return valor;
}

float leerFlotanteSeguro(const char* mensaje) {
    float valor;
    char entrada[100];
    while (1) {
        printf("%s", mensaje);
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            if (sscanf(entrada, "%f", &valor) == 1 && valor >= 0) break;
        }
        printf("Entrada invalida. Intente de nuevo.\n");
    }
    return valor;
}

void leerCadenaSeguro(const char* mensaje, char* destino, int tam) {
    char buffer[100];
    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%s", destino) == 1) break;
        }
        printf("Entrada invalida. Intente de nuevo.\n");
    }
}

int main() {
    int tiendas = leerEnteroSeguro("Ingrese el numero de tiendas: ");
    int dias = leerEnteroSeguro("Ingrese el numero de dias: ");

    char nombresTiendas[MAX_TIENDA][50];
    char nombresDias[MAX_DIA][50];
    float descuentos[MAX_TIENDA];
    int ventas[MAX_TIENDA][MAX_DIA];
    int totalPorTienda[MAX_TIENDA] = {0};
    int totalPorDia[MAX_DIA] = {0};

    for (int i = 0; i < tiendas; i++) {
        char mensaje[100];
        sprintf(mensaje, "Ingrese el nombre de la tienda %d: ", i + 1);
        leerCadenaSeguro(mensaje, nombresTiendas[i], 50);
        sprintf(mensaje, "Ingrese el descuento para %s (en %%): ", nombresTiendas[i]);
        descuentos[i] = leerFlotanteSeguro(mensaje);
    }

    for (int j = 0; j < dias; j++) {
        char mensaje[100];
        sprintf(mensaje, "Ingrese el nombre del dia %d: ", j + 1);
        leerCadenaSeguro(mensaje, nombresDias[j], 50);
    }

    int opcion;
    FILE *archivo;

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar ventas\n");
        printf("2. Ver totales por tienda\n");
        printf("3. Ver totales por dia\n");
        printf("4. Ver tienda y dia con mayores y menores ventas\n");
        printf("5. Ver promedios y graficos\n");
        printf("6. Exportar resultados\n");
        printf("7. Salir\n");
        opcion = leerEnteroSeguro("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                for (int i = 0; i < tiendas; i++) {
                    printf("Ventas de %s:\n", nombresTiendas[i]);
                    for (int j = 0; j < dias; j++) {
                        char mensaje[100];
                        sprintf(mensaje, "%s: ", nombresDias[j]);
                        ventas[i][j] = leerEnteroSeguro(mensaje);
                        totalPorTienda[i] += ventas[i][j];
                        totalPorDia[j] += ventas[i][j];
                    }
                }
                break;

            case 2:
                printf("\nTotales por tienda (con descuento aplicado):\n");
                for (int i = 0; i < tiendas; i++) {
                    float totalConDescuento = totalPorTienda[i] * (1 - descuentos[i] / 100);
                    printf("%s: %d (Total con descuento: %.2f)\n", nombresTiendas[i], totalPorTienda[i], totalConDescuento);
                }
                break;

            case 3:
                printf("\nTotales por dia:\n");
                for (int j = 0; j < dias; j++) {
                    printf("%s: %d\n", nombresDias[j], totalPorDia[j]);
                }
                break;

            case 4: {
                int maxTienda = 0, minTienda = 0, maxDia = 0, minDia = 0;
                for (int i = 1; i < tiendas; i++) {
                    if (totalPorTienda[i] > totalPorTienda[maxTienda]) maxTienda = i;
                    if (totalPorTienda[i] < totalPorTienda[minTienda]) minTienda = i;
                }
                for (int j = 1; j < dias; j++) {
                    if (totalPorDia[j] > totalPorDia[maxDia]) maxDia = j;
                    if (totalPorDia[j] < totalPorDia[minDia]) minDia = j;
                }
                printf("\nTienda con mayores ventas: %s (%d)\n", nombresTiendas[maxTienda], totalPorTienda[maxTienda]);
                printf("Tienda con menores ventas: %s (%d)\n", nombresTiendas[minTienda], totalPorTienda[minTienda]);
                printf("Dia con mayores ventas: %s (%d)\n", nombresDias[maxDia], totalPorDia[maxDia]);
                printf("Dia con menores ventas: %s (%d)\n", nombresDias[minDia], totalPorDia[minDia]);
                break;
            }

            case 5:
                printf("\nPromedios y Graficos:\n");
                for (int i = 0; i < tiendas; i++) {
                    float promedio = (float)totalPorTienda[i] / dias;
                    printf("%s: Promedio = %.2f\tGrafico: ", nombresTiendas[i], promedio);
                    for (int k = 0; k < promedio / 10; k++) printf("*");
                    printf("\n");
                }
                for (int j = 0; j < dias; j++) {
                    float promedio = (float)totalPorDia[j] / tiendas;
                    printf("%s: Promedio = %.2f\tGrafico: ", nombresDias[j], promedio);
                    for (int k = 0; k < promedio / 10; k++) printf("*");
                    printf("\n");
                }
                break;

            case 6:
                archivo = fopen("resultados.txt", "w");
                fprintf(archivo, "Totales por tienda (con descuento aplicado):\n");
                for (int i = 0; i < tiendas; i++) {
                    float totalConDescuento = totalPorTienda[i] * (1 - descuentos[i] / 100);
                    fprintf(archivo, "%s: %d (Total con descuento: %.2f)\n", nombresTiendas[i], totalPorTienda[i], totalConDescuento);
                }
                fprintf(archivo, "\nTotales por dia:\n");
                for (int j = 0; j < dias; j++) {
                    fprintf(archivo, "%s: %d\n", nombresDias[j], totalPorDia[j]);
                }
                fclose(archivo);
                printf("Resultados exportados a resultados.txt\n");
                break;

            case 7:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    return 0;
}
