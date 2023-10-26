#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int lowerBound(vector<int>& mtr, int x) {
    int left = 0, right = mtr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mtr[mid] >= x) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    vector<int> seq(n);
    for (int i = 0; i < n; ++i) {
        in >> seq[i];
    }

    vector<int> arr;
    for (int i = 0; i < n; ++i) {
        int ind = lowerBound(arr, seq[i]);
        if (ind == arr.size()) {
            arr.push_back(seq[i]);
        }
        else {
            arr[ind] = seq[i];
        }
    }

    int maxLen = arr.size();
    out << maxLen << endl;

    in.close();
    out.close();

    return 0;
}
