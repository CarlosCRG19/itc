#include <iostream>
#include <algorithm>
#include <vector>

#include "./DisjointSet.h"
#include "./solutions.h"

const int N = 9;

int main()
{   

    int adjMatrix[N][N] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };



    // kruskalMST(N, adjMatrix);
    
    int nFlux; std::cin >> nFlux;
    int **fluxMatrix = new int*[nFlux];
    for (int i = 0; i < nFlux; i++) {
        fluxMatrix[i] = new int[nFlux];
        for(int j = 0; j < nFlux; j++)
            std::cin >> fluxMatrix[i][j];
    }

    int maxFlow = fordFulkerson(nFlux, fluxMatrix, 0, 5);
    std::cout << "Max flow is: " << maxFlow << std::endl; 

    return 0;
}