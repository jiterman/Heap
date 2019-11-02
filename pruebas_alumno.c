#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

int comp_nros(const void* num1, const void* num2){
    if (*(int*)num1 > *(int*)num2) return 1;
    if (*(int*)num1 < *(int*)num2) return -1;
    else return 0;    
}

void pruebas_heap_vacio() {
    printf("\nINICIO DE PRUEBAS CON HEAP VACÍO\n");

    /* Declaro las variables a utilizar*/
    heap_t* heap = heap_crear(comp_nros);

    /* Inicio de pruebas */
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Ver primero es inválido", !heap_ver_max(heap));
    print_test("Desencolar es inválido", !heap_desencolar(heap));

    /* Destruyo el heap*/
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}

void pruebas_algunos_elementos(){
    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    /* Declaro las variables a utilizar*/
    heap_t* heap = heap_crear(comp_nros);
    int var1 = 5;
    int var2 = -10;
    int var3 = 0;

    /* Inicio de pruebas encolando todos los elementos */
    print_test("Se encola 5", heap_encolar(heap, &var1));
    print_test("Se encola -10", heap_encolar(heap, &var2));
    print_test("Se encola 0", heap_encolar(heap, &var3));

    /* Chequeo que el heap no se comporte como vacío */
    print_test("El heap no está vacío", !heap_esta_vacio(heap));

    /*Valido que se mantenga la invariante al desencolar cada elemento */
    print_test("Ver primero es 5", *(int*)heap_ver_max(heap) == 5);
    print_test("Desencolar devuelve 5", *(int*)heap_desencolar(heap) == 5);
    print_test("Ver primero es 0", *(int*)heap_ver_max(heap) == 0);
    print_test("Desencolar devuelve 0", *(int*)heap_desencolar(heap) == 0);
    print_test("Ver primero es -10", *(int*)heap_ver_max(heap) == -10);
    print_test("Desencolar devuelve -10", *(int*)heap_desencolar(heap) == -10);

    /* Chequeo que el heap se comporte como vacío */
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Ver primero es inválido", heap_ver_max(heap) == NULL);
    print_test("Desencolar es inválido", heap_desencolar(heap) == NULL);

    /* Destruyo el heap*/

    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}

void pruebas_de_volumen(int cant_elementos){
    printf("\nINICIO DE PRUEBAS DE VOLUMEN\n");

    /* Declaro las variables a utilizar*/
    heap_t* heap = heap_crear(comp_nros);
    int vector[cant_elementos];

    /* Comienzo a encolar elementos 
    chequeando en cada caso que el primero sea el correcto*/

    bool ok = true;
    bool ok2 = true;

    for (int i = 0; i < cant_elementos+1; i++){
        vector[i] = i;
        // Si algun elemento no se pudo guardar correctamente, ok sera false
        ok &= heap_encolar(heap, &vector[i]);
        ok2 &= (*(int*)heap_ver_max(heap) == vector[i]);
    }

    print_test("Se pudieron encolar todos los elementos", ok);
    print_test("En cada paso el primero era el correcto", ok2);

    /* Comienzo a desencolar elementos hasta que el heap esté vacío
    chequeando en cada caso la invariante y el primero*/

    ok = true;
    int n = cant_elementos;

    while (!heap_esta_vacio(heap)){
        ok &= (*(int*)heap_ver_max(heap) == vector[n]);
        heap_desencolar(heap);
        n--;      
    }

    print_test("En cada caso se cumple la invariante y el primero es el correspondiente", ok);

    heap_destruir(heap, NULL);
    print_test("El heap fue destruido", true);
}

void pruebas_destruir_heap(){
    printf("\nINICIO DE PRUEBAS DESTRUIR HEAP CON ELEMENTOS EN MEMORIA ESTÁTICA\n");

    /* Declaro las variables a utilizar*/
    heap_t* heap = heap_crear(comp_nros);
    int var1 = 5;
    int var2 = 10;

    /* Inicio de pruebas encolando todos los elementos */
    print_test("Se encola 5", heap_encolar(heap, &var1));
    print_test("Se encola 10", heap_encolar(heap, &var2));

    /* Chequeo que el heap no se comporte como vacío */
    print_test("El heap no está vacío", !heap_esta_vacio(heap));

    /* Destruyo el heap */
    heap_destruir(heap, NULL);
    print_test("El heap con elementos en el stack fue destruido", true);

    printf("INICIO DE PRUEBAS DESTRUIR HEAP CON ELEMENTOS QUE SE LIBERAN CON FREE\n");

    /* Declaro las variables a utilizar*/
    heap = heap_crear(comp_nros);
    int* a = malloc(sizeof(int)); *a = 10;
    int* b = malloc(sizeof(int)); *b = 4;

    /* Inicio de pruebas encolando todos los elementos */
    print_test("Se encola variable a", heap_encolar(heap, a));
    print_test("Se encola variable b", heap_encolar(heap, b));

    /* Destruyo el heap */
    heap_destruir(heap, free);
    print_test("El heap con elementos en memoria denámica fue destruido", true);

    printf("INICIO DE PRUEBAS DESTRUIR HEAP CON ELEM EN MEMORIA DINÁMICA DESENCOLADOS\n");
    
    /* Declaro las variables a utilizar*/
    heap = heap_crear(comp_nros);
    int* c = malloc(sizeof(int)); *c = 0;

    /* Inicio de pruebas encolando todos los elementos */
    print_test("Se encola el puntero c (en memoria dinámica)", heap_encolar(heap, c));

    /* Se desencolan los elementos */
    free(heap_desencolar(heap));
    print_test("Se desencoló y liberó el puntero c", true);

    /* Chequeo que el heap se comporte como vacío */
    print_test("El heap está vacío", heap_esta_vacio(heap));

    /* Destruyo la lista */
    heap_destruir(heap, NULL);
    print_test("Se destruyó el heap y sus elementos sin usar una función", true);
}

void pruebas_crear_arr(){
    printf("\nINICIO DE PRUEBAS CREAR HEAP A PARTIR DE ARREGLO\n");

    /* Declaro las variables a utilizar */
    int n_uno = 12, n_dos = 9, n_tres = 2018, n_pri = 1986, n_seg = 1996, n_ter = 2015, n_prox = 2019;
    void *arreglo[7];
    arreglo[0] = &n_uno;
    arreglo[1] = &n_dos;
    arreglo[2] = &n_tres;
    arreglo[3] = &n_pri;
    arreglo[4] = &n_seg;
    arreglo[5] = &n_ter;
    arreglo[6] = &n_prox;
    /* Creo el heap */

    heap_t* heap = heap_crear_arr(arreglo, 7, comp_nros);
    
    /* Reviso que se comporte como esperado */

    print_test("El maximo es el esperado", *(int*)heap_ver_max(heap) == 2019);
    print_test("La cantidad coincide", heap_cantidad(heap) == 7);

    print_test("Heap desencolar es 2019", *(int*)heap_desencolar(heap) == 2019);
    print_test("Heap desencolar es 2018", *(int*)heap_desencolar(heap) == 2018);
    print_test("Heap desencolar es 2015", *(int*)heap_desencolar(heap) == 2015);
    print_test("Heap desencolar es 1996", *(int*)heap_desencolar(heap) == 1996);
    print_test("Heap desencolar es 1986", *(int*)heap_desencolar(heap) == 1986);
    print_test("Heap desencolar es 12", *(int*)heap_desencolar(heap) == 12);

    print_test("El heap no está vacío", !heap_esta_vacio(heap));

    print_test("Heap desencolar es 9", *(int*)heap_desencolar(heap) == 9);

    print_test("El heap está vacío", heap_esta_vacio(heap));
    
    /* Destruyo el heap */

    heap_destruir(heap, NULL);
    print_test("Se destruyó el heap y sus elementos sin usar una función", true);

}

void pruebas_heap_sort(){
    printf("\nINICIO DE PRUEBAS ORDENAR ARREGLO CON HEAPSORT\n");

    /* Declaro las variables a utilizar*/
    int var = 9, var_uno = 81, var_dos = 102, var_tres = 18, var_cua = 0, var_cin = -3;
    void* arreglo[6];
    arreglo[0] = &var;
    arreglo[1] = &var_uno;
    arreglo[2] = &var_dos;
    arreglo[3] = &var_tres;
    arreglo[4] = &var_cua;
    arreglo[5] = &var_cin;
    int arreglo_ordenado[] = {-3,0,9,18,81,102};
    bool todo_ok = true;

    /* Utilizo heapsort*/
    heap_sort(arreglo,6,comp_nros);

    /* Reviso que haya ordenado como esperado*/

    for (int i = 0; i<6; i++){
        if (*(int*)arreglo[i] != arreglo_ordenado[i]) todo_ok = false;
    }
    print_test("El arreglo fue ordenado como se esperaba", todo_ok);
}

void pruebas_heap_alumno() {
    pruebas_heap_vacio();
    pruebas_algunos_elementos();
    pruebas_de_volumen(20);
    pruebas_destruir_heap();
    pruebas_crear_arr();
    pruebas_heap_sort();
}
