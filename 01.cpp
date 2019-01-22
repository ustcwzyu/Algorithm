/*
    Created by ustcwzyu at 2019/01/05.
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct Object {
    int id;
    int weight;
    int price;
    float d;//The value rate of the object.
};

//The definition of the heapnode.
struct MaxHeapQNode {
    MaxHeapQNode *parent;
    int lchild;
    int upprofit;
    int profit;
    int weight;
    int lev;
};

//The definition of the function of the priority_queue.
struct cmp {
    bool operator()(MaxHeapQNode *&a, MaxHeapQNode *&b) const {
        return a->upprofit < b->upprofit;
    }
};

bool compare(const Object &a, const Object &b) {
    return a.d >= b.d;
}

int n;//The number of the objects.
int c;//The capacity of the knapsack.
int cw;//The current weight of the knapsack.
int cp;//The current price of the knapsack.
int bestp;//The best price.
Object obj[100];
int bestx[100];//The best object sequence.

void InPut() {
	cout << "--please input the number of the objects:";
    cin >> n;
	cout << "--please input the capacity of the knapsack:";
	cin >> c;
	cout << "--please input the price and the weight of the objects:";
    for(int i = 1; i <= n; i++) {
     cin >> obj[i].price >> obj[i].weight;
     obj[i].id = i;
     obj[i].d = 1.0 * obj[i].price / obj[i].weight;
    }
 
	//Sort the objects by the value rate.
    sort(obj + 1, obj + n + 1, compare);
}

//Compute the upper value of the level.
int Bound(int i) {
    int left_c = c - cw;
    int restp = cp;
    while(left_c >= obj[i].weight && i <= n) {
        left_c -= obj[i].weight;
        restp += obj[i].price;
        i++;
    }
    if(i <= n) {
        restp += left_c * obj[i].d;
    }
    return restp;
}

/*
	q: The heap.
	E: The heap node.
	up: The upper value of the node.
	wt: The weight of the knapsack.
	curp: The current price of the objects.
	i: The level.
	ch: The choice of the object.(0/1)
*/
void AddAliveNode(priority_queue<MaxHeapQNode *, vector<MaxHeapQNode *>, cmp> &q, MaxHeapQNode *E, int up, int wt, int curp, int i, int ch) {
    MaxHeapQNode *p = new MaxHeapQNode;
    p->parent = E;
    p->lchild = ch;
    p->weight = wt;
    p->upprofit = up;
    p->profit = curp;
    p->lev = i + 1;
    q.push(p);
}

//Branch and bound.
void MaxKnapsack() {
	//priority_queue<Type, Container, Functional>
    priority_queue<MaxHeapQNode *, vector<MaxHeapQNode *>, cmp> q; // the heap.
    MaxHeapQNode *E = NULL;
    cw = cp = bestp = 0;
    int i = 1;
    int up = Bound(1);
    while(i != n + 1) {
        int wt = cw + obj[i].weight;
        if(wt <= c) {
            if(bestp < cp + obj[i].price)
                bestp = cp + obj[i].price;
            AddAliveNode(q, E, up, cw + obj[i].weight, cp + obj[i].price, i, 1);
        }
        up = Bound(i + 1);
        if(up >= bestp) {
            AddAliveNode(q, E, up, cw, cp, i, 0);
        }
        E = q.top();
        q.pop();
        cw = E->weight;
        cp = E->profit;
        up = E->upprofit;
        i = E->lev;
    }
	//Get the best choice sequence.
    for(int j = n; j > 0; j--) {
        bestx[obj[E->lev - 1].id] = E->lchild;
        E = E->parent;
    }
}

void OutPut() {
    cout << "--The best price is:" << bestp << endl;
    cout << "--The objects are:";
    for(int i = 1; i <= n; ++i)
        if(bestx[i] == 1)
          cout<< i << " ";
	cout << endl;
}

int main() {
    InPut();
    MaxKnapsack();
    OutPut();
	system("pause");
	return 0;
}