#include <iostream>
#include <iomanip>
using namespace std;
class program{
    public:
        int program_number,program_arrival_time,program_burst_time,program_completion_time,program_turnaround_time,program_waiting_time;
        void getdata(int a, int b, int c)
        {
            program_number = a;
            program_arrival_time = b;
            program_burst_time = c;
        }
};

int main()
{
    int a,b,c,d,size;
    float avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    cout<<"Enter the number of processes: ";
    cin>>size;
    program p[size];
    for(int i = 0; i < size; i++)
    {
        cout<<"Enter the process number: ";
        cin>>a;
        cout<<"Enter the arrival time of "<<a<<" process: ";
        cin>>b;
        cout<<"Enter the burst time of "<<a<<" process: ";
        cin>>c;
        p[i].getdata(a,b,c);
    }

    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0;j < size - i - 1; j++)
        {
            if(p[j].program_arrival_time > p[j+1].program_arrival_time)
            {
                program temp;
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    p[0].program_completion_time = p[0].program_arrival_time + p[0].program_burst_time;
    for(int i = 1; i < size; i++)
    {
        p[i].program_completion_time = p[i-1].program_completion_time + p[i].program_burst_time;
    }
    for(int i = 0; i < size; i++)
    {
        p[i].program_turnaround_time = p[i].program_completion_time - p[i].program_arrival_time;
        p[i].program_waiting_time = p[i].program_turnaround_time - p[i].program_burst_time;
    }

    cout<<left<<setw(15)<<"Process Number"
              <<setw(15)<<"Arrival Time"
              <<setw(15)<<"Burst Time"
              <<setw(20)<<"Completion Time"
              <<setw(15)<<"Turnaround Time"
              <<setw(15)<<"Waiting Time"
              <<endl;
    for(int i = 0; i < size; i++)
    {
        avg_turnaround_time += p[i].program_turnaround_time;
        avg_waiting_time += p[i].program_waiting_time;
        cout<<left<<setw(15)<<p[i].program_number
                  <<setw(15)<<p[i].program_arrival_time
                  <<setw(15)<<p[i].program_burst_time
                  <<setw(20)<<p[i].program_completion_time
                  <<setw(15)<<p[i].program_turnaround_time
                  <<setw(15)<<p[i].program_waiting_time
                  <<endl;
    }
    cout<<"Average Turnaround Time: "<<avg_turnaround_time/size<<endl;
    cout<<"Average Waiting Time: "<<avg_waiting_time/size<<endl;
    return 0;
}
