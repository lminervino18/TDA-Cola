#include <stdbool.h>
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La cola está planteada como una cola de punteros genéricos. */

typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;

nodo_t* _crear_nodo(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) return NULL;

    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

void _destruir_nodo(nodo_t* nodo) {
    free(nodo);
}

typedef struct cola{
    nodo_t* primero;
    nodo_t* ultimo;
} cola_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/


cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));

    if (cola == NULL) return NULL;

    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->primero == NULL;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    nodo_t* actual = cola->primero;
    nodo_t* prox;

    while(actual != NULL) {
         prox = actual->prox;

         if (destruir_dato != NULL){
             destruir_dato(actual->dato);
         }

         _destruir_nodo(actual);
         actual = prox;
    }
    free(cola);
}

bool cola_encolar(cola_t *cola, void *valor){
    nodo_t* nuevo_nodo = _crear_nodo(valor);

    if (nuevo_nodo == NULL) return false;

    if (cola_esta_vacia(cola)){
        cola->primero = nuevo_nodo;
    } else {
        cola->ultimo->prox = nuevo_nodo;
    }

    cola->ultimo = nuevo_nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola){

    if (cola_esta_vacia(cola)) return NULL;

    return cola->primero->dato;
}

void *cola_desencolar(cola_t *cola){

    if (cola_esta_vacia(cola)) return NULL;
    
    void* dato_a_devolver = cola->primero->dato;
    nodo_t* proximo = cola->primero->prox;
    _destruir_nodo(cola->primero);

    if (proximo == NULL) cola->ultimo = proximo;

    cola->primero = proximo;
    return dato_a_devolver;
}
