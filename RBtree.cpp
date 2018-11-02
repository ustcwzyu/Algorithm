/*
    Created By Ustcwzy 2018/11/2.
*/
#include<iostream>
#include<iomanip>
using namespace std;

enum RBTNodeColor{RED, BLACK};//define the color of RBTNode

template<class K, class V>
class RBTNode {
    public:
        K _key;
        V _value;
        RBTNodeColor _color;
        RBTNode<K, V>* _left;
        RBTNode<K, V>* _right;
        RBTNode<K, V>* _parent;
       RBTNode(const K &k,const V &v,const RBTNodeColor &c):
       _key(k), _value(v), _color(c), _left(NULL), _right(NULL), _parent(NULL) {}
};

template<class K, class V>
class RBTree {
    private:
        RBTNode<K, V>* _root;
    public:
        RBTree():_root(NULL) {_root = NULL;};

        bool insert(RBTNode<K, V>* &root, RBTNode<K, V> *z) {
            RBTNode<K, V> *y = NULL;
            RBTNode<K, V> *x = _root;
            while (x != NULL) {
                y = x;
                if (z->_key <= x->_key) {
                    x = x->_left;
                } else {
                    x = x->_right;
                }
            }
            z->_parent = y;
            if (y == NULL) {
                _root = z;
            } else {
                if (z->_key < y->_key) {
                    y->_left = z;
                } else {
                    y->_right = z;
                }
            }
            z->_left = NULL;
            z->_right = NULL;
            z->_color = RED;
            insertfixup(_root, z);
            return true;
        }

        bool insertfixup(RBTNode<K, V>* &root, RBTNode<K, V> *z) {
            while(z->_parent && z->_parent->_color == RED) {
                if (z->_parent == z->_parent->_parent->_left) {
                    RBTNode<K, V> *y = z->_parent->_parent->_right;
                    if (y != NULL && y->_color == RED) {
                        y->_color = BLACK;
                        z->_parent->_color = BLACK;
                        z->_parent->_parent->_color = RED;
                        z = z->_parent->_parent;
                    } else {
                        if (z == z->_parent->_right) {
                            z = z->_parent;
                            left_rotate(root, z);
                        }
                        z->_parent->_color = BLACK;
                        z->_parent->_parent->_color = RED;
                        right_rotate(root, z->_parent->_parent);
                    }
                } else if (z->_parent == z->_parent->_parent->_right) {
                    RBTNode<K, V> *y = z->_parent->_parent->_left;
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
            return true;
        }

        void left_rotate(RBTNode<K, V>* &root, RBTNode<K, V>* x) {
            RBTNode<K, V>* temp = x->_right;
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
        }

        void right_rotate(RBTNode<K, V>* &root, RBTNode<K,V>* x) {
            RBTNode<K, V>* temp = x->_left;
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
        }

        void insert(K key, V value) {
            RBTNode<K, V> *z = new RBTNode<K, V> (key, value, BLACK);
            insert(_root ,z);
        }

        void inorder() {
            inorder(_root);
        }

        void inorder(RBTNode<K, V>* tree) {
            if (tree != NULL) {
                inorder(tree->_left);
                cout<< tree->_key << " ";
                inorder(tree->_right);
            }
        }

        void print() {
            if (_root != NULL) {
                print(_root, _root->_key, 0);
            }
        }

    //Print the tree
        void print(RBTNode<K, V>* tree, K key, int direction) {
            if (tree != NULL) {
                if(direction==0)  {
                    cout << setw(2) << tree->_key << "(B) is root" << endl;
                } else {
                    cout << setw(2) << tree->_key <<  (tree->_color == RED ?"(R)":"(B)") << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;
                }
                print(tree->_left, tree->_key, -1);
                print(tree->_right,tree->_key,  1);
            }
        }
};

int main()
{
    int a[]= {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int i;
    int ilen = (sizeof(a)) / (sizeof(a[0])) ;
    RBTree<int, int>* tree=new RBTree<int, int>();

    cout << "--Original Data: ";
    for(i=0; i<ilen; i++)
        cout << a[i] <<" ";
    cout << endl;

    for(i=0; i<ilen; i++) 
    {
        tree->insert(a[i], a[i]);
            cout << "--Add Node: " << a[i] << endl;
            cout << "--The details of the tree: " << endl;
            tree->print();
            cout << endl;
    }

    cout << "\n-- Inorder: ";
    tree->inorder();
    system("pause");
    return 0;
}