#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cout << "Enter The Total Process: ";
    cin >> n;
    int process[n+1]={0},burst[n+1]={0};
    cout << "Enter The Process ID: ";
    for(int i=1; i<=n; i++){
        cin >> process[i];
    }
    cout << "Enter The Burst Time of Every Process: ";
    for(int i=1; i<=n; i++){
        cin >> burst[i];
    }
    int waiting[n+1]={0};
    for(int i=1; i<=n; i++){
        waiting[i] = burst[i-1] + waiting[i-1];
    }
    int turn[n+1]={0};
    for(int i=1; i<=n; i++){
        turn[i] = waiting[i] + burst[i];
    }
    double totalWait = 0, totalTurn = 0;
    for(int i=1; i<=n; i++){
        totalWait += waiting[i];
        totalTurn += turn[i];
    }
    double avgWait = totalWait/n;
    double avgTurn = totalTurn/n;
    cout << "Process ID\t\t Burst Time\t\t Waiting Time\t\t TurnAround Time\n";
    for(int i=1; i<=n; i++){
        cout << process[i] << "\t\t\t " << burst[i] << "\t\t\t " << waiting[i] << "\t\t\t " << turn[i] << endl;
    }
    cout << "Avg. Waiting Time = " << avgWait << endl;
    cout << "Avg. TurnAround Time = " << avgTurn << endl;

}
