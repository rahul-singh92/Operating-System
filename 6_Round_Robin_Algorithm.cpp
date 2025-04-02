#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;

class Program
{
    public:
        int program_number, program_arrival_time, program_burst_time, program_completion_time, program_turnaround_time, program_waiting_time, remaining_burst_time;
        void getdata(int a, int b, int c)
        {
            program_number = a;
            program_arrival_time = b;
            program_burst_time = c;
            remaining_burst_time = c;
        }
};

int main()
{
    int a,b,c,size,quantum;
    float avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    cout<<"Enter the number of processes: ";
    cin>>size;
    Program p[size];

    for(int i = 0;i < size;i++)
    {
        cout << "Enter the process number: ";
        cin >> a;
        cout << "Enter the arrival time of " << a << " process: ";
        cin >> b;
        cout << "Enter the burst time of " << a << " process: ";
        cin >> c;
        p[i].getdata(a, b, c);
    }

    cout<<"Enter the time quantum: ";
    cin>>quantum;

    int current_time = 0;
    queue<int> ready_queue;
    bool completed[size] = {false};
    int completed_processes = 0;

    sort(p, p + size, [](Program a, Program b)
    {
        return a.program_arrival_time < b.program_arrival_time;
    });
    
    int i = 0;
    while(completed_processes < size)
    {
        while(i < size && p[i].program_arrival_time <= current_time)
        {
            ready_queue.push(i);
            i++;
        }
        if(!ready_queue.empty())
        {
            int idx = ready_queue.front();
            ready_queue.pop();

            int time_slice = min(quantum, p[idx].remaining_burst_time);
            p[idx].remaining_burst_time -= time_slice;
            current_time += time_slice;

            if(p[idx].remaining_burst_time == 0)
            {
                p[idx].program_completion_time = current_time;
                +-p[idx].program_turnaround_time = p[idx].program_completion_time - p[idx].program_arrival_time;
                p[idx].program_waiting_time = p[idx].program_turnaround_time - p[idx].program_burst_time;

                completed[idx] = true;
                completed_processes++;
            }
            else
            {
                ready_queue.push(idx);
            }
        }
        else
        {
            current_time++;
        }
    }

    cout << left << setw(15) << "Program Number"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time"
         << endl;

    for (int i = 0; i < size; i++)
    {
        avg_turnaround_time += p[i].program_turnaround_time;
        avg_waiting_time += p[i].program_waiting_time;

        cout << left << setw(15) << p[i].program_number
             << setw(15) << p[i].program_arrival_time
             << setw(15) << p[i].program_burst_time
             << setw(20) << p[i].program_completion_time
             << setw(20) << p[i].program_turnaround_time
             << setw(15) << p[i].program_waiting_time
             << endl;
    }

    cout << "Average Turnaround Time: " << avg_turnaround_time / size << endl;
    cout << "Average Waiting Time: " << avg_waiting_time / size << endl;
}
