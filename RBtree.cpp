enum RBTNodeColor{RED, BLACK};//define the color of RBTNode

template<class K, class V>
class RBTNode {
    private:
        K _key;
        V _value;
        RBTNodeColor _color;
        RBTNode<K, V>* _left;
        RBTNode<K, V>* _right;
        RBTNode<K, V>* _parent;
    
    public:
       RBTNode(const K &k,const V &v,const RBTNodeColor &c):
       _key(k), _value(v), _color(c), _left(NULL), _right(NULL), _parent(NULL) {}
};

template<class K, class V>
class RBTree {
    private:
        RBTNode<K, V>* _root;
    public:
        RBTree:_root(NULL) {};

        bool insert(K k, V v) {
            if (_root == NULL) {
                _root = new RBTNode<K, V>(k, v, BLACK);
            }
            
        }
        void left_rotate(RBTNode<K, V>* x) {
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

        void right_rotate(RBTNode<K,V>* x) {
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
};