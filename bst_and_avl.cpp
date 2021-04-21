//Kamil W³odarczyk
#include <iostream>
#include <ctime>

using namespace std;

enum class EXCEPTION_CODE
{
    nodeEmpty,
};

void seeExceptions(EXCEPTION_CODE error)
{
    switch (error) {
    case EXCEPTION_CODE::nodeEmpty:
        std::cerr << "Wezel jest pusty!" << std::endl;
        break;
    default:
        std::cerr << "Nieznany blad!";
        break;
    }
}
//Zadanie 7.1
class Node {
private:
    int value;
    Node* left;
    Node* right;
    Node* parent;
public:
    Node(int v, Node* l, Node* r, Node* p)
    {
        value = v;
        left = l;
        right = r;
        parent = p;
    }
    int getValue()
    {
        return value;
    }
    Node* getLeft()
    {
        return left;
    }
    Node* getRight()
    {
        return right;
    }
    Node* getParent()
    {
        return parent;
    }
    void setValue(int v)
    {
        if (this)
        {
            value = v;
        }
    }
    void setLeft(Node* l)
    {
        left = l;
    }
    void setRight(Node* r)
    {
        right = r;
    }
    void setParent(Node* p)
    {
        parent = p;
    }
};

class BSTree {
private:
    Node* root;
public:
    BSTree()                        //tworzy puste drzewo
    {
        root = NULL;
    }
    Node* getRoot()            //zwraca wska¿nik do root - metoda pomocnicza w testowaniu
    {
        if (root)
        {
            return root;
        }
        else
        {
            return NULL;
        }
    }
    bool empty(Node* p)        //zwraca prawdê gdy drzewo jest puste
    {

        if (p)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void inorder(Node* p)
    {

        if (!empty(p))
        {
            inorder(p->getLeft());
            cout << p->getValue() << ' ';
            inorder(p->getRight());
        }
    }
    //BST   
    void insert(int x)            //wstawia wêze³ z wartoœci¹ x
    {
        Node* newNode = new Node(x, NULL, NULL, NULL);
        Node* tmp = root;
        Node* parent = NULL;
        if (empty(root))
        {
            root = newNode;
        }
        else
        {
            while (true)
            {
                if (tmp == NULL)
                {
                    tmp = newNode;
                    tmp->setParent(parent);
                    if (parent->getValue() > x)
                    {
                        parent->setLeft(tmp);
                    }
                    else
                    {
                        parent->setRight(tmp);
                    }
                    break;
                }
                else if (tmp->getValue() > x)
                {
                    parent = tmp;
                    tmp = tmp->getLeft();
                }
                else if (tmp->getValue() < x)
                {
                    parent = tmp;
                    tmp = tmp->getRight();
                }
                else
                {
                    break;
                }
            }
        }
    }
    Node* search(int x)         //zwraca wskaŸnik do wêz³a z wartoœci¹ x (lub NULL jeœli nie istnieje)
    {
        Node* tmp = root;
        while (!empty(tmp) && tmp->getValue() != x)
        {
            if (tmp->getValue() > x)
            {
                tmp = tmp->getLeft();
            }
            else
            {
                tmp = tmp->getRight();
            }
        }
        return tmp;
    }
    Node* minimum()            //zwraca wskaŸnik do wêz³a z minimaln¹ wartoœci¹
    {
        Node* tmp = root;
        if (empty(root))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        while (!empty(tmp->getLeft()))
        {
            tmp = tmp->getLeft();
        }
        return tmp;
    }
    Node* maximum()            //zwraca wskaŸnik do wêz³a z maksymaln¹ wartoœci¹
    {
        Node* tmp = root;
        if (empty(root))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        while (!empty(tmp->getRight()))
        {
            tmp = tmp->getRight();
        }
        return tmp;
    }
    Node* successor(Node* p)    //zwraca wskaŸnik do nastênika p
    {
        if (empty(root))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        if (!empty(p->getRight()))
        {
            p = p->getRight();
            while (!empty(p->getLeft()))
            {
                p = p->getLeft();
            }
            return p;
        }
        else
        {
            Node* tmp = p->getParent();
            while (!empty(p) && tmp == p->getRight())
            {
                tmp = p;
                p = p->getParent();
            }
            return p;
        }
    }
    Node* predecessor(Node* p)    //zwraca wskaŸnik do poprzednika p
    {
        {
            if (empty(root))
            {
                throw EXCEPTION_CODE::nodeEmpty;
            }
            if (!empty(p->getLeft()))
            {
                p = p->getLeft();
                while (!empty(p->getRight()))
                {
                    p = p->getRight();
                }
                return p;
            }
            
            else
            {
                Node* tmp = p->getParent();
                while (!empty(p) && tmp == p->getLeft())
                {
                    tmp = p;
                    p = p->getParent();
                }
                return p;
            }
        }
    }
    void del(Node* p)            //usuwa wêze³ wskazywany przez p
    {
        if (empty(p))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        else if (empty(p->getLeft()) && empty(p->getRight()))
        {
            
            if (p == root)
            {
                root = NULL;
            }
            else
            {
                Node* tmp = p->getParent();
                if (tmp->getLeft()==p)
                {
                    tmp->setLeft(NULL);
                }
                else
                {
                    tmp->setRight(NULL);
                }
            }
            delete p;
        }
        else if (!empty(p->getLeft()) && !empty(p->getRight()))
        {
            Node* succ = successor(p);
            p->setValue(succ->getValue());
            if (succ->getRight())
            {
                succ->getParent()->setLeft(succ->getRight());
                succ->getRight()->setParent(succ->getParent());
            }
            else if(succ!=p->getRight())
            {
                succ->getParent()->setLeft(NULL);
            }
            else
            {
                p->setRight(NULL);
            }
            delete succ;
        }
        else
        {
            Node* tmp;
            if (!empty(p->getLeft()))
            {
                tmp = p->getLeft();
            }
            else
            {
                tmp = p->getRight();
            }

            
            if (p==root)
            {
                root = tmp;
            }
            else
            {
                Node* parent = p->getParent();
                if (parent->getLeft() == p)
                {
                    parent->setLeft(tmp);
                }
                else
                {
                    parent->setRight(tmp);
                }
            }
            delete p;
        }
    }
    //Zadanie 7.2

    int size(Node* p)                  //zwraca rozmiar drzewa
    {
        if (!empty(p))
        {
            return (size(p->getLeft()) + 1 + size(p->getRight()));
        }
        return 0;
    }
    int hight(Node* p)              //zwraca wysokoœæ drzewa
    {
        
        if (empty(p))
        {
            return 0;
        }
        else
        {
            int l = hight(p->getLeft());
            int r = hight(p->getRight());
            if (l > r)
            {
                return(l + 1);
            }
            else
            {
                return(r + 1);
            }
        }
    }
    void clear(Node* p)           //usuwa wszystkie wêz³y z drzewa
    {
        if (p)
        {
            clear(p->getLeft());
            clear(p->getRight());
            delete p;
        }
        root = NULL;
    }
    
};

//Zadanie 8.1
class avlNode {
private:
    int bf;
    int value;
    avlNode* left;
    avlNode* right;
    avlNode* parent;
public:
    avlNode(int v, int bf)
    {
        value = v;
        this->bf = bf;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    int getValue()
    {
        return value;
    }
    avlNode* getLeft()
    {
        return left;
    }
    avlNode* getRight()
    {
        return right;
    }
    avlNode* getParent()
    {
        return parent;
    }
    void setValue(int v)
    {
        if (this)
        {
            value = v;
        }
    }
    void setLeft(avlNode* l)
    {
        left = l;
    }
    void setRight(avlNode* r)
    {
        right = r;
    }
    void setParent(avlNode* p)
    {
        parent = p;
    }
    int getBf()
    {
        return bf;
    }
    void setBf(int bf)
    {
        this->bf = bf;
    }
};

class AVLTree {
private:
    avlNode* root;
public:
    AVLTree()
    {
        root = NULL;
    }
    avlNode* getRoot()            //zwraca wska¿nik do root - metoda pomocnicza w testowaniu
    {
        if (root)
        {
            return root;
        }
        else
        {
            return NULL;
        }
    }
    bool empty(avlNode* p)        //zwraca prawdê gdy drzewo jest puste
    {

        if (p)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    avlNode* search(int x)         //zwraca wskaŸnik do wêz³a z wartoœci¹ x (lub NULL jeœli nie istnieje)
    {
        avlNode* tmp = root;
        while (!empty(tmp) && tmp->getValue() != x)
        {
            if (tmp->getValue() > x)
            {
                tmp = tmp->getLeft();
            }
            else
            {
                tmp = tmp->getRight();
            }
        }
        return tmp;
    }
    int hight(avlNode* p)              //zwraca wysokoœæ drzewa
    {
        if (p == NULL)
        {
            return 0;
        }
        else
        {
            int l = hight(p->getLeft());
            int r = hight(p->getRight());
            if (l > r)
            {
                return(l + 1);
            }
            else
            {
                return(r + 1);
            }
        }
    }
    avlNode* minimum()            //zwraca wskaŸnik do wêz³a z minimaln¹ wartoœci¹
    {
        avlNode* tmp = root;
        if (empty(root))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        while (!empty(tmp->getLeft()))
        {
            tmp = tmp->getLeft();
        }
        return tmp;
    }
    avlNode* maximum()            //zwraca wskaŸnik do wêz³a z maksymaln¹ wartoœci¹
    {
        avlNode* tmp = root;
        if (empty(root))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        while (!empty(tmp->getRight()))
        {
            tmp = tmp->getRight();
        }
        return tmp;
    }
    avlNode* successor(avlNode* p)    //zwraca wskaŸnik do nastênika p
    {
        if (empty(root))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        if (!empty(p->getRight()))
        {
            p = p->getRight();
            while (!empty(p->getLeft()))
            {
                p = p->getLeft();
            }
            return p;
        }
        else
        {
            avlNode* tmp = p->getParent();
            while (!empty(tmp) && p == tmp->getRight())
            {
                p = tmp;
                tmp = tmp->getParent();
            }
            return tmp;
        }
    }
    avlNode* predecessor(avlNode* p)    //zwraca wskaŸnik do poprzednika p
    {
        {
            if (empty(root))
            {
                throw EXCEPTION_CODE::nodeEmpty;
            }
            if (!empty(p->getLeft()))
            {
                p = p->getLeft();
                while (!empty(p->getRight()))
                {
                    p = p->getRight();
                }
                return p;
            }

            else
            {
                avlNode* tmp = p->getParent();
                while (!empty(tmp) && p == tmp->getLeft())
                {
                    p = tmp;
                    tmp = tmp->getParent();
                }
                return tmp;
            }
        }
    }
    void del(avlNode* p)            //usuwa wêze³ wskazywany przez p
    {
        if (empty(p))
        {
            throw EXCEPTION_CODE::nodeEmpty;
        }
        else if (empty(p->getLeft()) && empty(p->getRight()))
        {

            if (p == root)
            {
                root = NULL;
            }
            else
            {
                avlNode* tmp = p->getParent();
                if (tmp->getLeft() == p)
                {
                    tmp->setLeft(NULL);
                }
                else
                {
                    tmp->setRight(NULL);
                }
            }
            delete p;
        }
        else if (!empty(p->getLeft()) && !empty(p->getRight()))
        {

            avlNode* succParent = p;
            avlNode* succ = successor(p);
            p->setValue(succ->getValue());
            if (succ->getRight())
            {
                succ->getParent()->setLeft(succ->getRight());
                succ->getRight()->setParent(succ->getParent());
            }
            else if (succ != p->getRight())
            {
                succ->getParent()->setLeft(NULL);
            }
            else
            {
                p->setRight(NULL);
            }
            delete succ;
        }
        else
        {
            avlNode* tmp;
            if (!empty(p->getLeft()))
            {
                tmp = p->getLeft();
            }
            else
            {
                tmp = p->getRight();
            }


            if (p == root)
            {
                root = tmp;
            }
            else
            {
                avlNode* parent = p->getParent();
                if (parent->getLeft() == p)
                {
                    parent->setLeft(tmp);
                }
                else
                {
                    parent->setRight(tmp);
                }
            }
            delete p;
        }
    }
    int size(avlNode* p)                  //zwraca rozmiar drzewa
    {
        if (!empty(p))
        {
            return (size(p->getLeft()) + 1 + size(p->getRight()));
        }
        return 0;
    }
    void clear(avlNode* p)           //usuwa wszystkie wêz³y z drzewa
    {
        if (p)
        {
            clear(p->getLeft());
            clear(p->getRight());
            delete p;
        }
        root = NULL;
    }
    void RR(avlNode* A, avlNode* B) {
        A->setRight(B->getLeft());
        if (A->getRight())
        {
            A->getRight()->setParent(A);
        }
        B->setLeft(A);
        B->setParent(A->getParent());
        A->setParent(B);
        if (B->getParent())
        {
            if (B->getParent()->getLeft() == A)
            {
                B->getParent()->setLeft(B);
            }
            else
            {
                B->getParent()->setRight(B);
            }
        }
        else
        {
            root = B;
        }
        if (B->getBf() == -1)
        {
            A->setBf(0);
            B->setBf(0);
        }
        else
        {
            A->setBf(-1);
            B->setBf(1);
        }
    }
    void LL(avlNode* A, avlNode* B)
    {
        A->setLeft(B->getRight());
        if (A->getLeft())
        {
            A->getLeft()->setParent(A);
        }
        B->setRight(A);
        B->setParent(A->getParent());
        A->setParent(B);
        if (A->getParent())
        {
            if (A->getParent()->getLeft() == A)
            {
                A->getParent()->setLeft(B);
            }
            else
            {
                A->getParent()->setRight(B);
            }
        }
        else
        {
            root = B;
        }
        if (B->getBf() == 1)
        {
            A->setBf(0);
            B->setBf(0);
        }
        else
        {
            A->setBf(1);
            B->setBf(-1);
        }
    }
    void RL(avlNode* a, avlNode* b, avlNode* c)
    {
        LL(b, c);
        RR(a, c);
    }
    void LR(avlNode* a, avlNode* b, avlNode* c)
    {
        RR(b, c);
        LL(a, c);
    }
    void insert(int value)
    {
        avlNode* newNode = new avlNode(value, 0);
        avlNode* tmp = root;
        avlNode* parent = NULL;
        if (empty(root))
        {
            tmp = root = newNode;
        }
        else
        {
            while (true)
            {
                if (tmp == NULL)
                {
                    tmp = newNode;
                    tmp->setParent(parent);
                    if (parent->getValue() > value)
                    {
                        parent->setLeft(tmp);
                    }
                    else if (parent->getValue() < value)
                    {
                        parent->setRight(tmp);
                    }
                    else
                    {
                        break;
                    }
                    break;
                }
                else if (tmp->getValue() > value)
                {
                    parent = tmp;
                    tmp = tmp->getLeft();
                }
                else if (tmp->getValue() < value)
                {
                    parent = tmp;
                    tmp = tmp->getRight();
                }
                else
                {
                    break;
                }
            }
        }
        
        avlNode* t = tmp;
        avlNode* p = t->getParent();
        if (t == root)
        {
            return;
        }
        if (p->getBf() != 0)
        {
            p->setBf(0);
            return;
        }
        if (p->getLeft() == t)
        {
            p->setBf(1);
        }
        else
        {
            p->setBf(-1);
        }
        t = p->getParent();
        while (t != NULL)
        {
            if (t->getBf() == 0)
            {
                if (t->getLeft() == p)
                {
                    t->setBf(1);
                }
                else
                {
                    t->setBf(-1);
                }
                p = t;
                t = p->getParent();
            }
            else
            {
                if (t->getBf() == -1)
                {
                    if (t->getLeft() == p)
                    {
                        t->setBf(0);
                        return;
                    }
                    else if (p->getBf() == 1)
                    {
                        RL(t, p, p->getLeft());
                    }
                    else
                    {
                        RR(t, p);
                    }
                }
                else
                {
                    if (t->getRight() == p)
                    {
                        t->setBf(0);
                        return;
                    }
                    else if (p->getBf() == -1)
                    {
                        LR(t, p, p->getRight());
                    }
                    else
                    {
                        LL(t, p);
                    }
                }
            }


        }
    }
    void inorder(avlNode* p)
    {

        if (!empty(p))
        {
            inorder(p->getLeft());
            cout << p->getValue() << ' ';
            inorder(p->getRight());
        }
    }
};

int main()
{
    try
    {
        //Zadanie 7.1 - test
        cout << endl << "Zadanie 7.1 - test" << endl;
        BSTree* t = new BSTree();
        cout << endl << "insert(8), inorder(): 8 - "; t->insert(8); t->inorder(t->getRoot());
        cout << endl << "insert(5), inorder(): 5 8 - "; t->insert(5); t->inorder(t->getRoot());
        cout << endl << "insert(12), inorder(): 5 8 12 - "; t->insert(12); t->inorder(t->getRoot());
        cout << endl << "insert(2), inorder(): 2 5 8 12 - "; t->insert(2); t->inorder(t->getRoot());
        cout << endl << "insert(7), inorder(): 2 5 7 8 12 - "; t->insert(7); t->inorder(t->getRoot());
        cout << endl << "insert(9), inorder(): 2 5 7 8 9 12 - "; t->insert(9); t->inorder(t->getRoot());
        cout << endl << "insert(14), inorder(): 2 5 7 8 9 12 14 - "; t->insert(14); t->inorder(t->getRoot());
        cout << endl << "insert(1), inorder(): 1 2 5 7 8 9 12 14 - "; t->insert(1); t->inorder(t->getRoot());
        cout << endl << "insert(3), inorder(): 1 2 3 5 7 8 9 12 14 - "; t->insert(3); t->inorder(t->getRoot());
        cout << endl << "insert(17), inorder(): 1 2 3 5 7 8 9 12 14 17 - "; t->insert(17); t->inorder(t->getRoot());
        cout << endl << "successor(): 9 - " << t->successor(t->getRoot())->getValue();
        cout << endl << "predecessor(): 7 - " << t->predecessor(t->getRoot())->getValue();
        cout << endl << "hight(): 4 - " << t->hight(t->getRoot());
        cout << endl << "empty(): 0 - " << t->empty(t->getRoot());
        cout << endl << "del(getRoot()), getRoot(): 9 - "; t->del(t->getRoot()); cout << t->getRoot()->getValue();
        cout << endl << "del(minimum()), del(maximum), inorder(): 2 3 5 7 8 12 14 - "; t->del(t->minimum()); t->del(t->maximum()); t->inorder(t->getRoot());
        cout << endl << "getSize(): 7 - " << t->size(t->getRoot());
        cout << endl << "height(): 4 - " << t->hight(t->getRoot());
        cout << endl << "clear(), empty(): 1 - "; t->clear(t->getRoot()); cout << t->empty(t->getRoot());
        cout << endl << "getSize(): 0 - " << t->size(t->getRoot());
        cout << endl << "height(): 0 - " << t->hight(t->getRoot());

        //Zadanie 8.1 - test
        AVLTree* avl = new AVLTree();
        cout << endl << "empty(): 1 - " << avl->empty(avl->getRoot());
        cout << endl << "insert(8), inorder(): 8 - "; avl->insert(8); avl->inorder(avl->getRoot());
        cout << endl << "insert(5), inorder(): 5 8 - "; avl->insert(5); avl->inorder(avl->getRoot());
        cout << endl << "insert(12), inorder(): 5 8 12 - "; avl->insert(12); avl->inorder(avl->getRoot());
        cout << endl << "insert(2), inorder(): 2 5 8 12 - "; avl->insert(2); avl->inorder(avl->getRoot());
        cout << endl << "insert(7), inorder(): 2 5 7 8 12 - "; avl->insert(7); avl->inorder(avl->getRoot());
        cout << endl << "insert(9), inorder(): 2 5 7 8 9 12 - "; avl->insert(9); avl->inorder(avl->getRoot());
        cout << endl << "insert(17), inorder(): 2 5 7 8 9 17 - "; avl->insert(17); avl->inorder(avl->getRoot());
        cout << endl << "insert(1), inorder(): 1 2 5 7 8 9 17 - "; avl->insert(1); avl->inorder(avl->getRoot());
        cout << endl << "insert(3), inorder(): 1 2 3 5 7 8 9 17 - "; avl->insert(3); avl->inorder(avl->getRoot());
        cout << endl << "insert(14), inorder(): 1 2 3 5 7 8 9 14 17 - "; avl->insert(14); avl->inorder(avl->getRoot());
        cout << endl << "insert(19), inorder(): 1 2 3 5 7 8 9 14 17 19 - "; avl->insert(19); avl->inorder(avl->getRoot());
        cout << endl << "getRoot()->getValue(): 8 - " << avl->getRoot()->getValue();
        cout << endl << "hight(): 4 - " << avl->hight(avl->getRoot());
        cout << endl << "getRoot()->getLeft()->getValue(): 5 - " << avl->getRoot()->getLeft()->getValue();
        cout << endl << "getRoot()->getRight()->getValue(): 12 - " << avl->getRoot()->getRight()->getValue();
        cout << endl << "getRoot()->getBF(): 0 - " << avl->getRoot()->getBf();
    }
    catch (EXCEPTION_CODE error)
    {
        seeExceptions(error);
    }
    return 0;
}