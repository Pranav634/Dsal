#include <bits/stdc++.h>
using namespace std;

class Heap
{
public:
    int arr[100];
    int size;
    Heap()
    {
        arr[0] = -1;
        size = 0;
    }

    void insert(int val)
    {
        size = size + 1;
        int index = size;
        arr[index] = val;
        while (index > 1)
        {
            int parent = index / 2;
            if (arr[parent] < arr[index])
            {
                swap(arr[parent], arr[index]);
                index = parent;
            }
            else
            {
                return;
            }
        }
    }

    void print()
    {
        for (int i = 1; i <= size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void deleteFromHeap()
    {
        if (size == 0)
        {
            cout << "Nothing to delete" << endl;
            return;
        }

        arr[1] = arr[size];
        size--;

        int i = 1;
        while (i < size)
        {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;

            if (leftIndex <= size && arr[i] < arr[leftIndex])
            {
                swap(arr[i], arr[leftIndex]);
                i = leftIndex;
            }
            else if (rightIndex <= size && arr[i] < arr[rightIndex])
            {
                swap(arr[i], arr[rightIndex]);
                i = rightIndex;
            }
            else
            {
                return;
            }
        }
    }
};

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;
    if (left <= n && arr[largest] < arr[left])
    {
        largest = left;
    }
    if (right <= n && arr[largest] < arr[right])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n)
{
    int size = n;
    while (size > 1)
    {
        swap(arr[size], arr[1]);
        size--;
        heapify(arr, size, 1);
    }
}

int main()
{
    Heap h;
    int choice;
    do
    {
        cout << "Choose an operation:\n";
        cout << "1. Insert into heap\n";
        cout << "2. Delete from heap\n";
        cout << "3. Heapify an array\n";
        cout << "4. Heap sort an array\n";
        cout << "5. Exit\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int val;
            cout << "Enter value to insert: ";
            cin >> val;
            h.insert(val);
            cout << "Heap after insertion: ";
            h.print();
            break;
        }
        case 2:
        {
            h.deleteFromHeap();
            cout << "Heap after deletion: ";
            h.print();
            break;
        }
        case 3:
        {
            int ar[100]; // Change the size as per your requirement
            int n;
            cout << "Enter the size of the array: ";
            cin >> n;
            cout << "Enter the elements of the array:\n";
            for (int i = 1; i <= n; i++)
            {
                cin >> ar[i];
            }
            for (int i = n / 2; i > 0; i--)
            {
                heapify(ar, n, i);
            }
            cout << "Array after heapifying: ";
            for (int i = 1; i <= n; i++)
            {
                cout << ar[i] << " ";
            }
            cout << endl;
            break;
        }
        case 4:
        {
            int ar[100]; // Change the size as per your requirement
            int n;
            cout << "Enter the size of the array: ";
            cin >> n;
            cout << "Enter the elements of the array:\n";
            for (int i = 1; i <= n; i++)
            {
                cin >> ar[i];
            }
            heapsort(ar, n);
            cout << "Array after heap sort: ";
            for (int i = 1; i <= n; i++)
            {
                cout << ar[i] << " ";
            }
            cout << endl;
            break;
        }
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please choose again.\n";
        }

    } while (choice != 5);

    return 0;
}













//Kunal: 

#include <iostream>
using namespace std;

class Heap {
public:
    int arr[100];
    int size;

    Heap() {
        arr[0] = -1;
        size = 0;
    }

    void insert(int val) {
        size = size + 1;
        int index = size;
        arr[index] = val;
        while (index > 1) {
            int parent = index / 2;
            if (arr[parent] < arr[index]) {
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                return;
            }
        }
    }

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void deleteFromHeap() {
        if (size == 0) {
            cout << "Nothing to delete" << endl;
            return;
        }

        arr[1] = arr[size];
        size--;

        int i = 1;
        while (i < size) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;

            if (leftIndex <= size && arr[i] < arr[leftIndex]) {
                swap(arr[i], arr[leftIndex]);
                i = leftIndex;
            } else if (rightIndex <= size && arr[i] < arr[rightIndex]) {
                swap(arr[i], arr[rightIndex]);
                i = rightIndex;
            } else {
                return;
            }
        }
    }
};

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;
    if (left <= n && arr[largest] < arr[left]) {
        largest = left;
    }
    if (right <= n && arr[largest] < arr[right]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    int size = n;
    while (size > 1) {
        swap(arr[size], arr[1]);
        size--;
        heapify(arr, size, 1);
    }
}

int main() {
    Heap h;
    int choice, value, n;

    int ar[101]; // Maximum size 100 elements
    ar[0] = -1; // Sentinel value for heap sort

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Element\n";
        cout << "2. Delete Max Element\n";
        cout << "3. Print Max Heap\n";
        cout << "4. Perform Heap Sort\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the element to be inserted: ";
                cin >> value;
                h.insert(value);
                break;
            case 2:
                h.deleteFromHeap();
                break;
            case 3:
                cout << "Max Heap: ";
                h.print();
                break;
            case 4:
                cout << "Enter the number of elements for heap sort: ";
                cin >> n;
                if (n <= 0 || n > 100) {
                    cout << "Invalid number of elements! Please enter a number between 1 and 100." << endl;
                    break;
                }
                cout << "Enter " << n << " elements: ";
                for (int i = 1; i <= n; i++) {
                    cin >> ar[i];
                }
                heapsort(ar, n);
                cout << "Sorted Array: ";
                for (int i = 1; i <= n; i++) {
                    cout << ar[i] << " ";
                }
                cout << endl;
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


