#include <bits/stdc++.h>
using namespace std;
 
class Task {
public:
	void solve() {
		read_input();
		print_output(get_result());
	}
 
private:
	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, e; i < n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin >> x;
		fin.close();
	}
 
	int find_first() {
		int left = 0, right = n - 1, mid, res = -1;
		while (left <= right) {
			mid = (left + right) / 2;
			if (v[mid] >= x) {
				res = mid;
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}
		return res;
	}
 
	int find_last() {
		int left = 0, right = n - 1, mid, res = -1;
		while (left <= right) {
			mid = (left + right) / 2;
			if (v[mid] <= x) {
				res = mid;
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return res;
	}
 
	int get_result() {
		int first = find_first();
		int last = find_last();
		if (first == -1 || last == -1) {
			return 0;
		}
		return last - first + 1;
	}
 
	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
 
	int n, x;
	vector<int> v;
};
 
int main() {
	Task task;
	task.solve();
	return 0;
}