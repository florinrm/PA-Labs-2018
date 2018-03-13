#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Result {
	int len;
	vector<int> subsequence;
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> v;
	vector<int> w;

	int max (int a, int b) {
		if (a <= b)
			return b;
		return a;
	}

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}

		w.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= m; i++) {
			fin >> e;
			w.push_back(e);
		}

		fin.close();
	}

	Result get_result() {
		Result result;
		result.len = 0;
		vector<vector<int>> matrix;
		matrix.resize (v.size() + 1);
		for (int i = 0; i < v.size() + 1; ++i) {
			matrix[i].resize(w.size() + 1, 0);
		}

		/*
		TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
		si w (de lungime m).
		Se puncteaza separat urmatoarele 2 cerinte:
		2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune in
		``result.len``.
		2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal valid.
		Solutia pentru aceasta cerinta se va pune in ``result.subsequence``.
		*/
		for (int i = 1; i <= v.size(); ++i) {
			for (int j = 1; j <= w.size(); ++j) {
				if (v[i - 1] == w[j - 1])
					matrix[i][j] = 1 + matrix[i - 1][j - 1];
				else
					matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);
			}
		}

		result.len = matrix[v.size()][w.size()] - 1;
		// printf("%d\n", matrix[v.size()][w.size()]);
		int len = result.len;
		int i = v.size(), j = w.size();
		while (i > 0 && j > 0) {
			if (v[i - 1] == w[j - 1]) {
				result.subsequence.push_back(v[i - 1]);
				i--;
				j--;
			} else if (matrix[i - 1][j] > matrix[i][j - 1]) {
				i--;
			} else
				j--;
		}
		result.subsequence.pop_back(); // sa scap de -1 lelz
		reverse(result.subsequence.begin(), result.subsequence.end());
		return result;
	}

	void print_output(Result result) {
		ofstream fout("out");
		fout << result.len << '\n';
		for (int x : result.subsequence) {
			fout << x << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
