// Author: Sujal Bhor (21210)

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node *root;

    Node *InsertBst(Node *root, int data) {
        if (root == nullptr) {
            root = new Node(data);
        } else if (data > root->data) {
            root->right = InsertBst(root->right, data);
        } else {
            root->left = InsertBst(root->left, data);
        }
        return root;
    }

    Node *DeleteNode(Node *root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->data) {
            root->left = DeleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = DeleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node *temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            Node *temp = MinValue(root->right);
            root->data = temp->data;
            root->right = DeleteNode(root->right, temp->data);
        }
        return root;
    }

    int heightTree(Node* root) {
        if(root == nullptr) {
            return 0;
        }

        int left = heightTree(root->left);
        int right = heightTree(root->right);
        return max(left, right) + 1;
    }

public:
    BST() : root(nullptr) {}

    void CreateBst() {
        cout << "Enter Data to insert into BST (-1 to stop): ";
        int data;
        cin >> data;

        while (data != -1) {
            root = InsertBst(root, data);
            cout << "Enter Data: ";
            cin >> data;
        }
    }

    void InOrderAscending(Node *root) {
        if (root == nullptr) {
            return;
        }

        stack<Node *> stk;
        Node *curr = root;

        while (curr != nullptr || !stk.empty()) {
            while (curr != nullptr) {
                stk.push(curr);
                curr = curr->left;
            }

            curr = stk.top();
            stk.pop();
            cout << curr->data << " ";

            curr = curr->right;
        }
    }

    void InOrderDescending(Node *root) {
        if (root == nullptr) {
            return;
        }

        stack<Node *> stk;
        Node *curr = root;

        while (curr != nullptr || !stk.empty()) {
            while (curr != nullptr) {
                stk.push(curr);
                curr = curr->right;
            }

            curr = stk.top();
            stk.pop();
            cout << curr->data << " ";

            curr = curr->left;
        }
    }    

    void LevelOrder(Node *root) {
        if (root == nullptr) {
            return;
        }
        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            Node *front = q.front();
            q.pop();
            cout << front->data << " ";

            if (front->left != nullptr) {
                q.push(front->left);
            }
            if (front->right != nullptr) {
                q.push(front->right);
            }
        }
        cout << endl;
    }

    int longestPathInBST(Node *root) {
        if (root == nullptr) {
            return 0;
        }
        int leftHeight = heightTree(root->left);
        int rightHeight = heightTree(root->right);
        int longestPathThroughRoot = leftHeight + rightHeight + 1;
        int left = longestPathInBST(root->left);
        int right = longestPathInBST(root->right);
        return max(longestPathThroughRoot, max(left, right));
    }    

    int SearchBST(Node *root, int key) {
        int comparisons = -1;
        Node *curr = root;
        while (curr != nullptr) {
            comparisons++;
            if (key == curr->data) {
                return comparisons;
            } else if (key < curr->data) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return -1;
    }

    Node *MinValue(Node *root) {
        if (root == nullptr) {
            return nullptr;
        }
        Node *temp = root;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    Node *MaxValue(Node *root) {
        if (root == nullptr) {
            return nullptr;
        }
        Node *temp = root;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }

    void Insert(int data) {
        root = InsertBst(root, data);
    }

    void Delete(int key) {
        root = DeleteNode(root, key);
    }

    Node *GetRoot() {
        return root;
    }
};

int main() {
    BST bst;
    int choice;
    
    /* Declaration and initialization of comparisons outside the switch block */
    int comparisons = -1;
    int longestPath = 0;
    Node* maxNode = nullptr;
    Node* minNode = nullptr;

    do {
        cout << "\n---------------------------";
        cout << "\nBinary Search Tree Operations";
        cout << "\n---------------------------";
        cout << "\n1. Create BST";
        cout << "\n2. Insert Element";
        cout << "\n3. Delete Element";
        cout << "\n4. Inorder Traversal (Ascending)";
        cout << "\n5. Inorder Traversal (Descending)";
        cout << "\n6. Level Order Traversal";
        cout << "\n7. Search Element";
        cout << "\n8. Find Maximum Element";
        cout << "\n9. Find Minimum Element";
        cout << "\n10. Longest Path in BST";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bst.CreateBst();
                break;
            case 2:
                int data;
                cout << "Enter element to insert: ";
                cin >> data;
                bst.Insert(data);
                break;
            case 3:
                int key;
                cout << "Enter element to delete: ";
                cin >> key;
                bst.Delete(key);
                cout << "Element deleted." << endl;
                break;
            case 4:
                cout << "Inorder Traversal (Ascending): ";
                bst.InOrderAscending(bst.GetRoot());
                cout << endl;
                break;
            case 5:
                cout << "Inorder Traversal (Descending): ";
                bst.InOrderDescending(bst.GetRoot());
                cout << endl;
                break;
            case 6:
                cout << "Level Order Traversal: ";
                bst.LevelOrder(bst.GetRoot());
                cout << endl;
                break;
            case 7:
                cout << "Enter the element to search: ";
                cin >> key;
                comparisons = bst.SearchBST(bst.GetRoot(), key);
                if (comparisons == -1) {
                    cout << "Element not found." << endl;
                } else {
                    cout << "Element found in " << comparisons << " comparisons." << endl;
                }
                break;
            case 8:
                maxNode = bst.MaxValue(bst.GetRoot());
                if (maxNode == nullptr) {
                    cout << "Tree is empty." << endl;
                } else {
                    cout << "Maximum Value: " << maxNode->data << endl;
                }
                break;
            case 9:
                minNode = bst.MinValue(bst.GetRoot());
                if (minNode == nullptr) {
                    cout << "Tree is empty." << endl;
                } else {
                    cout << "Minimum Value: " << minNode->data << endl;
                }
                break;
            case 10:
                longestPath = bst.longestPathInBST(bst.GetRoot());
                cout << "The longest path is " << longestPath << endl;
            case 0:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 9." << endl;
        }
    } while (choice != 0);

    return 0;
}














Pranav :

#include<iostream>
using namespace std;

class BST {
	int data;
	BST *left, *right;

public:
	BST(int value) {
		data = value;
		left = right = NULL;
	}

	BST* Insert(BST*, int);
	void InOrder(BST*);
    void PreOrder(BST*);
    void PostOrder(BST*);
    void searchElement(BST*, int);
    int height(BST*);
    int minValue(BST*);
    int maxValue(BST*);
    void swap(BST*);
};

BST* BST::Insert(BST* root, int value)
{
	if (root == NULL) {
		return new BST(value);
	}

	if (value > root->data) {
		root->right = Insert(root->right, value);
	}
	else if (value < root->data) {
		root->left = Insert(root->left, value);
	}

	return root;
}

void BST::PreOrder(BST* root)
{
	if (!root) {
		return;
	}
    cout << root->data << " ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void BST::InOrder(BST* root)
{
	if (!root) {
		return;
	}
	InOrder(root->left);
	cout << root->data << " ";
	InOrder(root->right);
}

void BST::PostOrder(BST* root)
{
	if (!root) {
		return;
	}
	PostOrder(root->left);
    PostOrder(root->right);
	cout << root->data << " ";
}
void BST::searchElement(BST* root, int key){
	if(root == NULL){
		cout<<"Not found";
	}
	else if(root->data == key){
		cout<<"element found";
	}
	else if(root->data<key){
		searchElement(root->right, key);
	}
	else{
		searchElement(root->left, key);
	}
}

int BST::height(BST* root){
	if(root == NULL){
		return 0;
	}
	int leftH = height(root->left);
	int rightH = height(root->right);
	return max(leftH, rightH)+1;
}

int BST::minValue(BST* root){
    if(root->left == NULL){
        return root->data;
    }
    minValue(root->left);
}

int BST::maxValue(BST* root){
    if(root->right == NULL){
        return root->data;
    }
    maxValue(root->right);
}

void BST::swap(BST* root){
	if(root == NULL){
		return;
	}
	BST* temp = root->left;
	root->left = root->right;
	root->right = temp;

	swap(root->left);
	swap(root->right);
}




int main()
{
	BST *root = NULL;
	int Value;

	cout << "Enter values to insert into the BST"<<endl;

	while (true) {
		cout << "Enter value: ";
		cin >> Value;

		if (Value == -1) {
			break;
		}

		root = root->Insert(root, Value);
	}

	cout << "PreOrder traversal of the BST: ";
	root->PreOrder(root);
	cout << endl;

    cout << "Inorder traversal of the BST: ";
	root->InOrder(root);
	cout << endl;

    cout << "PosrOrder traversal of the BST: ";
	root->PostOrder(root);
	cout << endl;

    cout<<"Minimum value in a root node is: ";
    cout<<root->minValue(root);
    cout<<endl;

    cout<<"Maximum value in a root node is: ";
    cout<<root->maxValue(root);
    cout<<endl;

    int key;
    cout<<"enter the element to search: ";
    cin>>key;
    cout<<endl;
    root->searchElement(root, key);
    cout<<endl;
//    bool temp = searchElement(root, key);
//    if(temp){
//    	cout<<key<<" is found."<<endl;
//    }
//    else{
//    	cout<<key<<" is not found."<<endl;                          // 45 34 54 35 23 66 -1
//    }

    cout<<"no. of nodes in longest path: "<<root->height(root);
    cout<<endl;

    root->swap(root);
    cout<<"Inorder after swapping: ";
    root->InOrder(root);

    return 0;

}



