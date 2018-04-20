#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
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
	int time = 0;
	vector<bool> visited;
	vector<int> parent;
	vector<int> discovered;
	vector<int> lel;
	vector<int> adj[kNmax];

	struct Edge {
		int x;
		int y;
		Edge(int _x, int _y) : x(_x), y(_y) {}
	};
	vector<Edge> sol;
	stack <Edge> st;

	void read_input() {
		ifstream fin("biconex.in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void doStuff (int v) {
		visited[v] = true;
		++time;
		int kids = 0;
		discovered[v] = time;
		lel[v] = time;
		for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
			if (discovered[*i] == INT_MIN) {
				parent[*i] = v;
				++kids;
				st.push(Edge(v, *i));
				doStuff(*i);
				lel[v] = lel[v] <= lel[*i] ? lel[v] : lel[*i];
				if (discovered[v] == 1 && kids >= 2 
						|| discovered[v] > 1 && discovered[v] <= lel[*i]) {
					while (st.top().x != v || st.top().y != *i) {
						sol.push_back(st.top());
						st.pop();
					}
					sol.push_back(st.top());
						st.pop();

				}
			} else if (parent[v] != *i && discovered[*i] < lel[v]) {
				lel[v] = lel[v] <= discovered[*i] ? lel[v] : discovered[*i];
				st.push(Edge(v, *i));
			}
		}
	}

	vector<Edge> get_result() {
		/*
		TODO: Gasiti muchiile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/
		visited.resize(n + 1, false);
		parent.resize(n + 1, INT_MIN);
		lel.resize(n + 1, INT_MIN);
		discovered.resize(n + 1, INT_MIN);
		for (int i = 1; i <= n; ++i) {
			if (discovered[i] == INT_MIN) {
				doStuff(i);
			}
			while (!st.empty()) {
				sol.push_back(st.top());
				st.pop();
			}
		}
		return sol;
	}

	void print_output(vector<Edge> result) {
		ofstream fout("biconex.out");
		fout << result.size() << '\n';
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i].x << ' ' << result[i].y << '\n';
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
