#include <iostream>
using namespace std;

class Node {
    int lbit, rbit;
    int value;
    Node *left, *right;

public:
    Node() {
        lbit = rbit = 0;
        value = 0;
        left = right = NULL;
    }
    friend class DTBT;
};

class DTBT {
    Node* root;

public:
    DTBT() {
        root = new Node();
        root->value = 9999;
        root->rbit = 1;
        root->lbit = 0;
        root->left = root;
        root->right = root;
    }
    Node* getRoot();
    void create();
    void insert(int value);
    void preorder();
    Node* preorderSuccessor(Node*);
    void inorder();
    Node* inorderSuccessor(Node*);
    Node* inorderPredecessor(Node*);
    Node* caseA(Node*, Node*, Node*);
    Node* caseB(Node*, Node*, Node*);
    Node* caseC(Node*, Node*, Node*);
    Node* delThreadedBST(Node*, int);

};

Node* DTBT::getRoot() {
    return root;
}

void DTBT::create() {
    int n, ele;
    cout << "Enter the number of elements you want to insert in the TBST: ";
    cin >> n;

    for(int i = 0; i < n; ++i) {
        cout << "Enter the element: ";
        cin >> ele;
        this->insert(ele); 
    }
}

void DTBT::insert(int data) {
    if (root->left == root && root->right == root) {
        Node* p = new Node();
        p->value = data;
        p->left = root->left;
        p->lbit = root->lbit;
        p->rbit = 0;
        p->right = root->right;

        root->left = p;
        root->lbit = 1;
        return;
    }

    Node* cur = new Node;
    cur = root->left;
    while (1) {
        if (cur->value < data) {
            Node* p = new Node();
            p->value = data;
            if (cur->rbit == 0) {
                p->right = cur->right;
                p->rbit = cur->rbit;
                p->lbit = 0;
                p->left = cur;
                cur->rbit = 1;
                cur->right = p;
                return;
            }
            else
                cur = cur->right;
        }

        if (cur->value > data) {
            Node* p = new Node();
            p->value = data;
            if (cur->lbit == 0) {
                p->left = cur->left;
                p->lbit = cur->lbit;
                p->rbit = 0;
                p->right = cur;
                cur->lbit = 1;
                cur->left = p;
                return;
            }
            else
                cur = cur->left;
        }
    }
}

void DTBT::preorder() {
    Node* c = root->left;
    while (c != root) {
        cout << " " << c->value << " (lbit: " << c->lbit << ", rbit: " << c->rbit << ")";
        c = preorderSuccessor(c);
    }
}

Node* DTBT::preorderSuccessor(Node* c) {
    if (c->lbit == 1) {
        return c->left;
    }
    while (c->rbit == 0) {
        c = c->right;
    }
    return c->right;
}


void DTBT::inorder() {
    Node* c = root->left;
    while (c->lbit == 1)
        c = c->left;
    while (c != root) {
        cout << " " << c->value << " (lbit: " << c->lbit << ", rbit: " << c->rbit << ")";
        c = inorderSuccessor(c);
    }
}

Node* DTBT::inorderSuccessor(Node* c) {
    if (c->rbit == 0)
        return c->right;
    else
        c = c->right;
    while (c->lbit == 1) {
        c = c->left;
    }
    return c;
}

Node* DTBT::inorderPredecessor(Node* ptr) {
    if (ptr->lbit == 0)
        return ptr->left;
    ptr = ptr->left;
    while (ptr->rbit == 1)
        ptr = ptr->right;
    return ptr;
}

Node* DTBT::caseA(Node* root, Node* par, Node* ptr) {
    if (par == NULL)
        root = NULL;
    else if (ptr == par->left) {
        par->lbit = 0;
        par->left = ptr->left;
    }
    else {
        par->rbit = 0;
        par->right = ptr->right;
    }
    free(ptr);
    return root;
}

Node* DTBT::caseB(Node* root, Node* par, Node* ptr) {
    Node* child;
    if (ptr->lbit == 1)
        child = ptr->left;
    else
        child = ptr->right;
    if (par == NULL)
        root = child;
    else if (ptr == par->left)
        par->left = child;
    else
        par->right = child;
    Node* s = inorderSuccessor(ptr);
    Node* p = inorderPredecessor(ptr);
    if (ptr->lbit == 1)
        p->right = s;
    else {
        if (ptr->rbit == 1)
            s->left = p;
    }
    free(ptr);
    return root;
}

Node* DTBT::caseC(Node* root, Node* par, Node* ptr) {
    Node* parsucc = ptr;
    Node* succ = ptr->right;
    while (succ->lbit == 1) {
        parsucc = succ;
        succ = succ->left;
    }
    ptr->value = succ->value;
    if (succ->lbit == 0 && succ->rbit == 0)
        root = caseA(root, parsucc, succ);
    else
        root = caseB(root, parsucc, succ);
    return root;
}

Node* DTBT::delThreadedBST(Node* root, int dkey) {
    Node *par = NULL, *ptr = root;
    int found = 0;
    while (ptr != NULL) {
        if (dkey == ptr->value) {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->value) {
            if (ptr->lbit == 1)
                ptr = ptr->left;
            else
                break;
        }
        else {
            if (ptr->rbit == 1)
                ptr = ptr->right;
            else
                break;
        }
    }
    if (found == 0)
        printf("dkey not present in tree\n");
    else if (ptr->lbit == 1 && ptr->rbit == 1)
        root = caseC(root, par, ptr);
    else if (ptr->lbit == 1)
        root = caseB(root, par, ptr);
    else if (ptr->rbit == 1)
        root = caseB(root, par, ptr);
    else
        root = caseA(root, par, ptr);
    return root;
}

int main() {
    DTBT t1;
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create Tree\n";
        cout << "2. Insert Element\n";
        cout << "3. Delete Element\n";
        cout << "4. Display Inorder\n";
        cout << "5. Display Preorder\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                t1.create();
                break;
            case 2:
                cout << "Enter the element to be inserted: ";
                cin >> value;
                t1.insert(value);
                break;
            case 3:
                cout << "Enter the element to be deleted: ";
                cin >> value;
                t1.delThreadedBST(t1.getRoot(), value);
                break;
            case 4:
                cout << "Inorder Traversal of DTBST:\n";
                t1.inorder();
                break;
            case 5:
                cout << "Preorder Traversal of DTBST:\n";
                t1.preorder();
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
























Arinjay : 


#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int rbit;
    int lbit;

    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
        this->rbit = 0;
        this->lbit = 0;
    }

    friend class TBST;
};

class TBST {
public:
    Node* root, *head;

    TBST() {
        root = NULL;
        head = NULL;
    }

    Node* get_root() {
        return root;
    }

    void insert(int x) {
        if (root == NULL) {
            head = new Node(999);
            head->right = head;
            root = new Node(x);
            head->left = root;
            head->lbit = 1;
            root->left = head;
            root->right = head;
            return;
        }
        else {
            Node* p = root;
            Node* q = new Node(x);

            while (true) {
                if (x == p->data) {
                    delete q;
                    return;
                }
                else if (x < p->data) {
                    if (p->lbit == 1) {
                        p = p->left;
                    }
                    else {
                        q->left = p->left;
                        q->right = p;
                        p->left = q;
                        p->lbit = 1;
                        return;
                    }
                }
                else {
                    if (p->rbit == 1) {
                        p = p->right;
                    }
                    else {
                        q->right = p->right;
                        q->left = p;
                        p->right = q;
                        p->rbit = 1;
                        return;
                    }
                }
            }
        }
    }

   void Inorder(Node* root) {
    if (root == NULL)
        return;

    Node* p = root;

    while (p->lbit == 1) {
        p = p->left;
    }

    while (p != head) {
        cout << "Data: " << p->data << ", ";
        cout << "lbit: " << p->lbit << ", ";
        cout << "rbit: " << p->rbit << endl;

        if (p->rbit == 1) {
            p = p->right;
            while (p->lbit == 1) {
                p = p->left;
            }
        }
        else {
            p = p->right;
        }
    }
    cout << endl;
}

Node* InOrderPredecessor(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->lbit == 1) {
        root = root->left;
        while (root->rbit == 1) {
            root = root->right;
        }
        return root;
    }

    return NULL;
}

    Node* InOrderSuccessor(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        if (root->rbit == 0) {
            return root->right;
        }

        root = root->right;
        while (root->lbit == 1) {
            root = root->left;
        }

        return root;
    }

Node* deletionNode(Node* &root, int key) {
    if (root == NULL) {
        return root;
    }

    Node* p = NULL;
    Node* curr = root;

    // Search for the node to be deleted
    while (curr && curr->data != key) {
        p = curr;

        if (key < curr->data) {
            if (curr->lbit == 1) {
                curr = curr->left;
            }
            else {
                break;
            }
        }
        else {
            if (curr->rbit == 1) {
                curr = curr->right;
            }
            else {
                break;
            }
        }
    }

    if (curr == NULL) {
        return root; // Node not found, return unchanged tree
    }

    if (curr->lbit == 0 || curr->rbit == 0) {
        // Node has at most one child
        Node* child;
        if (curr->lbit == 0 && curr->rbit == 1) {
            child = curr->right;
        }
        else if (curr->rbit == 0 && curr->lbit == 1) {
            child = curr->left;
        }
        else {
            // Node has no children
            if (p == NULL) {
                root = NULL;
            }
            else if (curr == p->left) {
                p->lbit = 0;
                p->left = curr->left;
            }
            else {
                p->rbit = 0;
                p->right = curr->right;
            }

            delete curr;
            return root;
        }

        if (p == NULL) {
            root = child;
        }
        else if (curr == p->left) {
            p->lbit = 0;
            p->left = child;
        }
        else {
            p->rbit = 0;
            p->right = child;
        }

        delete curr;
    }
    else {
        // Node has both children
        Node* pred = InOrderPredecessor(curr);
        if (pred != NULL) {
            if (pred->lbit == 1) {
                pred->left = curr->left;
            }
            else {
                pred->right = curr->left;
            }
            pred->lbit = curr->lbit;
        }

        Node* s = InOrderSuccessor(curr);
        if (s != NULL) {
            if (s->rbit == 1) {
                s->right = curr->right;
            }
            else {
                s->left = curr->right;
            }
            s->rbit = curr->rbit;
        }

        if (p == NULL) {
            root = curr->right;
        }
        else if (curr == p->left) {
            p->left = s;
        }
        else {
            p->right = s;
        }

        delete curr;
    }

    return root;
}






};

int main() {
    TBST tree;

    int choice;
    int value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a value\n";
        cout << "2. Display TBST (In-order traversal)\n";
        cout << "3. Delete a node\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Exiting program.\n";
                break;
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                tree.insert(value);
                cout << "Value inserted successfully.\n";
                break;
            case 2:
                cout << "In-order traversal of TBST with lbit and rbit:\n";
                tree.Inorder(tree.get_root());
                break;
            case 3:
                cout << "Enter the value to delete: ";
                cin >> value;
                tree.root = tree.deletionNode(tree.root, value);
                cout << "Node deleted successfully.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}


