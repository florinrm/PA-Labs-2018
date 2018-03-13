#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> dist;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 0, d; i < n; i++) {
			fin >> d;
			dist.push_back(d);
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati numarul minim de opriri necesare pentru a ajunge
		la destinatie.
		*/
		int start = 0, count = 0;
		for (int i = 0; i < dist.size(); ++i) {
			while ((dist[i] - start) <= m && i < dist.size()) {
				i++;
				if ((dist[i] - start) > m) {
					++count;
					start = dist[i - 1];
				}
			}
		}
		return count;

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
