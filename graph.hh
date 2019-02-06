#ifndef ALGORITHMS_HH
#define ALGORITHMS_HH

#include <iostream>
#include <time.h>
#include <random>

#include <struct_header.hh>
#include <disjoint_set.hh>

#include <algorithm>


#include <vector>


#include <map>

#include <tuple>


#include <set>


#include <random>




class Graph
{
public:
    Graph();
    ~Graph();
    void add_vertices(int amount);
    void add_edges(int amount, int N);

    void add_vertex();
    void add_vertex(Vertex* vertex);
    void add_edge(int weight, Vertex* first, Vertex* second);

    Graph KruskalMst(int N);
    Vertex *find_Set(Vertex* searched);
    void union_sets(Vertex* a, Vertex* b);

    void test();


private:
    std::vector<Vertex*> vertices_;
    std::vector<std::tuple<int, Vertex*, Vertex*>> edges_;


};

#endif // ALGORITHMS_HH
