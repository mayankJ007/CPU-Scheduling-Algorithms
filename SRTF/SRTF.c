/*
main idea of SRTF : Har moment CPU check karta hai ki available processes mein kis process ka remaining burst time sabse kam hai.
*/

#include<stdio.h>
#include<limits.h>

typedef struct Process{
    int p_id; // process id;
    int at; // arrival time
    int bt; // burst time
    int rem_bt; // remaining burst time
    int ct; // completion time
    int tat; // turn around time 
    int wt; // waiting time
    int rt; // response time

    int started; // 0 = process ko CPU nahi mila
                 // 1 = process ko pehli baar CPU mil chuka hai 
}process;

int main(){

    int n;
    int curr_time = 0; // current CPU time
    int completed = 0; // counter for number of process completed till time
    float sum_tat = 0 , sum_wt = 0 , sum_rt = 0; // sum of total TAT , WT and RT

    printf("Enter number of processes : ");
    scanf("%d",&n);
    process p[n];

    // Input process details
    for(int i=0;i<n;i++){
        p[i].p_id = i+1;    // assign process id
        p[i].started = 0;   // Initially process do not have cpu

        printf("Enter AT and BT of P%d : ",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].rem_bt = p[i].bt;  // starting mai remaining burst time or burst time same hoga         
    }

    // SRTF(smallest remaining time first) scheduling 
    while(completed<n){ // while all the processes are not completed
        int mindex = -1; // index of selected shortest process
        int remaining_bt = INT_MAX; // smallest remaining time of selected process till now

        // find available process having smallest bt 
        for(int i=0;i<n;i++){
            if(p[i].at<=curr_time && p[i].rem_bt>0){
                if(p[i].rem_bt < remaining_bt){
                    remaining_bt = p[i].rem_bt;
                    mindex = i;
                }
            }
        }

        // if no process is available at current time
        if(mindex==-1) curr_time++; // CPU remains idle , move time foreward
        else{ //process is available execute it 
            if(p[mindex].started==0){ // started = 0 -> → First time CPU mil raha hai.
                p[mindex].rt = curr_time - p[mindex].at; // calculate response time
                p[mindex].started = 1; // process has started
            }
            p[mindex].rem_bt--; // decrease remaining burst time
            curr_time++; // 1 unit time is passed

            if(p[mindex].rem_bt==0){ // process is completely finished
                p[mindex].ct = curr_time; // then current time is completion time
                p[mindex].tat = p[mindex].ct - p[mindex].at;
                p[mindex].wt = p[mindex].tat - p[mindex].bt;

                sum_tat +=p[mindex].tat;
                sum_wt += p[mindex].wt;
                sum_rt += p[mindex].rt;

                completed++; 
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
