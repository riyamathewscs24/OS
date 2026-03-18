#include<stdio.h>

int main()
{
    int n,tq,i,time=0,remain;
    printf("Enter number of processes:");
    scanf("%d",&n);

    int at[n],bt[n],rt[n],ct[n],tat[n],wt[n];

    for(i=0;i<n;i++)
    {
        printf("Enter AT BT for P%d:",(i+1));
        scanf("%d %d",&at[i],&bt[i]);
        rt[i]=bt[i];
    }

    printf("Enter time quantum:");
    scanf("%d",&tq);

    remain=n;

    while(remain>0)
    {
        int executed=0;

        for(i=0;i<n;i++)
        {
            if(rt[i]>0 && at[i]<=time)
            {
                executed=1;

                if(rt[i]<=tq)
                {
                    time+=rt[i];
                    ct[i]=time;
                    rt[i]=0;
                    remain--;
                }
                else
                {
                    time+=tq;
                    rt[i]-=tq;
                }
            }
        }

        if(executed==0)
        {
            time++;
        }
    }

    float total_wt=0,total_tat=0;

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        total_wt+=wt[i];
        total_tat+=tat[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",(i+1),at[i],bt[i],ct[i],tat[i],wt[i]);
    }

    printf("\nAverage waiting time=%.2f", total_wt/n);
    printf("\nAverage turnaround time=%.2f\n", total_tat/n);

    return 0;
}
