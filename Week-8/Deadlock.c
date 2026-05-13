#include <stdio.h>

int main() {

    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m];
    int avail[m], finish[n];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize finish array
    for(i = 0; i < n; i++) {

        int flag = 0;

        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                flag = 1;
                break;
            }
        }

        if(flag == 1)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    int found;

    do {

        found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {

                    if(request[i][j] > avail[j])
                        break;
                }

                // Process can execute
                if(j == m) {

                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    printf("\nP%d is executed (", i);

                    for(k = 0; k < m; k++) {

                        printf("%d", avail[k]);

                        if(k != m - 1)
                            printf(" ");
                    }

                    printf(")");

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

    } while(found);

    int deadlock = 0;

    // Check deadlock
    for(i = 0; i < n; i++) {

        if(finish[i] == 0) {
            deadlock = 1;
        }
    }

    if(deadlock == 0) {

        printf("\n\nNO DEADLOCK DETECTED\n");
    }
    else {

        printf("\n\nSYSTEM IS IN DEADLOCK\n");

        printf("\nDeadlocked Processes are:\n");

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {
                printf("P%d ", i);
            }
        }
    }

    // Final Table
    printf("\n\n");
    printf("Process\tAllocation\tRequest\n");
    printf("------------------------------------------\n");

    for(i = 0; i < n; i++) {

        printf("P%d\t", i);

        // Allocation
        for(j = 0; j < m; j++) {
            printf("%d ", alloc[i][j]);
        }

        printf("\t\t");

        // Request
        for(j = 0; j < m; j++) {
            printf("%d ", request[i][j]);
        }

        printf("\n");
    }

    return 0;
}
