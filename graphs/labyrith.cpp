// https://cses.fi/problemset/task/1193/

#include <bits/stdc++.h>
using namespace std;
 
#define ii pair<int, int>
#define mp make_pair
#define f first
#define s second
 
int r, c;
char mat[1001][1001];
bool visited[1001][1001];
int directions[4][2] = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};
char labels[4] = {'D', 'U', 'R', 'L'};
int previousPath[1001][1001];
ii begin_pos, end_pos;
void print_path(ii curr);
int main()
{
    cin >> r >> c;
    queue<ii> queue;
 
 
    for (int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> mat[i][j];
 
            if(mat[i][j] == 'A') {
                begin_pos = mp(i, j);
            } else if(mat[i][j] == 'B') {
                end_pos = mp(i, j);
            }
        }
    }
    queue.push(begin_pos);
    visited[begin_pos.f][begin_pos.s] = true;
 
    while(!queue.empty()) {
        ii  curr = queue.front(); queue.pop();
        int x = curr.f;
        int y = curr.s;
 
        if(x == end_pos.f && y == end_pos.s) {
            cout << "YES\n";
            print_path(curr);
            return 0;
        }
 
        for(int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];
 
            if(new_x < 0 || new_x >= r || new_y < 0 || new_y >= c) continue;
            if(visited[new_x][new_y]) continue;
            if(mat[new_x][new_y] == '#') continue;
            visited[new_x][new_y] = true;
            previousPath[new_x][new_y] = i;
            queue.push(mp(new_x, new_y));
        }
    }
    cout << "NO";
}
 
void print_path(ii curr) {
    vector<int> steps;
    while(curr != begin_pos) {
        int p = previousPath[curr.f][curr.s];
        steps.push_back(p);
        curr = mp(curr.f - directions[p][0], curr.s - directions[p][1]);
    }
    reverse(steps.begin(), steps.end());
 
    cout << steps.size() << "\n";
 
    for(int step : steps) {
        cout << labels[step] << "";
    }
}