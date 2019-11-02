#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TAM_INICIAL 10
#define CRIT_ACHICAR 4
#define FACTOR_AMP_HEAP 2
#define FACTOR_REDUC_HEAP 2

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
	size_t padre = (pos-1) / 2;
	if (cmp(arreglo[padre], arreglo[pos]) < 0){
		swap(arreglo[pos], arreglo[pos]);
		upheap(arreglo, padre, cmp);
    }
}

void downheap(void** arreglo, size_t tam, size_t pos, cmp_func_t cmp){
	if (pos >= tam) return;
	size_t min = pos; // Posición del padre
	size_t izq = (2 * pos) + 1;
	size_t der = (2 * pos) + 2;
	if (izq < tam && cmp(arreglo[izq], arreglo[min]) > 0) min = izq;
	if (der < tam && cmp(arreglo[der], arreglo[min]) > 0) min = der;
	if (min != pos){
		swap(arreglo[pos], arreglo[min]);
		downheap(arreglo, tam, min, cmp);
    }
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
    heap->cmp = cmp;

    return heap;
}

bool heap_redimensionar(heap_t *heap, size_t nuevo_tam){
    void* datos_nuevo = realloc(heap->datos, nuevo_tam * sizeof(void*));

    if (!datos_nuevo) return false;

    heap->datos = datos_nuevo;
    heap->tam = nuevo_tam;
    return true;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = heap_crear(cmp);
    if (!heap) return NULL;

    for (int i = 0; i < n; i++) {
        if (!heap_encolar(heap, arreglo[i])) {
            heap_destruir(heap, NULL);
            return NULL;
        }
    }

    return heap;
}

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

bool heap_encolar(heap_t *heap, void *elem){
    if (!heap) return false;
    if (heap->cant == heap->tam && !heap_redimensionar(heap, heap->tam++)) return false;
    heap->cant++;
    heap->datos[heap->cant] = elem;
    upheap(heap->datos,heap->cant,heap->cmp); 
    return true;
}

void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    void* valor = heap->datos[0];

    swap(heap->datos[0], heap->datos[heap->cant - 1]);
    heap->cant -= 1;

    downheap(heap->datos, heap->cant, 0, heap->cmp);

    heap->cant -= 1;
    if (heap->cant <= (heap->tam/CRIT_ACHICAR) && heap->tam > TAM_INICIAL) heap_redimensionar(heap, heap->tam/FACTOR_REDUC_HEAP);

    return valor;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    //hago heapify
    if (cant == 1 || cant == 0) return;
    heap_t* heap = heap_crear_arr(elementos, cant, cmp);
    swap(elementos[0], elementos[cant]);
    cant--;
    downheap(elementos, cant, 0, cmp);
    heap_sort(elementos, cant, cmp);
}