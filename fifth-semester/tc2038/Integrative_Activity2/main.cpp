#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./solutions.h"
#include "./types.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

typedef vector<int> vi;

void fillSquareMatrix(vector<vi> &matrix)
{
  int N = matrix.size();

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      cin >> matrix[i][j];
    }
  }
}

void fillArrayOfPoints(vector<Point> &points)
{
  int N = points.size();

  for (int i=0; i<N; i++) {
    string pointAsString;
    cin >> pointAsString;

    pointAsString.erase(0, 1);
    pointAsString.erase(pointAsString.size() - 1, 1);

    char delimiterChar = ',';
    size_t delimeterCharPosition = pointAsString.find(delimiterChar);

    if (delimeterCharPosition != string::npos) {
      Point p;

      double x = stod(pointAsString.substr(0, delimeterCharPosition));
      pointAsString.erase(0, delimeterCharPosition + 1);
      double y = stod(pointAsString);

      p.x = x; p.y = y;

      points.push_back(p);
    }
  }
}

int main()
{
  int N;
  cin >> N;

  vector<vi> neighborhoodsDistances(N, vi(N)), neighborhoodsTransmissions(N, vi(N));
  vector<Point> stations(N);

  fillSquareMatrix(neighborhoodsDistances);
  fillSquareMatrix(neighborhoodsTransmissions);

  fillArrayOfPoints(stations);

  // Optimal wiring
  kruskalMST(neighborhoodsDistances);
  cout << "\n";

  // Mail delivery route
  tsp(neighborhoodsDistances);
  cout << "\n";

  // Max flow between nodes
  fordFulkerson(neighborhoodsTransmissions, 0, N - 1); // Sample node
  cout << "\n";

  // Convex Hull
  grahamScan(stations);
}
