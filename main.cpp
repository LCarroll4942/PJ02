// Landon Carroll 1223803607

#include "main.h"

int main(int argc, char **argv) {
	ELEMENT** V;
	HEAP* pHeap;
	FILE *outputFile;
	char instruction[256];
	int index, returnValue, n;
	double newKey;

	// Check for valid command line arguments
	if (argc != 3) {
		fprintf(stderr, "Usage: ./PJ2 <I-File> <O-File>\n");
		fprintf(stderr, "<I-File> is the input file\n");
		fprintf(stderr, "<O-File> is the output file\n");
		exit(0);
	}

	V = NULL;
	pHeap = NULL;
	outputFile = NULL;
	n = 0;

	while (1) {
		returnValue = nextInstruction(instruction, &index, &newKey);

		if (returnValue == 0) {
			fprintf(stderr, "Warning: Invalid instruction: %s\n", instruction);
			continue;
		}

		// stop, read, printarray, printheap, buildheap, extractmin, write, decreasekey, insert

		if (strcmp(instruction, "Stop") == 0) {
			fprintf(stdout, "Instruction: Stop\n");

			// Free Memory
			if (V) {
				for (int i = 1; i <= n; i++) {
					if (V[i]) free(V[i]);
				}
				free(V);
			}

			if (pHeap) {
				free(pHeap->H);
				free(pHeap);
			}

			if (outputFile) {
				fclose(outputFile);
			}
			exit(0);
		}

		if (strcmp(instruction, "Read") == 0) {
			handleRead(argv[1], &V, &pHeap, &n);
		}

		if (strcmp(instruction, "PrintArray") == 0) {
			fprintf(stdout, "Instruction: PrintArray\n");

			if (!V) {
				fprintf(stderr, "Error: array is NULL\n");
				continue;
			}
			else {
				for (int i = 1; i <= n; i++) {
					printf("%d %lf %d\n", i, V[i]->key, V[i]->pos);
				}
			}

			continue;
		}
		if (strcmp(instruction, "PrintHeap") == 0) {
			fprintf(stdout, "Instruction: PrintHeap\n");
			if (pHeap == NULL || pHeap->H == NULL) {
				fprintf(stderr, "Error: heap is NULL\n");
				continue;
			}
			else {
				printf("Capacity = %d, size = %d\n", pHeap->capacity, pHeap->size);

				for (int i = 1; i <= pHeap->size; i++) {
					printf("H[%d] = %d\n", i, pHeap->H[i]);
				}
			}
			continue;
		}

		if (strcmp(instruction, "BuildHeap") == 0) {
			fprintf(stdout, "Instruction: BuildHeap\n");
			if (V == NULL || pHeap == NULL) {
				fprintf(stderr, "Error: cannot build heap from NULL\n");
				continue;
			}
			buildHeap(V, pHeap, n);
			continue;
		}

		if (strcmp(instruction, "ExtractMin") == 0) {
			fprintf(stdout, "Instruction: ExtractMin\n");
			if (!pHeap) {
				fprintf(stderr, "Error: heap is NULL\n");
				continue;
			}
			if (pHeap->size == 0) {
				fprintf(stderr, "Error: heap is empty\n");
				continue;
			}
			extractMin(V, pHeap);
			continue;
		}

		if (strcmp(instruction, "Write") == 0) {
			fprintf(stdout, "Instruction: Write\n");

			if (!V || n == 0) {
    			fprintf(stderr, "Error: array is NULL\n");
   				continue;
			}

			outputFile = fopen(argv[2], "w");
			if (!outputFile) {
				fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
				continue;
			}
			for (int i = 1; i <= n; i++) {
				fprintf(outputFile, "%d %lf %d\n", i, V[i]->key, V[i]->pos);
			}
			fclose(outputFile);
			outputFile = NULL;
			continue;
		}

		if (strcmp(instruction, "DecreaseKey") == 0) {
			fprintf(stdout, "Instruction: DecreaseKey %d %lf\n", index, newKey);
			if (index < 1 || index > n || newKey >= V[index]->key) {
				fprintf(stderr, "Error: invalid call to DecreaseKey\n");
				continue;
			}
			if (V[index]->pos == 0) {
				fprintf(stderr, "Error: V[%d] not in the heap\n", index);
				continue;
			}
			decreaseKey(V, pHeap, index, newKey);
			continue;
		}

		if (strcmp(instruction, "Insert") == 0) {
			fprintf(stdout, "Instruction: Insert %d\n", index);
			if (index < 1 || index > n) {
				fprintf(stderr, "Error: index out of bound\n");
				continue;
			}
			if (V[index]->pos != 0) {
				fprintf(stderr, "Error: V[%d] already in the heap\n", index);
				continue;
			}
			insert(V, pHeap, index);
			continue;
		}
	}

	return 1;
}
