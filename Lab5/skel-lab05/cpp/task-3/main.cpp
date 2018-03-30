#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<vector<int>> table;
	vector<int> sol;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		table.resize(n);
		sol.resize(n + 1, 0);
		for (int i = 0; i < n; ++i)
			table[i].resize(n, 0);
		fin.close();
	}

	int checkTable (int row, int col) {
		for (int i = 0; i < col; ++i) {
			if (table[row][i])
				return 0;
		}
		for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
			if (table[i][j])
				return 0;
		}
		for (int i = row, j = col; j >= 0 && i < n; ++i, --j) {
			if (table[i][j])
				return 0;
		}
		return 1;
	}

	int queens (int col) {
		if (col >= n)
			return 1;
		for (int i = 0; i < n; ++i) {
			if (checkTable(i, col)) {
				table[i][col] = 1;
				sol[i + 1] = col;
				if (queens(col + 1))
					return 1;
				table[i][col] = 0;
			}
		}
		return 0;
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/
		queens(0);
		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i != n ? ' ' : '\n');
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
