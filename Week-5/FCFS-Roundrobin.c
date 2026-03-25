#include <stdio.h>

#define MAX 20

struct Process {
    int pid;
    int at;
    int bt;
    int type; // 0 = System, 1 = User
    int ct;
    int tat;
    int wt;
};

int main() {
    struct Process p[MAX], sys[MAX], user[MAX];
    int n, i, j;
    int sc = 0, uc = 0;
    int time = 0;

    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        p[i].pid = i;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Type (0-System, 1-User): ");
        scanf("%d", &p[i].type);

        // Separate into queues
        if(p[i].type == 0)
            sys[sc++] = p[i];
        else
            user[uc++] = p[i];
    }

    // Sort System queue (FCFS → by Arrival Time)
    for(i = 0; i < sc - 1; i++) {
        for(j = i + 1; j < sc; j++) {
            if(sys[i].at > sys[j].at) {
                struct Process temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }

    // Sort User queue
    for(i = 0; i < uc - 1; i++) {
        for(j = i + 1; j < uc; j++) {
            if(user[i].at > user[j].at) {
                struct Process temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }

    // Execute System Queue (Higher Priority)
    for(i = 0; i < sc; i++) {
        if(time < sys[i].at)
            time = sys[i].at;

        time += sys[i].bt;
        sys[i].ct = time;

        sys[i].tat = sys[i].ct - sys[i].at;
        sys[i].wt = sys[i].tat - sys[i].bt;

        total_wt += sys[i].wt;
        total_tat += sys[i].tat;
    }

    // Execute User Queue (After System queue)
    for(i = 0; i < uc; i++) {
        if(time < user[i].at)
            time = user[i].at;

        time += user[i].bt;
        user[i].ct = time;

        user[i].tat = user[i].ct - user[i].at;
        user[i].wt = user[i].tat - user[i].bt;

        total_wt += user[i].wt;
        total_tat += user[i].tat;
    }

    // Output
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < sc; i++) {
        printf("P%d\t%d\t%d\tSystem\t%d\t%d\t%d\n",
               sys[i].pid, sys[i].at, sys[i].bt,
               sys[i].ct, sys[i].tat, sys[i].wt);
    }

    for(i = 0; i < uc; i++) {
        printf("P%d\t%d\t%d\tUser\t%d\t%d\t%d\n",
               user[i].pid, user[i].at, user[i].bt,
               user[i].ct, user[i].tat, user[i].wt);
    }

    // Averages
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
