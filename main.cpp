#include <iostream>
#include <algorithms.hh>



int main()
{
    Graph graph;

    int N = 1000;
    int M = 10000;
    graph.add_vertices(N);
    graph.add_edges(M, N);

    return 0;
}
