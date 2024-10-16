#include <stdio.h>

int main()
{
    int i, j, l, rs[50], frame[10], nf, k, avail, count = 0;

    // Input for length of reference string
    printf("Enter length of reference string: ");
    scanf("%d", &l);

    // Input for reference string
    printf("Enter reference string:\n");
    for (i = 1; i <= l; i++)
    {
        scanf("%d", &rs[i]);
    }

    // Input for number of frames
    printf("Enter number of frames: ");
    scanf("%d", &nf);

    // Initialize frames to -1 (indicating they are empty)
    for (i = 0; i < nf; i++)
    {
        frame[i] = -1;
    }

    j = 0; // Pointer to track which frame to replace
    printf("\nRef. str  Page frames\n");

    // Loop through the reference string
    for (i = 1; i <= l; i++)
    {
        printf("%4d\t", rs[i]);

        avail = 0; // Check if the current page is already in a frame

        for (k = 0; k < nf; k++)
        {
            if (frame[k] == rs[i])
            {
                avail = 1; // Page is already in memory
                break;
            }
        }

        if (avail == 0)
        {                     // Page fault occurs if the page is not found in memory
            frame[j] = rs[i]; // Replace the oldest page (FIFO)
            j = (j + 1) % nf; // Update the frame pointer for the next replacement
            count++;          // Increase page fault count

            // Print current frame status
            for (k = 0; k < nf; k++)
            {
                if (frame[k] != -1)
                    printf("%4d", frame[k]);
                else
                    printf("   -");
            }
        }
        printf("\n");
    }

    // Output total number of page faults
    printf("\nTotal number of page faults: %d\n", count);

    return 0;
}
