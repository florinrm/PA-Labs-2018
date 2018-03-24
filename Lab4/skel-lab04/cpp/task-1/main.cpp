#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de subsiruri ale lui v cu suma numerelor para si
		returnati restul impartirii numarului la 10^9 + 7.
		*/
		vector <long long int> even; // pare
		vector <long long int> odd; // impare;
		even.resize(n + 1, 0LL);
		odd.resize(n + 1, 0LL);

		for (int i = 1; i <= n; ++i) {
			if (v[i] % 2 == 0) {
				even[i] = (2 * even[i - 1] + 1) % kMod;
                odd[i] = (2 * odd[i - 1]) % kMod;
			} else {
				even[i] = (even[i - 1] + odd[i - 1]) % kMod;
                odd[i] = (even[i - 1] + odd[i - 1] + 1) % kMod;

			}
		}

		return even[n];
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
