#include "graph.hh"

using std::find;
using std::swap;
using std::vector;
using std::remove;
using std::map;
using std::tuple;
using std::make_tuple;
using std::set;
using std::pair;
using std::make_pair;
using std::sort;


Graph::Graph()
{
    vertices_ = {};
    edges_ = {};
}



void Graph::clear()
{
    for (auto vertex: vertices_) {
        delete vertex;
    }
    vertices_.clear();
    edges_.clear();

}

void Graph::add_vertices(int amount)
{
    for (int i = 0; i < amount; i++) {
        add_vertex();
    }
}

void Graph::add_edges(int amount, int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    //gen.seed(time(nullptr));
    std::uniform_int_distribution<> weight(1, 1000);

    int edge_count = 0;


    /* PRUFER SEQUENCE RANDOM TREE GENERATION
    for (unsigned int i = 0; i < vertices_.size() - 2; i++){
        prufer_sequece.push_back(rand() % vertices_.size() );
    }
    for (auto prufer: prufer_sequece){
        vertices_.at(prufer)->degree++;
    }

    for(auto prufer: prufer_sequece){
        for(auto vertex: vertices_){
            if(vertex->degree == 1){
                add_edge(vertices_.at(prufer), vertex, 1);
                vertices_.at(prufer)->degree--;
                vertex->degree--;
                break;
            }

        }
    }
    while(u == nullptr || v == nullptr){
        if((*it)->degree == 1 ){
            if(u == nullptr){
                u = (*it);
            }
            else {
                v = (*it);
            }
        }
        it++;
    }
    add_edge(u,v,1);

    */
    //Generate pseudo random tree to ensure that graph is connected

    vector<Vertex*> all_vertices = vertices_;
    vector<Vertex*> visited_vertices;
    std::uniform_int_distribution<> all_random(0, N - 1);
    int random_index = all_random(gen);
    Vertex* root = vertices_.at(random_index);
    all_vertices.erase(all_vertices.begin() + random_index);
    visited_vertices.push_back(root);

    while(!all_vertices.empty())
    {
        std::uniform_int_distribution<> all_random(0, all_vertices.size() - 1);
        random_index = all_random(gen);
        Vertex* new_vertex = all_vertices.at(random_index);
        all_vertices.erase(all_vertices.begin() + random_index);

        std::uniform_int_distribution<> visited_random(0, visited_vertices.size() - 1);
        random_index = visited_random(gen);
        Vertex* neigbhor_vertex = visited_vertices.at(random_index);


        add_edge(weight(gen), new_vertex, neigbhor_vertex);
        edge_count++;

        visited_vertices.push_back(new_vertex);
    }

    while(edge_count < amount){
        random_index = rand() % vertices_.size();
        Vertex* vertex_a = vertices_.at(random_index);

        random_index = rand() % vertices_.size();
        Vertex* vertex_b = vertices_.at(random_index);

        if(vertex_a != vertex_b && vertex_a->adjcacent_vertices.find(vertex_b) == vertex_a->adjcacent_vertices.end()){
            add_edge( weight(gen), vertex_a, vertex_b);
            edge_count++;
        }
    }
     /*
    int sum = 0;

    Tarkastuksia debuggausta varten.
    for (auto vertex: vertices_)
    {
        std::cout<<vertex->degree<<" ";
        sum += vertex->degree;
    }

    std::cout<<sum<<std::endl;
    */
}

void Graph::add_vertex()
{
    Vertex *vertex = new Vertex();
    vertices_.push_back(vertex);
}

void Graph::add_vertex(Vertex* vertex)
{
    //Adding vertices to kruskal tree and
    //clearing their adjacency lists.
    //vertex->key = 0;
    vertices_.push_back(vertex);

}

void Graph::add_edge(int weight, Vertex* first, Vertex* second)
{
    first->adjcacent_vertices.insert(make_pair(second, weight));
    second->adjcacent_vertices.insert(make_pair(first, weight));
    first->degree++;
    second->degree++;


    edges_.push_back(make_tuple(weight, first, second));

}

void Graph::add_edge_mst(int weight, Vertex *first, Vertex *second)
{
    first->adjcacent_vertices_mst.insert(make_pair(second, weight));
    second->adjcacent_vertices_mst.insert(make_pair(first, weight));


    edges_.push_back(make_tuple(weight, first, second));
}
//Kruskal algortmi
Graph Graph::KruskalMst(int N)
{

    Graph tree;
    Vertex* first;
    Vertex* second;
    Vertex* first_set;
    Vertex* second_set;
    int edge_counter = 0;

    //initialize tree as a disjoint sets.
    for(auto vertex: vertices_){
        tree.add_vertex(vertex);
    }

    sort(edges_.begin(), edges_.end());

    for(auto edge: edges_){

        first = std::get<1>(edge);
        second = std::get<2>(edge);

        first_set = tree.find_Set(first);
        second_set = tree.find_Set(second);

        if(first_set != second_set){
            tree.union_sets(first_set, second_set);

            tree.add_edge_mst(std::get<0>(edge), first, second);
            ++edge_counter;

        }
        if(edge_counter >= N-1){
            return tree;
        }
    }
    return tree;


}

Vertex* Graph::find_Set(Vertex* searched)
{
    if(searched->parent != searched){
        searched->parent = find_Set(searched->parent);
    }
    return searched->parent;
}

void Graph::union_sets(Vertex *a, Vertex *b)
{
    a = find_Set(a);
    b = find_Set(b);
    if(a == b){return;}

    if(a->key > b->key){
        b->parent = a;
    }
    else if(a->key < b->key){
        a->parent = b;
    }
    else{
        b->parent = a;
        a->key++;
    }

}

Graph Graph::PrimMst(int N)
{
    Graph tree;

    std::priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>,
            decltype(&compare_edge_weight)> queue(&compare_edge_weight);
    Vertex* root = vertices_.at(0);
    pair<int, Vertex*> vertex;



    //tree.add_vertex(root);
    root->distance = 0;
    queue.push(make_pair(root->distance ,root));

    while(!queue.empty()){
        vertex = queue.top();
        queue.pop();
        if(vertex.second->visited == true){continue;}
        /*if(vertex->distance > queue.top()->distance){
            queue.push(vertex);
            continue;
        }*/
        tree.add_vertex(vertex.second);
        vertex.second->distance = vertex.first;
        //std::cout<<vertex->distance<<std::endl;

        if(tree.size() == N){break;}

        for(auto edge: vertex.second->adjcacent_vertices){
            if(edge.first->visited == false && edge.first->distance > edge.second){
                //edge.first->distance = edge.second;
                edge.first->parent = vertex.second;

                queue.push(make_pair(edge.second, edge.first));
                //std::cout<<queue.top()->distance<<std::endl;



            }
           /*else {
                if((edge).first->distance > (edge).second && (edge).first != vertex->parent){
                    (edge).first->distance = (edge).second;
                     (edge).first->parent = vertex;
                }
            }
        */

        }
        vertex.second->visited = true;
    }
    for(auto vertex: vertices_){
        if(vertex->parent != vertex){
            tree.add_edge_mst(vertex->distance, vertex, vertex->parent);
        }
    }
    return tree;

}

int Graph::size()
{
    return vertices_.size();
}

bool Graph::compare_edge_weight(const pair<int,Vertex*> a, const pair<int,Vertex*> b)
{
    return a.first >= b.first;
}

void Graph::test()
{
    int sum = 0;
    for(auto edge: edges_){
        sum += std::get<0>(edge);
    }
    std::cout<<sum<<std::endl;;
}











