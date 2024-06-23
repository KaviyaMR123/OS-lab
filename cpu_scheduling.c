#include <stdio.h>
#include<stdlib.h> 
struct process
{
    int at;      
    int bt;     
    int tt;      
    int wt;     
    int ct;      
    int pid;     
    int prio;    
    int completed; 
    int st;      
    int rt;      
    int rem;     
} p[10], temp;
int n, i, j, total;
void fcfs() 
{
    total = 0;
    float avg_wt = 0, avg_tt = 0;
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (p[j].at > p[j + 1].at) 
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) 
    {
        if (total < p[i].at) 
        {
            total = p[i].at;
        }
        p[i].ct = total + p[i].bt;
        total = p[i].ct;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
    }
    printf("PID | ARR | BURST | TURN | COMP | WAIT\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].tt, p[i].ct, p[i].wt);
        avg_wt += p[i].wt;
        avg_tt += p[i].tt;
    }
    printf("\nAverage waiting time: %f", avg_wt / n);
    printf("\nAverage turnaround time: %f", avg_tt / n);
}
void sjf() 
{
    int totalburst = 0, completed = 0, currenttime = 0;
    total = 0;
    float avg_wt = 0, avg_tt = 0;
    for (i = 0; i < n; i++) 
    {
        totalburst += p[i].bt;
    }
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (p[j].at > p[j + 1].at) 
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("\nGantt Chart\n");
    for (i = 0; i < n; i++) 
    {
        p[i].completed = 0;
    }

    while (completed != n) 
    {
        int min_index = -1;
        int minimum = totalburst;
        for (i = 0; i < n; i++) 
        {
            if (p[i].at <= currenttime && p[i].completed == 0) 
            {
                if (p[i].bt < minimum) 
                {
                    minimum = p[i].bt;
                    min_index = i;
                }
                if (p[i].bt == minimum) 
                {
                    if (p[i].at < p[min_index].at) 
                    {
                        minimum = p[i].bt;
                        min_index = i;
                    }
                }
            }
        }
        if (min_index == -1) 
        {
            currenttime++;
        }
        else 
        {
            p[min_index].st = currenttime;
            p[min_index].ct = p[min_index].st + p[min_index].bt;
            p[min_index].tt = p[min_index].ct - p[min_index].at;
            p[min_index].wt = p[min_index].tt - p[min_index].bt;
            completed++;
            p[min_index].completed = 1;
            currenttime = p[min_index].ct;
            avg_wt += p[min_index].wt;
            avg_tt += p[min_index].tt;
            printf("|p%d|%d", p[min_index].pid, p[min_index].ct);
        }
    }
    printf("\nPID\t ARR\t BURST\t COMP\t TURN\t WAIT\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }
    printf("\nAverage waiting time: %f", avg_wt / n);
    printf("\nAverage turnaround time: %f", avg_tt / n);
}
void priority() 
{
    float avg_wt = 0, avg_tt = 0;
    for (i = 0; i < n; i++) 
    {
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (p[j].at > p[j + 1].at) 
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("\nGantt Chart\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d ", p[i].pid);
    }
    printf("\n");
    int completed = 0, currenttime = 0;
    while (completed != n) 
    {
        int max_priority = 10000;
        int min_index = -1;
        for (i = 0; i < n; i++) 
        {
            if (p[i].at <= currenttime && p[i].completed == 0) 
            {
                if (p[i].prio < max_priority) 
                {
                    max_priority = p[i].prio;
                    min_index = i;
                }
            }
        }
        if (min_index == -1) 
        {
            currenttime++;
        } else 
        {
            p[min_index].st = currenttime;
            p[min_index].ct = p[min_index].st + p[min_index].bt;
            completed++;
            p[min_index].tt = p[min_index].ct - p[min_index].at;
            p[min_index].wt = p[min_index].tt - p[min_index].bt;
            currenttime = p[min_index].ct;
            avg_wt += p[min_index].wt;
            avg_tt += p[min_index].tt;
            printf("|p%d|%d", p[min_index].pid, p[min_index].ct);
            p[min_index].completed = 1;
        }
    }
    printf("\nPID\t PRIOR\t ARR\t BURST\t COMP\t TURN\t WAIT\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].prio, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }
    printf("\nAverage waiting time: %f", avg_wt / n);
    printf("\nAverage turnaround time: %f", avg_tt / n);
}
void roundrobin() 
{
    int slice, time = 0, remain, flag = 0;
    float avg_wt = 0, avg_tt = 0;
    printf("\nEnter the time slice: ");
    scanf("%d", &slice);
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (p[j].at > p[j + 1].at) 
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    remain = n;
    for (i = 0; i < n; i++) 
    {
        p[i].rem = p[i].bt;
        p[i].completed = 0;
    }
    printf("\nPID\t ARR \t BURST \t TURN \t COMP \t WAIT\n");
    for (time = 0, i = 0; remain != 0;) 
    {
        if (p[i].rem <= slice && p[i].rem > 0) 
        {
            time += p[i].rem;
            p[i].rem = 0;
            flag = 1;
        }
        else if (p[i].rem > 0)
        {
            p[i].rem -= slice;
            time += slice;
        }
        if (p[i].rem == 0 && flag == 1) 
        {
            remain--;
            p[i].ct = time;
            p[i].tt = p[i].ct - p[i].at;
            p[i].wt = p[i].tt - p[i].bt;
            avg_tt += p[i].tt;
            avg_wt += p[i].wt;
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].tt, p[i].ct, p[i].wt);
            flag = 0;
        }
        if (i == n - 1)
        {
            i = 0;
        }
        else if (p[i + 1].at <= time) 
        {
            i++;
        }
        else 
        {
            i = 0;
        }
    }
    printf("\nAverage turnaround time: %f", avg_tt / n);
    printf("\nAverage waiting time: %f", avg_wt / n);
}
int main() 
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) 
    {
        printf("\nEnter the PID, Arrival time, Burst time, Priority (in order): ");
        scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].prio);
    }
    printf("\nFIRST COME FIRST SERVE\n");
    fcfs();
    printf("\nSHORTEST JOB FIRST\n");
    sjf();
    printf("\nPRIORITY\n");
    priority();
    printf("\nROUND ROBIN\n");
    roundrobin();
    return 0;
}
