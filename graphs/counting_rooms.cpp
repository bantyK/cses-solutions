#include <iostream>
// https://cses.fi/problemset/task/1192
using namespace std;

char mat[1000][1000];
int m, n;

void dfs(int i, int j) {
    if (i < 0 || i >= m) return;
    if (j < 0 || j >= n) return;
    if (mat[i][j] == '#') return;

    mat[i][j] = '#';

    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
}

int main() {
    cin >> m >> n;
    char in;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == '.') {
                dfs(i, j);
                count += 1;
            }
        }
    }
    cout << count << "\n";
    return 0;
}