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
			bool ok = false;
			while ((dist[i] - start) <= m && i < dist.size()) {
				i++;
				if ((dist[i] - start) > m) {
					++count;
					start = dist[i - 1];
				}
			}
		}
		return count;

		/*
		int start = 0, count = 0;
		for (int i = 0; i < dist.size(); ++i) {
			bool ok = false;
			while ((start + dist[i]) <= m) {
				++i;
				if ((start + dist[i]) > m)
					ok = true;

			}
			if (!ok) {
				start = dist[i - 1];
			++count;
			}
		} */
		/*
		return count; 
		if (dist[dist.size() - 1] <= m)
			return 0;
		
		int result = 0, coord = 0, pos = 0;
		vector<int> benzinarii;

		while (coord < dist.size() - 1) {
			pos = coord;
			while (dist[pos] <= dist[coord] + m && pos < dist.size())
				++pos;
			benzinarii.push_back (dist[pos - 1]);
			if (pos > coord - 1)
				coord = pos - 1;
			else
				coord++;
		}
		result = benzinarii.size();
		return result; */
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
