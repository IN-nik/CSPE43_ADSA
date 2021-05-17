#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;
unordered_set<int> visited;
vector<int> path;
int N, start; // Number of cities

inline void print2d(const vector<vector<int>> &matrix) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (matrix[i][j] == INF)
        cout << setw(4) << "INF"
             << " ";
      else
        cout << setw(4) << matrix[i][j] << " ";
    }
    cout << "\n";
  }
}
vector<vector<int>> makeReducable(vector<vector<int>> matrix, int row,
                                  int col) {
  matrix[col - 1][row - 1] = INF;
  for (int x : visited) {
    matrix[col - 1][x - 1] = INF;
  }
  for (int i = 0; i < N; i++) {
    matrix[i][col - 1] = INF;
    matrix[row - 1][i] = INF;
  }
  return matrix;
}

int reductionCost(vector<vector<int>> &matrix) {
  int cost = 0;
  int mn;
  vector<int> row_mins, col_mins;
  for (int i = 0; i < N; i++) {
    mn = INF;
    for (int j = 0; j < N; j++) {
      mn = min(mn, matrix[i][j]);
    }
    row_mins.push_back(mn);
    if (mn == INF || mn == 0)
      continue;
    cost = cost + mn;
    for (int j = 0; j < N; j++) {
      if (matrix[i][j] == INF)
        continue;
      matrix[i][j] -= mn;
    }
  }
  for (int j = 0; j < N; j++) {
    mn = INF;
    for (int i = 0; i < N; i++) {
      mn = min(mn, matrix[i][j]);
    }
    col_mins.push_back(mn);
    if (mn == INF || mn == 0)
      continue;
    cost = cost + mn;
    for (int i = 0; i < N; i++) {
      if (matrix[i][j] == INF)
        continue;
      matrix[i][j] -= mn;
    }
  }

  cout << "Row min values: ";
  for (int x : row_mins) {
    if (x == INF)
      cout << "INF ";
    else
      cout << x << ' ';
  }
  cout << '\n';
  cout << "Column min values: ";
  for (int x : col_mins) {
    if (x == INF)
      cout << "INF ";
    else
      cout << x << ' ';
  }
  cout << '\n';

  return cost;
}

void tspbnb(vector<vector<int>> matrix, int par = -1, int nextcity = 1,
            int passedCost = 0) {
  if (visited.size() == N) {
    return;
  }
  if (par == -1) {
    nextcity = start;
    // cout<<start<<"->";
    path.push_back(start);
    visited.insert(start);
  }
  pair<int, int> costind;
  costind = {INT_MAX, -1};
  for (int rem = 1; rem <= N; rem++) {
    if (visited.find(rem) != visited.end())
      continue;
    if (rem == start)
      continue;
    vector<vector<int>> tmp = makeReducable(matrix, nextcity, rem);
    cout << "Reduced matrix for path from city " << nextcity << " to " << rem
         << " is as :\n";
    int tmpcost = reductionCost(tmp) + matrix[nextcity - 1][rem - 1];
    costind = min(costind, {tmpcost, rem});
    cout << "After make reducable:\n";
    print2d(tmp);
    cout << "with reduction cost = " << passedCost << "+"
         << tmpcost - matrix[nextcity - 1][rem - 1] << "+"
         << matrix[nextcity - 1][rem - 1] << " = " << tmpcost + passedCost
         << "\n\n";
  }
  visited.insert(costind.second);
  // cout<<costind.second<<"->";
  path.push_back(costind.second);
  tspbnb(makeReducable(matrix, nextcity, costind.second), nextcity,
         costind.second, costind.first + passedCost);
}

int main() {
  cout << "Enter number of cities:\n";
  cin >> N;
  cout << "Enter starting city (1 index based):\n";
  cin >> start;
  vector<vector<int>> matrix(N, vector<int>(N)), A;
  cout << "Enter adjacency matrix:\n";
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> matrix[i][j];
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j)
        matrix[i][j] = INF;
    }
  }
  cout << "\n";
  int passedCost = reductionCost(matrix);
  cout << "Initial Reduction Cost is : " << passedCost << "\n";
  cout << "And the initial A[][] matrix is as :\n";
  print2d(matrix);
  cout << "\n\n";
  tspbnb(matrix, -1, start, passedCost);
  cout << "\n\nFinal Path is as :\n";
  for (int i = 0; i < N; i++) {
    cout << path[i] << "->";
  }
  cout << start;
}
