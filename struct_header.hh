#ifndef STRUCT_HEADER_HH
#define STRUCT_HEADER_HH

#include <map>
using std::map;

struct Vertex{
    map<Vertex*, int> adjcacent_vertices;
    bool visited;

    int key;
    Vertex* parent;

    int degree;

    Vertex()
    {
        adjcacent_vertices = {};
        visited = false;
        key = 0;
        parent = this;
        degree = 0;
    }
};


#endif // STRUCT_HEADER_HH
