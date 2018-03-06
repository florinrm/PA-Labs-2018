#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Object {
	int weight;
	int price;

	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

bool cmp (const Object &one, const Object &two) {
		return ((double) one.price / one.weight) > ((double) two.price / two.weight);
	}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	vector<Object> objs;

	void read_input() {
		ifstream fin("in");
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}

	double get_result() {
		/*
		TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
		*/
		sort(objs.begin(), objs.end(), cmp);
		double result = 0, sum_weight = 0;
		for (int i = 0; i < objs.size(); ++i) {
			if ((sum_weight + objs[i].weight) <= w) {
				sum_weight += objs[i].weight;
				result += objs[i].price;
			} else {
				double remainder = w - sum_weight;
				result += remainder * ((double) objs[i].price / objs[i].weight);
				sum_weight += remainder;
			}
		}
		return result;
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}