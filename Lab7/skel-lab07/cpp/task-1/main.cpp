#include <fstream>
#include <vector>
#include <list>
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
	int source;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
		vector<int> d(n + 1, -1);
        d[source] = 0;
        queue<int> queueBFS;
        int minDist = 1;
        queueBFS.push(source);

        while (!queueBFS.empty()) {
            int tempS = queueBFS.front();
            queueBFS.pop();
            for (auto i = adj[tempS].begin(); i != adj[tempS].end(); i++) {
                if (d[*i] == -1) {
                    d[*i] = minDist + d[tempS];
                    queueBFS.push(*i);
                }
            }
        }

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
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
