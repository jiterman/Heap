#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TAM_INICIAL 10
#define CRIT_ACHICAR 4
#define FACTOR_AMPLIACION_PILA 2
#define FACTOR_REDUCCION_PILA 2

struct heap {
	void** datos;
	size_t cant;
	size_t tam;
	cmp_func_t cmp;
};

void swap (void **x, void **y) {
    void* valor_aux = *x;
    *x = *y;
    *y = valor_aux;
}

void upheap(void** arreglo, size_t pos, cmp_func_t cmp){
	if (pos == 0) return;
	padre = (pos-1) / 2;
	if (cmp(arreglo[padre], arreglo[pos]) < 0) 
		swap(arreglo[pos], arreglo[pos]);
		upheap(arreglo, padre, cmp);
}

void downheap(void** arreglo, size_t tam, size_t pos, cmp_func_t cmp)
	if (pos >= tam) return;
	min = pos; // PADRE
	izq = (2 * pos) + 1;
	der = (2 * pos) + 2;
	if (izq < tam && cmp(arreglo[izq], arreglo[min]) > 0) min = izq;
	if (der < tam && cmp(arreglo[der], arreglo[min]) > 0) min = der;
	if (min != pos)
		swap(arreglo[pos], arreglo[min]);
		downheap(arreglo, tam, min, cmp);
}

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

bool heap_redimensionar(heap_t *heap, size_t nuevo_tam){
    void* datos_nuevo = realloc(heap->datos, nuevo_tam * sizeof(void*));

    if (!datos_nuevo) return false;

    heap->datos = datos_nuevo;
    heap->tam = nuevo_tam;
    return true;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
    if (destruir_elemento) while (!heap_esta_vacio(heap)) destruir_elemento(heap_desencolar(heap));
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}
bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

bool heap_encolar(heap_t *heap, void *elem);

void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

void *heap_desencolar(heap_t *heap);

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    //hago heapify
    heap_t* heap = heap_crear_arr(elementos, cant, cmp);

}