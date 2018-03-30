#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;
	vector<vector<int> > all;
	vector<int> vect;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		vect.resize(n);
		fin.close();
	}


	bool check (int count) {
		for (int i = 0; i <= count - 2; ++i) {
			if (vect[i] == vect[count - 1])
				return false;
		}
		return true;
	}

	void backtracking (int count) {
		if (count > k) {
			vector<int> dummy; // ca sa adaug in matrice
			for (int i = 0; i < count; ++i)
				dummy.push_back(vect[i]);
			dummy.pop_back();
			all.push_back(dummy);
		}
		else {
			for (int i = 0; i < n; ++i) {
				vect[count - 1] = i + 1;
				if (check (count)) {
					backtracking(count + 1);
				}
			}
		}
	}

	vector<vector<int> > get_result() {

		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/

		backtracking(1);

		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
