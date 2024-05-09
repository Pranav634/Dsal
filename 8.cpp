#include <iostream>
using namespace std;

class OptimalBST {
private:
    float a[20], b[20], wt[20][20], c[20][20];
    int r[20][20], n;
    int keys[20]; // Array to store keys

public:
    void inputProbabilitiesAndKeys() {
        int i;
        cout << "\nEnter the no. of nodes : ";
        cin >> n;
        cout << "\nEnter the keys:\n";
        for (i = 1; i <= n; i++) {
            cout << "Key[" << i << "]: ";
            cin >> keys[i];
        }
        cout << "\nEnter the probability for successful search:\n";
        for (i = 1; i <= n; i++) {
            cout << "p[" << keys[i] << "]: ";
            cin >> a[i];
        }
        cout << "\nEnter the probability for unsuccessful search:\n";
        keys[0]=0;
        for (i = 1; i <= n; i++) {
            cout << "q[" << keys[i] << "]: ";
            cin >> b[i];
        }
    }

    void constructOBST() {
        initializeOBST();
        calculateOBST();
        printOptimalBST();
    }

    void showSearchCosts() {
        cout << "\n\nSearch costs for each key:\n";
        for (int i = 1; i <= n; ++i) {
            cout << "Cost of search for key " << keys[i] << ": " << c[i - 1][i] << endl;
        }
    }

private:
    void initializeOBST() {
        // Initialization of the wt, c, and r arrays for i-i and i-i+1 cases
        for (int i = 0; i < n; i++) {
            c[i][i] = 0.0;
            r[i][i] = 0;
            wt[i][i] = b[i];
            wt[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
            c[i][i + 1] = b[i] + b[i + 1] + a[i + 1];
            r[i][i + 1] = i + 1;
        }
        c[n][n] = 0.0;
        r[n][n] = 0;
        wt[n][n] = b[n];
    }

    void calculateOBST() {
        // Calculation of the wt, c, and r arrays for j-i=2,3,4,...,n cases
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= n - i; j++) {
                wt[j][j + i] = b[j + i] + a[j + i] + wt[j][j + i - 1];
                c[j][j + i] = 9999;
                for (int l = j + 1; l <= j + i; l++) {
                    if (c[j][j + i] > (c[j][l - 1] + c[l][j + i])) {
                        c[j][j + i] = c[j][l - 1] + c[l][j + i];
                        r[j][j + i] = l;
                    }
                }
                c[j][j + i] += wt[j][j + i];
            }
        }
    }

    void printOptimalBST() {
        cout << "\n\nOptimal BST is :: ";
        cout << "\nw[0][" << n << "] :: " << wt[0][n];
        cout << "\nc[0][" << n << "] :: " << c[0][n];
        cout << "\nr[0][" << n << "] :: " << r[0][n];
        // printTreeStructure(0, n);
    }

    void printTreeStructure(int l1, int r1) {
        if (l1 >= r1)
            return;
        if (r[l1][r[l1][r1] - 1] != 0)
            cout << "\n Left child of " << keys[r[l1][r1] - 1] << " :: " << keys[r[l1][r[l1][r1] - 1]];
        if (r[r[l1][r1]][r1] != 0)
            cout << "\n Right child of " << keys[r[l1][r1] - 1] << " :: " << keys[r[r[l1][r1]][r1] - 1];
        printTreeStructure(l1, r[l1][r1] - 1);
        printTreeStructure(r[l1][r1], r1);
    }
};

int main() {
    OptimalBST obst;
    cout << "\n**** PROGRAM FOR OBST ******\n";
    obst.inputProbabilitiesAndKeys();
    obst.constructOBST();
    obst.showSearchCosts();
    return 0;
}

