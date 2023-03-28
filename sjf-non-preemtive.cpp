#include<bits/stdc++.h>
using namespace std;

/*
Turn Around Time = Completion Time - Arrival Time
Waiting Time = Turnaround time - Burst Time
*/

struct fcfs
{
	int id,art,bt,ct,tat,wt,visited;
};


int main(){
	int n;
	cin >> n;
	std::vector<fcfs> process;
	for(int i=0; i<n; i++){
		int id,art,bt;
		cin >> id >> art >> bt;
		process.push_back({id,art,bt,0,0,0,0});
	}

	int totalTime=0;
	while(1){
		int idx = -1,mn = INT_MAX,pidle=INT_MAX;
		for(int i=0; i<n; i++){
			if(totalTime>=process[i].art && !process[i].visited){
				if(process[i].bt<mn){
					mn = process[i].bt;
					idx = i;
				}
			}

			else if(!process[i].visited){
				pidle = min(pidle,process[i].art);
			}

		}
		if(idx==-1){
			totalTime += (pidle - totalTime);
		}
		else{
			totalTime += mn;
			process[idx].ct = totalTime;
			process[idx].visited = 1;
		}
		// cout << totalTime << endl;
		int f=1;
		for(int i=0; i<n; i++){
			if(!process[i].visited) f=0;
		}
		if(f) break;

	}
	double totalTAT = 0,totalWT=0;
	cout << "ID\t AT\t BT\t CT\t TT\t WT\n";
	for(int i=0; i<n; i++){
		process[i].tat = process[i].ct - process[i].art;
		process[i].wt = process[i].tat - process[i].bt;
		totalTAT += process[i].tat;
		totalWT += process[i].wt;

		cout << process[i].id << "\t " << process[i].art << "\t " << process
		[i].bt << "\t " <<process[i].ct << "\t " <<process
		[i].tat << "\t " << process[i].wt << endl;
	}
	cout << "Average TurnAround Time : " << totalTAT/n << endl;
	cout << "Average Waiting Time : " << totalWT/n << endl;
}