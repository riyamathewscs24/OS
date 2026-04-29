#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // for sleep()
#include <semaphore.h>

#define MAX 5

int hungry[MAX];        // Stores positions of hungry philosophers
int eaten[MAX] = {0};   // Tracks whether each philosopher has eaten
int hungry_count = 0;   // Total number of hungry philosophers

sem_t mutex;  // Semaphore to control eating access

// Wrapper for semaphore wait
void wait_(sem_t* s) {
    sem_wait(s);
}

// Wrapper for semaphore signal
void signal_(sem_t* s) {
    sem_post(s);
}

// Prints the list of waiting (hungry) philosophers
void print_waiting() {
    for (int i = 0; i < hungry_count; i++) {
        printf("P %d is waiting\n", hungry[i]);
    }
}

// Simulates the eating process based on allowed simultaneous eaters
void simulate_eating(int eat_limit) {
    int finished = 0;

    // Initialize semaphore with eat_limit (1 or 2)
    sem_init(&mutex, 0, eat_limit);

    // Loop until all hungry philosophers have eaten
    while (finished < hungry_count) {
        print_waiting();  // Show all waiting philosophers

        int served = 0;
        for (int i = 0; i < hungry_count && served < eat_limit; i++) {
            if (!eaten[i]) {  // If philosopher hasn't eaten yet
                wait_(&mutex);  // Acquire access
                printf("P %d is granted to eat\n", hungry[i]);

                sleep(1);  // Simulate eating time

                printf("P %d has finished eating\n", hungry[i]);
                signal_(&mutex);  // Release access

                eaten[i] = 1;  // Mark as eaten
                served++;
                finished++;
            }
        }
    }

    sem_destroy(&mutex);  // Clean up semaphore
}

int main() {
    int total_philosophers;
    int choice;

    // Input total philosophers and how many are hungry
    printf("Enter the total number of philosophers: ");
    scanf("%d", &total_philosophers);

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    // Input positions of hungry philosophers
    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, total_philosophers);
        scanf("%d", &hungry[i]);
    }

    // Menu loop for choosing eating policy
    do {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Reset eaten status before each run
        for (int i = 0; i < hungry_count; i++) {
            eaten[i] = 0;
        }

        if (choice == 1) {
            printf("Allow one philosopher to eat at any time\n");
            simulate_eating(1);  // One can eat
        } else if (choice == 2) {
            printf("Allow two philosophers to eat at any time\n");
            simulate_eating(2);  // Two can eat
        }

    } while (choice != 3);  // Exit on choice 3

    return 0;
}
