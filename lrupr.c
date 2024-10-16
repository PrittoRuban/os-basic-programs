#include <stdio.h>

int arrmin(int[], int);

int main()
{
    int i, j, len, rs[50], frame[10], nf, k, avail, count = 0;
    int access[10], freq = 0, dm;

    // Input the length of reference string and reference string
    printf("Length of Reference string : ");
    scanf("%d", &len);
    printf("Enter reference string :\n");
    for (i = 0; i < len; i++)
        scanf("%d", &rs[i]);

    // Input the number of frames
    printf("Enter no. of frames : ");
    scanf("%d", &nf);

    // Initialize frame array and access array
    for (i = 0; i < nf; i++)
    {
        frame[i] = -1; // -1 means empty frame
        access[i] = 0; // Initialize access times
    }

    j = 0;
    printf("\nRef. str Page frames");

    // Page replacement simulation
    for (i = 0; i < len; i++)
    {
        printf("\n%4d\t", rs[i]);
        avail = 0;

        // Check if page is already in one of the frames
        for (k = 0; k < nf; k++)
        {
            if (frame[k] == rs[i])
            {
                avail = 1;
                access[k] = ++freq; // Update access time
                break;
            }
        }

        // If page is not available in frame, we need to replace it
        if (avail == 0)
        {
            dm = 0;

            // Check for an empty frame
            for (k = 0; k < nf; k++)
            {
                if (frame[k] == -1)
                {
                    frame[k] = rs[i];
                    access[k] = ++freq; // Mark it as accessed
                    count++;
                    dm = 1; // Mark as inserted in an empty frame
                    break;
                }
            }

            // If no empty frame is available, replace the least recently used one
            if (dm == 0)
            {
                j = arrmin(access, nf); // Get the frame to be replaced
                frame[j] = rs[i];       // Replace the page
                access[j] = ++freq;     // Update access time
                count++;
            }

            // Display the current state of frames
            for (k = 0; k < nf; k++)
                printf("%4d", frame[k]);
        }
    }

    printf("\n\nTotal no. of page faults : %d\n", count);

    return 0;
}

// Function to find the index of the frame with the least recent access time
int arrmin(int a[], int n)
{
    int i, min = a[0], min_index = 0;
    for (i = 1; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
            min_index = i;
        }
    }
    return min_index; // Return the index of the least recently used frame
}
