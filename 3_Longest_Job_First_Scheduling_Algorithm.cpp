#include <iostream>
#include <iomanip>
using namespace std;

class Program{
    public:
        int program_number,program_arrival_time,program_burst_time,program_completion_time,program_turnaround_time,program_waiting_time;
        void getdata(int a,int b,int c)
        {
            program_number = a;
            program_arrival_time = b;
            program_burst_time = c;
        }
};

int main()
{
    int a,b,c,size;
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

    int current_time = 0;
    bool completed[size] = {false};
    int completed_process = 0;

    while(completed_process < size)
    {
        int idx = -1;
        int max_burst_time = 0;

        for(int i = 0;i < size;i++)
        {
            if(!completed[i] && p[i].program_arrival_time <= current_time)
            {
                if(p[i].program_burst_time > max_burst_time || (p[i].program_burst_time == max_burst_time && p[i].program_arrival_time < p[idx].program_arrival_time))
                {
                    max_burst_time = p[i].program_burst_time;
                    idx = i;
                }
            }
        }

        if(idx != -1)
        {
            p[idx].program_completion_time = current_time + p[idx].program_burst_time;
            p[idx].program_turnaround_time = p[idx].program_completion_time - p[idx].program_arrival_time;
            p[idx].program_waiting_time = p[idx].program_turnaround_time - p[idx].program_burst_time;

            current_time = p[idx].program_completion_time;
            completed[idx] = true;
            completed_process++;
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
    cout << "Average Turnarounf Time: " << avg_turnaround_time / size << endl;
    cout << "Average Waiting TIme: " << avg_waiting_time / size << endl;
}