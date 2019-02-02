#ifndef ALGORITHMS_HH
#define ALGORITHMS_HH

#include <iostream>
#include <time.h>
#include <random>

#include <algorithm>
using std::find;
using std::swap;

#include <vector>
using std::vector;
using std::remove;

#include <map>
using std::map;

#include <tuple>
using std::tuple;
using std::make_tuple;

#include <set>
using std::set;

using std::pair;
using std::make_pair;

#include <random>

struct Vertex{
    map<Vertex*, int> adjcacent_vertices;
    bool visited;
    int degree;
};


class Graph
{
public:
    Graph();
    ~Graph();
    void add_vertices(int amount);
    void add_edges(int amount, int N);


private:
    vector<Vertex*> vertices_;
    vector<tuple<Vertex*, Vertex*, int>> edges_;

    void add_vertex();
    void add_edge(Vertex*, Vertex*, int);
};

#endif // ALGORITHMS_HH
