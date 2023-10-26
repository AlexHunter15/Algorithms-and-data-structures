#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isHeap(vector<int>& arr) {
    int n = arr.size();

    for (int i = n - 1; i > 0; i--) {
        int p = (i - 1) / 2;
        if (arr[i] < arr[p]) {
            return false;
        }
    }

    return true;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        in >> arr[i];
    }

    if (isHeap(arr)) {
        out << "Yes" << endl;
    }
    else {
        out << "No" << endl;
    }

    in.close();
    out.close();

    return 0;
}
