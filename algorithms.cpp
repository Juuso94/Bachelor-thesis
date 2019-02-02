#include "algorithms.hh"

Graph::Graph()
{

}

Graph::~Graph()
{

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
    std::uniform_int_distribution<> weight(1, 1000);
    srand(time(nullptr));
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
    int random_index = rand() % N;
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


        add_edge(new_vertex, neigbhor_vertex, weight(gen));
        edge_count++;

        visited_vertices.push_back(new_vertex);
    }

    while(edge_count < amount){
        random_index = rand() % vertices_.size();
        Vertex* vertex_a = vertices_.at(random_index);

        random_index = rand() % vertices_.size();
        Vertex* vertex_b = vertices_.at(random_index);

        if(vertex_a != vertex_b && vertex_a->adjcacent_vertices.find(vertex_b) == vertex_a->adjcacent_vertices.end()){
            add_edge(vertex_a, vertex_b, weight(gen));
            edge_count++;
        }
    }
    int sum = 0;

    // Tarkastuksia debuggausta varten.
    for (auto vertex: vertices_)
    {
        std::cout<<vertex->degree<<" ";
        sum += vertex->degree;
    }

    std::cout<<sum;
}

void Graph::add_vertex()
{
    Vertex *vertex = new Vertex {{}, false, 0};
    vertices_.push_back(vertex);
}

void Graph::add_edge(Vertex* first, Vertex* second, int weight)
{
    first->adjcacent_vertices.insert(make_pair(second, weight));
    second->adjcacent_vertices.insert(make_pair(first, weight));
    first->degree++;
    second->degree++;


    edges_.push_back(make_tuple(first, second, weight));

}
