#include<bits/stdc++.h>
using namespace std;

struct triple
{
    int PID,PAT,PBT,PCT,PTAT,PWT;
};

bool cmp(triple a, triple b)
{
    return a.PAT < b.PAT;
}

int main()
{
    int process;
    cin >> process;
    std::vector<int> pid(process),pat(process),pbt(process);
    std::vector<triple> pre,P;
    // Process ID
    for(int i=0; i<process; i++)
    {
        cin >> pid[i];
    }
    // Process Arrival Time
    for(int i=0; i<process; i++)
    {
        cin >> pat[i];
    }
    // Process Burst Time
    for(int i=0; i<process; i++)
    {
        cin >> pbt[i];
        // Create temp struct and push it.
        triple temp;
        temp.PID = pid[i];
        temp.PAT = pat[i];
        temp.PBT = pbt[i];
        temp.PCT = 0;
        temp.PTAT = 0;
        temp.PWT = 0;
        pre.push_back(temp);
        P.push_back(temp);
    }
    // Sort by Arrival Time
    sort(pre.begin(), pre.end(),cmp);

    std::vector<pair<int,int>> gch;
    queue<int> q;
    int totalTime = 0,timeQ=2,pointer=0,prev=-1;
    int t=9;
    while(t--)
    {
        int start = pointer;
        // Insert Ready Process into Queue
        for(int i=start; i<process; i++)
        {
            int atime = pre[i].PAT;
            int id = pre[i].PID;
            if(atime<=totalTime)
            {
                q.push(id);
                pointer++;
            }
            else break;
        }
        // Check previous Process from Running Queue
        if(prev!=-1) q.push(prev);

        int currId = q.front();
        int currBt,idx;
        // Find the current burst time and index
        for(int i=0; i<process; i++)
        {
            if(pre[i].PID==currId)
            {
                currBt = pre[i].PBT;
                idx = i;
                break;
            }
        }
        q.pop();
        if(currBt>2)
        {
            totalTime += 2;
            pre[idx].PBT -= 2;
            prev = currId;
        }
        else
        {
            totalTime += currBt;
            pre[idx].PBT = 0;
            prev = -1;
        }
        // Gantt Chart
        gch.push_back({currId,totalTime});

        // Check All Burst Time
        int f = 1;
        for(int i=0; i<process; i++)
        {
            if(pre[i].PBT>0) f = 0;
        }
        if(f) break;
    }

    // Store the Completition time
    int s = gch.size()-1, e = s-process+1;
    for(int i=gch.size()-1; i>=e; i--)
    {
        int curr = gch[i].first;
        //Find the process id
        for(int j=0; j<process; j++)
        {
            if(curr==pid[j])
            {
                P[j].PCT = gch[i].second;
                break;
            }
        }
    }
    // Store the Turn Around time and Waiting time and find the Avg
    float ttat = 0, twt = 0;
    for(int i=0; i<process; i++)
    {
        int currCT = P[i].PCT;
        int currAT = P[i].PAT;
        int currBT = P[i].PBT;
        // TAT = CT-AT, WT = TAT-BT
        P[i].PTAT = currCT - currAT;
        int currTAT = P[i].PTAT;
        P[i].PWT = currTAT - currBT;

        ttat += currTAT;
        twt += P[i].PWT;
    }

    cout << "Process\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\n";
    for(int i=0; i<process; i++)
    {
        cout << P[i].PID << "\t\t" << P[i].PAT << "\t\t" << P[i].PBT << "\t\t" << P[i].PCT << "\t\t" << P[i].PTAT << "\t\t" << P[i].PWT << endl;
    }
    cout << "Average Turn-Around Time: " << ttat/process << endl;
    cout << "Average Waiting Time: " << twt/process << endl;


}
