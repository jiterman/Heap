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
    print_test("Ver max es inválido", !heap_ver_max(heap));
    print_test("Desencolar es inválido", !heap_desencolar(heap));

    /* Destruyo el heap*/
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido\n", true);
}

void pruebas_encolar_null(){

    printf("INICIO DE PRUEBAS ENCOLANDO NULL\n");

    /* Declaro las variables a utilizar*/
    heap_t* heap = heap_crear(comp_nros);

    /* Inicio de pruebas encolando NULL */
    print_test("Se encola NULL", heap_encolar(heap, NULL));

    /* Chequeo que el heap no se comporte como vacío */
    print_test("El heap no está vacío", !heap_esta_vacio(heap));

    /*Valido que ver max y desencolar devuelvan NULL */
    print_test("Ver max devuelve elem NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar devuelve elem NULL", heap_desencolar(heap) == NULL);

    /* Destruyo el heap*/
    heap_destruir(heap, NULL);
    print_test("El heap fue destruido\n", true);
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

    /*Valido que se mantenga la condición de heap al desencolar cada elemento */
    print_test("Ver max es 5", *(int*)heap_ver_max(heap) == 5);
    print_test("Desencolar devuelve 5", *(int*)heap_desencolar(heap) == 5);
    print_test("Ver max es 0", *(int*)heap_ver_max(heap) == 0);
    print_test("Desencolar devuelve 0", *(int*)heap_desencolar(heap) == 0);
    print_test("Ver max es -10", *(int*)heap_ver_max(heap) == -10);
    print_test("Desencolar devuelve -10", *(int*)heap_desencolar(heap) == -10);

    /* Chequeo que el heap se comporte como vacío */
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Ver max es inválido", heap_ver_max(heap) == NULL);
    print_test("Desencolar es inválido", heap_desencolar(heap) == NULL);

    /* Destruyo el heap*/

    heap_destruir(heap, NULL);
    print_test("El heap fue destruido\n", true);
}

void pruebas_de_volumen(){
    printf("INICIO DE PRUEBAS DE VOLUMEN\n");

    /* Defino la cantidad de elementos que voy a encolar */
    int cant_elementos = 10000;

    /* Declaro las variables a utilizar*/
    heap_t* heap = heap_crear(comp_nros);
    int vector[cant_elementos];

    /* Comienzo a encolar elementos 
    chequeando en cada caso que el max sea el correcto*/

    bool ok = true;
    bool ok2 = true;

    for (int i = 0; i < cant_elementos+1; i++){
        vector[i] = i;
        // Si algun elemento no se pudo guardar correctamente, ok sera false
        ok &= heap_encolar(heap, &vector[i]);
        ok2 &= (*(int*)heap_ver_max(heap) == vector[i]);
    }

    print_test("Se pudieron encolar todos los elementos", ok);
    print_test("En cada paso el max era el correcto", ok2);

    /* Comienzo a desencolar elementos hasta que el heap esté vacío
    chequeando en cada caso la condición de heap y el max*/

    ok = true;
    int n = cant_elementos - 1;

    while (!heap_esta_vacio(heap)){
        ok &= (*(int*)heap_ver_max(heap) == vector[n]);
        heap_desencolar(heap);
        n --;      
    }

    print_test("En cada caso se cumple la condición de heap y el max es el correspondiente", ok);

    heap_destruir(heap, NULL);
    print_test("El heap fue destruido\n", true);
}

void pruebas_destruir_heap(){
    printf("INICIO DE PRUEBAS DESTRUIR HEAP CON ELEMENTOS EN MEMORIA ESTÁTICA\n");

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
    int* a = malloc(sizeof(int)); *a = 5;
    int* b = malloc(sizeof(int)); *b = 10;

    /* Inicio de pruebas encolando todos los elementos */
    print_test("Se encola variable a", heap_encolar(heap, a));
    print_test("Se encola variable b", heap_encolar(heap, b));

    /* Destruyo el heap */
    heap_destruir(heap, free);
    print_test("El heap con elementos en memoria denámica fue destruido", true);

    printf("INICIO DE PRUEBAS DESTRUIR HEAP CON ELEM EN MEMORIA DINÁMICA DESENCOLADOS\n");
    
    /* Declaro las variables a utilizar*/
    heap = heap_crear(comp_nros);
    int* c = malloc(sizeof(int)); *c = 1;

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
    printf("INICIO DE PRUEBAS CREAR HEAP A PARTIR DE ARREGLO\n");

    /* Declaro las variables a utilizar */

    int arreglo[] = {9,12,2018,1986,2015,1996,2019};

    /* Creo el heap */

    heap_t* heap = heap_crear_arr(arreglo, 7, comp_nros);
    
    /* Reviso que se comporte como esperado */

}

void pruebas_heap_sort(){
    printf("INICIO DE PRUEBAS ORDENAR ARREGLO CON HEAPSORT\n");

    /* Declaro las variables a utilizar*/

    int arreglo[] = {9,81,102,18,0,-3};
    int arreglo_ordenado[] = {-3,0,9,18,81,102};
    bool todo_ok = true;

    /* Utilizo heapsort*/
    heap_sort(arreglo,6,comp_nros);

    /* Reviso que haya ordenado como esperado*/

    for (int i = 0; i<6 && todo_ok; i++){
        if (arreglo[i] != arreglo_ordenado[i]) todo_ok = false;
    }
    print_test("El arreglo fue ordenado como se esperaba", todo_ok);
}

void pruebas_heap_alumno() {
    pruebas_heap_vacio();
    pruebas_encolar_null();
    pruebas_algunos_elementos();
    pruebas_de_volumen();
    pruebas_destruir_heap();
    pruebas_crear_arr();
    pruebas_heap_sort();
}
