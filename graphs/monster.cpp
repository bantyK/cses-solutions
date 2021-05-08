#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define ii pair<int, int>
#define f first
#define s second
#define int long long int

int m, n;
vector<ii> monster_positions;
vector<vector<int>> graph;
map<ii, ii> parent_map;
ii start, __end;
vector<ii> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void preprocess_monster_movement();
bool isValid(int, int, int);
bool escaped(int, int, int);
bool player_movement();

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = INT_MAX;
        }
    }

    char c;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> c;

            if (c == '#')
            {
                graph[i][j] = 0;
            }
            else if (c == 'M')
            {
                graph[i][j] = 0; // monster is already present here
                monster_positions.push_back(mp(i, j));
            }
            else if (c == 'A')
            {
                graph[i][j] = 0;
                start = mp(i, j);
            }
            else
            {
                graph[i][j] = INT_MAX;
            }
        }
    }

    if (start.f == 0 || start.s == 0 || start.f == m - 1 || start.s == n - 1)
    {
        cout << "YES\n";
        cout << 0;
        return 0;
    }

    preprocess_monster_movement();

    if(!player_movement())
    {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";
}
/**
 * prepopulate the graph with minimum time requird 
 *  
 */
void preprocess_monster_movement()
{
    queue<pair<pair<int, int>, int>> queue;
    for (auto m : monster_positions)
    {
        queue.push(mp(m, 0));
    }

    while (!queue.empty())
    {
        int cx = queue.front().first.first;
        int cy = queue.front().first.second;
        int timer = queue.front().second;
        queue.pop();
        ++timer;
        for (auto direction : directions)
        {
            int newX = cx + direction.first;
            int newY = cy + direction.second;
            if (isValid(newX, newY, timer))
            {
                graph[newX][newY] = timer; // this is the best time when we can reach the current position
                queue.push(mp(mp(newX, newY), timer));
            }
        }
    }
}

bool isValid(int x, int y, int timer)
{
    if (x < 0 || x >= m || y < 0 || y >= n)
        return false;
    if (graph[x][y] <= timer)
        return false;
    return true;
}

bool escaped(int x, int y, int timer)
{
    if (!isValid(x, y, timer))
        return false;
    if (x == 0 || y == 0 || x == m - 1 || y == n - 1)
        return true;
    return false;
}

bool player_movement()
{
    queue<pair<pair<int, int>, int>> q;
    q.push(mp(start, 0));

    while (!q.empty())
    {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int timer = q.front().second;
        q.pop();
        ++timer;

        for (ii direction : directions)
        {
            int nx = cx + direction.first;
            int ny = cy + direction.second;

            if (escaped(nx, ny, timer))
            {
                parent_map[mp(nx, ny)] = mp(cx, cy);
                __end = mp(nx, ny);
                return true;
            }

            if (isValid(nx, ny, timer))
            {
                parent_map[mp(nx, ny)] = mp(cx, cy);
                q.push(mp(mp(nx, ny), timer));
            }
        }
    }
    return false;
}