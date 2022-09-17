# **graph++**


Minimal C++ libary for performing graph operations.



## **Algorithms**


### 0. Constructors and Allied Classes

```
    Edge(int start, int end, float weight)
        Self-explanatory

    Graph(int vertices) 
        Initializes empty graph with specified number of vertices.
    
    Graph(vector<vector<Edge>> adjacency_list)
        Initializes non-empty graph with adjacency list.
```

### 1. Basic Paths and Cycles

```
    Graph.addDirectedEdge(Edge)
    Graph.addDirectedEdge(start, end, weight)
    Graph.addUndirectedEdge(start, end, weight)
    Graph.getDegree(vertex)
    Graph.display()
    Graph.hasPath(src, dest)
    Graph.allPaths(src, dest)
    Graph.connectedVertices(vertex)
    Graph.splitConnectedComponents()
    Graph.isConnected()
    Graph.isEulerian()
    Graph.explore(vertex)
```

### 2. Hamiltonian
```
    Graph.hamiltonian.paths(src)
    Graph.hamiltonian.cycles(src)
```

### 3. Minimal Spanning Trees

```
    Graph.minimalSpanningTree.prim()
    * Graph.minitmalSpanningTree.krushkal()
```

### 4. Shortest Paths and Allied Algorithms

```
    Graph.singleSourceShortestPaths.bellmanFord(src)
    Graph.singleSourceShortestPaths.dijkstra(src)
    Graph.singleSourceShortestPaths.detectNegativeCycle()
```

### 5. Maximum Flow 
```
    * Graph.maximumFlow.fordFulkerson(source, sink)
    * Graph.maximumFlow.edmondsKarp(source, sink)
```


> methods marked * are still in development.