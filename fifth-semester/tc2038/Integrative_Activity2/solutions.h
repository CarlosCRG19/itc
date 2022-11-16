#ifndef SOLUTIONS_H
#define SOLUTIONS_H

struct Edge {
    int weight;
    int src;
    int dest;

    Edge(int weight, int src, int dest) {
        this->weight = weight;
        this->src = src;
        this->dest = dest;
    }
};

bool compareEdge(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

// Introduce graph as edge list
void kruskalMST(int n, int adjMatrix[N][N])
{
    // std::cout << "here" << std::endl;
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
        if (dSet.find(src) != dSet.find(dest)) {
            dSet.merge(src, dest);
            std::cout << src << " -- " << dest << std::endl;
        }
    }

}

#endif