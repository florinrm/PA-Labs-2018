#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Faceti sortarea topologica a grafului stocat cu liste de
		adiacenta in adj.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		vector<int> topsort;
		vector<int> in_muchii (n + 1, 0);
		queue<int> sorting;
		for (int i = 1; i <= n; ++i) {
			for (int node: adj[i]) {
				++in_muchii[node];
			}
		}

		for (int i = 1; i <= n; ++i) {
			if (in_muchii[i] == 0)
				sorting.push(i);
		}
		int count = 0;
		while (!sorting.empty()) {
			int node = sorting.front();
			sorting.pop();
			topsort.push_back(node);
			for (int nod: adj[node]) {
				if (--in_muchii[nod] == 0)
					sorting.push(nod);
			}
			++count;
		}

		return topsort;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
