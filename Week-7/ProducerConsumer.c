#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5;   // buffer size
int x = 0;

// wait (P) operation
void wait(int *s)
{
    (*s)--;
}

// signal (V) operation
void signal(int *s)
{
    (*s)++;
}

// Producer function
void producer()
{
    if (mutex == 1 && empty != 0)
    {
        wait(&mutex);
        wait(&empty);
        wait(&full);

        x++;
        printf("Producer has produced: Item %d\n", x);

        signal(&mutex);
    }
    else
    {
        printf("Buffer is full!\n");
    }
}

// Consumer function
void consumer()
{
    if (mutex == 1 && full != 0)
    {
        wait(&mutex);
        signal(&empty);
        signal(&full);

        printf("Consumer has consumed: Item %d\n", x);
        x--;

        signal(&mutex);
    }
    else
    {
        printf("Buffer is empty!\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\nEnter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            producer();
            break;

        case 2:
            consumer();
            break;

        case 3:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
