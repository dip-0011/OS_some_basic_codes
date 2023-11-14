#include <stdio.h>
#include <conio.h>

struct process
{
    int pid;       // process id
    // int t_arv;     // arrival time
    int t_brst;    // burst time = absoluete time of completion
    int t_trn_arr; // turn around time = completion time - arrival time
    int t_w;       // waiting time = completion time - arrival time
};

int n_processes;

int main()
{
    printf("\nEnter the number of processes: ");
    scanf("%d", &n_processes);
    struct process p[n_processes];
    // enter process informaion
    printf("\nEnter process infromation:");
    for (int i = 0; i < n_processes; i++)
    {
        printf("\n\tProcess id: ");
        scanf("%d", &p[i].pid);
        // printf("\n\tArrival time: ");
        // scanf("%d", &p[i].t_arv);
        printf("\n\tBurst time: ");
        scanf("%d", &p[i].t_brst);
    }

    printf("\nProcess Id\t\tBrust time");
    for (int i = 0; i < n_processes; i++)
    {
        // printf("\n\t%d\t\t%d\t\t\t%d", p[i].pid, p[i].t_arv, p[i].t_brst);
        printf("\n\t%d\t\t\t%d", p[i].pid, p[i].t_brst);
    }

    struct process temp;
    for (int i = 0; i < n_processes; i++) // sorting according to arrival time
    {
        for (int j = 0; j < n_processes; j++)
        {
            if (p[i].t_brst < p[j].t_brst)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    // waiting time calculation
    p[0].t_w = 0;
    for (int i = 1; i < n_processes; i++)
    {
        p[i].t_w = p[i - 1].t_w + p[i - 1].t_brst;
    }
    // turn around time calculation
    for (int i = 0; i < n_processes; i++)
    {
        p[i].t_trn_arr = p[i].t_w + p[i].t_brst;
    }

    int tot_trn = 0;
    int tot_w = 0;
    float avg_t_trn_arr, avg_t_w;
    for (int i = 0; i < n_processes; i++)
    {
        tot_trn = +p[i].t_trn_arr;
        tot_w = +p[i].t_w;
    }
    avg_t_trn_arr = tot_trn / n_processes;
    avg_t_w = tot_w / n_processes;
    // printing all the parameters
    printf("\nProcess Id\t\tBrust time\t\tWaiting Time\t\tTurn Around Time");
    for (int i = 0; i < n_processes; i++)
    {
        // printf("\n\t%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d", p[i].pid, p[i].t_arv, p[i].t_brst, p[i].t_w, p[i].t_trn_arr);
        printf("\n\t%d\t\t\t%d\t\t\t%d\t\t\t%d", p[i].pid, p[i].t_brst, p[i].t_w, p[i].t_trn_arr);
    }

    printf("\nThe avarage waiting time is : %f",avg_t_w);
    printf("\nThe avarage turn around time is: %f",avg_t_trn_arr);


    return 0;
}