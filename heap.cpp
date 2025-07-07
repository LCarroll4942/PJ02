// Landon Carroll 1223803607

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Swap two positions in the heap
void swap(HEAP* pHeap, ELEMENT** V, int i, int j) {
    int temp = pHeap->H[i];
    pHeap->H[i] = pHeap->H[j];
    pHeap->H[j] = temp;

    V[pHeap->H[i]]->pos = i;
    V[pHeap->H[j]]->pos = j;
}

// Maintain min-heap property at node i
void heapify(ELEMENT** V, HEAP* pHeap, int i) {
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= pHeap->size &&
        V[pHeap->H[left]]->key < V[pHeap->H[smallest]]->key) {
        smallest = left;
    }

    if (right <= pHeap->size &&
        V[pHeap->H[right]]->key < V[pHeap->H[smallest]]->key) {
        smallest = right;
    }

    if (smallest != i) {
        swap(pHeap, V, i, smallest);
        heapify(V, pHeap, smallest);
    }
}

void buildHeap(ELEMENT** V, HEAP* pHeap, int n) {
    pHeap->size = n;

    for (int i = 1; i <= n; i++) {
        V[i]->pos = i;
        pHeap->H[i] = i;
    }

    for (int i = n / 2; i >= 1; i--) {
        heapify(V, pHeap, i);
    }
}

// Insert a new element into the heap
void insert(ELEMENT** V, HEAP* pHeap, int index) {
    pHeap->size++;
    int i = pHeap->size;
    pHeap->H[i] = index;
    V[index]->pos = i;

    // Compare with parent elements until in right place
    while (i > 1 && V[pHeap->H[i]]->key < V[pHeap->H[i / 2]]->key) {
        swap(pHeap, V, i, i / 2);
        i = i / 2;
    }

    printf("Element V[%d] inserted into the heap\n", index);
}

// Decrease the key value and restore heap
void decreaseKey(ELEMENT** V, HEAP* pHeap, int index, double newKey) {
    int i = V[index]->pos;
    V[index]->key = newKey;

    // Compare with parent elements until in right place
    while (i > 1 && V[pHeap->H[i]]->key < V[pHeap->H[i / 2]]->key) {
        swap(pHeap, V, i, i / 2);
        i = i / 2;
    }
}

// Remove and return the min element from the heap
void extractMin(ELEMENT** V, HEAP* pHeap) {
    int minIndex = pHeap->H[1];

    // Replace root with last element
    pHeap->H[1] = pHeap->H[pHeap->size];
    V[pHeap->H[1]]->pos = 1;

    V[minIndex]->pos = 0; // Mark as removed
    pHeap->size--;

    // Restore min-heap property
    heapify(V, pHeap, 1);
}

void handleRead(char* inputFile, ELEMENT*** pV, HEAP** ppHeap, int* n) {
    fprintf(stdout, "Instruction: Read\n");

    // Free Memory before being reallocated
    if (*pV) {
        for (int i = 1; i <= *n; i++) {
            if ((*pV)[i]) {
                free((*pV)[i]);
            }
        }
        free(*pV);
        *pV = NULL;
    }

    if (*ppHeap) {
      if ((*ppHeap)->H) free((*ppHeap)->H);
        free(*ppHeap);
        *ppHeap = NULL;  
    }

    FILE* file = fopen(inputFile, "r");
    if (!file) {
        fprintf(stderr, "Error: cannot open file %s\n", inputFile);
        return;
    }

    // Read first integer (n)
    fscanf(file, "%d", n);

    // Allocate array of ELEMENT*
    *pV = (ELEMENT**)calloc(*n + 1, sizeof(ELEMENT*));  // +1 because we start indexing from 1
    if (!*pV) {
        fprintf(stderr, "Error: memory allocation failed for V\n");
        fclose(file);
        return;
    }

    // Allocate and initialize each ELEMENT
    for (int i = 1; i <= *n; i++) {
        double key;
        fscanf(file, "%lf", &key);

        (*pV)[i] = (ELEMENT*)calloc(1, sizeof(ELEMENT));
        if (!(*pV)[i]) {
            fprintf(stderr, "Error: memory allocation failed for V[%d]\n", i);
            fclose(file);
            return;
        }

        (*pV)[i]->index = i;
        (*pV)[i]->key = key;
        (*pV)[i]->pos = 0;
    }

    // Close input file
    fclose(file);

    // Allocate HEAP and initialize
    *ppHeap = (HEAP*)calloc(1, sizeof(HEAP));
    if (!*ppHeap) {
        fprintf(stderr, "Error: memory allocation failed for heap\n");
        return;
    }

    (*ppHeap)->capacity = *n;
    (*ppHeap)->size = 0;
    (*ppHeap)->H = (int*)calloc(*n + 1, sizeof(int));  // Heap indices start at 1

    if (!(*ppHeap)->H) {
        fprintf(stderr, "Error: memory allocation failed for heap array\n");
        return;
    }
}