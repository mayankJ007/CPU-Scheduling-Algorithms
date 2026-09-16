/*
SJF ka main rule :
                    Current time par jo processes available hain, unmein se jiski BT sabse kam hai, usko execute karo.
*/
#include<stdio.h>
#include<limits.h>

// structure to store process information
typedef struct Process{
    int p_id; // process id
    int at; // arrival time
    int bt; // burst time
    int ct; // completion time
    int tat; // turn around time
    int wt; // waiting time
}Process;

int main(){

    int n; // number of processes
    printf("Enter number of processes : ");
    scanf("%d",&n);
    Process p[n];

    int completed = 0; // counter for number of process completed
    int curr_time = 0; // current CPU time
    int sum_tat = 0 , sum_wt = 0; // sum of turn around time and waiting time
    int done[n]; // 0 = process not completed , 1 = completed
    for(int i=0;i<n;i++) done[i] = 0;

    // Input process details
    for(int i=0;i<n;i++){
        p[i].p_id = i+1; // assign process ID

        printf("Enter arrival time and burst time pf P%d",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }

    // SJF scheduling
    while(completed<n){ // while all the processes are not completed
        int mindex = -1; // index of selected shortest process
        int min_bt = INT_MAX; // smallest burst time found

        // find shortest available process
        for(int i=0;i<n;i++){
            // check if process has arrived and is not completed
            if(p[i].at <= curr_time && done[i]==0){
                if(p[i].bt < min_bt){
                    min_bt = p[i].bt; // store smallest BT
                    mindex = i; // store process index
                }
            }
        }

        // if no process is available at current time
        if(mindex==-1) curr_time++; // CPU remains idle , move time foreward
        else{ // Execute the selected process completely
            curr_time+=p[mindex].bt;
            p[mindex].ct = curr_time;
            p[mindex].tat = p[mindex].ct - p[mindex].at;
            p[mindex].wt = p[mindex].tat - p[mindex].bt;

            sum_tat+=p[mindex].tat;
            sum_wt+=p[mindex].wt;

            done[mindex] = 1; // mark process as completed
            completed++;
        }
    }

    // Display output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].p_id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\nAverage TAT : %.2f",(float)sum_tat/n);
    printf("\nAverage WT = %.2f",(float)sum_wt/n);

    return 0;
}
