#include <iostream>
#include <cstring>
#define TABLE_SIZE 10
using namespace std;

class Node
{
    int key;
    char value[10];
    Node *next;
    friend class Dictionary;

public:
    Node()
    {
        key = 0;
        strcpy(value, "");
        next = nullptr;
    }
    Node(int key, char *value)
    {
        this->key = key;
        strcpy(this->value, value);
        this->next = nullptr;
    }
};

class Dictionary
{
    Node *Hashtable[TABLE_SIZE];

public:
    Dictionary()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            Hashtable[i] = nullptr;
        }
    }
    void insert(int, char *);
    void display();
    void Search(int);
    void deletePair(int);
};

void Dictionary::insert(int key, char *value)
{

    int index = key % TABLE_SIZE;
    Node *newnode = new Node(key, value);

    if (Hashtable[index] == nullptr)
    {
        Hashtable[index] = newnode;
    }
    else
    {
        Node *temp = Hashtable[index];
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

void Dictionary::display()
{
    cout << endl;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *temp = Hashtable[i];
        cout << i << " : ";
        if (temp != nullptr)
        {
            while (temp != NULL)
            {
                cout << "( " << temp->key << "-" << temp->value << " ) , ";
                temp = temp->next;
            }
        }
        cout << endl;
    }
}

void Dictionary::Search(int key)
{
    int index = key % TABLE_SIZE;
    if (Hashtable[index] == nullptr)
    {
        cout << "No pair with given key exist !!!!" << endl;
        return;
    }
    else
    {
        Node *temp = Hashtable[index];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                cout << "key found => (key: " << temp->key << ", value: " << temp->value << ")" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "No pair with given key exist !!!!" << endl;
        return;
    }
}

void Dictionary::deletePair(int key){
    int index = key % TABLE_SIZE;
    if (Hashtable[index] == nullptr)
    {
        cout << "No pair with given key exist !!!!" << endl;
        return;
    }
    else
    {
        Node *temp = Hashtable[index];
        Node*prev=temp;
        if(temp->key== key){
            if(temp->next == nullptr){
                Hashtable[index]=nullptr;
                cout<<"Node ( " << temp->key << "-" << temp->value << " ) deleted successfully"<<endl;
                delete temp;    
            }else{
                prev = temp;
                temp=temp->next;
                Hashtable[index]=temp;
                cout<<"Node ( " << prev->key << "-" << prev->value << " ) deleted successfully"<<endl;
                delete prev;
            }
            
        }else{
        while (temp->next != nullptr)
        {
            if (temp->next->key == key)
            {
                prev= temp->next;
                temp->next=prev->next;
                prev->next=nullptr;
                
                cout<<"Node ( " << prev->key << "-" << prev->value << " ) deleted successfully"<<endl;
                delete prev;
                return;
            }
            temp = temp->next;
       
        }
        }
}
}
int main()
{

    Dictionary dt;
    int choice;
    do
    {
        cout << "\nEnter your choice: \n1.Insert pair \n2.Search key-value pair \n3.Delete pair \n4.Display\n5.Exit\n==>  ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            int n, key;
            char val[10];
            cout << "Enter how many pairs you want to insert : ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter key " << i + 1 << " -> ";
                cin >> key;
                cout << "Enter value " << i + 1 << " ->  ";
                cin >> val;
                dt.insert(key, val);
            }
            break;
        case 2:
            // int key;
            cout << "Enter key to search ";
            cin >> key;
            dt.Search(key);
            break;
        case 3:
        cout<<"Enter key to delete ";
        cin>>key;
        dt.deletePair(key);
        break;
        case 4:
            dt.display();
            break;
        default:
            break;
        }
    } while (choice != 5);
    return 0;
}

