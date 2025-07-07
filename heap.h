// Landon Carroll 1223803607

#pragma once
#include "data_structures.h"

void handleRead(char* inputFile, ELEMENT*** pV, HEAP** ppHEAP, int* n);
void buildHeap(ELEMENT** V, HEAP* pHeap, int n);
void insert(ELEMENT** V, HEAP* pHeap, int index);
void decreaseKey(ELEMENT** V, HEAP* pHeap, int index, double newKey);
void extractMin(ELEMENT** V, HEAP* pHeap);
void heapify(ELEMENT** V, HEAP* pHEAP, int i);