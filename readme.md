# **graph++**


Minimal C++ libary for performing graph operations.



## **Algorithms**



### 1. Basic Paths and Cycles

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
    * explore(vertex)
    * inDegree(vertex)
    * outDegree(vertex)
    * getHamiltonianPath()
    * getHamiltonianCycle()
```

### 2. Minimal Spanning Trees

```
    * prim()
    * krushkal()
```

### 3. Shortest Path

```
    * djikstra(src, dest)
    * aStar(src, dest)
```

### 4. Advanced 
```
    * topologicalSort()
```


> methods marked * are still in development.