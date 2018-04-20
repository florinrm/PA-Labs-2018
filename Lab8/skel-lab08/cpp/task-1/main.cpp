#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
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
	vector<int> adjt[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}
	vector<bool> visited;
	stack <int> st;
	vector <int> buff;

	void kindOfDFS (int v) {
		visited[v] = true;
		for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
			if (!visited[*i])
				kindOfDFS(*i);
		}
		st.push(v);
	}

	void DFS (int v) {
		visited[v] = true;
		buff.push_back(v);
		for (auto i = adjt[v].begin(); i != adjt[v].end(); ++i) {
			if (!visited[*i])
				DFS(*i);
		}
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.
		
		Atentie: graful transpus este stocat in adjt.
		*/
		vector<vector<int>> sol;
		visited.resize(n + 1, false);
		for (int i = 1; i <= n; ++i) {
			if (!visited[i])
				kindOfDFS(i);
		}
		for (int i = 1; i <= n; ++i)
			visited[i] = false;
		while (!st.empty()) {
			int v = st.top();
			st.pop();
			if (!visited[v]) {
				DFS(v);
				sol.push_back(buff);
				buff.clear();
			}
		}
		return sol;
	}

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
