#include <stdio.h>
#include <stdlib.h>
struct Process {
    int priority;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void calculateWaitingTurnaroundTime(struct Process processes[], int n, int time_quantum) {
    int remaining_time[n],i;
    for ( i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }
    int time = 0;
    int complete = 0;
    int current_priority = -1;

    while (complete < n) {
    	int i;
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && remaining_time[i] > 0) {
                if (current_priority == -1 || processes[i].priority < current_priority) {
                    current_priority = processes[i].priority;
                    if (remaining_time[i] > time_quantum) {
                        time += time_quantum;
                        remaining_time[i] -= time_quantum;
                    } else {
                        time += remaining_time[i];
                        processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
                        processes[i].turnaround_time = time - processes[i].arrival_time;
                        remaining_time[i] = 0;
                        complete++;
                        current_priority = -1;
                    }
                }
            }
        }
    }
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    
    int i;
    for (i = 0; i < n; i++) {
        printf("Enter priority, arrival time, and burst time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].priority, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculateWaitingTurnaroundTime(processes, n, time_quantum);


    printf("Process\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int j;
	for (j = 0; j < n; j++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", j + 1, processes[j].priority, processes[j].arrival_time,
               processes[j].burst_time, processes[j].waiting_time, processes[j].turnaround_time);
    }

    return 0;
}
