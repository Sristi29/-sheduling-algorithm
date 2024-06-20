#include <iostream>
#include <algorithm>
using namespace std;

struct Process
{
    int pid;
    int bt;
    int wt;
    int tat;
};

void findWaitingTime(Process proc[], int n)
{
    proc[0].wt = 0;

    for (int i = 1; i < n; i++)
    {
        proc[i].wt = proc[i - 1].bt + proc[i - 1].wt;
    }
}

void findTurnAroundTime(Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

bool comparison(Process a, Process b)
{
    return (a.bt < b.bt);
}

void findAverageTime(Process proc[], int n)
{
    sort(proc, proc + n, comparison);

    findWaitingTime(proc, n);

    findTurnAroundTime(proc, n);

    cout << "Processes   Burst time   Waiting time   Turn around time\n";

    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        cout << "   " << proc[i].pid << "\t\t" << proc[i].bt << "\t    " << proc[i].wt << "\t\t  " << proc[i].tat << endl;
    }

    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << " \nAverage turn around time = " << (float)total_tat / (float)n;
}

int main()
{
    Process proc[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);

    findAverageTime(proc, n);
    return 0;
}
