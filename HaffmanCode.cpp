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
        Node* BuildHuffmanTree(vector<Node*> HuffmanNode) {
            while(HuffmanNode.size() > 1) {
                sort(HuffmanNode.begin(), HuffmanNode.end(), ComNode);   //sort the Huffmannode by the frequecy

                Node *first = HuffmanNode[0];    //the smallest node
                Node *second = HuffmanNode[1];   //the second smallest node
                Node *merge = new Node;      //merge the two node selected
                merge->weight = first->weight + second->weight; //merge the frequency
                merge->lchild = first; //tag the two node
                merge->rchild = second;

                vector<Node*>::iterator iter;
                iter = HuffmanNode.erase(HuffmanNode.begin(), HuffmanNode.begin()+2);    //delete the first and second
                HuffmanNode.push_back(merge);                                 //add the new merged node
            }
            return HuffmanNode[0];            //return the root
        }

        //Print with backtrack
        void PrintHuffman(Node *node, vector<int> Huffmanchar) {
            if(node->lchild==NULL && node->rchild==NULL) {//If the node is a leaf, then print
                cout << node->value << ": ";
                for(vector<int>::iterator iter=Huffmanchar.begin(); iter!=Huffmanchar.end(); iter++)
                    cout << *iter;
                cout << endl;
                return;
            } else {
                Huffmanchar.push_back(1);
                PrintHuffman(node->lchild, Huffmanchar);
                Huffmanchar.pop_back();
                Huffmanchar.push_back(0);
                PrintHuffman(node->rchild, Huffmanchar);
                Huffmanchar.pop_back();
            }
        }
};


int main()
{
    cout << "------------ Huffman -----------" << endl;
    cout << "--Input the characters to encode:" << endl;
    vector<Node*> HuffmanNode;
    HuffmanTree hftree;
    char ch;
    while((ch=getchar())!='\n') {
        if(ch==' ') continue;
        Node *temp = new Node;
        temp->value = ch;
        temp->lchild = temp->rchild = NULL;
        HuffmanNode.push_back(temp);
    }

    cout << endl << "--Input the frequency of the characters:" << endl;
    for(int i = 0; i < HuffmanNode.size(); i++)
        cin >> HuffmanNode[i]->weight;

    Node *root = hftree.BuildHuffmanTree(HuffmanNode);
    vector<int> Huffmanchar;
    cout << endl << "--The encoded characters are as following:" << endl;
    hftree.PrintHuffman(root, Huffmanchar);

    system("pause");
}