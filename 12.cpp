#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

class Record {
    int id, salary, experience;
    string name;

public:
    // Constructor to initialize a Record object
    Record(string title, int i1, int i2, int i3) {
        this->name = title;
        this->id = i1;
        this->salary = i2;
        this->experience = i3;
    }

    // Function to convert Record object to string format
    string toString() {
        string output;
        return output + to_string(id) + "-" + name + "-" + to_string(experience) + "-" + to_string(salary);
    }

    friend class File;
};

class File {
    int tableSize;
    string fileName;
    int *table;

    // Function to calculate hash value for a given id
    int hash(int id) {
        return id % this->tableSize;
    }

public:
    // Constructor to initialize a File object with filename and table size
    File(string name, int size) {
        this->fileName = name;
        this->tableSize = size;
        this->table = new int[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = -1;
        }
    }

    // Function to insert a record into the file
    void insert(Record r) {
        ofstream output;
        output.open(this->fileName, ios::app);
        int index = hash(r.id);
        int address = output.tellp();
        table[index] = address;
        output.write(r.toString().c_str(), r.toString().length());
        output.write("\n", 1);
        output.close();
    }

    // Function to delete a record from the file
    void deleleRecord(int id) {
        int index = hash(id);
        this->table[index] = -1;
        ifstream input;
        input.open(this->fileName, ios::in);
        vector<string> lines;

        while (!input.eof()) {
            string record;
            input >> record;
            if ((int(record[0]) - 48) != id) {
                lines.push_back(record);
            }
        }
        input.close();

        ofstream output;
        output.open(this->fileName, ios::out);
        for (int i = 0; i < lines.size(); i++) {
            int location = output.tellp();
            string line = lines[i];
            output.write(line.c_str(), line.length());
            output.write("\n", 1);
            int index = hash(int(line[0]) - 48);
            this->table[index] = location;
        }
        output.close();
    }

    // Function to display all records in the file
    void displayRecords() {
        ifstream input;
        input.open(this->fileName, ios::in);
        input.seekg(ios::beg);
        while (!input.eof()) {
            string line;
            input >> line;
            cout << line << endl;
        }
        input.close();
    }

    // Function to display the hash table
    void displayTable() {
        for (int i = 0; i < this->tableSize; i++) {
            cout << table[i] << endl;
        }
    }

};

int main() {
    File f("data.txt", 5);

    int choice, id;

    // Menu
    cout << "Menu:" << endl;
    cout << "1. Insert Record" << endl;
    cout << "2. Delete Record" << endl;
    cout << "3. Display Records" << endl;
    cout << "4. Display Hash Table" << endl;
    cout << "5. Exit" << endl;

    while (true) {
        cout << "-----------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int id, salary, experience;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter salary: ";
                cin >> salary;
                cout << "Enter experience: ";
                cin >> experience;
                Record newRecord(name, id, salary, experience);
                f.insert(newRecord);
                cout << "Record inserted successfully!" << endl;
                break;
            }
            case 2: {
                cout << "Enter ID to delete: ";
                cin >> id;
                f.deleleRecord(id);
                cout << "Record deleted successfully!" << endl;
                break;
            }
            case 3: {
                cout << "Records:" << endl;
                f.displayRecords();
                break;
            }
            case 4: {
                cout << "Hash Table:" << endl;
                f.displayTable();
                break;
            }
            case 5: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}


