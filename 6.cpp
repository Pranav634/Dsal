#include<bits/stdc++.h>
using namespace std;
#define ll long long

class Node {
    string data="";
    Node *down=NULL,*right=NULL;
    friend class Graph;
};

class Graph {
public:
    int tot=0;
    Node *head=new Node;

    void Create() {
        cout<<"Enter number of vertices:";
        ll a;
        cin>>tot;
        cout<<endl;
        a=tot;
        Node *temp=head;
        while(a--) {
            string str;
            ll b;
            cout<<"Enter name of city and number of connected cities: ";
            cin>>str>>b;
            cout<<endl;
            Node *k=new Node;
            k->data=str;
            temp->down=k;
            temp=k;
            Node *p=k;
            while(b--) {
                cout<<"Enter connected city: ";
                string hk;
                cin>>hk;
                cout<<endl;
                Node *New=new Node;
                New->data=hk;
                temp->right=New;
                temp=New;
            }
            temp=p;
        }
    }

    void Display() {
        Node *temp=head->down;
        while(temp!=NULL) {
            Node *t2=temp->right;
            cout<<temp->data;
            while(t2!=NULL) {
                cout<<"->"<<t2->data;
                t2=t2->right;
            }
            cout<<"->NULL";
            cout<<endl;
            cout<<"|"<<endl;
            cout<<"v"<<endl;
            temp=temp->down;
        }
        cout<<"NULL"<<endl;
        cout<<endl;
    }

    void Degree() {
        cout<<head->down->data<<endl;
        map<string,ll>m;
        Node *temp=head->down;
        while(temp!=NULL) {
            Node *t2=temp->right;
            ll count=0;
            while(t2!=NULL) {
                count++;
                t2=t2->right;
            }
            m[temp->data]=count;
            temp=temp->down;
        }
        for(auto &it:m) {
            cout<<it.first<<" "<<it.second<<endl;
        }
    }

    void DFS() {
        set<string>s;
        stack<string>se;
        string d = head->down->data;
        se.push(head->down->data);
        while(!se.empty()) {
            string x=se.top();
            se.pop();
            if(s.find(x)==s.end()) {
                cout<<x<<" ";
                Node *temp=head->down;
                s.insert(x);
                while(temp->data!=x) {
                    temp=temp->down;
                }
                while(temp!=NULL) {
                    se.push(temp->data);
                    temp=temp->right;
                }
            }
        }
    }

    void BFS() {
        set<string>s;
        queue<string>se;
        string d = head->down->data;
        se.push(head->down->data);
        while(!se.empty()) {
            string x=se.front();
            se.pop();
            if(s.find(x)==s.end()) {
                cout<<x<<" ";
                Node *temp=head->down;
                s.insert(x);
                while(temp->data!=x) {
                    temp=temp->down;
                }
                while(temp!=NULL) {
                    se.push(temp->data);
                    temp=temp->right;
                }
            }
        }
    }
};

int main() {
    Graph g;
    int choice;
    bool exitFlag = false;

    while(!exitFlag) {
        cout << "\n\nMenu:\n";
        cout << "1. Create Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find Degrees of Vertices\n";
        cout << "4. Perform DFS\n";
        cout << "5. Perform BFS\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                g.Create();
                break;
            case 2:
                cout<<"Adjacency matrix of graph\n";
                g.Display();
                break;
            case 3:
                cout<<"Degree of each vertex: \n";
                g.Degree();
                break;
            case 4:
                cout<<"DFS : ";
                g.DFS();
                cout<<endl;
                break;
            case 5:
                cout<<"BFS : ";
                g.BFS();
                cout<<endl;
                break;
            case 6:
                exitFlag = true;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
    return 0;
}

// 5 nasik 3 pune mumbai nagpur pune 3 nasik mumbai delhi mumbai 4 nasik pune delhi nagpur delhi 3 mumbai nagpur pune nagpur 3 mumbai delhi nasik

