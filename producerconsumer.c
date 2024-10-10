#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h> // Include this header for the wait function
#include <unistd.h>   // For fork and sleep
#include <string.h>   // For memset
#define N 5           // Number of items to produce/consume
#define BUFSIZE 1     // Size of the buffer (1 for single item)
#define PERMS 0666    // Permissions for shared memory and semaphores

int *buffer;
int nextp = 0, nextc = 0; // Indices for producer and consumer
int mutex, full, empty;   // Semaphore variables

// Function to perform semaphore operation
void sem_op(int id, int value)
{
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = value;
    op.sem_flg = 0; // Set to 0 to block until the operation can be performed

    if (semop(id, &op, 1) < 0)
    {
        perror("semop failed"); // Improved error handling
        exit(1);
    }
}

// Function to create semaphore and initialize its value
void sem_create(int semid, int initval)
{
    union semun
    {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } s;
    s.val = initval;

    if (semctl(semid, 0, SETVAL, s) < 0)
    {
        perror("Error in executing semctl"); // Improved error handling
        exit(1);
    }
}

// Producer function
void producer()
{
    int data;

    // Wrap around the producer index
    if (nextp == N)
    {
        nextp = 0;
    }

    printf("Enter data for producer to produce: ");
    scanf("%d", &data);   // Read data from user
    buffer[nextp] = data; // Store data in buffer
    nextp++;
}

// Consumer function
void consumer()
{
    int g;

    // Wrap around the consumer index
    if (nextc == N)
    {
        nextc = 0;
    }

    g = buffer[nextc]; // Get data from buffer
    nextc++;
    printf("\nConsumer consumes data: %d\n", g);
}

// Wait (P) operation
void sem_wait(int id)
{
    sem_op(id, -1); // Wait operation
}

// Signal (V) operation
void sem_signal(int id)
{
    sem_op(id, 1); // Signal operation
}

int main()
{
    int shmid, i;
    pid_t pid;

    // Create shared memory
    if ((shmid = shmget(IPC_PRIVATE, BUFSIZE * sizeof(int), IPC_CREAT | PERMS)) < 0)
    {
        perror("Unable to create shared memory");
        return 1;
    }

    // Attach shared memory
    buffer = (int *)shmat(shmid, NULL, 0);
    if (buffer == (int *)-1)
    {
        perror("Shared memory allocation error");
        exit(1);
    }

    // Create semaphores
    if ((mutex = semget(IPC_PRIVATE, 1, PERMS | IPC_CREAT)) == -1)
    {
        perror("Can't create mutex semaphore");
        exit(1);
    }
    if ((empty = semget(IPC_PRIVATE, 1, PERMS | IPC_CREAT)) == -1)
    {
        perror("Can't create empty semaphore");
        exit(1);
    }
    if ((full = semget(IPC_PRIVATE, 1, PERMS | IPC_CREAT)) == -1)
    {
        perror("Can't create full semaphore");
        exit(1);
    }

    // Initialize semaphores
    sem_create(mutex, 1); // Mutex semaphore
    sem_create(empty, N); // Initially, all buffer slots are empty
    sem_create(full, 0);  // Initially, no slots are full

    // Fork process
    if ((pid = fork()) < 0)
    {
        perror("Error in process creation");
        exit(1);
    }

    if (pid > 0)
    { // Parent process (Producer)
        for (i = 0; i < N; i++)
        {
            sem_wait(empty);   // Wait for an empty slot
            sem_wait(mutex);   // Enter critical section
            producer();        // Produce an item
            sem_signal(mutex); // Leave critical section
            sem_signal(full);  // Signal that an item is produced
        }
        wait(NULL); // Wait for child process to finish
    }
    else
    { // Child process (Consumer)
        for (i = 0; i < N; i++)
        {
            sem_wait(full);    // Wait for a full slot
            sem_wait(mutex);   // Enter critical section
            consumer();        // Consume an item
            sem_signal(mutex); // Leave critical section
            sem_signal(empty); // Signal that an item is consumed
        }
        printf("\n");
    }

    // Cleanup
    if (shmdt(buffer) == -1)
    {
        perror("Error detaching shared memory");
    }
    shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
    semctl(mutex, 0, IPC_RMID);    // Remove mutex semaphore
    semctl(empty, 0, IPC_RMID);    // Remove empty semaphore
    semctl(full, 0, IPC_RMID);     // Remove full semaphore

    return 0; // Explicit return statement
}
