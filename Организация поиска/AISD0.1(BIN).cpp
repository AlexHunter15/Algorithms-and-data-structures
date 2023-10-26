#include <cstdio>

int binSearch(const int arr[], int n, int x) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            return mid;
        }
        else if (arr[mid] < x) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

int lowerBound(const int arr[], int n, int x) {
    int low = 0;
    int high = n;

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < x) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    return low;
}

int upperBound(const int arr[], int n, int x) {
    int low = 0;
    int high = n;

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= x) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    return low;
}

int main() {
    int n;
    scanf_s("%d", &n);
    static int arr[300000];

    for (int i = 0; i < n; ++i) {
        scanf_s("%d", &arr[i]);
    }

    int k;
    scanf_s("%d", &k);
    static int q[300000];

    for (int i = 0; i < k; ++i) {
        scanf_s("%d", &q[i]);
    }

    for (int i = 0; i < k; ++i) {
        int x = q[i];
        int ind = binSearch(arr, n, x);

        if (ind != -1) {
            int l = lowerBound(arr, n, x);
            int r = upperBound(arr, n, x);

            printf("1 %d %d\n", l, r);
        }
        else {
            int l = lowerBound(arr, n, x);
            printf("0 %d %d\n", l, l);
        }
    }

    return 0;
}
