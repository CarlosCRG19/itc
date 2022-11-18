#ifndef SOLUTIONS_H
#define SOLUTIONS_H
#include <limits.h>
#include <iostream>
#include <queue>
#include <vector>

int INFINITE = 99999;

struct Edge
{
	int weight;
	int src;
	int dest;

	Edge(int weight, int src, int dest)
	{
		this->weight = weight;
		this->src = src;
		this->dest = dest;
	}
};

bool compareEdge(Edge e1, Edge e2)
{
	return e1.weight < e2.weight;
}

void kruskalMST(int n, int adjMatrix[9][9])
{
	std::vector<Edge> edges;

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
	std::sort(edges.begin(), edges.end(), compareEdge);

	// Step 2: iterate on i, initialize DisjointSet
	DisjointSet dSet(n);

	for (int i = 0; i < n; i++)
	{
		int src = edges[i].src, dest = edges[i].dest;
		if (dSet.find(src) != dSet.find(dest))
		{
			dSet.merge(src, dest);
			std::cout << src << " -- " << dest << std::endl;
		}
	}
}

// This search will look try to find a way to go from
bool breadthFirstSearch(int n, int path[], int **graph, int source, int target)
{

	bool visitedBitMask[n];
	for (int i = 0; i < n; i++)
		visitedBitMask[i] = false;

	std::queue<int> q;
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

int fordFulkerson(int n, int **graph, int source, int target)
{
	int maxFlow = 0;
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
		int residualFlow = std::numeric_limits<int>::max();
		// Path holds edges
		// Traverse path
		for (int node = target; node != source; node = path[node])
		{
			int parent = path[node];
			residualFlow = std::min(residualFlow, residualGraph[parent][node]);
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
	return maxFlow;
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
int tspAuxiliar(std::vector<std::vector<int>> &districts,
				std::vector<std::vector<int>> &dpStates,
				std::vector<std::vector<int>> &previousDistricts,
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
void tsp(std::vector<std::vector<int>> districts)
{
	std::vector<std::vector<int>> dpStates(districts.size(), std::vector((1 << districts.size()) - 1, INFINITE));
	std::vector<std::vector<int>> previousDistricts(districts.size(), std::vector((1 << districts.size()) - 1, INFINITE));
	std::vector<int> minimumDistanceRoute(districts.size());

	int currentDistrict = 0;
	int currentState = 1;

	std::cout << "Minimum distance: " << tspAuxiliar(districts, dpStates, previousDistricts, 0, 1, districts.size()) << std::endl;
	std::cout << "Best route: ";
	// Trace best route of visitedBitMask districts
	for (int i = 0; i < minimumDistanceRoute.size(); i++)
	{
		minimumDistanceRoute[i] = currentDistrict;
		currentDistrict = previousDistricts[currentDistrict][currentState];
		currentState = currentState | (1 << currentDistrict);
		std::cout << minimumDistanceRoute[i] << "-> ";
	}
	std::cout << 0 << std::endl;
}

#endif