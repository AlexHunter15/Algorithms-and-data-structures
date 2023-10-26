#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), arr(n, -1), p(n, -1);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    arr[0] = a[0];

    for (int i = 1; i < n; ++i) {
        if (i >= 2) {
            if (arr[i - 2] + a[i] > arr[i]) {
                arr[i] = arr[i - 2] + a[i];
                p[i] = i - 2;
            }
        }
        if (i >= 3) {
            if (arr[i - 3] + a[i] > arr[i]) {
                arr[i] = arr[i - 3] + a[i];
                p[i] = i - 3;
            }
        }
    }

    int l = n - 1;
    if (arr[l] <= 0) {
        cout << "-1" << endl;
    }
    else {
        vector<int> res;
        while (l >= 0) {
            res.push_back(l + 1);
            l = p[l];
        }
        cout << arr[n - 1] << endl;
        for (int i = res.size() - 1; i >= 0; --i) {
            cout << res[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
