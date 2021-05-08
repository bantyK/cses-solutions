// https://cses.fi/problemset/task/1194/
#include<bits/stdc++.h>
 
#define SZ 1001
#define mp make_pair
#define ii pair<int, int>
using namespace std;
int graph[SZ][SZ];
int previousPath[SZ][SZ];
vector<ii > monster_positions;
ii playerStartPos, playerEscapePos;
vector<ii > moves = {{1,  0},
                     {-1, 0},
                     {0,  1},
                     {0,  -1}};
char directions[] = {'D', 'U', 'R', 'L'};
int rows, cols;
 
bool isValidMovement(int x, int y, int time) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        // cannot move outside the grid
        return false;
    }
 
    // this represent that a monster has already reached to this cell before this time
    if (graph[x][y] <= time) {
        return false;
    }
 
    return true;
}
 
void preprocess_monster_movement() {
    queue<pair<ii, int>> queue;
    // multi value BFS, this will avoid overwriting same cell again and again by monsters
    for (auto monsterPos : monster_positions) {
        queue.push(mp(monsterPos, 0));
    }
 
    while (!queue.empty()) {
 
        pair<ii, int> curr = queue.front();
        int cx = curr.first.first;
        int cy = curr.first.second;
        int currTime = curr.second;
        queue.pop();
        ++currTime;
 
        for (auto direction : moves) {
            int newX = cx + direction.first;
            int newY = cy + direction.second;
 
            if (isValidMovement(newX, newY, currTime)) {
                graph[newX][newY] = currTime;
                queue.push(mp(mp(newX, newY), currTime));
            }
        }
    }
}
 
bool playerEscaped(int x, int y, int time) {
    if (!isValidMovement(x, y, time)) {
        // if the monster reaches to a boundary cell first then that cannot be considered as escape point
        return false;
    }
    // player has reached a boundary position before any monster
 
    if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1) {
        return true;
    }
 
    return false; // for any other cell, it is not a escape point
}
 
bool player_movement() {
    queue<pair<ii, int>> queue;
 
    queue.push(mp(playerStartPos, 0));
 
    while (!queue.empty()) {
        pair<ii, int> curr = queue.front();
        curr = queue.front();
        int cx = curr.first.first;
        int cy = curr.first.second;
        int currTime = curr.second;
        queue.pop();
        if (playerEscaped(cx, cy, currTime)) {
            playerEscapePos = {cx, cy};
            return true;
        }
 
        ++currTime;
 
        for (int i = 0; i < 4; i++) {
            int newX = cx + moves[i].first;
            int newY = cy + moves[i].second;
 
            if (isValidMovement(newX, newY, currTime)) {
                previousPath[newX][newY] = i;
                graph[cx][cy] = currTime; // visited
                queue.push(mp(mp(newX, newY), currTime));
            }
        }
    }
    return false;
}
 
void printPath() {
    ii curr = playerEscapePos;
    vector<char> path;
    while (curr.first != playerStartPos.first || curr.second != playerStartPos.second) {
        int step = previousPath[curr.first][curr.second];
        path.push_back(directions[step]);
        curr = mp(curr.first - moves[step].first, curr.second - moves[step].second);
    }
    cout << path.size() << "\n";
//    reverse(path.begin(), path.end());
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
    }
}
 
int main() {
    cin >> rows >> cols;
    char c;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> c;
            if (c == 'A') {
                // player
                graph[i][j] = 0;
                playerStartPos = mp(i, j);
            } else if (c == 'M') {
                // monster
                graph[i][j] = 0;
                monster_positions.emplace_back(i, j);
            } else if (c == '#') {
                // wall
                graph[i][j] = 0;
            } else {
                graph[i][j] = INT_MAX;
            }
        }
    }
    if (playerStartPos.first == 0 || playerStartPos.first == rows - 1 || playerStartPos.second == 0 ||
        playerStartPos.second == cols - 1) {
        cout << "YES\n";
        cout << 0;
        return 0;
    }
 
    preprocess_monster_movement();
 
    if (!player_movement()) {
        cout << "NO\n";
        return 0;
    }
 
    cout << "YES\n";
    printPath();
 
}
