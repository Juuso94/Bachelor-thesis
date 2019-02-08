#include <iostream>
#include <graph.hh>
#include <chrono>



int main()
{
    Graph graph;



    int N = 1000000;


    //int M = 0.05*(N*(N-1));
    int M = 1000050;

    std::cout<<M<<std::endl;

    graph.add_vertices(N);
    graph.add_edges(M, N);

    auto start = std::chrono::high_resolution_clock::now();
    Graph tree = graph.PrimMst(N);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout<<std::endl<<duration.count()<<std::endl;


    graph.test();
    tree.test();

    //tree = tree.KruskalMst(N);

    graph.clear();

    return 0;
}
