#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Point {
    int x, y;
};

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

vector<vector<int>> bfs(int n, int m, const vector<vector<int>>& grid, Point start) {
    vector<vector<int>> dist(m, vector<int>(n, INF));
    queue<Point> q;
    dist[start.y][start.x] = 0;
    q.push(start);

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[ny][nx] != 1) {
                if (dist[ny][nx] == INF) {
                    dist[ny][nx] = dist[curr.y][curr.x] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    return dist;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> grid(m, vector<int>(n));
    Point start, end;
    vector<Point> umbrellas;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = {j, i};
            } else if (grid[i][j] == 3) {
                end = {j, i};
            } else if (grid[i][j] == 4) {
                umbrellas.push_back({j, i});
            }
        }
    }

    vector<vector<int>> distFromStart = bfs(n, m, grid, start);
    vector<vector<int>> distFromEnd = bfs(n, m, grid, end);

    int minTotalDist = INF;
    for (const auto& u : umbrellas) {
        if (distFromStart[u.y][u.x] != INF && distFromEnd[u.y][u.x] != INF) {
            minTotalDist = min(minTotalDist, distFromStart[u.y][u.x] + distFromEnd[u.y][u.x]);
        }
    }

    if (minTotalDist == INF) {
        // This case might not be reachable if the problem guarantees a path exists,
        // but it's good practice. For now, let's output a large value or -1 if appropriate.
        // The problem doesn't specify what to output if no path exists.
        // Usually it's -1 or no output. Let's assume -1 if not specified.
        cout << -1 << endl;
    } else {
        cout << minTotalDist << endl;
    }

    return 0;
}
