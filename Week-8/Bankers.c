#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safe[n];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize finish array
    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j])
                        break;
                }

                // Process can execute
                if(j == m) {

                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    printf("\nP%d is visited (", i);

                    for(k = 0; k < m; k++) {
                        printf("%d", avail[k]);

                        if(k != m - 1)
                            printf(" ");
                    }

                    printf(")");

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    // Check Safe State
    if(count == n) {

        printf("\n\nSYSTEM IS IN SAFE STATE\n");

        printf("\nSafe Sequence is:\n");
        for(i = 0; i < n; i++) {
            printf("P%d ", safe[i]);
        }

        // Final Table
        printf("\n\n");
        printf("Process\tAllocation\tMax\t\tNeed\n");
        printf("---------------------------------------------------\n");

        for(i = 0; i < n; i++) {

            printf("P%d\t", i);

            // Allocation
            for(j = 0; j < m; j++) {
                printf("%d ", alloc[i][j]);
            }

            printf("\t\t");

            // Max
            for(j = 0; j < m; j++) {
                printf("%d ", max[i][j]);
            }

            printf("\t\t");

            // Need
            for(j = 0; j < m; j++) {
                printf("%d ", need[i][j]);
            }

            printf("\n");
        }
    }
    else {
        printf("\nSYSTEM IS NOT IN SAFE STATE");
    }

    return 0;
}
