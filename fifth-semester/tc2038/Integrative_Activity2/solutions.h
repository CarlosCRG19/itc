#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <cmath>
#include <limits.h>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "./types.h"

using std::cout;
using std::numeric_limits;
using std::min;
using std::pow;
using std::queue;
using std::sort;
using std::stack;
using std::vector;

int INFINITE = numeric_limits<int>::max();

bool compareEdge(Edge e1, Edge e2)
{
	return e1.weight < e2.weight;
}

/**
 * @brief Algorithm to find the minimum spanning tree
 *
 * @param districts Adjacency matrix with the weights (distances) between districts.
 *
 * Time complexity: O(v^2 + log(e)).
 * Space complexity: O(v + e).
 */
void kruskalMST(vector<vector<int> > &adjMatrix)
{
  int n = adjMatrix.size();
	vector<Edge> edges;

	// Fill edges with the edges in adjMatrix
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (adjMatrix[i][j] != 0)
				edges.push_back(Edge(adjMatrix[i][j], j, i));
		}
	}

	// Step 1: sort edges
	sort(edges.begin(), edges.end(), compareEdge);

	// Step 2: iterate on i, initialize DisjointSet
	DisjointSet dSet(n);

	for (int i = 0; i < n; i++)
	{
		int src = edges[i].src, dest = edges[i].dest;
		if (dSet.find(src) != dSet.find(dest))
		{
			dSet.merge(src, dest);
		}
	}
}

/**
 * @brief Recursive function that gets called until route is traced.
 *
 * @param districts Adjacency matrix with the weights (distances) between districts.
 * @param dpStates Permutations of possible routes.
 * @param previousDistricts Permutations with order of visits.
 * @param visitedBitMask Bit mask that represents visited districts. 0 means that the
 * district has not been visited and 1 represents a visited district. As a binary number, it can
 * also represent the permutations of possible visited districts. Because of this, it can also be
 * represented as (2^n)-1, where n is the number of districts. However, using a binary representation
 * can be useful in order to compare visited nodes and insert new ones.
 * @param numberOfDistricts Number of districts.
 *
 * @return best route distance
 *
 * Time complexity: O(n^2 * 2^n) .
 * Space complexity: O(n * 2^n) .
 */
int tspAuxiliar(vector<vector<int> > &districts,
				vector<vector<int> > &dpStates,
				vector<vector<int> > &previousDistricts,
				int currentDistrict,
				int visitedBitMask,
				int numberOfDistricts)
{

	// Bitmask that represents that all districts have been visited.
	int fullBitMask = (1 << numberOfDistricts) - 1;
	// Every district has been visited.
	if (visitedBitMask == fullBitMask)
	{
		return districts[currentDistrict][0];
	}
	// A value for this subroute already exists and can be used.
	if (dpStates[currentDistrict][visitedBitMask] != INFINITE)
	{
		return dpStates[currentDistrict][visitedBitMask];
	}

	int index = INFINITE;
	// Check remaining districts.
	for (int i = 0; i < numberOfDistricts; i++)
	{
		// Check if it has been visited
		if (!(i == currentDistrict || (visitedBitMask & (1 << i))))
		{
			// Remaining distance
			int distance = districts[currentDistrict][i] + tspAuxiliar(districts, dpStates, previousDistricts, i, visitedBitMask | (1 << i), numberOfDistricts);
			// Check if distance is less than current value
			if (distance < dpStates[currentDistrict][visitedBitMask])
			{
				dpStates[currentDistrict][visitedBitMask] = distance;
			}
			index = i;
		}
	}

	// Permutations with visited districts
	previousDistricts[currentDistrict][visitedBitMask] = index;

	return dpStates[currentDistrict][visitedBitMask];
}

/**
 * @brief Finds the shortest route that includes every district
 * using dynamic programming and memoization.
 *
 * @param districts Adjacency matrix with the weights (distances) between districts.
 *
 * Time complexity: O(n^2 * 2^n) .
 * Space complexity: O(n * 2^n) .
 */
void tsp(vector<vector<int> > districts)
{
	vector<vector<int> > dpStates(districts.size(), vector<int>((1 << districts.size()) - 1, INFINITE));
	vector<vector<int> > previousDistricts(districts.size(), vector<int>((1 << districts.size()) - 1, INFINITE));
	vector<int> minimumDistanceRoute(districts.size());

	int currentDistrict = 0;
	int currentState = 1;

	cout << "Minimum distance: \n" << tspAuxiliar(districts, dpStates, previousDistricts, 0, 1, districts.size()) << "\n\n";
	cout << "Traveling salesman problem: \n";

	// Trace best route of visitedBitMask districts
	for (int i = 0; i < minimumDistanceRoute.size(); i++)
	{
		minimumDistanceRoute[i] = currentDistrict;
		currentDistrict = previousDistricts[currentDistrict][currentState];
		currentState = currentState | (1 << currentDistrict);
		cout << minimumDistanceRoute[i] << " -> ";
	}

	cout << 0 << "\n";
}

// This search will look try to find a way to go from
bool breadthFirstSearch(int n, int path[], int **graph, int source, int target)
{
	bool visitedBitMask[n];
	for (int i = 0; i < n; i++)
		visitedBitMask[i] = false;

	queue<int> q;
	q.push(source);
	visitedBitMask[source] = true;
	path[source] = -1;

	while (!q.empty())
	{
		int node = q.front();
		q.pop();

		for (int v = 0; v < n; v++)
		{
			if (visitedBitMask[v] == false && graph[node][v] > 0)
			{
				if (v == target)
				{
					path[v] = node;
					return true;
				}
				q.push(v);
				path[v] = node;
				visitedBitMask[v] = true;
			}
		}
	}
	return false;
}

void fordFulkerson(vector<vector<int> > graph, int source, int target)
{
	int n = graph.size(), maxFlow = 0;
	int path[n];

	int **residualGraph = new int *[n];
	for (int i = 0; i < n; i++)
	{
		residualGraph[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			residualGraph[i][j] = graph[i][j];
		}
	}

	while (breadthFirstSearch(n, path, residualGraph, source, target))
	{
		int residualFlow = INFINITE;
		// Path holds edges
		// Traverse path
		for (int node = target; node != source; node = path[node])
		{
			int parent = path[node];
			residualFlow = min(residualFlow, residualGraph[parent][node]);
		}

		// Perform augmentation
		for (int node = target; node != source; node = path[node])
		{
			int parent = path[node];
			residualGraph[parent][node] -= residualFlow;
			residualGraph[node][parent] += residualFlow;
		}
		maxFlow += residualFlow;
	}

	cout << "Maximum flow between two nodes is: \n" << maxFlow << "\n";
}

Point p0;

void swapPoints(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

Point nextToTop(stack<Point> &s)
{
    Point top = s.top();
    s.pop();

    Point nextToTop = s.top();
    s.push(top);

    return nextToTop;
}

int squareDistance(Point p1, Point p2)
{
    return int(pow((p1.x - p2.x), 2) +
               pow((p1.y - p2.y), 2));
}

int getPointWithMinY(vector<Point> &points, int &N)
{
    int min = 0;

    for (int i = 1; i < N; i++)
    {
        int y = points[i].y;

        if ((y < points[min].y) || (points[min].y == y &&
                                    points[i].x < points[min].x))
        {
            min = i;
        }
    }

    return min;
}

int getOrientation(Point p0, Point p1, Point p2)
{
    int val = (p1.y - p0.y) * (p2.x - p1.x) -
              (p1.x - p0.x) * (p2.y - p1.y);

    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int orientation = getOrientation(p0, *p1, *p2);

    if (orientation == 0)
        return (squareDistance(p0, *p2) >= squareDistance(p0, *p1)) ? -1 : 1;

    return (orientation == 2) ? -1 : 1;
}

stack<Point> getConvexPolygonPoints(vector<Point> points, int N)
{
    int min = getPointWithMinY(points, N);

    swapPoints(points[0], points[min]);

    p0 = points[0];
    qsort(&points[1], N - 1, sizeof(Point), compare);

    int m = 1;
    for (int i = 1; i < N; i++)
    {
        while (i < N - 1 && getOrientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    stack<Point> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);

    for (int i = 3; i < m; i++)
    {
        while (s.size() > 1 &&
               getOrientation(nextToTop(s), s.top(), points[i]) != 2)
            s.pop();
        s.push(points[i]);
    }

    return s;
}

void reverseStack(stack<Point> &s)
{
    stack<Point> tempStack;
    while (!s.empty())
    {
        Point p = s.top();
        s.pop();

        tempStack.push(p);
    }

    s = tempStack;
}

void printPointsStack(stack<Point> &s)
{
    while (!s.empty())
    {
        Point p = s.top();
        if (s.size() == 1)
            cout << "(" << p.x << ", " << p.y << ")"
                 << "\n";
        else
            cout << "(" << p.x << ", " << p.y << "), ";
        s.pop();
    }
}

void counterClockwisePrint(stack<Point> s)
{
    cout << "Convex hull points in counter-clock wise order:\n";

    reverseStack(s);
    printPointsStack(s);
}

/**
 * @brief Algorithm that finds the convex hull of a finite set of points
 *
 * @param points Set of points on the plane from which the convex hull will be calculated.
 *
 * Time complexity: O(n * log(n)).
 * Space complexity: O(n).
 */
void grahamScan(vector<Point> &points)
{
  int N = points.size();

  if (N <= 2) {
      cout << "Need more points to create convex hull\n";
      return;
  }

  stack<Point> polygonPoints = getConvexPolygonPoints(points, N);
  counterClockwisePrint(polygonPoints);
}

#endif
