/*
main logic : At every time unit , select the highest priority available process and
             execute it ; if a higher priority process arrives , preempt the current
              process
*/
#include<stdio.h>

typedef struct process{
    int p_id; // process id
    int at; // arrival time
    int bt; // burst time
    int ct; // completion time
    int tat; // turn around time
    int wt; // waiting time
    int rt; // response time
    int priority; // lower priority number = higher priority
    int rem_bt; // remaining burst time of the process
    int started; // 0=process had not started, 1=process already started
}process;

int main(){

    int n; // number of processes
    int curr_time = 0; // current time of CPU
    int completed = 0; // counter for number of process completed

    float sum_tat=0, sum_wt=0, sum_rt=0;

    printf("Enter number of processes : ");
    scanf("%d",&n);
    process p[n];

    // taking AT , BT and Priority as input
    for(int i=0;i<n;i++){
        p[i].p_id = i+1;
        p[i].started=0;

        printf("Enter AT , BT and Priority of P%d : ",i+1);
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].priority);
        p[i].rem_bt = p[i].bt;  // initially remaining BT is equal to original BT
    }

    // Preemptive Priority Scheduling
    while(completed<n){
        int highdex = -1; // stores index of the process having highest priority

        // finding highest priority process among arrived and incomplete process
        for(int i=0;i<n;i++){
            if(p[i].at<=curr_time && p[i].rem_bt>0){
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
        // if no process has arrived CPU remaind idle and time increases
        if(highdex==-1) curr_time++;
        else{
            if(p[highdex].started==0){ // for response time calculation
                p[highdex].rt = curr_time - p[highdex].at;
                p[highdex].started = 1;
            }
            p[highdex].rem_bt--;
            curr_time++;
            if(p[highdex].rem_bt==0){ // if remaining burst time is 0 , then process is completed
                p[highdex].ct = curr_time;
                p[highdex].tat = p[highdex].ct - p[highdex].at;
                p[highdex].wt = p[highdex].tat - p[highdex].bt;

                completed++; 

                sum_tat+=p[highdex].tat;
                sum_wt+=p[highdex].wt;
                sum_rt+=p[highdex].rt;
            }
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
