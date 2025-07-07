// Landon Carroll 1223803607

#pragma once

typedef struct TAG_ELEMENT {
	int index;
	double key;
	int pos;	// 0 if not in heap, otherwise index in heap
} ELEMENT;

typedef struct TAG_HEAP {
	int capacity;
	int size;
	int* H;		// Array of indices into the ELEMENT array
} HEAP;