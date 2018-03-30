#include <iostream>
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
	string caractere;
	vector<int> freq;
	vector<vector<char> > all;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin >> caractere;
		caractere = " " + caractere; // Adaugare element fictiv -
									 // indexare de la 1.
		freq.push_back(-1); // Adaugare element fictiv - indexare de la 1.
		for (int i = 1, f; i <= n; i++) {
			fin >> f;
			freq.push_back(f);
		}
		fin.close();
	}

	bool check (vector<char> sol, char character, int p) {
		int s = 0;
		if (p < k)
			return true;
		for (int i = 1; i <= k; ++i)
			if(sol[p - i] != character)
				return true;
		return false;
	}	
	
	int sum_vector () {
		int s = 0;
		for(int m = 1; m < freq.size(); m++)
			s = s + freq[m];
		return s;
	}
	
	void back (int k, vector<int> aux, vector<char> sol) {
		vector<int> aux1;
		aux1.push_back(0);	
		if(k == sum_vector ())
			return;	
		for (int i = 1; i < caractere.size(); ++i) {	
			if(aux[i] > 0 && check(sol, caractere[i], k)) {
				for(int l = 1; l < freq.size(); l++) {	
					aux1.push_back(aux[l]);
				}	
				sol.push_back(caractere[i]);
				--aux[i];
				
				if(k == sum_vector() - 1) {
					all.push_back(sol);
				}	
				back(k + 1, aux, sol);
				for(int l = 1; l < freq.size(); l++) {
					aux[l] = aux1[l];
				}
				sol.pop_back();
			}
			else 
				continue;
		}
		
	}

	vector<vector<char> > get_result() {
		

		/*
		TODO: Construiti toate sirurile cu caracterele in stringul caractere
		(indexat de la 1 la n), si frecventele in vectorul freq (indexat de la
		1 la n), stiind ca nu pot fi mai mult de K aparitii consecutive ale
		aceluiasi caracter.

		Pentru a adauga un nou sir:
			vector<char> sir;
			all.push_back(sir);
		*/
		vector<int> aux;
		aux.push_back(0); // retarded index
		vector<char> sol;
		for (int i = 1; i <= freq.size(); ++i) {
			aux.push_back(freq[i]);
		}
		back(0, aux, sol);
		return all;
	}

	void print_output(vector<vector<char> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j];
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
