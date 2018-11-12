/*
    Created by Ustcwzy 2018/11/9.
*/

#include<iostream>
#include<iomanip>
using namespace std;

enum Color{RED, BLACK};//define the color of RBTNode

//define the interval of the tree
typedef struct Interval{
    int low;
    int high;
}Interval;

class IntTNode {
    public:
        Color _color;
        Interval _int;
        IntTNode* _left;
        IntTNode* _right;
        IntTNode* _parent;
        int _max;//the highest point.
        
        IntTNode(Interval interval, Color c) {
            _int.low = interval.low;
            _int.high = interval.high;
            _left = NULL;
            _right = NULL;
            _parent = NULL;
            _max = interval.high;
            _color = c;
        }
};

class IntervalTree{
    private:
        IntTNode* _root;
    public:
        int getMax(int high, int leftmax, int rightmax) {
            int temp = (leftmax>rightmax)?leftmax:rightmax;
            return (high>temp)?high:temp;
        }

        void left_rotate(IntTNode* &root, IntTNode* x) {
            IntTNode* temp = x->_right;
            x->_right = temp->_left;
            if (temp->_left != NULL) {
                temp->_left->_parent = x;
            }
            temp->_parent = x->_parent;
            if (x->_parent == NULL) {
                _root = temp;
            } else if (x == x->_parent->_left) {
                x->_parent->_left = temp;
            } else {
                x->_parent->_right = temp;
            }
            temp->_left = x;
            x->_parent =temp;

            //adjust the additional information max
            x->_max = temp->_max;
            temp->_max = getMax(temp->_int.high, temp->_left->_max, temp->_right->_max);
        }

        void right_rotate(IntTNode* &root, IntTNode* x) {
            IntTNode* temp = x->_left;
            x->_left = temp->_right;
            if (temp->_right != NULL) {
                temp->_right->_parent = x;
            }
            temp->_parent = x->_parent;
            if (x->_parent == NULL) {
                _root = temp;
            } else if (x == x->_parent->_right) {
                x->_parent->_right = temp;
            } else {
                x->_parent->_left = temp;
            }
            temp->_right = x;
            x->_parent =temp;

            //max
            x->_max = temp->_max;
            temp->_max = getMax(temp->_int.high, temp->_left->_max, temp->_right->_max);
        }

        void insert(Interval interval) {
            IntTNode* z = new IntTNode(interval, BLACK);
            insert(_root, z);
        }
        
        void insert(IntTNode* &root, IntTNode* z) {
            IntTNode *y = NULL; //y is used to record the node scanned.
            IntTNode *x = _root; //scan from the root.
            while (x != NULL) { 
                //find the position to insert.
                if (z->_max > x->_max) {
                    x->_max = z->_max;
                }
                y = x;
                if (z->_int.low < x->_int.low) {
                    x = x->_left;
                } else {
                    x = x->_right;
                }
            }
            z->_parent = y;
            if (y == NULL) {
                _root = z;
            } else {
                if (z->_int.low < y->_int.low) {
                    y->_left = z;
                } else {
                    y->_right = z;
                }
            }
            z->_left = NULL;
            z->_right = NULL;
            z->_color = RED;
            insertfixup(_root, z);
        }

        void insertfixup(IntTNode* &root, IntTNode *z) {
            while(z->_parent && z->_parent->_color == RED) {
                //if the color of the parent z is black, no need for fixing up.
                if (z->_parent == z->_parent->_parent->_left) {
                    //case 1, 2, 3
                    IntTNode *y = z->_parent->_parent->_right;
                    if (y != NULL && y->_color == RED) {
                        // case 1
                        y->_color = BLACK;
                        z->_parent->_color = BLACK;
                        z->_parent->_parent->_color = RED;
                        z = z->_parent->_parent;
                    } else {
                        //case 2, 3
                        if (z == z->_parent->_right) {
                            //transition between case 2 and case 3
                            z = z->_parent;
                            left_rotate(root, z);
                        }
                        z->_parent->_color = BLACK;
                        z->_parent->_parent->_color = RED;
                        right_rotate(root, z->_parent->_parent);
                    }
                } else if (z->_parent == z->_parent->_parent->_right) {
                    //case 4, 5, 6
                    IntTNode *y = z->_parent->_parent->_left;
                    if (y != NULL && y->_color == RED) {
                        y->_color = BLACK;
                        z->_parent->_color = BLACK;
                        z->_parent->_parent->_color = RED;
                        z = z->_parent->_parent;
                    } else {
                        if (z == z->_parent->_left) {
                            z = z->_parent;
                            right_rotate(root, z);
                        }
                        z->_parent->_color = BLACK;
                        z->_parent->_parent->_color = RED;
                        left_rotate(root, z->_parent->_parent);
                    }
                }
            }
            _root->_color = BLACK;
        }

        void print() {
            if (_root != NULL) {
                print(_root, _root->_int, 0);
            }
        }

        void print(IntTNode* tree, Interval interval, int direction) {
            if (tree != NULL) {
                if(direction==0)  {
                    cout << "[" << tree->_int.low << "," << tree->_int.high << "]" << "(B)" << "(" << tree->_max << ") is root" << endl;
                } else {
                    cout << "[" << tree->_int.low << "," << tree->_int.high << "]" <<  (tree->_color == RED ?"(R)":"(B)") << "(" << tree->_max << ")" << " is " << "[" << interval.low << "," << interval.high << "]" << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;
                }
                print(tree->_left, tree->_int, -1);
                print(tree->_right,tree->_int,  1);
            }
        }

        IntTNode* IntervalSearch(Interval interval) {
            IntTNode* x= _root;
            while (x != NULL && !isOverlap(x->_int, interval)) {
                if (x->_left != NULL && x->_left->_max >= interval.low) {
                    x = x->_left;
                } else {
                    x = x->_right;
                }
            }
            return x;
        }

        bool isOverlap(Interval i1, Interval i2) {
            if (i1.low <= i2.high && i2.low <= i1.high) {
                return true;
            }
            return false;
        }
};

int main()
{
    Interval a[6];
    int i;
    for (i = 0; i < 6; i++) {
        cin >> a[i].low >> a[i].high;
    }
    IntervalTree* tree=new IntervalTree();

    cout << "--Original Data: ";
    for(i = 0; i < 6; i++)
        cout << "[" << a[i].low <<"," << a[i].high << "] ";
    cout << endl;

    for(i=0; i<6; i++) 
    {
        tree->insert(a[i]);
        cout << "--Add Node: " << "[" << a[i].low << "," << a[i].high << "]" << endl;
        cout << "--The details of the tree: " << endl;
        tree->print();
        cout << endl;
    }

    cout << "--IntervalSearch:" << endl;
    cout << "--Input the interval:" << endl;
    Interval interval;
    cin >> interval.low >> interval.high;
    IntTNode* result = tree->IntervalSearch(interval);
    if (result!=NULL) {
        cout << "[" << result->_int.low << "," << result->_int.high << "]" << endl;
    } else {
        cout << "the node does not exist.";
    }
    system("pause");
    return 0;
}