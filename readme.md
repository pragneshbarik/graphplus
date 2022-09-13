# **graph++**


Minimal C++ libary for performing graph operations.



## **Algorithms**



### *1. Basic Paths and Cycles*

```
    addDirectedEdge(start, end, weight)
    addUndirectedEdge(start, end, weight)
    getDegree(vertex)
    hasPath(src, dest)
    allPaths(src, dest)
    connectedVertices(vertex)
    splitConnectedComponents()
    isConnected()
    isEulerian()
    explore(vertex)
```

### *2. Hamiltonian*
```
    hamiltonian.paths(src)
    hamiltonian.cycles(src)
```

### *3. Minimal Spanning Trees*

```
    minimalSpanningTree.prim()
    * minitmalSpanningTree.krushkal()
```

### *4. Shortest Paths and Allied Algorithms*

```
    singleSourceShortestPaths.dijkstra(src)
    singleSourceShortestPaths.bellmanFord(src)
    singleSourceShortestPaths.detectNegativeCycle()
    
```

### 5. Maximum Flow 
```
    * maximumFlow.fordFulkerson(source, sink)
    * maximumFlow.edmondsKarp(source, sink)
```


> methods marked * are still in development.