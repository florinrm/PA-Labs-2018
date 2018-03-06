#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework (int _deadline, int _score) : deadline(_deadline), score(_score) {}

	bool operator < (const Homework & lel) {
    	return score > lel.score || (score == lel.score && deadline < lel.deadline);
  	}

};

bool cmp (const Homework &one, const Homework &two) {
	if (one.score == two.score)
		return one.deadline < two.deadline;
	else
		return one.score > two.score;
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati punctajul maxim pe care il puteti obtine planificand
		optim temele.
		*/
		sort (hws.begin(), hws.end());
		for (int i = 0; i < hws.size(); ++i) {
			cout << hws[i].score << " " << hws[i].deadline << endl;
		}
		int total_score = 0, weeks = 0;
		for (int i = 0; i < hws.size(); ++i) {
			if (weeks <= hws[i].deadline) {
				++weeks;
				total_score += hws[i].score;
			}
		}

		return total_score;
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