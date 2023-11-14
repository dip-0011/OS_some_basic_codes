/*A program to check the Deadlock Avoidance(telling apart safe and unsafe state) of current
processes using Banker's Algorithm*/
#include <stdio.h>
#include <stdbool.h>

struct process_info // structure of an individual process
{
    int max[10];       // Maximum number of resources a process may need
    int allocated[10]; // Number of currently allocated resources
    int need[10];      // Number of remaining resources the process needs
};

int no_of_process;
int no_of_resources;

// function to collect process information
void info_input(struct process_info process[no_of_process], int available[no_of_resources])
{
    // Fill array of Structure
    for (int i = 0; i < no_of_process; i++)
    {
        printf("Enter process[%d] info\n", i);
        printf("Enter Maximum Need: ");
        for (int j = 0; j < no_of_resources; j++)
            scanf("%d", &process[i].max[j]);
        printf("Enter No. of Allocated Resources for this process: ");
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &process[i].allocated[j]);
            // calculate need/future need
            // process[i].need[j] = process[i].max[j] - process[i].allocated[j];
            if ((process[i].max[j] - process[i].allocated[j]) < 0) // if need is negetive
            {
                process[i].need[j] = 0;
            }
            else
            {
                process[i].need[j] = process[i].max[j] - process[i].allocated[j];
            }
        }
    }
    printf("Enter Available Resources: ");
    for (int i = 0; i < no_of_resources; i++)
    {
        scanf("%d", &available[i]);
    }

    // return;
}

// function to print the collected information in tabular form
void print_info(struct process_info process[no_of_process])
{
    printf("\nPID\tMaximum\t\tAllocated\tNeed\n");
    for (int i = 0; i < no_of_process; i++)
    {
        printf("P[%d]\t", i);
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].max[j]);
        printf("\t\t");
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].allocated[j]);
        printf("\t\t");
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].need[j]);
        printf("\n");
    }

    // return;
}

// function to find if it's in safe state by Banker's Algorithm
bool banker_algo(struct process_info process[no_of_process], int available[no_of_resources], int safeSequence[no_of_process])
{
    bool finish[no_of_process]; // finish matrix containing which process is ended
    int work[no_of_resources];  // contains the number of resouces being used by individual  process
    // initiating work and finish matrix for Banker's Algorithm
    for (int i = 0; i < no_of_resources; i++)
    {
        work[i] = available[i];
    }
    for (int i = 0; i < no_of_process; i++)
    {
        finish[i] = false;
    }

    bool proceed = true;
    int k = 0;
    while (proceed)
    {
        proceed = false;
        for (int i = 0; i < no_of_process; i++)
        {
            bool flag = true;
            // Find Index i

            if (finish[i] == false)
            {
                for (int j = 0; j < no_of_resources; j++)
                {
                    // if Need <= Work
                    if (process[i].need[j] <= work[j])
                    {
                        continue;
                    }
                    else
                    {
                        flag = false; // implies that the current process need > work
                        break;
                    }
                }
                if (flag == false)
                    continue; // check for next process

                // If we get Index i(or process i), update work
                for (int j = 0; j < no_of_resources; j++)
                {
                    work[j] = work[j] + process[i].allocated[j];
                }
                finish[i] = true;
                safeSequence[k++] = i;
                proceed = true; // tells that we got atleast one process in safe state, we can proceed
            }
        } // end of outer for loop

    } // end of while
    // count the number of processes finished
    int i;
    int finished = 0;
    for (i = 0; i < no_of_process; i++)
    {
        if (finish[i] == true)
        {
            finished++;
        }
        
    }
    // If all processes are completed, then return true
    if (finished == no_of_process)
        return true;
    else
        return false;
}

// function to check if the processes are in safe state
bool check_state(struct process_info process[no_of_process], int available[no_of_resources], int safeSequence[no_of_process])
{
    // if banker's algo is passed, the process is in safe state
    if (banker_algo(process, available, safeSequence) == true)
    {
        return true;
    }
    else // if not, the process is in unsafe state
        return false;
}

int main()
{
    printf("Enter No of Process\n");
    scanf("%d", &no_of_process);
    printf("Enter No of type of Resources in system\n");
    scanf("%d", &no_of_resources);
    int available[no_of_resources];
    int safeSequence[no_of_process];
    // Create Array of Structure to store Processes's Informations
    struct process_info process[no_of_process];
    printf("Enter details of processes\n");
    // Take the Input
    info_input(process, available);
    // Print the Info in Tabular Form
    print_info(process);
    if (check_state(process, available, safeSequence))
    {
        printf("\nSystem is in Safe State\n");
        printf("Safe Sequence is: ");
        for (int i = 0; i < no_of_process; i++)
        {
            printf("P[%d] ", safeSequence[i]);
        }
    }
    else
        printf("\nSystem is in Unsafe State\n");
    return 0;
}
