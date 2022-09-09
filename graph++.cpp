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

        bool hasPathHelper(int src, int dest, vector<bool> &visited) {
            if(src == dest) 
                return true;

            visited[src] = true;

            for(auto edge : adjacency_list[src]) {
                if(visited[edge.end]==false) 
                    return hasPathHelper(edge.end, dest, visited);
            }
            return false;
        }


        void allPathsHelper(
            int src, int dest, vector<bool> &visited, vector<int> &soFar, vector<vector<int>> &paths) {


            visited[src] = true;
            soFar.push_back(src);
            if(src==dest) {
                paths.push_back(soFar);
            }
            else {
                for(auto edge: adjacency_list[src]) {
                    if(visited[edge.end]==false){ 
                        allPathsHelper(edge.end, dest, visited, soFar, paths);
                    }
                }
            }
            
            soFar.pop_back();
            visited[src] = false;

        }

    
    public:
        Graph(int vertices) {
            this->vertices = vertices;
            adjacency_list.resize(vertices);
        }

        void addDirectedEdge(int start, int end, float weight) {
            Edge newEdge(start, end, weight);
            adjacency_list[start].push_back(newEdge);
        }

        void addUndirectedEdge(int v1, int v2, float weight) {
            Edge newEdge1(v1, v2, weight);
            Edge newEdge2(v2, v1, weight);
            adjacency_list[v1].push_back(newEdge1);
            adjacency_list[v2].push_back(newEdge2);
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

        bool hasPath(int src, int dest) {
            vector<bool> visited(vertices, 0);
            return hasPathHelper(src, dest, visited);
        }

        int getDegree(int vertex) {
            return adjacency_list[vertex].size();
        }    


        vector<vector<int>> allPaths(int src, int dest) {
            vector<int> soFar;
            vector<vector<int>> paths;
            vector<bool> visited(vertices, 0);
            allPathsHelper(src, dest, visited, soFar, paths);

            return paths;

        }

        vector<Graph> connectedComponents() {
        }

        
        
};



int main(int argc, char const *argv[])
{
    Graph graph(7);
    graph.addUndirectedEdge(0, 1, 10);
    graph.addUndirectedEdge(0, 3, 10);
    graph.addUndirectedEdge(1, 2, 10);
    graph.addUndirectedEdge(2, 3, 10);
    graph.addUndirectedEdge(3, 4, 10);
    graph.addUndirectedEdge(4, 5, 10);
    graph.addUndirectedEdge(4, 6, 10);
    graph.addUndirectedEdge(5, 6, 10);


    for(auto x: graph.allPaths(0, 6)){ 
        for(auto y : x) {
            cout<<y<<" ";
        }
    cout<<endl;
    }

    // graph.printEdgeList();
    return 0;
}
