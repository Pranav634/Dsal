#include <iostream>
#include <string>
using namespace std;

struct Client
{
    string name;
    long long teleNumber;

    Client(string name = "", long long tele = 0)
    {
        this->name = name;
        this->teleNumber = tele;
    }

    bool isEmpty() const
    {
        return name.empty() && teleNumber == 0;
    }
};

class Hash
{
private:
    static const int tableSize = 10;
    Client table[tableSize];

    long long hashFunction(long long PhoneNum)
    {
        return (3 * PhoneNum + 5) % tableSize;
    }

    bool isOriginal(int index)
    {
        return index == hashFunction(table[index].teleNumber);
    }

    bool isFull() const
    {
        for (int i = 0; i < tableSize; ++i)
        {
            if (table[i].isEmpty())
            {
                return false; // if at least one empty
            }
        }
        return true;
    }

public:
    Hash()
    {
        for (int i = 0; i < tableSize; ++i)
        {
            table[i] = Client();
        }
    }

    void insertLPWithoutReplacement(string name, long long TeleNum)
    {
        if (isFull())
        {
            cout << "Hash table is full. Cannot insert more elements." << endl;
            return;
        }

        long long index = hashFunction(TeleNum);
        while (!table[index].isEmpty())
        {
            index = (index + 1) % tableSize;
        }
        // Found an empty space
        table[index] = Client(name, TeleNum);
    }

    void insertLPWithReplacement(string name, long long telenum)
    {
        if (isFull())
        {
            cout << "Hash table is full. Cannot insert more elements." << endl;
            return;
        }

        long long index = hashFunction(telenum);

        if (table[index].isEmpty())
        {
            table[index] = Client(name, telenum);
        }
        else
        {
            if (isOriginal(index))
            {
                while (!table[index].isEmpty())
                {
                    index = (index + 1) % tableSize;
                }
                // Found an empty space
                table[index] = Client(name, telenum);
            }
            else
            {
                Client temp = table[index];
                table[index] = Client(name, telenum);
                while (!table[index].isEmpty())
                {
                    index = (index + 1) % tableSize;
                }
                // Found an empty space
                table[index] = temp;
            }
        }
    }

    bool search(string name, long long teleNumber, int &comparisons)
    {
        long long index = hashFunction(teleNumber);
        long long originalIndex = index; // Store the original index for comparison

        while (!table[index].isEmpty())
        {
            comparisons++;
            if (table[index].name == name && table[index].teleNumber == teleNumber)
            {
                cout << "Element found at index " << index << endl;
                return true;
            }
            index = (index + 1) % tableSize;
            // If we have cycled back to the original index, it means the element is not found
            if (index == originalIndex)
            {
                break;
            }
        }
        cout << "Element not found" << endl;
        return false;
    }

    void printTable() const
    {
        for (int i = 0; i < tableSize; ++i)
        {
            if (!table[i].isEmpty())
            {
                cout << "Index " << i << ": " << table[i].name << " --> " << table[i].teleNumber << endl;
            }
            else
            {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }
};

int main()
{
    Hash h;
    int choice;
    string name;
    long long teleNumber;
    int comparisons;

    do
    {
        cout << "\nHash Table Operations:" << endl;
        cout << "1. Insert with Replacement" << endl;
        cout << "2. Insert without Replacement" << endl;
        cout << "3. Search" << endl;
        cout << "4. Print Table" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter telephone number: ";
            cin >> teleNumber;
            h.insertLPWithReplacement(name, teleNumber);
            break;
        case 2:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter telephone number: ";
            cin >> teleNumber;
            h.insertLPWithoutReplacement(name, teleNumber);
            break;
        case 3:
            cout << "Enter name to search: ";
            cin >> name;
            cout << "Enter telephone number to search: ";
            cin >> teleNumber;
            comparisons = 0;
            h.search(name, teleNumber, comparisons);
            cout << "Number of comparisons: " << comparisons << endl;
            break;
        case 4:
            cout << "Hash Table Contents:" << endl;
            h.printTable();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}












//divya


#include <iostream>
using namespace std;
#define size 10

class probe_without_rep
{
    public:
    int hashing(int key)
    {
        return key%size;
    }

    int probe(int H[],int key)
    {
        int index=hashing(key);
        int i=1;
        int new_index=(index+i)%size;
        while(H[new_index] != 0)
        {
            i++;
            new_index=(index+i)%size;
        }
        return new_index;
    }

    void insert(int H[],int key)
    {
        int index;
        index=hashing(key);
        if(H[index]!=0)
        {
            index=probe(H,key);
        }
        H[index]=key;
    }

    void search(int H[],int key)
    {
        int index=hashing(key);
        if(H[index]==key)
        {
            cout<<"Element found!"<<endl;
        }
        else
        {
            int i=1;  
            int search_index;
            int flag=0;
            while(i<=9)
            {
                search_index=(index+i)%size;
                if(H[search_index]==key)
                {
                    flag=1;
                }
                i++;
            }

            if(flag==1)
            {
                cout<<"Element found!"<<endl;
            }
            else
            {
                cout<<"Element not found!"<<endl;
            }
        }
    }
};

class probe_with_rep
{
    public:

    void insert(int H[],int key)
    {
        int index;
        index=hashing(key);
        if(H[index]!=0)
        {
            index=probe(H,key);
        }
        H[index]=key;
    }

    int hashing(int key)
    {
        return key%size;
    }

    int probe(int H[], int key)
    {
        int index=hashing(key);
        if (H[index] % size == index)   //if the element is already at correct position,probe as done in w/o replacement
        {
            int i=1;
            int new_index=(index+i)%size;
            while(H[new_index] != 0)
            {
                i++;
                new_index=(index+i)%size;
            }
            return new_index;
        }
        else   //element already peresent is at wrong index then replace it.
        {
            int start=hashing(key);
            int temp=H[start]; //Take the element in temp variable

            int i=1;
            int new_index=(start+i)%size;  //new index for element at wrong position
            while(H[new_index] != 0)
            {
                i++;
                new_index=(start+i)%size;
            }
            H[new_index]=temp;

            return start;
        }
    }

    void search(int H[],int key)
    {
        int index=hashing(key);
        if(H[index]==key)
        {
            cout<<"Element found!"<<endl;
        }
        else
        {
            int i=1;  
            int search_index;
            int flag=0;
            while(i<=9)
            {
                search_index=(index+i)%size;
                if(H[search_index]==key)
                {
                    flag=1;
                }
                i++;
            }

            if(flag==1)
            {
                cout<<"Element found!"<<endl;
            }
            else
            {
                cout<<"Element not found!"<<endl;
            }
        }
    }
};

int main()
{
    int probe_type;
    cout << "1. Linear probing without replacement" << endl;
    cout << "2. Linear probing with replacement" << endl;
    cout<<"Which probing you want to do: ";
    cin>>probe_type;

    int H[10]={0};

    int choice = -1;
    bool flag = true;

    if(probe_type==1)
    {
        while (flag)
        {
            probe_without_rep obj1;

            cout << "===== TELEPHONE DATABASE =====" << endl;
            cout << "1. Insert" << endl;
            cout << "2. Display" << endl;
            cout << "3. Search" << endl;
            cout << "4. Delete" << endl;
            cout << "5. EXIT..." << endl;
            cout << "-------------------------" << endl;
            cout << "\nEnter Your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    char ch;
                    {
                        do
                        {
                            int num;
                            cout<<"Enter phone number: ";
                            cin>>num;
                            obj1.insert(H,num);
                            cout<<"Want to continue(y/n): ";
                            cin>>ch;
                        } while (ch=='Y' || ch=='y');    
                    }
                    break;
                }

                case 2:
                {
                    cout<<"Index\tPhone number"<<endl;
                    for(int i=0;i<10;i++)
                    {
                        cout<<i<<"\t"<<H[i]<<endl;
                    }
                    break;
                }

                case 3:
                {
                    int key;
                    cout<<"Enter number to search: ";
                    cin>>key;
                    obj1.search(H,key);
                    break;
                }
                
                case 4:
                {
                    int del_num;
                    cout<<"Enter number to delete: "<<endl;
                    cin>>del_num;
                    for(int i=0;i<=9;i++)
                    {
                        if(H[i]==del_num)
                        {
                            H[i]=0;
                            break;
                        }
                    }
                    break;
                }

                case 5:
                {
                    flag=false;
                    break;
                }
            }
        }
    }
    else if(probe_type==2)
    {
        probe_with_rep obj1;

        while(flag)
        {
            cout << "===== TELEPHONE DATABASE =====" << endl;
            cout << "1. Insert" << endl;
            cout << "2. Display" << endl;
            cout << "3. Search" << endl;
            cout << "4. Delete" << endl;
            cout << "5. EXIT..." << endl;
            cout << "-------------------------" << endl;
            cout << "\nEnter Your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    char ch;
                    {
                        do
                        {
                            int num;
                            cout<<"Enter phone number: ";
                            cin>>num;
                            obj1.insert(H,num);
                            cout<<"Want to continue(y/n): ";
                            cin>>ch;
                        } while (ch=='Y' || ch=='y');    
                    }
                    break;
                }

                case 2:
                {
                    cout<<"Index\tPhone number"<<endl;
                    for(int i=0;i<10;i++)
                    {
                        cout<<i<<"\t"<<H[i]<<endl;
                    }
                    break;
                }

                case 3:
                {
                    int key;
                    cout<<"Enter number to search: ";
                    cin>>key;
                    obj1.search(H,key);
                    break;
                }
                
                case 4:
                {
                    int del_num;
                    cout<<"Enter number to delete: "<<endl;
                    cin>>del_num;
                    for(int i=0;i<=9;i++)
                    {
                        if(H[i]==del_num)
                        {
                            H[i]=0;
                            break;
                        }
                    }
                    break;
                }

                case 5:
                {
                    flag=false;
                    break;
                }
            }
        }
    }
}
    // obj1.insert(H,24);
    // obj1.insert(H,30);
    // obj1.insert(H,47);
    // obj1.insert(H,61);
    // obj1.insert(H,62);
    // obj1.insert(H,17);
    // obj1.insert(H,89);
    // obj1.insert(H,99);
    // obj1.insert(H,33);
    // obj1.search(H,22);

