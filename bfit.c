#include <stdio.h>

struct process
{
    int size;
    int flag;
    int holeid;
} p[10];

struct hole
{
    int hid;
    int size;
    int actual;
} h[10];

// Function to sort holes by size (Best Fit)
void bsort(struct hole bh[], int n)
{
    struct hole temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bh[i].size > bh[j].size)
            {
                temp = bh[i];
                bh[i] = bh[j];
                bh[j] = temp;
            }
        }
    }
}

int main()
{
    int i, np, nh, j;

    // Input number of holes
    printf("Enter the number of Holes: ");
    scanf("%d", &nh);

    // Input size of each hole
    for (i = 0; i < nh; i++)
    {
        printf("Enter size for hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size; // Store actual size
        h[i].hid = i;            // Assign a hole ID
    }

    // Input number of processes
    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    // Input size of each process
    for (i = 0; i < np; i++)
    {
        printf("Enter the size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0; // Initially, process is not allocated
    }

    // Perform Best Fit allocation
    for (i = 0; i < np; i++)
    {
        bsort(h, nh); // Sort holes by size for best fit
        for (j = 0; j < nh; j++)
        {
            if (p[i].flag != 1)
            { // If process is not yet allocated
                if (p[i].size <= h[j].size)
                {                           // Check if hole can accommodate process
                    p[i].flag = 1;          // Mark process as allocated
                    p[i].holeid = h[j].hid; // Assign the hole ID
                    h[j].size -= p[i].size; // Reduce the size of the hole
                    break;                  // Exit after allocation
                }
            }
        }
    }

    // Output the results of allocation
    printf("\n\tBest fit allocation\n");
    printf("\nProcess\tPSize\tHole");
    for (i = 0; i < np; i++)
    {
        if (p[i].flag != 1)
            printf("\nP%d\t%d\tNot allocated", i, p[i].size); // Process not allocated
        else
            printf("\nP%d\t%d\tH%d", i, p[i].size, p[i].holeid); // Process allocated
    }

    // Output the status of each hole
    printf("\n\nHole\tActual\tAvailable");
    for (i = 0; i < nh; i++)
    {
        printf("\nH%d\t%d\t%d", h[i].hid, h[i].actual, h[i].size); // Actual size and available size of each hole
    }
    printf("\n");

    return 0;
}
