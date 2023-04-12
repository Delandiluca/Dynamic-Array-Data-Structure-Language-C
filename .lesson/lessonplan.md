# Dynamic Array

```c
 /*

	Implementação do array dinâmico.

	*/

#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 2;

struct arrayDinamico {
	int tamanho;
	int ultimo;
	int *vetor;
};

typedef struct arrayDinamico ArrayDinamico;

int create(ArrayDinamico **array); // Inicializa o array dinâmico
int append(ArrayDinamico *arrayPtr, int valor);
int insert(ArrayDinamico *arrayPtr, int valor, int indice );
int resize(ArrayDinamico *arrayPtr);
int le(ArrayDinamico *arrayPtr, int *valor, int indice);
int delete(ArrayDinamico *arrayPtr, int indice); 
void print(ArrayDinamico *arrayPtr);

int main(void) {
	ArrayDinamico *ad;
	create(&ad);
  int a;
	
	return 0;
}

int create(ArrayDinamico **array){
	ArrayDinamico *arrayPtr = malloc(sizeof(ArrayDinamico));
	if ( !arrayPtr ){
		return 0; // não conseguiu alocar espaço para o Array dinâmico
	}
	arrayPtr->tamanho = MAXIMO;
	arrayPtr->ultimo = 0;
	arrayPtr->vetor = malloc(arrayPtr->tamanho*sizeof(int));
	if (!(arrayPtr->vetor)) return 0;
	*array = arrayPtr; // Altera a referência 
	return 1;
}

int append(ArrayDinamico *arrayPtr, int valor) {
	if (!arrayPtr) return 0;
	if (arrayPtr->tamanho == arrayPtr->ultimo) {
		if (resize(arrayPtr)) {
			arrayPtr->vetor[arrayPtr->ultimo] = valor; 
			arrayPtr->ultimo++;
			return 1;
		}
		return 0; // não foi possível realocar. 
	}
	arrayPtr->vetor[arrayPtr->ultimo++] = valor;
	return 1;
}

int resize(ArrayDinamico *arrayPtr) { 
    if (!arrayPtr) return 0;
    arrayPtr->tamanho = arrayPtr->tamanho * 2; 
    arrayPtr->vetor = realloc(arrayPtr->vetor, arrayPtr->tamanho * sizeof(int));
    if ( !arrayPtr->vetor ) return 0; 
    return 1; 
}

int delete(ArrayDinamico *arrayPtr, int indice) {
    if ( !arrayPtr ) return 0;
    if (arrayPtr->ultimo == 0) return 0;    
    if ( indice < 0 || indice >= arrayPtr->ultimo){	
		 return 0; 
		}
    arrayPtr->ultimo--;
    for (int i = indice; i < arrayPtr->ultimo; i++) {
        arrayPtr->vetor[i] = arrayPtr->vetor[i+1]; 
    }
    return 1; 
}

int search(ArrayDinamico *arrayPtr, int *valor, int indice) {
    if (!arrayPtr) return 0; 
    if (indice >= 0 && indice < arrayPtr->ultimo) {
        *valor = arrayPtr->vetor[indice]; 
        return 1; 
    }
    valor = NULL;
    return 0; 
}


int insert(ArrayDinamico *arrayPtr, int valor, int indice ) { 
    if (!arrayPtr) return 0; 
    if ( indice < 0 || indice >= arrayPtr->ultimo ) return 0; 
    arrayPtr->vetor[indice] = valor; 
    return 1;
}

void print(ArrayDinamico *arrayPtr) {
	printf("\nTamanho: %d\n", arrayPtr->tamanho);
	printf("último: %d\n", arrayPtr->ultimo);	
	for (int i = 0; i < arrayPtr->ultimo; i++) {
		int valor;
		search(arrayPtr, &valor, i); 
		printf(" %3d ", i); 
	}
	puts("");
	for (int i = 0; i < arrayPtr->ultimo; i++) {
		int valor;
		search(arrayPtr, &valor, i); 
		printf("[%3d]",valor);
	}
	puts("");
}
