#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

const int DOWN = 5;
const int LEFT = -1;
const int RIGHT = 1;
const int UP = -5;

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Failed to open input.txt or output.txt" << endl;
        return 1;
    }

    int n, m, k;
    inputFile >> n >> m >> k;
    vector<int> in(k);
    vector<int> out(k);
    vector<vector<int>> v(n, vector<int>(m));

    for (int i = 0; i < k; ++i) {
        inputFile >> in[i];
        --in[i];
    }
    for (int i = 0; i < k; ++i) {
        inputFile >> out[i];
        --out[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inputFile >> v[i][j];
        }
    }

    for (int i = 0; i < k; ++i) {
        v[n - 1][out[i]] = -3;
    }

    int count = 0;

    for (int i = 0; i < k; ++i) {
        stack<pair<pair<int, int>, int>> temp;

        if (v[0][in[i]] != 0) {
            continue;
        }

        temp.push(make_pair(make_pair(0, in[i]), DOWN));

        while (!temp.empty()) {
            auto item = temp.top().first;
            int dir = temp.top().second;
            temp.pop();

            if (v[item.first][item.second] < -2) {
                ++count;
                v[item.first][item.second] = -4 - i;
                break;
            }
            else {
                v[item.first][item.second] = i + 2;
            }

            int next_pos[3];
            switch (dir) {
            case DOWN:
                next_pos[0] = LEFT;
                next_pos[1] = DOWN;
                next_pos[2] = RIGHT;
                break;
            case LEFT:
                next_pos[0] = UP;
                next_pos[1] = LEFT;
                next_pos[2] = DOWN;
                break;
            case RIGHT:
                next_pos[0] = DOWN;
                next_pos[1] = RIGHT;
                next_pos[2] = UP;
                break;
            default:
                next_pos[0] = RIGHT;
                next_pos[1] = UP;
                next_pos[2] = LEFT;
            }

            bool all = true;

            for (int j = 0; j < 3; ++j) {
                int next_i = item.first + next_pos[j] / 5;
                int next_j = item.second + next_pos[j] % 5;

                if (next_i >= 0 && next_i < n &&
                    next_j >= 0 && next_j < m &&
                    (v[next_i][next_j] == 0 || v[next_i][next_j] < -2)) {

                    pair<int, int> new_item(next_i, next_j);
                    temp.push(make_pair(item, dir));
                    temp.push(make_pair(new_item, next_pos[j]));
                    all = false;
                    break;
                }
            }

            if (all) {
                v[item.first][item.second] = -2;
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int l = 0; l < m; ++l) {
            if (v[j][l] == -2) {
                v[j][l] = 0;
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        if (v[n - 1][out[i]] == -3) {
            v[n - 1][out[i]] = 0;
        }
        else {
            v[n - 1][out[i]] = -v[n - 1][out[i]] - 2;
        }
    }

    outputFile << count << endl;
    for (int i = 0; i < n; ++i) {
        outputFile << v[i][0];
        for (int j = 1; j < m; ++j) {
            outputFile << " " << v[i][j];
        }
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
