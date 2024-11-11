#include <iostream> 


class avltree { 
    struct node { 
        int Key; 
        node* Left; 
        node* Right; 
        int Height; 

        node(int value) : Key(value), Left(nullptr), Right(nullptr), Height(1) {} 
    };

    node* Root; 

    int getheight(node* n) { 
        if (n == nullptr) return 0;
        return n->Height;
    }

    int getbalancefactor(node* n) { 
        if (n == nullptr) return 0;
        return getheight(n->Left) - getheight(n->Right);
    }

    node* rightrotate(node* y) { 
        node* x = y->Left;
        node* T2 = x->Right;

        x->Right = y;
        y->Left = T2;

        y->Height = std::max(getheight(y->Left), getheight(y->Right)) + 1;
        x->Height = std::max(getheight(x->Left), getheight(x->Right)) + 1;

        return x;
    }

    node* leftrotate(node* x) { 
        node* y = x->Right;
        node* T2 = y->Left;

        y->Left = x;
        x->Right = T2;

        x->Height = std::max(getheight(x->Left), getheight(x->Right)) + 1;
        y->Height = std::max(getheight(y->Left), getheight(y->Right)) + 1;

        return y;
    }

    node* insertnode(node* n, int key) { 
        if (n == nullptr) return new node(key);

        if (key < n->Key) {
            n->Left = insertnode(n->Left, key);
        }
        else if (key > n->Key) {
            n->Right = insertnode(n->Right, key);
        }
        else {
            return n;
        }

        n->Height = 1 + std::max(getheight(n->Left), getheight(n->Right));
        int balance = getbalancefactor(n);

        if (balance > 1 && key < n->Left->Key)
            return rightrotate(n);

        if (balance < -1 && key > n->Right->Key)
            return leftrotate(n);

        if (balance > 1 && key > n->Left->Key) {
            n->Left = leftrotate(n->Left);
            return rightrotate(n);
        }

        if (balance < -1 && key < n->Right->Key) {
            n->Right = rightrotate(n->Right);
            return leftrotate(n);
        }

        return n;
    }

    bool isempty() const { 
        return Root == nullptr;
    }

public:
    avltree() : Root(nullptr) {} 

    void insert(int key) {
        Root = insertnode(Root, key); 
    }

    bool empty() const {
        return isempty(); 
    }
};

// 
int main() {
    avltree t; 
    //t.insert(10);
    //t.insert(20);
    //t.insert(5);

    std::cout << "Tree empty? " << (t.empty() ? "Yes" : "No") << std::endl; 
    return 0;
}
