/*
Main idea of RR : Each process gets the CPU for a fixed amount of time called the
                  Time Quantum. If the process is not completed within that time,
                  it is preempted and placed at the end of the Ready Queue.
                  The CPU then executes the next process in the queue.
*/

#include<stdio.h>

typedef struct process{
    int p_id; // process id
    int at; // arrival time
    int bt; // burst time
    int ct; // completion time
    int tat; // turn around time
    int wt; // waiting time
    int rt,started; // response time and started=0/1, if 0->process did not get cpu yet
    int rem_bt; // remaining burst time
}process;

int queue[100]; // ready queue
int f=0,r=0; // front=0 and rear=0

int main(){

    int n, tq;
    int curr_time = 0; // current CPU time
    int completed = 0; // counter for number of process completed

    float sum_tat=0, sum_wt=0, sum_rt=0;

    printf("Enter number of processes : ");
    scanf("%d",&n);
    process p[n];

    // taking input
    for(int i=0;i<n;i++){
        p[i].p_id = i+1;

        printf("Enter AT and BT of P%d : ",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);

        p[i].rem_bt = p[i].bt; // initially remaining BT = original BT
        p[i].started=0; // initially no process gets cpu
    }

    printf("Enter time quantum : ");
    scanf("%d",&tq);
    int visited[n];
    for(int i=0;i<n;i++) visited[i]=0;

    // Round Robin Scheduling Algo
    while(completed<n){
        // add newly arrived process to the ready queue.
        // visited=0 means process has not been added to the queue yet
        for(int i=0;i<n;i++){
            if(p[i].at<=curr_time && p[i].rem_bt>0 && visited[i]==0){
                queue[r++]=i;
                visited[i]=1;
            }
        }
        if(f==r){   // if ready queue is empty , no process is available
            curr_time++;
            continue;
        }

        int index = queue[f++]; // take process from the front of the queue
        if(p[index].started==0){
            p[index].rt = curr_time - p[index].at;
            p[index].started=1;
        }
        if(p[index].rem_bt > tq){
            p[index].rem_bt-=tq;    // execute for time quantum
            curr_time+=tq;
        }
        else{ // if remaining BT is equal to or less than tq . process will complete
            curr_time+=p[index].rem_bt;
            p[index].rem_bt=0;

            p[index].ct = curr_time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            completed++;
            sum_tat+=p[index].tat;
            sum_wt+=p[index].wt;
            sum_rt+=p[index].rt;
        }
        // after tq if new process have arrived, add them to the ready queue
        for(int i=0;i<n;i++){
            if(p[i].at<=curr_time && p[i].rem_bt>0 && visited[i]==0){
                queue[r++] = i;
                visited[i] =1;
            }
        }
        // also if current process is not completed yet ,then insert it at the end of the queue
        if(p[index].rem_bt>0) queue[r++]=index; 
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
