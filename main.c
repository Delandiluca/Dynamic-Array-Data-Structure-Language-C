#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5;

struct arrayDynamic {
  int max;
  int size;
  int *vector;
};
typedef struct arrayDynamic DynamicArray;

int create(DynamicArray **array); // Inicializa o array dinâmico
int append(DynamicArray *arrayPtr, int value);
int insert(DynamicArray *arrayPtr, int value, int index);
int resize(DynamicArray *arrayPtr);
int search(DynamicArray *arrayPtr, int *value, int index);
int erase(DynamicArray *arrayPtr, int index);
void print(DynamicArray *arrayPtr);
void instructions(void);

int main(void) {
  DynamicArray *ad;
  create(&ad);

  unsigned int choice;
  int item;
  int index;

  instructions();
  printf("%s", "? ");
  scanf("%u", &choice);

  while (choice != 6) {

    switch (choice) {

    case 1:
      printf("%s", "Enter a element: ");
      scanf("\n%d", &item);
      // printf("\n%c", item);
      append(ad, item);
      print(ad);
      break;

    case 2:
      printf("%s", "Enter a index: ");
      scanf("\n%d", &index);
      erase(ad, index);
      printf("Index %d has been erased.\n", index);

      print(ad);
      break;
    case 3:
      printf("%s", "Enter a index: ");
      scanf("\n%d", &index);
      int value;
      search(ad, &value, index);
      printf("Elemento da index %d é o %d", index, value);
      print(ad);
      break;
    case 4:
      printf("%s", "Enter a value: ");
      scanf("\n%d", &item);
      printf("%s", "Enter a index: ");
      scanf("\n%d", &index);
      insert(ad, item, index);
      puts("Item has been inserted in index.\n");
      print(ad);
      break;
    case 5:
      print(ad);
      break;
    default:
      puts("Invalid choice.\n");
      instructions();
      break;
    }

    printf("%s", "? ");
    scanf("%u", &choice);
  }

  return 0;
}

void instructions(void) {
  printf("Enter your choice:\n"
         "   1 to add an item to the array\n"
         "   2 to erase an item with index from the array\n"
         "   3 to return an item with index from the array\n"
         "   4 to insert an item with index from the array\n"
         "   5 to print all the array\n");
}

int create(DynamicArray **array) {
  DynamicArray *arrayPtr = malloc(sizeof(DynamicArray));
  if (!arrayPtr) {
    return 0; // não conseguiu alocar espaço para o Array dinâmico
  }
  arrayPtr->max = MAX_SIZE;
  arrayPtr->size = 0;
  arrayPtr->vector = malloc(arrayPtr->max * sizeof(int));
  if (!(arrayPtr->vector))
    return 0;
  *array = arrayPtr; // Altera a referência
  return 1;
}

int append(DynamicArray *arrayPtr, int value) {
  if (!arrayPtr)
    return 0;
  if (arrayPtr->max == arrayPtr->size) {
    if (resize(arrayPtr)) {
      arrayPtr->vector[arrayPtr->size] = value;
      arrayPtr->size++;
      return 1;
    }
    return 0; // não foi possível realocar.
  }
  arrayPtr->vector[arrayPtr->size++] = value;
  return 1;
}

int resize(DynamicArray *arrayPtr) {
  if (!arrayPtr)
    return 0;
  arrayPtr->max = arrayPtr->max * 2;
  arrayPtr->vector = realloc(arrayPtr->vector, arrayPtr->max * sizeof(int));
  if (!arrayPtr->vector)
    return 0;
  return 1;
}

int erase(DynamicArray *arrayPtr, int index) {
  if (!arrayPtr)
    return 0;
  if (arrayPtr->size == 0)
    return 0;
  if (index < 0 || index >= arrayPtr->size) {
    arrayPtr->size--;
    return 0;
  }
  for (int i = index; i < arrayPtr->size; i++) {
    arrayPtr->vector[i] = arrayPtr->vector[i + 1];
  }
  arrayPtr->size--;
  return 1;
}

int search(DynamicArray *arrayPtr, int *value, int index) {
  if (!arrayPtr)
    return 0;
  if (index >= 0 && index < arrayPtr->size) {
    *value = arrayPtr->vector[index];
    return 1;
  }
  value = NULL;
  return 0;
}

int insert(DynamicArray *arrayPtr, int value, int index) {
  if (!arrayPtr)
    return 0;

  if (index < 0 || index > arrayPtr->size)
    return 0;

  if (arrayPtr->max == arrayPtr->size) {
    if (!resize(arrayPtr))
      return 0; // não foi possível realocar.
  }

  if (index == arrayPtr->size) {
    arrayPtr->vector[index] = value;
    arrayPtr->size++;
    return 1;
  }

  for (int i = arrayPtr->size; i > index; i--) {
    arrayPtr->vector[i] = arrayPtr->vector[i - 1];
  }

  arrayPtr->vector[index] = value;
  arrayPtr->size++;

  return 1;
}

void print(DynamicArray *arrayPtr) {
  printf("\nMax: %d\n", arrayPtr->max);
  printf("Size: %d\n", arrayPtr->size);
  for (int i = 0; i < arrayPtr->size; i++) {
    int value;
    search(arrayPtr, &value, i);
    printf(" %3d ", i);
  }
  puts("");
  for (int i = 0; i < arrayPtr->size; i++) {
    int value;
    search(arrayPtr, &value, i);
    printf("[%3d]", value);
  }
  puts("");
}