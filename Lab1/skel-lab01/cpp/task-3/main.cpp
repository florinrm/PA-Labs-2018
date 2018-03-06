#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result(n, x, y));
	}

private:
	int n, x, y;

	void read_input() {
		ifstream fin("in");
		fin >> n >> x >> y;
		fin.close();
	}

	int get_result(int n, int x, int y) {
		/*
		TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune
		2^n x 2^n
		*/
		if (n == 1) {
			if (x == 1 && y == 1)
				return 1;
			if (x == 1 && y == 2)
				return 2;
			if (x == 2 && y == 1)
				return 3;
			if (x == 2 && y == 2)
				return 4;
		} // cazul de baza

		int pas = (int) pow(2, (2 * n - 2));
		int middle = (int) pow (2, (n - 1)); // pentru cadrane
		if (x <= middle && y <= middle)
			return get_result(n - 1, x, y); // reducem pana la cazul de baza
		if (x <= middle && y > middle)
			return pas + get_result (n - 1, x, y - middle);
		if (x > middle && y <= middle)
			return 2 * pas + get_result (n - 1, x - middle, y);	
		if (x > middle && y > middle)
			return 3 * pas + get_result (n - 1, x - middle, y - middle);
		return 0;
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
