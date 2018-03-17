#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdio>

using namespace std;

int min (int a, int b);
int min (int a, int b, int c);

int main () {
    int n;
    ifstream read ("custi.in");
    read >> n;
    vector<vector<int> > matrix;
    vector<vector<int> > table;
    matrix.resize(n + 1);
    table.resize(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        matrix[i].resize(n + 1);
        table[i].resize(n + 1);
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j)
            read >> matrix[i][j];
    }
    read.close();

    vector<int> result;
    result.resize(n + 1); // salvez numarul de aparitii
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (matrix[i][j] == 1) {
                table[i][j] = 1 + min (table[i - 1][j - 1], table[i - 1][j], table[i][j - 1]);
                ++result[table[i][j]];
            }
        }
    }
    for (int i = n - 1; i >= 1; --i)
        result[i] += result[i + 1];
    ofstream print ("custi.out");
    for (int i = 1; i < n + 1; ++i)
        print << result[i] << endl;
    print.close();
    return 0;
}

int min (int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}

int min (int a, int b, int c) {
    if (c <= min (a, b))
        return c;
    else
        return min (a, b);
}