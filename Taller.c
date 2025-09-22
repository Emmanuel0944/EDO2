#include <stdio.h>
#define TOTAL 8

typedef struct {
    int codigo;
    float nota;
} Estudiante;

/* Datos predefinidos */
Estudiante alumnos[TOTAL] = {
    {2024101, 4.5},
    {2024102, 3.2},
    {2024105, 4.9},
    {2024103, 2.8},
    {2024106, 3.7},
    {2024104, 5.0},
    {2024108, 4.1},
    {2024107, 3.9}
};

/* ---------- FUNCIONES RECURSIVAS ---------- */

/* 1. Nota máxima */
float maxCalificacion(const Estudiante *grupo, int tam) {
    if (tam == 1) {
        return grupo[0].nota;
    }
    float mayorPrevio = maxCalificacion(grupo, tam - 1);
    return (grupo[tam - 1].nota > mayorPrevio) ? grupo[tam - 1].nota : mayorPrevio;
}

/* 2. Suma de notas */
float sumaCalificaciones(const Estudiante *grupo, int pos, int tam) {
    if (pos >= tam) {
        return 0.0f;
    }
    return grupo[pos].nota + sumaCalificaciones(grupo, pos + 1, tam);
}

/* 3. Selection Sort recursivo por código */

/* Encontrar índice del mínimo entre inicio..fin */
int indiceMinimo(const Estudiante *arr, int inicio, int fin) {
    if (inicio == fin) {
        return inicio;
    }
    int idxRestante = indiceMinimo(arr, inicio + 1, fin);
    return (arr[inicio].codigo < arr[idxRestante].codigo) ? inicio : idxRestante;
}

/* Intercambio */
void cambiar(Estudiante *uno, Estudiante *dos) {
    Estudiante temp = *uno;
    *uno = *dos;
    *dos = temp;
}

/* Selection Sort recursivo */
void ordenarPorCodigo(Estudiante *arr, int inicio, int tam) {
    if (inicio >= tam - 1) {
        return; // caso base
    }
    int idxMin = indiceMinimo(arr, inicio, tam - 1);
    if (idxMin != inicio) {
        cambiar(&arr[inicio], &arr[idxMin]);
    }
    ordenarPorCodigo(arr, inicio + 1, tam);
}

/* ---------- FUNCIONES AUXILIARES ---------- */

void mostrarLista(const Estudiante *arr, int cantidad) {
    printf("\nLista de estudiantes:\n");
    for (int j = 0; j < cantidad; j++) {
        printf("Codigo: %d  |  Nota: %.2f\n", arr[j].codigo, arr[j].nota);
    }
}

/* ---------- MAIN ---------- */
int main() {
    int opcion;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Nota maxima (recursivo)\n");
        printf("2. Promedio del curso (recursivo)\n");
        printf("3. Ordenar por codigo (Selection Sort recursivo)\n");
        printf("4. Mostrar lista\n");
        printf("0. Salir\n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                float maximo = maxCalificacion(alumnos, TOTAL);
                printf("Nota maxima: %.2f\n", maximo);
                break;
            }
            case 2: {
                float totalNotas = sumaCalificaciones(alumnos, 0, TOTAL);
                float promedio = totalNotas / TOTAL;
                printf("Promedio del curso: %.2f\n", promedio);
                break;
            }
            case 3: {
                ordenarPorCodigo(alumnos, 0, TOTAL);
                printf("Lista ordenada por codigo.\n");
                mostrarLista(alumnos, TOTAL);
                break;
            }
            case 4:
                mostrarLista(alumnos, TOTAL);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
