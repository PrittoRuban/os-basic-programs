#include <stdio.h>

struct process
{
    int size;
    int flag;
    int holeid;
} p[10];

struct hole
{
    int size;
    int actual;
} h[10];

int main()
{
    int i, np, nh, j;

    // Input the number of holes
    printf("Enter the number of Holes: ");
    scanf("%d", &nh);

    // Input the size of each hole
    for (i = 0; i < nh; i++)
    {
        printf("Enter size for hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size; // Store the actual size for reporting
    }

    // Input the number of processes
    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    // Input the size of each process
    for (i = 0; i < np; i++)
    {
        printf("Enter the size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0; // Initially, no process is allocated
    }

    // First Fit allocation
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nh; j++)
        {
            if (p[i].flag != 1)
            { // Check if the process is not yet allocated
                if (p[i].size <= h[j].size)
                {                           // Check if hole can fit the process
                    p[i].flag = 1;          // Mark process as allocated
                    p[i].holeid = j;        // Store the hole ID
                    h[j].size -= p[i].size; // Reduce the size of the hole
                    break;                  // Stop searching for holes for this process
                }
            }
        }
    }

    // Output the allocation results
    printf("\n\tFirst fit allocation\n");
    printf("\nProcess\tPSize\tHole");
    for (i = 0; i < np; i++)
    {
        if (p[i].flag != 1)
            printf("\nP%d\t%d\tNot allocated", i, p[i].size); // Process not allocated
        else
            printf("\nP%d\t%d\tH%d", i, p[i].size, p[i].holeid); // Process allocated to hole
    }

    // Output the hole status
    printf("\n\nHole\tActual\tAvailable");
    for (i = 0; i < nh; i++)
    {
        printf("\nH%d\t%d\t%d", i, h[i].actual, h[i].size); // Actual and available sizes
    }
    printf("\n");

    return 0;
}
