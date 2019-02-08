#ifndef ALGORITHMS_HH
#define ALGORITHMS_HH

#include <iostream>
#include <time.h>
#include <random>

#include <struct_header.hh>
#include <min_heap.hh>

#include <algorithm>

#include <vector>

#include <queue>

#include <map>

#include <tuple>


#include <set>


#include <random>




class Graph
{
public:
    Graph();
    ~Graph() = default;

    void clear();

    void add_vertices(int amount);
    void add_edges(int amount, int N);

    void add_vertex();
    void add_vertex(Vertex* vertex);

    void add_edge(int weight, Vertex* first, Vertex* second);
    void add_edge_mst(int weight, Vertex* first, Vertex* second);

    Graph KruskalMst(int N);

    Graph PrimMst(int N);

    int size();

    void test();


private:
    std::vector<Vertex*> vertices_;
    std::vector<std::tuple<int, Vertex*, Vertex*>> edges_;

    Vertex *find_Set(Vertex* searched);
    void union_sets(Vertex* a, Vertex* b);

    static bool compare_edge_weight(const pair<int,Vertex*> a, const pair<int,Vertex*> b);

    bool is_adjacent(Vertex* p);


};

#endif // ALGORITHMS_HH
