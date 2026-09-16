#include<stdio.h>

typedef struct process{
    int p_id; // process id
    int at;  // arrival time
    int bt;  // burst time
    int ct;  // completion time
    int tat; // turn around time
    int wt; // waiting time
    int rt; // response time
}process;

// Bubble sort according to arrival time
void bubbleSort(process p[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(p[j].at > p[j+1].at){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main(){

    int n;
    float avg_tat , avg_wt , avg_rt , sum_tat=0 , sum_wt=0 , sum_rt=0;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    process p[n];

    // input arrival time and burst time
    for(int i=0;i<n;i++){
        p[i].p_id = i+1;

        printf("Enter arrival time and burst time of P%d : ",p[i].p_id);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }

    // sort according to arrival time
    bubbleSort(p,n);

    // calculate CT , TAT , WT
    for(int i=0;i<n;i++){
        if(i==0){ // for 1st process
            p[i].ct = p[i].at + p[i].bt;
        }
        else{
            if(p[i].at > p[i-1].ct)
                p[i].ct = p[i].at + p[i].bt;
            else // p[i].at < p[i-1].ct
                p[i].ct = p[i-1].ct + p[i].bt;
        }

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;

        sum_tat += p[i].tat;
        sum_wt  += p[i].wt;
        sum_rt  += p[i].rt;
    }

    // output
    printf("\nProcess  AT \t BT \t CT \t TAT \t WT \t RT\n");
    for(int i=0;i<n;i++){
        printf("P%d \t %d \t %d \t %d \t %d \t %d \t %d\n",p[i].p_id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    printf("\nAverage TAT : %.2f",sum_tat/n);
    printf("\nAverage WT : %.2f",sum_wt/n);
    printf("\nAverage RT : %.2f",sum_rt/n);

    return 0;
}
