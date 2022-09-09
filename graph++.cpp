// graph++, A minimal library for performing operations on Graph Data Structure
// v0.0.1
// Author: Pragnesh Barik
#include <iostream>
#include <vector>

using namespace std;

class Edge {
    public:
    int start, end;
    float weight;

    Edge(int start, int end, float weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }  
};

class Graph{
    private:
        vector<vector<Edge>> adjacency_list; 
        int vertices;
    
    public:
        Graph(int vertices) {
            this->vertices = vertices;
            adjacency_list.resize(vertices);
        }



        void addEdge(int start, int end, float weight) {
            Edge newEdge(start, end, weight);
            adjacency_list[start].push_back(newEdge);
        }

        void printEdgeList() {
            for (auto vertex: adjacency_list) {
                for(auto edge: vertex) {
                    cout
                    <<"Start: "<<edge.start
                    <<", End: "<<edge.end
                    <<", Weight: "<<edge.weight
                    <<endl;
                }
            }
        }

        bool hasPathHelper(int src, int dest, vector<bool> &visited) {
            if(src == dest) {
                return true;
            }

            visited[src] = true;

            for(auto edge : adjacency_list[src]) {
                if(visited[edge.end]==false) 
                    return hasPathHelper(edge.end, dest, visited);
            }

            return false;
        }


        bool hasPath(int src, int dest) {
            vector<bool> visited(vertices, 0);
            return hasPathHelper(src, dest, visited);
        }

        int getDegree(int vertex) {
            return adjacency_list[vertex].size();
        }
        
};



int main(int argc, char const *argv[])
{
    Graph graph(3);
    graph.addEdge(0, 2, 10);
    graph.addEdge(1, 2, 20);
    graph.addEdge(0, 1, 10);
    graph.printEdgeList();
    return 0;
}
