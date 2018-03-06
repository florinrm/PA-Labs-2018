#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

int merge (std::vector<int> vect, int lower, int middle, int upper) {
    int count = 0;
    int i = lower, j = middle + 1;
    std::vector<int> aux;
    while ((i < middle) && (j <= upper)) {
        if (vect[i] <= vect[j]) {
            aux.push_back (vect[i++]);
        } else {
            aux.push_back (vect[j++]);
            count += middle - i;
        }
    }
    while (i < middle)
        aux.push_back (vect[i++]);
    while (j <= upper)
        aux.push_back (vect[j++]);
    for (int p = lower; p < upper; ++p)
        vect[p] = aux[p - lower];
    return count;
}

int mergeSortCounting (std::vector<int> v, int lower, int upper) {
    if (lower >= upper)
        return 0;
    int count = 0;
    int middle = lower + (upper - lower) / 2;
    count += mergeSortCounting (v, lower, middle);
    count += mergeSortCounting (v, middle + 1, upper);
    count += merge (v, lower, middle + 1, upper);
    return count;
}

int count_inversions(std::vector<int> v)
{
    return mergeSortCounting (v, 0, v.size() - 1);
}


int main () {
    int array[] = {0, 1, 9, 4, 5, 7, 6, 8, 2};
    std::vector<int> vect (array, array + sizeof(array) / sizeof(int));
    for (int i = 0; i < vect.size(); ++i)
        std::cout << vect[i] << " ";
    std::cout << std::endl;
    std::cout << "Numarul de inversiuni in vector: " << count_inversions (vect) << std::endl;
    return 0;
}