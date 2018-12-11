#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//The definition of the tree node. 
typedef struct Node {
    char value;                 
    int weight;               //frequency
    Node *lchild, *rchild;
}Node;

//The definition of the compare rule
bool ComNode(Node *p, Node *q) {
    return p->weight < q->weight;
}

class HuffmanTree {
    public:
        Node* BuildHuffmanTree(vector<Node*> vctNode) {
            while(vctNode.size() > 1)                            //vctNode森林中树个数大于1时循环进行合并
            {
                sort(vctNode.begin(), vctNode.end(), ComNode);   //sort the vctnode by the frequecy

                Node *first = vctNode[0];    //the smallest node
                Node *second = vctNode[1];   //the second smallest node
                Node *merge = new Node;      //merge the two node selected
                merge->weight = first->weight + second->weight; //merge the frequency
                merge->lchild = first; //tag the two node
                merge->rchild = second;

                vector<Node*>::iterator iter;
                iter = vctNode.erase(vctNode.begin(), vctNode.begin()+2);    //delete the first and second
                vctNode.push_back(merge);                                 //add the new merged node
            }
            return vctNode[0];            //return the root
        }

        //Print with backtrack
        void PrintHuffman(Node *node, vector<int> vctchar) {
            if(node->lchild==NULL && node->rchild==NULL) {//If the node is a leaf, then print
                cout << node->value << ": ";
                for(vector<int>::iterator iter=vctchar.begin(); iter!=vctchar.end(); iter++)
                    cout << *iter;
                cout << endl;
                return;
            } else {
                vctchar.push_back(1);
                PrintHuffman(node->lchild, vctchar);
                vctchar.pop_back();
                vctchar.push_back(0);
                PrintHuffman(node->rchild, vctchar);
                vctchar.pop_back();
            }
        }
};


int main()
{
    cout << "------------ Huffman -----------" << endl;
    cout << "--Input the characters to encode:" << endl;
    vector<Node*> vctNode;
    HuffmanTree hftree;
    char ch;
    while((ch=getchar())!='\n') {
        if(ch==' ') continue;
        Node *temp = new Node;
        temp->value = ch;
        temp->lchild = temp->rchild = NULL;
        vctNode.push_back(temp);
    }

    cout << endl << "--Input the frequency of the characters:" << endl;
    for(int i = 0; i < vctNode.size(); i++)
        cin >> vctNode[i]->weight;

    Node *root = hftree.BuildHuffmanTree(vctNode);
    vector<int> vctchar;
    cout << endl << "--The encoded characters are as following:" << endl;
    hftree.PrintHuffman(root, vctchar);

    system("pause");
}