#include <iostream>
#include <vector>

using namespace std;

int besttime = 100000;          //time
vector<int> bestlist;           //best machine list
vector<int> list;               //machine list
vector<int> time_mac;          //machine end time
class Solution {
    public:
    void BackTrack(int* work,int n,int k,int now)
    {
        if(now == n)          //condition
        {
            int maxtime = time_mac[0];
            for(int i = 1;i < k;i++)
                maxtime = maxtime>time_mac[i]?maxtime:time_mac[i];
            if(maxtime < besttime)
            {
                besttime = maxtime;
                for(int i = 0;i < n;i++)
                    bestlist[i] = list[i];
            }
            return ;
        }
        else
        {
            for(int i = 0;i < k;i++)
            {
                if(time_mac[i] + work[now] < besttime)      //branch and bound
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

int main()
{
    int n = 7,k = 3;    //n tasks, k machines
    int work[n] = {2,14,4,16,6,5,3};     //time
    time_mac.resize(k);
    bestlist.resize(n);
    list.resize(n);

    Solution s;
    s.BackTrack(work,n,k,0);
    cout<<"每个任务的执行时间为：";
    for(int i = 0;i < n;i++)
        cout<<work[i]<<' ';
    cout<<endl<<"最佳调度所有任务都完成的最小时间为："<<besttime<<endl;
    for(int i = 0;i < n;i++)
        cout<<"任务"<<i<<"分配给"<<bestlist[i]<<"号机器"<<endl;
    system("pause");
    return 0;
}