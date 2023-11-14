#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

// #define n_p 100
// #define n_m 100

struct mem_frag
{
    int size;
    int frag;
    bool allocated;
};
struct process
{
    int pid;
    int size;
    bool allocated; // process id and its memory requirement
};

int no_of_memfrag;
int no_of_process;

int main()
{
    printf("\nEnter the number of memory fragments: ");
    scanf("%d", &no_of_memfrag);
    struct mem_frag memory[no_of_memfrag];
    printf("\nEnter the number of processes: ");
    scanf("%d", &no_of_process);
    struct process p[no_of_process];

    for (int i = 0; i < no_of_memfrag; i++)
    {
        printf("\nMemory fragment size of fragment %d is:\n", i + 1);
        scanf("%d", &memory[i].size);
        memory[i].allocated = false;
        memory[i].frag = 0;
    }

    for (int i = 0; i < no_of_process; i++)
    {
        printf("\nProcess ID of Process is: ");
        scanf("%d", &p[i].pid); // assigning values to each element in array
        printf("\nWrite the size of the process: ");
        scanf("%d", &p[i].size);
        p[i].allocated = false;
    }

    struct mem_frag temp;
    for (int i = 0; i < no_of_memfrag; i++)
    {
        for (int j = 0; j < no_of_memfrag; j++)
        {
            if (memory[i].size > memory[j].size)
            {
                temp = memory[i];
                memory[i] = memory[j];
                memory[j] = temp;
            }
        }
    }
    for (int i = 0; i < no_of_memfrag; i++)
    {
        for (int j = 0; j < no_of_process; j++)
        {
            if ((memory[i].allocated == false) && (p[j].allocated == false))
            {
                if ((memory[i].size > p[j].size))
                {
                    memory[i].allocated = true;
                    p[j].allocated = true;
                    memory[i].frag = memory[i].size - p[j].size;
                }
                if (memory[i].size < p[j].size)
                {
                    printf("Fragment not available\n");
                }
            }
        }
    }

    printf("\nProcess info:");
    printf("\nProcess Id\tProcess Size\tAllocation Status");
    for (int i = 0; i < no_of_process; i++)
    {
        printf("\n%d\t\t%d\t\t%d",p[i].pid,p[i].size,p[i].allocated);
    }
    
    printf("\nFragment No\tFragment Size\tFragment Allocation\tFree Fragment");
    for (int i = 0; i < no_of_memfrag; i++)
    {
        printf("\n%d\t\t%d\t\t%d\t\t%d",i+1,memory[i].size,memory[i].allocated,memory[i].frag);
    }
    

    return 0;
}