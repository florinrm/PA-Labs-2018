#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> vect;
	vector<vector<int> > all;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		vect.resize(n + 1);
		fin.close();
	}

	void back (int k) {
		for (int i = vect[k - 1] + 1; i <= n; ++i) {
			vect[k] = i;
			vector<int> buff;
			for (int j = 1; j <= k; ++j) {
				buff.push_back(vect[j]);
			}
			all.push_back(buff);
			back(k + 1);
		}		 
	}
	

	vector<vector<int> > get_result() {

		/*
		TODO: Construiti toate submultimile multimii {1, ..., N}.

		Pentru a adauga o noua submultime:
			vector<int> submultime;
			all.push_back(submultime);
		*/
		vector<int> meh;
		meh.resize(0); // multime vida - sa treaca testele
		all.push_back(meh);
		back(1);
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
