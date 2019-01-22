#include <iostream>
#include <vector>
#define MAX_TIME 1000000

using namespace std;

int besttime = MAX_TIME;          //time
vector<int> bestlist;           //best machine list
vector<int> list;               //machine list
vector<int> time_mac;          //machine end time

class Solution {
    public:
    int getmax(int k) {
        int maxtime = time_mac[0];
        for(int i = 1;i < k;i++)
            maxtime = maxtime > time_mac[i] ? maxtime : time_mac[i];
        return maxtime;
    }

    void BackTrack(int* work,int n,int k,int now) {
        if(now == n)          //condition
        {
            int maxtime = getmax(k);
            if(maxtime < besttime) {
                besttime = maxtime;
                for(int i = 0;i < n;i++)
                    bestlist[i] = list[i];
            }
            return ;
        } else {
            for(int i = 0;i < k;i++) {
                if(time_mac[i] + work[now] < besttime)      //branch and bounds
                {
                    time_mac[i] += work[now];
                    list[now] = i;
                    BackTrack(work,n,k,now+1);
                    time_mac[i] -= work[now];
                }
            }
        }
        return ;
    }
};

int main() {
    int n = 7,k = 3;    //n tasks, k machines
    int work[n] = {2,14,4,16,6,5,3};     //time
    time_mac.resize(k);
    bestlist.resize(n);
    list.resize(n);

    Solution s;
    s.BackTrack(work,n,k,0);
    cout<<"Time of each task£º";
    for(int i = 0;i < n;i++)
        cout<<work[i]<<' ';
    cout<<endl<<"The best time is£º"<<besttime<<endl;
    for(int i = 0;i < n;i++)
        cout<<"Task"<<i<<"£º"<<bestlist[i]<<"Machine"<<endl;
    system("pause");
    return 0;
}