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

    in.close(); // Закрываем входной файл

    long long l = 0;

    // Используем две минимальные кучи для оптимизации
    priority_queue<long long, vector<long long>, greater<long long>> heap1, heap2;

    while (!min_heap.empty() || heap1.size() > 1 || heap2.size() > 1) {
        // Заполняем две минимальные кучи
        while (min_heap.size() > 1 && (heap1.empty() || heap2.empty() || min_heap.top() <= heap1.top() || min_heap.top() <= heap2.top())) {
            long long x = min_heap.top();
            min_heap.pop();
            long long y = min_heap.top();
            min_heap.pop();
            heap1.push(x);
            heap2.push(y);
        }

        long long x = heap1.top();
        heap1.pop();
        long long y = heap2.top();
        heap2.pop();

        long long sum = x + y;
        l += sum;

        // Вставляем сумму обратно в минимальные кучи
        if (!heap1.empty() && (min_heap.empty() || heap1.top() < min_heap.top())) {
            heap2.push(sum);
        }
        else {
            heap1.push(sum);
        }
    }

    out << l << endl; // Записываем результат в выходной файл

    out.close(); // Закрываем выходной файл

    return 0;
}
