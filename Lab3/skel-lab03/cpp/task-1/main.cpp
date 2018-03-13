#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, S;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n >> S;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int min (int a, int b) {
		if (a <= b)
			return a;
		else
			return b;
	}

	int get_result() {
		/*
		TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
		suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
		*/
		if (S < 0)
			return -1;
		vector<int> data;
		data.resize(S + 1, 0);
		for (int i = 1; i <= S; ++i)
			data[i] = INT_MAX;
		for (int i = 1; i <= S; ++i) { // caci indexarea e de la 1 lelz
			for (int j = 1; j <= n; ++j) {
				if (i >= v[j])
					data[i] = min (data[i], data[i - v[j]] + 1);
			}
		}
		if (data[S] == INT_MIN)
			return -1;
		else
			return data[S];
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
