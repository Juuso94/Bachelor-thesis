#include <iostream>
#include <graph.hh>
#include <chrono>
#include <fstream>
#include <string>
#include <math.h>



int main()
{
    std::ofstream outfile;
    outfile.open("Prim_sparse.txt", std::ios::app);

    std::vector<int> test_cases = {5000, 7500, 10000, 15000, 20000, 25000, 30000, 40000};

    for(auto N: test_cases){

        //int M = sqrt(N) * N;

        int M = 5 * N;

        double mean = 0;

        outfile << "Prim, "<< N <<" "<< M;

        for (int i = 0; i< 20; i++) {

            Graph graph;

            //std::cout<<endl<<M<<std::endl;

            graph.add_vertices(N);
            graph.add_edges(M, N);

            auto start = std::chrono::high_resolution_clock::now();
            Graph tree = graph.PrimMst(N);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;

            double result = log2(duration.count() * 1000);

            mean += result;

            auto result_string = std::to_string(result);

            //std::cout<<result<< endl;

            //graph.test();
            //tree.test();

            outfile<< " " << result_string << " ";

            graph.clear();

        }
        mean = mean / 20;
        outfile << mean << endl << endl;
    }
    return 0;
}
