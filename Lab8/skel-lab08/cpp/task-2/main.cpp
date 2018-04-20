#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
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
	int time = 0;
	vector<bool> visited;
	vector<int> parent;
	vector<int> discovered;
	vector<bool> articulation;
	vector<int> lel;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void doStuff (int v) {
		int kids = 0;
		visited[v] = true;
		++time;
		discovered[v] = time;
		lel[v] = time;
		for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
			if (!visited[*i]) {
				parent[*i] = v;
				++kids;
				doStuff (*i);
				lel[v] = lel[v] <= lel[*i] ? lel[v] : lel[*i];
				if (parent[v] == INT_MIN && kids > 1)
					articulation[v] = true;
				if (parent[v] != INT_MIN && lel[*i] >= discovered[v])
					articulation[v] = true;
			} else if (*i != parent[v])
				lel[v] = lel[v] <= discovered[*i] ? lel[v] : discovered[*i];
		}
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/
		vector<int> sol;
		visited.resize(n + 1, false);
		articulation.resize(n + 1, false);
		parent.resize(n + 1, INT_MIN);
		lel.resize(n + 1, 0);
		discovered.resize(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			if (!visited[i])
				doStuff(i);
		}
		for (int i = 1; i <= n; ++i) {
			if (articulation[i])
				sol.push_back(i);
		}
		return sol;
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
