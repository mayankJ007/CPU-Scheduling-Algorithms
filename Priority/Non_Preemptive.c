#include<stdio.h>
#include<limits.h>

typedef struct process {
    int p_id; // process id
    int at; // arrival time
    int bt; // burst time
    int ct; // completion time
    int tat;  // turn around time
    int wt; // waiting time
    int rt; // response time
    int done; // 0=not completed , 1=completed
    int priority; 
}process;


int main(){

    int n; // number of processes
    int curr_time = 0; // current CPU time
    int completed = 0; // counter for number of process completed

    float sum_tat=0, sum_wt=0, sum_rt=0;

    printf("Enter number of processes : ");
    scanf("%d",&n);
    process p[n];

    // input AT, BT and Priority
    for(int i=0;i<n;i++){
        p[i].p_id = i+1; // assigning process id
        p[i].done = 0; // initially no process is completed , hence 0

        printf("Enter AT , BT and priority of P%d : ",i+1);
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
    }

    // Priority Scheduling (Non Preemptive)
    while(completed<n){
        int highdex = -1; // index of highest priority process selected till now
        // Find highest priority among arrived processes
        for(int i=0;i<n;i++){
            if(p[i].at<=curr_time && p[i].done==0){
                if(highdex==-1 || p[i].priority<p[highdex].priority){
                    highdex = i;
                }
                // if priority is same , process with earlier AT will be selected, 
                // also if AT of two process will be same then currently running process will continue
                else if(p[i].priority==p[highdex].priority && p[i].at < p[highdex].at){
                    highdex = i;
                }
            }
        }
        if(highdex==-1){    // if no process has arrived yet , CPU remains idle and time
            curr_time++;
        }
        else{
            p[highdex].rt = curr_time - p[highdex].at;
            curr_time += p[highdex].bt;
            p[highdex].ct = curr_time;
            p[highdex].tat = p[highdex].ct - p[highdex].at;
            p[highdex].wt = p[highdex].tat - p[highdex].bt;
            p[highdex].done = 1;
            completed++;

            sum_tat+=p[highdex].tat;
            sum_wt+=p[highdex].wt;
            sum_rt+=p[highdex].rt;
        }
    }
    // Display output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].p_id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    printf("\nAverage TAT : %.2f",sum_tat/n);
    printf("\nAverage WT = %.2f",sum_wt/n);
    printf("\nAverage RT  = %.2f\n", sum_rt / n);
    return 0;
}
