#include <iostream>
#include <vector>
#include <fstream>
#include "mqueue.hpp"
using namespace std;

struct Point {
    int x, y;
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void bfs(vector<vector<int>>& maze, int startX, int startY) {
    int n = maze.size();
    int m = maze[0].size();
    vector<vector<Point>> prev(n, vector<Point>(m, {-1, -1}));
    
    mqueue<Point> q;
    q.push({startX, startY});
    prev[startX][startY] = {startX, startY};

    while (!q.empty()) {
        Point p = q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if(!(nx >= 0 && nx < n && ny >= 0 && ny < m)&&maze[p.x][p.y])
            {
                q.push({nx, ny});
                prev[nx][ny] = p;
                cout << maze[p.x][p.y] << endl;
                vector<Point> path;
                for (Point at = {nx, ny}; at.x != startX || at.y != startY; at = prev[at.x][at.y])
                {
                    
                    path.push_back(at);
                    }
                    cout << "Length: "<<path.size() - 1 << " "<<"Path to exit:\n";
                    path.push_back({startX, startY});
                    reverse(path.begin(), path.end());
                    path.pop_back();
                    for (const auto &point : path)
                    cout << "(" << point.x << ", " << point.y << ") ";
                    
                    cout << endl;
                    return;
            }
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] != 0 && prev[nx][ny].x == -1) {
                q.push({nx, ny});
                prev[nx][ny] = p;

             
            }
        }
    }
    cout << "No path to exit found.\n";
}

int main() {
    ifstream into("input.txt");
    int n, m, startX, startY;
    into >> n >> m >> startX >> startY;

    vector<vector<int>> maze(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            into >> maze[i][j];
        }
    }

    bfs(maze, startX, startY);
    return 0;
}