#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    long long n;
    in >> n;

    vector<int> arr;
    int h = 0;
    long long r = n;

    while (r > 0) {
        if (r % 2 == 1) {
            arr.push_back(h); 
            r -= 1;
        }
        r /= 2; 
        h++;
    }

    if (r == 0) {
        for (int h : arr) {
            out << h << endl;
        }
    }
    else {
        out << "-1" << endl;
    }

    in.close();
    out.close();

    return 0;
}
