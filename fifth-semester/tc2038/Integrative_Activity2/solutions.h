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

	bool visited[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	std::queue<int> q;
	q.push(source);
	visited[source] = true;
	path[source] = -1;

	while (!q.empty())
	{
		int node = q.front();
		q.pop();

		for (int v = 0; v < n; v++)
		{
			if (visited[v] == false && graph[node][v] > 0)
			{
				if (v == target)
				{
					path[v] = node;
					return true;
				}
				q.push(v);
				path[v] = node;
				visited[v] = true;
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

int tspAuxiliar(std::vector<std::vector<int>> &districts,
				std::vector<std::vector<int>> &dpStates,
				std::vector<std::vector<int>> &previousDistricts,
				int currentDistrict,
				int visited,
				int numberOfDistricts)
{
	int fullBitMask = (1 << numberOfDistricts) - 1;
	if (visited == fullBitMask)
	{
		return districts[currentDistrict][0];
	}

	if (dpStates[currentDistrict][visited] != INFINITE)
	{
		return dpStates[currentDistrict][visited];
	}

	int index = INFINITE;
	for (int i = 0; i < numberOfDistricts; i++)
	{
		if (!(i == currentDistrict || (visited & (1 << i))))
		{
			int distance = districts[currentDistrict][i] + tspAuxiliar(districts, dpStates, previousDistricts, i, visited | (1 << i), numberOfDistricts);
			if (distance < dpStates[currentDistrict][visited])
				dpStates[currentDistrict][visited] = distance;
			index = i;
		}
	}

	previousDistricts[currentDistrict][visited] = index;

	return dpStates[currentDistrict][visited];
}

int tsp(std::vector<std::vector<int>> districts)
{
	std::cout << "xd" << std::endl;

	std::vector<std::vector<int>> dpStates(districts.size(), std::vector((1 << districts.size()) - 1, INFINITE));
	std::vector<std::vector<int>> previousDistricts(districts.size(), std::vector((1 << districts.size()) - 1, INFINITE));
	std::vector<int> minimumDistanceRoute(districts.size());

	int currentDistrict = 0;
	int currentState = 1;

	std::cout << "Minimum distance: " << tspAuxiliar(districts, dpStates, previousDistricts, 0, 1, districts.size()) << std::endl;
	std::cout << "Best route: ";
	for (int i = 0; i < minimumDistanceRoute.size(); i++)
	{
		minimumDistanceRoute[i] = currentDistrict;
		currentDistrict = previousDistricts[currentDistrict][currentState];
		currentState = currentState | (1 << currentDistrict);
		std::cout << minimumDistanceRoute[i] << "-> ";
	}
	std::cout << 0 << std::endl;

	return 0;
}

#endif