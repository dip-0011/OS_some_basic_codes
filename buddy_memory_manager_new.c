#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//int id = 0;
struct node
{
    int sz;           // size of the process
    int ac_sz;        // actual size
    int p_id;         // name of the node
    struct node *lnk; // link to next node
};

struct node *node_fst = NULL;

int chk_pow(int num);
int find_num(int num);
void ins_proc(int loc, int memac, int mem_req);
int seg_alloc(int tot_mem, int req_mem, int id);
int deletion(int p_id);
void details(int id);
void printmemory();

int chk_pow(int num)
{
    if (num <= 0)
    {
        return 0;
    }
    while (num % 2 == 0)
    {
        num /= 2;
    }
    return num == 1;
}

int find_num(int num)
{
    int n, num_f;
    for (int i = 0; num > pow(2, i); i++)
    {
        n = i + 1;
    }
    num_f = pow(2, n);
    return num_f;
}

int seg_alloc(int tot_mem, int req_mem, int id)
{
    int size = tot_mem;
    int size1 = find_num(req_mem);

    if (req_mem > tot_mem)
    {
        printf("Memory allocation is not possible!!!");
        exit(1);
    }
    while (1)
    {
        if (req_mem <= size && req_mem > (size / 2))
        {
            ins_proc(id, size1, req_mem);
            tot_mem = tot_mem - size1;
            break;
        }
        else // checks where the process fits
        {
            size = size / 2;
        }
    }
    return tot_mem;
}

void ins_proc(int loc, int memac, int mem_req)
{
    int cur_loc = 1;
    struct node *temp = node_fst;
    struct node *temp_p = NULL;
    struct node *new = (struct node *)malloc(sizeof(struct node *));
    // creating the new node
    new->sz = mem_req;
    new->ac_sz = memac;
    new->p_id = loc;
    new->lnk = NULL;

    if (loc == 1)
    {
        new->lnk = node_fst;
        node_fst = new;
    }
    else
    {
        while (cur_loc < loc)
        {
            temp_p = temp;
            temp = temp->lnk;
            // if (temp == NULL)
            // {
            //     temp->ac_sz = 0;
            //     temp->sz = 0;
            //     temp->p_id = cur_loc;
            //     temp->lnk = NULL;
            // }
            cur_loc++;
        }
        temp_p->lnk = new;
        new->lnk = temp;
    }
    return;
}

int deletion(int p_id)
{
    int rec_mem;
    struct node *temp;
    if (p_id == 1)
    {
        temp = node_fst;
        rec_mem = temp->ac_sz;
        node_fst = node_fst->lnk;
        free(temp);
    }
    else
    {
        int cur_loc = 1; // current location

        struct node *temp_p = NULL; // previous node
        temp = node_fst;
        while (cur_loc < p_id)
        {
            temp_p = temp;
            temp = temp->lnk;
            cur_loc++;
        }
        temp_p->lnk = temp->lnk;
        rec_mem = temp->ac_sz;
        free(temp);
    }
    return rec_mem;
}

void details(int id)
{
    struct node *temp = node_fst;
    while (temp != NULL)
    {
        if (temp->p_id == id)
        {
            printf("\nThe size of the process is %d", temp->sz);
            printf("\nThe process is occupying %d unit of the memory", temp->ac_sz);
            break;
        }
        temp = temp->lnk;
    }
    return;
}

void printmemory() // printing the memory structure
{
    struct node *temp = node_fst;
    printf("\n");
    while (temp != NULL)
    {
        printf("process id %d--->", temp->p_id);
        temp = temp->lnk;
    }
    return;
}

int main()
{
    int tot_size, req_size, ch, p_id;
    int recv_mem;

    printf("\nBuddy System initiation!!");
    printf("\nEnter the total size of the memory: ");
    scanf("%d", &tot_size);

    if (!chk_pow(tot_size))
    {
        printf("Error!! Not correct memory size!! Buddy System failed!!");
        exit(1);
    }

    do
    {
        printf("\n\nUser actions: ");
        printf("\nOpt1: Allocate memory to a new process.");
        printf("\nOpt2: Delete a process.");
        printf("\nOpt3. Print the current memory map.");
        printf("\nOpt4: Print details of a process.");
        printf("\nOpt5. Quit the program.");
        printf("\nChoose your action:");

        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("\nStarting memory allocation");
            printf("\nEnter size of the process: ");
            scanf("%d", &req_size);
            printf("\nEnter the process id: ");
            scanf("%d", &p_id);
            tot_size = seg_alloc(tot_size, req_size, p_id);
            printf("\nThe process is successfully allocated.");
            printf("\nRemaining memory size: %d", tot_size);
            break;

        case 2:
            printf("\nStarting the process deletion procedure.");
            printf("\nEnter the process id: ");
            scanf("%d", &p_id);
            recv_mem = deletion(p_id);
            tot_size = tot_size + recv_mem;
            printf("\nThe process is successfully deleted.");
            printf("\nCurrent memory size: %d", tot_size);
            break;

        case 3:
            printf("\nPrinting the current memory map......");
            printmemory();
            printf("\nSuccessfully printed the memory map.");
            break;

        case 4:
            printf("\nTo print the information put the Process id: ");
            scanf("%d", &p_id);
            details(p_id);
            printf("\nSuccessfully printed the details of process with id %d.", p_id);
            break;

        default:
            if(ch!=5)
                printf("\nNo such option!! Error!! Error!!");
            break;
        }
    } while (ch != 5);
    return 0;
}
