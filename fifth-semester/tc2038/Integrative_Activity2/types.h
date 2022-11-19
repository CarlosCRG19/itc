#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>
#include <utility>

using std::pair;

/**
 * This class abstracts the behavior of our disjoint set.
 * It consists of two main operations:
 * - union
 * - find
*/
class DisjointSet
{
private:
    int n;
    int *parents;

public:
    DisjointSet(int n) {
        this->n = n;
        this->parents = new int[n];
        // Build parents array; each element will have itself as parent
        for (size_t i = 0; i < n; i++)
            parents[i] = i;
    }

    /**
     * @brief returns which set the element belongs to
    */
    int find(int element)
    {
        if (element == parents[element])
        {
            return element;
        }
        return find(parents[element]);
    }

    /**
     * @brief turns element into a child of parentNode (making it part of that subset)
    */
    void merge(int element, int parentNode)
    {
        parents[element] = parentNode;
    }
};

struct Edge
{
	int dest, weight, src;

	Edge(int d, int w, int s) : dest(d), weight(w), src(s) {}
};

typedef pair<double, double> Point;
#define x first
#define y second

#endif
