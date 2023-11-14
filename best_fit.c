#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct mem_frag {
    int size;
    int frag;
    bool allocated;
};

struct process {
    int pid;
    int size;
    bool allocated;
};

int no_of_memfrag;
int no_of_process;

// Function to perform best fit memory allocation
void bestFit(struct mem_frag memory[], struct process p[], int no_of_memfrag, int no_of_process) {
    struct mem_frag temp;
    
    // Sort memory fragments by size in ascending order
    for (int i = 0; i < no_of_memfrag; i++) {
        for (int j = i + 1; j < no_of_memfrag; j++) {
            if (memory[i].size > memory[j].size) {
                temp = memory[i];
                memory[i] = memory[j];
                memory[j] = temp;
            }
        }
    }

    // Allocate processes based on best fit
    for (int i = 0; i < no_of_process; i++) {
        int bestFitIndex = -1;
        int bestFitSize = INT_MAX;

        for (int j = 0; j < no_of_memfrag; j++) {
            if (!memory[j].allocated && memory[j].size >= p[i].size) {
                int frag = memory[j].size - p[i].size;
                if (frag < bestFitSize) {
                    bestFitIndex = j;
                    bestFitSize = frag;
                }
            }
        }

        if (bestFitIndex != -1) {
            memory[bestFitIndex].allocated = true;
            memory[bestFitIndex].frag = bestFitSize;
            p[i].allocated = true;

            printf("Process %d (Size: %d) is allocated to Memory Fragment %d (Size: %d, Fragment: %d)\n",
                p[i].pid, p[i].size, bestFitIndex, memory[bestFitIndex].size, memory[bestFitIndex].frag);
        } else {
            printf("Process %d (Size: %d) cannot be allocated due to insufficient memory.\n", p[i].pid, p[i].size);
        }
    }
}

int main() {
    printf("\nEnter the number of memory fragments: ");
    scanf("%d", &no_of_memfrag);
    struct mem_frag memory[no_of_memfrag];

    printf("\nEnter the number of processes: ");
    scanf("%d", &no_of_process);
    struct process p[no_of_process];

    for (int i = 0; i < no_of_memfrag; i++) {
        printf("\nMemory fragment size of fragment %d is:\n", i + 1);
        scanf("%d", &memory[i].size);
        memory[i].allocated = false;
        memory[i].frag = 0;
    }

    for (int i = 0; i < no_of_process; i++) {
        printf("\nProcess ID of Process is: ");
        scanf("%d", &p[i].pid);
        printf("\nWrite the size of the process: ");
        scanf("%d", &p[i].size);
        p[i].allocated = false;
    }

    bestFit(memory, p, no_of_memfrag, no_of_process);

    return 0;
}
