#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main() {
    ifstream in("huffman.in");
    ofstream out("huffman.out");
    int n;
    in >> n;

    priority_queue<long long, vector<long long>, greater<long long>> min_heap;

    for (int i = 0; i < n; i++) {
        long long pi;
        in >> pi;
        min_heap.push(pi);
    }

    long long l = 0;

    while (min_heap.size() > 1) {
        long long x = min_heap.top();
        min_heap.pop();
        long long y = min_heap.top();
        min_heap.pop();
        long long sum = x + y;
        l += sum;
        min_heap.push(sum);
    }

    out << l << endl;

    in.close();
    out.close();

    return 0;
}
