#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TAM_INICIAL 10
#define CRIT_AGRANDAR 3
#define CRIT_ACHICAR 2
#define FACTOR_CARGA_AMPLIACION 2
#define FACTOR_CARGA_REDUCCION 4

struct heap {
	void** datos;
	size_t cant;
	size_t tam;
	cmp_function_t cmp;
};

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;

    void** datos = malloc(TAM_INICIAL * sizeof(void*));
    if (!datos){
        free(heap);
        return NULL;
    }

    heap->cant = 0;
    heap->tam = TAM_INICIAL;

    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);
void heap_destruir(heap_t *heap, void destruir_elemento(void *e));

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}
bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

bool heap_encolar(heap_t *heap, void *elem);

void *heap_ver_max(const heap_t *heap){
    if heap_esta_vacio(heap) return NULL;
    return heap->datos[0];
}

void *heap_desencolar(heap_t *heap);

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);