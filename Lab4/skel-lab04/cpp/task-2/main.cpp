#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	string expr;

	void read_input() {
		ifstream fin("in");
		fin >> n >> expr;
		expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de parantezari ale expresiei date astfel incat
		rezultatul sa dea true si returnati restul impartirii numarului
		la 10^9 + 7.
		*/
		vector<vector<long long int>> tableTrue;
		vector<vector<long long int>> tableFalse;
		tableTrue.resize(n + 1);
		tableFalse.resize(n + 1);

        for (int i = 0; i <= n; i++) {
            tableTrue[i].resize(n + 1, 0LL);
			tableFalse[i].resize(n + 1, 0LL);
        }

        for (int i = 1; i <= n; i++) {
            if (expr[i] == 'T') {
            	tableTrue[i][i] = 1LL;
                tableFalse[i][i] = 0LL;
            }
            else if (expr[i] == 'F') {
                tableTrue[i][i] = 0LL;
                tableFalse[i][i] = 1LL;
            }
    	}

        for (int x = 2; x < n; x += 2) {
            for (int i = 1; i <= n - x; i += 2) {
                int j = i + x;
                for (int k = i + 1; k < j; k += 2) {

					switch (expr[k]) {
						case '&':
							tableTrue[i][j] += (1LL * tableTrue[i][k - 1] * tableTrue[k + 1][j]) % kMod;
                            tableFalse[i][j] += (1LL * tableFalse[i][k - 1] * tableTrue[k + 1][j] 
									+ 1LL * tableTrue[i][k - 1] * tableFalse[k + 1][j] 
									+ 1LL * tableFalse[i][k - 1] * tableFalse[k + 1][j]) % kMod;
							break;
						case '|':
							tableTrue[i][j] += (1LL * tableTrue[i][k - 1] * tableTrue[k + 1][j] 
									+ 1LL * tableTrue[i][k - 1] * tableFalse[k + 1][j] 
									+ 1LL * tableFalse[i][k - 1] * tableTrue[k + 1][j]) % kMod;
                            tableFalse[i][j] += (1LL * tableFalse[i][k - 1] * tableFalse[k + 1][j]) % kMod;
							break;
						case '^':
							tableTrue[i][j] += (1LL * tableTrue[i][k - 1] * tableFalse[k + 1][j] 
									+ 1LL * tableFalse[i][k - 1] * tableTrue[k + 1][j]) % kMod;
                            tableFalse[i][j] += (1LL * tableTrue[i][k - 1] * tableTrue[k + 1][j] 
									+ 1LL * tableFalse[i][k - 1] * tableFalse[k + 1][j]) % kMod;
							break;
					}
					tableTrue[i][j] = tableTrue[i][j] % kMod;
            		tableFalse[i][j] = tableFalse[i][j] % kMod;
                }
            }
    	}
        return tableTrue[1][n];

	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
