/* 
 * DynamicArray header File  
 * Author: Clifford Dunn
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define TYPE void*

typedef struct DynamicArray DynamicArray;
typedef int (*compareFunction)(TYPE, TYPE);
typedef void (*printFunction)(TYPE);

struct DynamicArray;

DynamicArray* dyNew(int capacity);
void dyDelete(DynamicArray* array);

// Dynamic array
static void setCapacity(DynamicArray* array, int capacity);
static void init(DynamicArray* array, int capacity);
DynamicArray* dyNew(int capacity);

void dyAdd(DynamicArray* array, TYPE value);
void dyAddAt(DynamicArray* array, TYPE value, int position);
void dyPut(DynamicArray* array, TYPE value, int position);
void dyRemoveAt(DynamicArray* array, int position);
TYPE dyGet(DynamicArray* array, int position);
int dySize(DynamicArray* array);
void dySwap(DynamicArray* array, int position1, int position2);
void dyDelete(DynamicArray* array);

// Stack
void dyStackPush(DynamicArray* stack, TYPE value);
void dyStackPop(DynamicArray* stack);
TYPE dyStackTop(DynamicArray* stack);
int dyStackIsEmpty(DynamicArray* stack);

// Deque/Stack/Queue
void dyDequePushFront(DynamicArray* deque, TYPE value);
void dyDequePushBack(DynamicArray* deque, TYPE value);
TYPE dyDequeFront(DynamicArray* deque);
TYPE dyDequeBack(DynamicArray* deque);
void dyDequePopFront(DynamicArray* deque);
void dyDequePopBack(DynamicArray* deque);
int dyDequeIsEmpty(DynamicArray* deque);

// Bag
void dyBagAdd(DynamicArray* bag, TYPE value);
void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction compare);
int dyBagContains(DynamicArray* bag, TYPE value, compareFunction compare);

// Ordered bag
void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction compare);
void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction compare);
int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction compare);

// Heap
void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction compare);
TYPE dyHeapGetMin(DynamicArray* heap);
void dyHeapRemoveMin(DynamicArray* heap, compareFunction compare);
void dyHeapSort(DynamicArray* heap, compareFunction compare);
static void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare);
static void buildHeap(DynamicArray* heap, compareFunction compare);

// Iterator
typedef struct DynamicArrayIterator DynamicArrayIterator;

struct DynamicArrayIterator {
	DynamicArray* array;
	int current;
};

DynamicArrayIterator* dyIteratorNew(DynamicArray* array);
void dyIteratorDelete(DynamicArrayIterator* iterator);
int dyIteratorHasNext(DynamicArrayIterator* iterator);
TYPE dyIteratorNext(DynamicArrayIterator* iterator);
void dyIteratorRemove(DynamicArrayIterator* iterator);

// Utility
// Prints the size, capacity, and elements of array, calling the print function on
// each element.
// @param array
// @param print
void dyPrint(DynamicArray* array, printFunction print);
void dyCopy(DynamicArray* source, DynamicArray* destination);

#endif
