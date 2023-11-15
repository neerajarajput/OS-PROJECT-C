#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

int wt[100], bt[100], at[100], tat[100], n, p[100];
float awt[5], atat[5];

void create_file_csv(char *filename, int a[][2], int n, int m) {
    printf("\n Creating %s.csv file", filename);
    FILE *fp;
    int i, j;
    filename = strcat(filename, ".csv");
    fp = fopen(filename, "w+");
    fprintf(fp, "FCFS, SJF, RR, SRTF, Innovative Algo");
    for (i = 0; i < m; i++) {
        fprintf(fp, "\n%d", i + 1);
        for (j = 0; j < n; j++)
            fprintf(fp, ",%d ", a[i][j]);
    }
    fclose(fp);
    printf("\n %s file created", filename);
}

void input() {
    printf("Enter Number of processes:");
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
        p[i] = i + 1;
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time of process %d:", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter Arrival Time of process %d:", i + 1);
        scanf("%d", &at[i]);
    }
    for (i = 0; i < 5; i++) {
        awt[i] = 0.0;
        atat[i] = 0.0;
    }
}

void changeArrival() {
    int a = at[0];
    int i;
    for (i = 0; i < n; i++) {
        if (at[i] < a)
            a = at[i];
    }
    if (a != 0) {
        for (i = 0; i < n; i++)
            at[i] = at[i] - a;
    }
}

void fcfs() {
    wt[0] = 0;
    tat[0] = bt[0];
    int i;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
    }
    awt[0] = (float)wt[n - 1] / n;
    atat[0] = (float)tat[n - 1] / n;

    // Display results
    printf("P No.\tAT\tBT\tWT\tTAT\n\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], wt[i], tat[i]);
    }
}

void sjf() {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0];
    int total_wt = wt[0], total_tat = tat[0];
    for (i = 1; i < n; i++) {
        wt[i] = total_wt;
        total_wt += bt[i];
        tat[i] = total_tat + bt[i];
        total_tat += tat[i];
    }

    awt[1] = (float)total_wt / n;
    atat[1] = (float)total_tat / n;

    // Display results
    printf("P No.\tAT\tBT\tWT\tTAT\n\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], wt[i], tat[i]);
    }
}

void rr() {
    int i, total = 0, x, counter = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, temp[100];
    x = n;

    for (i = 0; i < n; i++) {
        temp[i] = bt[i];
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &time_quantum);

    printf("\nP No.\tBT\tTAT\tWT\n\n");
    for (total = 0, i = 0; x != 0;) {
        if (temp[i] <= time_quantum && temp[i] > 0) {
            total = total + temp[i];
            temp[i] = 0;
            counter = 1;
        } else if (temp[i] > 0) {
            temp[i] = temp[i] - time_quantum;
            total = total + time_quantum;
        }

        if (temp[i] == 0 && counter == 1) {
            printf("P[%d]\t%d\t%d\t%d\n", i + 1, bt[i], total - at[i], total - at[i] - bt[i]);
            wait_time = wait_time + total - at[i] - bt[i];
            turnaround_time = turnaround_time + total - at[i];
            counter = 0;
        }

        if (i == n - 1) {
            i = 0;
        } else if (at[i + 1] <= total) {
            i++;
        } else {
            i = 0;
        }
        
    }
    
    awt[2] = (float)wait_time / n;
    atat[2] = (float)turnaround_time / n;
    
}

void srtf() {
    int i, x[10], b[10], count = 0, time, smallest;
    double avg = 0, tt = 0, end;

    for (i = 0; i < n; i++) {
        x[i] = bt[i];
    }

    bt[9] = 9999;

    for (time = 0; count != n; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && bt[i] < bt[smallest] && bt[i] > 0)
                smallest = i;
        }

        bt[smallest]--;
        if (bt[smallest] == 0) {
            count++;
            end = time + 1;
            avg = avg + end - at[smallest] - x[smallest];
            tt = tt + end - at[smallest];
        }
    }

    atat[3] = tt / n;
    awt[3] = avg / n;
}

void innovative() {
    int bt1[n], i, j, temp, tq;
    int b[n];
    float twt = 0, ttat = 0;

    for (i = 0; i < n; i++) {
        bt1[i] = bt[i];
    }

    for (i = 0; i < n; i++) {
        b[i] = bt[i];
    }

    int num = n;
    int time = 0;
    int max;
    int sum, t, a, ap;
    ap = 0;

    // Stage 1: Sort processes based on burst time in ascending order
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (b[i] < b[j] && at[i] <= time) {
                temp = p[j];
                p[j] = p[i];
                p[i] = temp;

                temp = at[j];
                at[j] = at[i];
                at[i] = temp;

                temp = bt1[j];
                bt1[j] = bt1[i];
                bt1[i] = temp;
            }
        }
    }

    // Stage 2: Calculate Smart time quantum
    sum = 0;
    a = 0;
    max = 0;

    for (i = 0; i < n; i++) {
        if (at[i] <= time && b[i] != 0) {
            a++;
            if (b[i] > max) {
                max = b[i];
            }
            sum += b[i];
        }
    }

    tq = (sqrt((sum / a) * max) + max) / 2;
    ap = a;

    // Stage 3: Execute processes
    while (num > 0) {
        a = 0;

        // Sorting in ascending order
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (b[i] < b[j] && at[i] <= time) {
                    temp = p[j];
                    p[j] = p[i];
                    p[i] = temp;

                    temp = at[j];
                    at[j] = at[i];
                    at[i] = temp;

                    temp = bt1[j];
                    bt1[j] = bt1[i];
                    bt1[i] = temp;
                }
            }
        }

        t = 0;

        // Execute processes
        for (i = 0; i < n; i++) {
            if (at[i] <= time && b[i] != 0) {
                if (b[i] < tq) {
                    // Execute process for less than Smart time quantum
                    t += b[i];
                    bt1[i] = 0; // Update remaining burst time
                } else {
                    // Execute process for Smart time quantum
                    t += tq;
                    bt1[i] -= tq; // Update remaining burst time
                }

                // If process is completed
                if (bt1[i] == 0) {
                    wt[i] = time - at[i]; // Update waiting time
                    tat[i] = wt[i] + bt[i]; // Update turnaround time
                    num--;
                }
            }
        }

        time += t;
    }

    // Stage 4: Calculate averages
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt[4] = twt / n;
    atat[4] = ttat / n;

    // Display results
    printf("P No.\tWT\tTAT\n\n");
    for (j = 1; j <= n; j++) {
        for (i = 0; i < n; i++) {
            if (j == p[i]) {
                printf("process %d\t%d\t\t%d\n", p[i], wt[i], tat[i]);
            }
        }
    }
}   

void display(int c) {
    int i;
    printf("\nAlgorithm: ");
    switch (c) {
        case 1:
            printf("FCFS\n");
            break;
        case 2:
            printf("SJF\n");
            break;
        case 3:
            printf("Round Robin\n");
            break;
        case 4:
            printf("SRTF\n");
            break;
        case 5:
            printf("Innovative Algorithm\n");
            break;
        default:
            break;
    }

    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f\n", awt[c - 1], atat[c - 1]);
}

int main() {
    printf("Welcome to CPU Scheduling:\n\n");
    input();
    int c, choice;
    changeArrival();
    printf("Choice\tAlgorithm used\n1\tFCFS Algorithm\n2\tSJF Algorithm\n3\tRound Robin\n4\tSRTF Algorithm\n5\tOur innovative algorithm\n");
    do {
        printf("Enter your choice from the above table: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                fcfs();
                break;
            case 2:
                sjf();
                break;
            case 3:
                rr();
                break;
            case 4:
                srtf();
                break;
            case 5:
                innovative();
                break;
            default:
                printf("Please enter choice from 1 to 5 only\n");
                break;
        }
        display(c);
        printf("\nEnter 1 to continue or 0 to stop: ");
        scanf("%d", &choice);
    } while (choice == 1);

    getch();
    int a[5][2], i;
    for (i = 0; i < 5; i++) {
        a[i][0] = awt[i];
        a[i][1

] = atat[i];
    }
    create_file_csv("schedule", a, 5, 2);

    return 0;
}
