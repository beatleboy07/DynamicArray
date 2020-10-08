/* 
 * Dynamic Array Implementation File
 * Author: Clifford Dunn
 */


#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



// --- Dynamic array --- // 

struct DynamicArray 
{
	TYPE* data;
	int size;
	int capacity;
};


static void setCapacity(DynamicArray* array, int capacity) 
{
	TYPE* data = malloc(sizeof(TYPE) * capacity);

	for(int i = 0; i < array->size; i++) 
	{
		data[i] = array->data[i];
	}

	free(array->data);
	array->data = data;
	array->capacity = capacity;
}


static void init(DynamicArray* array, int capacity) 
{
	assert(capacity > 0);
	array->data = NULL;
	array->size = 0;
	setCapacity(array, capacity);
}


DynamicArray* dyNew(int capacity) 
{
	DynamicArray* array = malloc(sizeof(DynamicArray));
	init(array, capacity);
	return array;
}


void dyDelete(DynamicArray* array) 
{
	free(array->data);
	free(array);
}


void dyAdd(DynamicArray* array, TYPE value) 
{
	if(array->size >= array->capacity) 
	{
		setCapacity(array, 2 * array->capacity);
	}

	array->data[array->size] = value;
	array->size++;
}


void dyAddAt(DynamicArray* array, TYPE value, int position) 
{
	assert(position <= array->size);
	dyAdd(array, value);
	for(int i = array->size - 1; i > position; i--) 
	{
		dySwap(array, i, i-1);
	}
}


void dyPut(DynamicArray* array, TYPE value, int position) 
{
	assert(position < array->size);
	array->data[position] = value;
}


void dyRemoveAt(DynamicArray* array, int position) 
{
	assert(position < array->size);
	for(int i = position; i< array->size - 1; i++) 
	{
		array->data[position] = array->data[position + 1];
	}
	array->size--;
}


TYPE dyGet(DynamicArray* array, int position) 
{
	assert(position < array->size);
	return array->data[position];
}


int dySize(DynamicArray* array) 
{
	return array->size;
}


void dySwap(DynamicArray* array, int position1, int position2)
{
	assert(position1 < array->size);
	assert(position2 < array->size);
	TYPE temp = array->data[position1];
	array->data[position1] = array->data[position2];
	array->data[position2]= temp;
}



// --- Stack --- //


void dyDequePushBack(DynamicArray* deque, TYPE value)
{
	dyAdd(deque, value);
}


void dyDequePopBack(DynamicArray* deque)
{
	dyRemoveAt(deque, deque->size - 1);
}


TYPE dyDequeBack(DynamicArray* deque)
{
	return dyGet(deque, deque->size - 1);
}


int dyDequeIsEmpty(DynamicArray* deque)
{
	return deque->size == 0;
}



// --- Bag --- //


static int findFirst(DynamicArray* array, TYPE value, compareFunction compare)
{
	for(int i = 0; i < array->size; i++)
	{
		if(compare(value, array->data[i]) == 0)
		{
			return i;
		}
	}

	return -1;
}


void dyBagAdd(DynamicArray* bag, TYPE value)
{
	dyAdd(bag, value);
}


void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction compare)
{
	int position = findFirst(bag, value, compare);
	
	if(position != -1)
	{
		dyRemoveAt(bag, position);
	}
}

int dyBagContains(DynamicArray* bag, TYPE value, compareFunction compare)
{
	return findFirst(bag, value, compare) != -1;
}



// --- Ordered Bag --- //


static int binarySearch(DynamicArray* array, TYPE value, compareFunction compare)
{
    int low = 0;
    int high = array->size - 1;

    while(low <= high)
    {
        int middle = (low + high) / 2;
        if(compare(value, array->data[middle]) < 0)
            high = middle - 1;

        else if(compare(value, array->data[middle]) > 0)
            low = middle + 1;

        else
            return middle;
    }

    return low;
}


void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    dyAddAt(bag, value, position);
}


void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    if(compare(value, bag->data[position]) == 0)
    {
        dyRemoveAt(bag, position);
    }
}


int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    return compare(value, dyGet(bag, position) ) == 0;
}



// --- Heap --- //


void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare)
{
    assert(heap != NULL);
    assert(dySize(heap) != 0);
    assert(last <- dySize(heap));
    assert(position <= last);

    int leftChild = (2 * position) + 1;
    int rightChild = (2 * position) + 2;

    int leftChildExists = 0;
    int rightChildExists = 0;


    if(leftChild <= last)
        leftChildExists = 1;
    if(rightChild <= last)
        rightChildExists = 1;

    if(leftChildExists && rightChildExists)
    {
        if(compare(dyGet(heap, leftChild), dyGet(heap, rightChild) ) == -1)
        {
            if(compare(dyGet(heap, leftChild), dyGet(heap, position) ) == -1)
            {
                dySwap(heap, position, leftChild);
                adjustHeap(heap, last, leftChild, compare);
            }

            if(compare(dyGet(heap, rightChild), dyGet(heap, position) ) == -1)
            {
                dySwap(heap, position, rightChild);
                adjustHeap(heap, last, rightChild, compare);
            }
        }

        else if(compare(dyGet(heap, rightChild), dyGet(heap, position) ) == -1)
        {
            dySwap(heap, position, rightChild);
            adjustHeap(heap, last, rightChild, compare);
        }
    }

    else if(leftChildExists)
    {
        if(compare(dyGet(heap, leftChild), dyGet(heap, position) ) == -1) 
        {
            dySwap(heap, position, leftChild);
            adjustHeap(heap, last, leftChild, compare);
        }
    }
}


void buildHeap(DynamicArray* heap, compareFunction compare)
{
    int maxPos = heap->size -1;

    for(int i = (maxPos - 1) / 2; i >= 0; i--)
    {
        adjustHeap(heap, maxPos, i, compare);
    }
}


void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction compare)
{
    dyAdd(heap, value);

    int currentPos = dySize(heap) - 1;

    while(currentPos > 0) 
    {
        int parent = (currentPos - 1) / 2;
        if(compare(dyGet(heap, currentPos), dyGet(heap, parent) ) == -1)
        {
            dySwap(heap, currentPos, parent);
            currentPos = parent;
        }

        else
            break;
    }
}


void dyHeapRemoveMin(DynamicArray* heap, compareFunction compare)
{
    assert(heap != NULL);

    int last = dySize(heap);

    if(last != 0) 
    {
        dyPut(heap, dyGet(heap, last - 1), 0);
        dyRemoveAt(heap, last - 1);

        if(dySize(heap) > 1)
            adjustHeap(heap, dySize(heap) - 1, 0, compare);
    }
}


TYPE dyHeapGetMin(DynamicArray* heap)
{
    return dyGet(heap, 0);
}


void dyHeapSort(DynamicArray* heap, compareFunction compare)
{
    assert(heap != NULL);
    assert(dySize(heap) > 0);

    buildHeap(heap, compare);
    int last;

    for(last = dySize(heap) - 1; last > 0; last--)
    {
        dySwap(heap, 0, last);
        adjustHeap(heap, last-1, 0, compare);
    }
}



// --- Iterator --- //


DynamicArrayIterator* dyIteratorNew(DynamicArray* array)
{
    DynamicArrayIterator* iterator = malloc(sizeof(DynamicArrayIterator) );
    iterator->array = array;
    iterator->current = 0;
    return iterator;
}


void dyIteratorDelete(DynamicArrayIterator* iterator)
{
    free(iterator);
}


int dyIteratorHasNext(DynamicArrayIterator* iterator)
{
    return iterator->current < iterator->array->size;
}


TYPE dyIteratorNext(DynamicArrayIterator* iterator)
{
    TYPE value = dyGet(iterator->array, iterator->current);
    iterator->current++;
    return value;
}


void dyIteratorRemove(DynamicArrayIterator* iterator)
{
    iterator->current--;
    dyRemoveAt(iterator->array, iterator->current);
}




// --- Utility --- //


void dyPrint(DynamicArray* array, printFunction print)
{
    printf("\nsize: %d\ncapacity: %d\n[\n", array->size, array->capacity);

    for(int i = 0; i < array->size; i++)
    {
        printf("%d : ", i);
        print(array->data[i]);
        printf("\n");
    }

    printf("]\n");
}


void dyCopy(DynamicArray* source, DynamicArray* destination)
{
    free(destination->data);
    init(destination, source->capacity);
    for(int i = 0; i < source->size; i++)
    {
        destination->data[i] = source->data[i];
    }

    destination->size = source->size;
}
