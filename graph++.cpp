// graph++, A minimal library for performing operations on Graph Data Structure.
// v0.0.1
// Author: Pragnesh Barik
#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<queue>


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

class Path {
    public:
        int currentVertex;
        vector<int> soFar;
        int weight;

        Path(int current, vector<int> soFar, int weight){
            this->currentVertex =  current;
            this->soFar = soFar;
            this->weight = weight;
        }

        Path(){}
};
class GraphOperations {
    protected :
    vector<vector<Edge>> adjacency_list; 
    int vertices;

    public:
    void update(vector<vector<Edge>> adjacency_list, int vertices) {
        this->adjacency_list = adjacency_list;
        this->vertices = vertices;
    }

};
class SingleSourceShortestPaths : public GraphOperations{
    private :
    
    class compare {
    public :
        bool operator()(const Path& A, const Path& B){
            return A.weight > B.weight;
        }
    };


    public:
    
    SingleSourceShortestPaths(){}
    SingleSourceShortestPaths(vector<vector<Edge>> adjacency_list, int vertices) {
        update(adjacency_list, vertices);
    }


    vector<Path> dijkstra(int src) {
            priority_queue<Path,vector<Path>,compare> pathQ;
            vector<bool> visited(vertices, false);
            vector<int> soFar;
            vector<Path> shortestPaths;
            soFar.push_back(src);
            pathQ.push(Path(src, soFar,  0));

            while (!pathQ.empty()){
                Path currentPath = pathQ.top();
                pathQ.pop();

                if(visited[currentPath.currentVertex]) continue;
                visited[currentPath.currentVertex] = true;

                shortestPaths.push_back(currentPath);


                for(auto edge : adjacency_list[currentPath.currentVertex]){
                    if(!visited[edge.end]){
                        vector<int> newSoFar = currentPath.soFar;
                        newSoFar.push_back(edge.end);
                        Path newPath(edge.end, newSoFar, currentPath.weight + edge.weight);
                        pathQ.push(newPath);
                    }
                }
            }
            return shortestPaths;
        }

        
        vector<float> bellmanFord(int src) {
            vector<float> distVec(this->vertices, INT_MAX);
            distVec[src] = 0;

            for(int i=1; i<vertices; i++)
                for(auto &edges : adjacency_list)
                    for(auto &edge : edges) 
                        if(distVec[edge.start]+edge.weight < distVec[edge.end]) 
                            distVec[edge.end]=distVec[edge.start] + edge.weight; 
            
            return distVec;
        }

        bool detectNegativeCycles() {
            vector<float> distVec=bellmanFord(0);
            vector<float> tempVec = distVec;
            
            for(auto &edges : adjacency_list)
                    for(auto &edge : edges) 
                        if(distVec[edge.start]+edge.weight < distVec[edge.end]) 
                            distVec[edge.end]=distVec[edge.start] + edge.weight; 

            return(tempVec!=distVec);
        }

};
class Hamiltonian : public GraphOperations {
    private:
    
    void helper(
        int src, int origin, 
        unordered_set<int> &visited, 
        vector<int> &soFar, 
        set<vector<int>> &paths, 
        set<vector<int>> &cycles) {
        
        visited.insert(src);
        soFar.push_back(src);
        
        if(visited.size()==vertices){
            for(auto edge: adjacency_list[src]) {
                if(edge.end==origin)
                    cycles.insert(soFar);
                else 
                    paths.insert(soFar); 
            }
            return;
        }

        for(auto edge: adjacency_list[src]) {
            if(visited.find(edge.end)==visited.end()){
                helper(edge.end, origin, visited, soFar, paths, cycles);
            }
        }

        soFar.pop_back();
        visited.erase(src);
    }

    
    public:

    Hamiltonian() {}
    
    Hamiltonian(vector<vector<Edge>> adjacency_list, int vertices) {
        update(adjacency_list, vertices);
    }

    set<vector<int>> paths(int src) {
        unordered_set<int> visited;
        vector<int> soFar;
        set<vector<int>> Hpaths, Hcycles;
        helper(src, src, visited, soFar, Hpaths, Hcycles);
        return Hpaths;
    }

    set<vector<int>> cycles(int src) {
        unordered_set<int> visited;
        vector<int> soFar;
        set<vector<int>> Hpaths, Hcycles;
        helper(src, src, visited, soFar, Hpaths, Hcycles);
        return Hcycles;
    }

};
class MinimalSpanningTree : public GraphOperations {
    
    public:
    MinimalSpanningTree(vector<vector<Edge>> adjacency_list, int vertices){
        update(adjacency_list, vertices);
    }

    MinimalSpanningTree(){}
    vector<vector<Edge>> prim() {
            class compare {
                public :
                    bool operator()(const Edge& A, const Edge& B){
                        return A.weight > B.weight;
                    }
                };
            vector<vector<Edge>> mst;
            mst.resize(vertices);

            priority_queue<Edge, vector<Edge>, compare> edgeQ;
            vector<bool> visited(vertices, false);
            Edge tempEdge(-1, 0, 0);
            edgeQ.push(tempEdge);

            while(!edgeQ.empty()){
                Edge topEdge = edgeQ.top();
                edgeQ.pop();

                if(visited[topEdge.end]) continue;

                visited[topEdge.end] = true;

                if(topEdge.start!=-1){
                    mst[topEdge.start].push_back(topEdge);
                }
                for(auto edge : adjacency_list[topEdge.end]){
                    if(!visited[edge.end]){
                        Edge e(topEdge.end, edge.end, edge.weight);
                        edgeQ.push(e);
                    }
                }
            }
        return mst;
        
        }    

};
class MaximumFlow : public GraphOperations{};
 
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


        void connectedVerticesHelper(int src, vector<bool> &visited, vector<int> &vertexList) {
            visited[src] = true;
            vertexList.push_back(src);

            for(auto edge: adjacency_list[src]){
                if(!visited[edge.end]) {
                    connectedVerticesHelper(edge.end, visited, vertexList);
                }
            }
        }


        vector<int> connectedVertices(int src, vector<bool> &visited) {
            // vector<bool> visited;
            visited.resize(vertices, false);
            vector<int> vertexList;
            connectedVerticesHelper(src, visited, vertexList);
        
            return vertexList;
        }

        void initialize() {
            SingleSourceShortestPaths *sssp;
            Hamiltonian *hp;
            MinimalSpanningTree *mst;

            sssp = new SingleSourceShortestPaths(this->adjacency_list, this->vertices);
            hp = new Hamiltonian(this->adjacency_list, this->vertices);
            mst = new MinimalSpanningTree(this->adjacency_list, this->vertices);
            
            singleSourceShortestPaths = *sssp;
            hamiltonian = *hp;
            minimalSpanningTree = *mst;
            
            delete hp, sssp, mst;
        }


        void notify(){
            if(adjacency_list.size()>vertices) 
                this->vertices=adjacency_list.size();
            hamiltonian.update(adjacency_list, vertices);
            singleSourceShortestPaths.update(adjacency_list, vertices);
            minimalSpanningTree.update(adjacency_list, vertices);

        }

    
    public:  
        Hamiltonian hamiltonian;
        SingleSourceShortestPaths singleSourceShortestPaths;
        MinimalSpanningTree minimalSpanningTree;

        Graph(int vertices) {
            this->vertices = vertices;
            adjacency_list.resize(vertices);
            initialize();
            notify();
        }

        Graph(vector<vector<Edge>> adjacency_list){
            this->adjacency_list = adjacency_list;
            this->vertices = adjacency_list.size();
        }

    
        int getVertices() {
            return vertices;
        }


        void addDirectedEdge(int start, int end, float weight) {
            Edge newEdge(start, end, weight);
            adjacency_list[start].push_back(newEdge);
            notify();
        }


        vector<vector<Edge>> getAdjacencyList() {
            return adjacency_list;
        }


        void addUndirectedEdge(int v1, int v2, float weight) {
            Edge newEdge1(v1, v2, weight);
            Edge newEdge2(v2, v1, weight);
            adjacency_list[v1].push_back(newEdge1);
            adjacency_list[v2].push_back(newEdge2);
            notify();
        }


        void display() {
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

    
        vector<int> connectedVertices(int src) {
            vector<bool> visited;
            visited.resize(vertices, false);
            vector<int> vertexList;

            connectedVerticesHelper(src, visited, vertexList);
            
            return vertexList;
        }


        vector<vector<int>> splitConnectedComponents() {
            vector<vector<int>> components;
            vector<bool> visited(vertices, false);

            for(int i=0; i<vertices; i++) {
                if(!visited[i]){
                 components.push_back(connectedVertices(i, visited));   
                }
            }

            return components;
        }


        bool isConnected() {
            return (splitConnectedComponents().size()==1);
        }



        /**
         * @brief Only works for directed graphs.
         * 
         */
        bool isEulerian() {
            for(auto vertex : adjacency_list)
                if(vertex.size()%2 != 0) return false;
    
            return true;
        }


        /**
         * @brief returns bfs sequence of a graph.
         * 
         * @param src 
         * @return vector<int> 
         */
        vector<int> explore(int src){
            vector<bool> visited(vertices, false);
            queue<int> vertexQ;
            vector<int> bfs;
            vertexQ.push(src);

            while (!vertexQ.empty()){
                int vertexToExplore;
                
                vertexToExplore = vertexQ.front();
                vertexQ.pop();

                if(visited[vertexToExplore]) continue;

                visited[vertexToExplore]=true;

                bfs.push_back(vertexToExplore);
                
                for(auto edge :  adjacency_list[vertexToExplore]) {
                    if(!visited[edge.end]){
                        vertexQ.push(edge.end);
                    }
                }
                 
            }
            return bfs;
        }

           

};

void display(vector<int> a){
    for(auto &x : a)cout<<x<<" ";
    cout<<endl;
}
void display(vector<vector<int>> a){
    for(auto &x: a){
        for(auto &y: x){
            cout<<y<<" ";
        }
        cout<<endl;
    }
        cout<<endl;

}
void display(vector<vector<Edge>> adjacency_list){
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
void display(vector<Path> a){
    for(auto &x : a){
        cout<<"Path: ";
        for(auto vertex: x.soFar){
            cout<<vertex<<" ";
        }
    cout<<"Weight: "<<x.weight<<endl;
    }
}


int main(int argc, char const *argv[]){
    Graph graph(7);
    // graph.addUndirectedEdge(0, 1, 10);
    // graph.addUndirectedEdge(0, 3, 10);
    // graph.addUndirectedEdge(1, 2, 10);
    // graph.addUndirectedEdge(2, 3, 10);
    // graph.addUndirectedEdge(3, 4, 10);
    // graph.addUndirectedEdge(4, 5, 10);
    // graph.addUndirectedEdge(4, 6, 10);
    // graph.addUndirectedEdge(5, 6, 10);
    
    graph.addUndirectedEdge(0, 1, 10);
    graph.addUndirectedEdge(0, 3, 80);
    graph.addUndirectedEdge(1, 2, 10);
    graph.addUndirectedEdge(2, 3, 10);
    graph.addUndirectedEdge(3, 4, 10);
    graph.addUndirectedEdge(4, 5, 10);
    graph.addUndirectedEdge(4, 6, 10);
    graph.addUndirectedEdge(5, 6, 10);
    
    Graph tree(graph.minimalSpanningTree.prim());
    tree.display();
    // for(auto x:graph.hamiltonian.cycles(0)) {
    //     for(auto y:x) {
    //         cout<<y<<' ';
    //     }
    //     cout<<endl;
    // };

    // display(graph.singleSourceShortestPaths.dijkstra(0));

    // cout<<graph.isConnected();

    // display(graph.dijkstra(0));
    // for(auto x: graph.allPaths(1, 6)){ 
    //     for(auto y : x) {
    //         cout<<y<<" ";
    //     }
    // cout<<endl;
    // }

    // graph.printEdgeList();
    return 0;
}
