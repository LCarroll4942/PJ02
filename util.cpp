// Landon Carroll 1223803607

#include <stdio.h>
#include <string.h>
#include "util.h"

// Returns 1 if instruction is valid
int nextInstruction(char* instruction, int* index, double* newKey) {
	int returnValue = 0;
	*index = -1;
	*newKey = 0.0;

	// Take instruction from stdin
	fscanf(stdin, "%s", instruction);	

	// Check for valid instruction
	if (strcmp(instruction, "Stop") == 0) return 1;
	if (strcmp(instruction, "Read") == 0) return 1;
	if (strcmp(instruction, "PrintArray") == 0) return 1;
	if (strcmp(instruction, "PrintHeap") == 0) return 1;
	if (strcmp(instruction, "BuildHeap") == 0) return 1;
	if (strcmp(instruction, "ExtractMin") == 0) return 1;
	if (strcmp(instruction, "Write") == 0) return 1;

	if (strcmp(instruction, "DecreaseKey") == 0) {
		returnValue += fscanf(stdin, "%d", index);
		returnValue += fscanf(stdin, "%lf", newKey);
		if (returnValue == 2) {
			return 1;
		}
		else {
			return 0;
		}
	}

	if (strcmp(instruction, "Insert") == 0) {
		returnValue = fscanf(stdin, "%d", index);
		if (returnValue == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}

	// Unknown instruction
	return 0;

}