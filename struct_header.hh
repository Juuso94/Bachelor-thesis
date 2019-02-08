#ifndef STRUCT_HEADER_HH
#define STRUCT_HEADER_HH

#include <map>
# define INF 0x3f3f3f3f

struct Vertex{
    std::map<Vertex*, int> adjcacent_vertices;
    std::map<Vertex*, int> adjcacent_vertices_mst;
    bool visited;

    int key;
    int distance;
    Vertex* parent;

    int degree;

    Vertex()
    {
        adjcacent_vertices = {};
        adjcacent_vertices_mst = {};
        visited = false;
        key = 0;
        distance = INF;
        parent = this;
        degree = 0;
    }
};


#endif // STRUCT_HEADER_HH
