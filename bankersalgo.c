#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // Maximum number of processes and resources

int r[MAX];        // Available instances of resources
int av[MAX];       // Available resources
int all[MAX][MAX]; // Allocation matrix
int max[MAX][MAX]; // Maximum matrix
int ne[MAX][MAX];  // Need matrix
int w[MAX];        // Work array
int safe[MAX];     // Safe sequence

int main()
{
    int np = 0, nr = 0, count = 0, cnt = 0;

    printf("Enter the number of processes in the system: ");
    scanf("%d", &np);
    printf("Enter the number of resources in the system: ");
    scanf("%d", &nr);

    for (int i = 0; i < nr; i++)
    {
        printf("Enter the number of instances of resource R%d: ", i + 1);
        scanf("%d", &r[i]);
        av[i] = r[i]; // Initially, available resources are the same as instances
    }

    // Initialize matrices
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            all[i][j] = max[i][j] = ne[i][j] = 0;
        }
        w[i] = 0; // Initialize work array
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            scanf("%d", &all[i][j]);
            av[j] -= all[i][j]; // Update available resources
        }
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Calculate the need matrix
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            ne[i][j] = max[i][j] - all[i][j];
        }
    }

    // Print process details
    for (int i = 0; i < np; i++)
    {
        printf("Process P%d:\n", i + 1);
        for (int j = 0; j < nr; j++)
        {
            printf("Allocated: %d\t", all[i][j]);
            printf("Maximum: %d\t", max[i][j]);
            printf("Need: %d\n", ne[i][j]);
        }
        printf("\n");
    }

    printf("Availability: ");
    for (int i = 0; i < nr; i++)
    {
        printf("R%d %d\t", i + 1, av[i]);
    }
    printf("\n");

    // Safe sequence calculation
    printf("Safe sequence: ");
    for (count = 0; count < np; count++)
    {
        for (int i = 0; i < np; i++)
        {
            cnt = 0;
            for (int j = 0; j < nr; j++)
            {
                if (ne[i][j] <= av[j] && w[i] == 0)
                {
                    cnt++;
                }
            }
            if (cnt == nr)
            {
                safe[count] = i + 1; // Store safe sequence
                for (int l = 0; l < nr; l++)
                {
                    av[l] += all[i][l]; // Update available resources
                }
                printf("P%d ", safe[count]);
                w[i] = 1; // Mark process as finished
            }
        }
    }

    printf("\n");
    return 0; // Explicit return statement
}
