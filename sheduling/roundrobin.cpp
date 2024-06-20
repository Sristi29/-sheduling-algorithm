#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process
{
    int pid;
    int bt;
    int rem;

    Process(int id, int burst_time) : pid(id), bt(burst_time), rem(burst_time) {}
};

void roundRobin(vector<Process> &processes, int quantum)
{
    int n = processes.size();
    queue<Process> ready_queue;
    int total_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; ++i)
    {
        processes[i].rem = processes[i].bt;
        ready_queue.push(processes[i]);
    }

    while (!ready_queue.empty())
    {
        Process current_process = ready_queue.front();
        ready_queue.pop();

        int execute_time = min(quantum, current_process.rem);
        total_time += execute_time;
        current_process.rem -= execute_time;

        if (current_process.rem > 0)
        {
            ready_queue.push(current_process);
        }

        total_waiting_time += total_time - current_process.bt;
        total_turnaround_time += total_time;
    }

    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "Round Robin Scheduling (Quantum = " << quantum << ")\n";
    cout << "PID\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i)
    {
        cout << processes[i].pid << "\t" << processes[i].bt << "\t\t"
             << total_time - processes[i].bt << "\t\t" << total_time << endl;
    }
    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

int main()
{
    vector<Process> processes = {{1, 10}, {2, 5}, {3, 8}, {4, 12}};
    int quantum = 3;

    roundRobin(processes, quantum);

    return 0;
}
