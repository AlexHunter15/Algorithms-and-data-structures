#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string str;
    input >> str;

    int n = str.length();
    vector<vector<int>> mtr(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        mtr[i][i] = 1;
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (str[i] == str[j]) {
                mtr[i][j] = mtr[i + 1][j - 1] + 2;
            }
            else {
                mtr[i][j] = max(mtr[i + 1][j], mtr[i][j - 1]);
            }
        }
    }

    int l = mtr[0][n - 1];

    string pal;
    pal.reserve(l);

    int i = 0, j = n - 1;
    while (i < j) {
        if (str[i] == str[j]) {
            pal += str[i];
            i++;
            j--;
        }
        else if (mtr[i][j] == mtr[i + 1][j]) {
            i++;
        }
        else {
            j--;
        }
    }

    string rev = pal;
    if (i == j) {
        pal += str[i];
    }
    reverse(rev.begin(), rev.end());
    pal += rev;

    output << l << endl;
    output << pal << endl;

    input.close();
    output.close();

    return 0;
}





/*#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string S;
    input >> S;

    int n = S.length();
    vector<int> dp(n, 0);
    vector<int> prev_dp(n, 0);

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (S[i] == S[j]) {
                dp[j] = prev_dp[j - 1];
            }
            else {
                dp[j] = min(dp[j - 1], dp[j]) + 1;
            }
        }
        swap(dp, prev_dp);
    }

    int minDeletions = prev_dp[n - 1];

    string palindrome;
    palindrome.reserve(n - minDeletions);

    int i = 0, j = n - 1;
    while (i < j) {
        if (S[i] == S[j]) {
            palindrome += S[i];
            i++;
            j--;
        }
        else if (prev_dp[j] == prev_dp[j - 1] + 1) {
            j--;
        }
        else {
            i++;
        }
    }

    if (i == j) {
        palindrome += S[i];
    }

    output << palindrome.length() << endl;
    output << palindrome << endl;

    input.close();
    output.close();

    return 0;
}
*/