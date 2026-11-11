Let's revise **Graph Algorithms comprehensively for C++ interviews**, particularly for SDE-2 roles.

I'll organize them by category rather than randomly listing algorithms. This will help you identify which algorithm to apply when you encounter a graph problem.

# 1. Graph Fundamentals

Before algorithms, revise these concepts.

| Concept | Explanation |
|---|---|
| Directed graph | Edges have direction |
| Undirected graph | Edges work both ways |
| Weighted graph | Edges have weights |
| Unweighted graph | All edges have equal weight |
| Cyclic graph | Contains at least one cycle |
| DAG | Directed Acyclic Graph |
| Connected graph | Every vertex is reachable from every other vertex |
| Strongly connected graph | Every vertex can reach every other vertex in a directed graph |
| Dense graph | Number of edges approaches V² |
| Sparse graph | Number of edges is relatively small |

### Graph representations

**1. Adjacency Matrix**
- Space: O(V²)
- Checking an edge: O(1)
- Iterating neighbours: O(V)

**2. Adjacency List**
- Space: O(V + E)
- Checking an edge: O(degree)
- Iterating neighbours: O(degree)

**3. Edge List**
- Stores edges as `(u, v, weight)`.
- Space: O(E).
- Particularly useful for Kruskal and Bellman-Ford.

For competitive programming and interviews, adjacency lists are generally preferred.

---

# 2. Graph Traversal Algorithms

These are the foundation of almost every graph problem.

| Algorithm | Purpose | Time Complexity |
|---|---|---|
| BFS | Level-order traversal | O(V + E) |
| DFS | Depth-first traversal | O(V + E) |
| Iterative DFS | DFS using stack | O(V + E) |
| Multi-source BFS | Shortest distance from multiple sources | O(V + E) |

### BFS (Breadth First Search)

Uses a queue.

Important applications:
- Shortest path in an unweighted graph.
- Minimum number of moves.
- Level-wise traversal.
- Connected components.
- Multi-source shortest paths.
- Grid problems.

**Key property:** BFS finds the shortest path in terms of number of edges when all edges have equal weight.

### DFS (Depth First Search)

Uses recursion or a stack.

Important applications:
- Connected components.
- Cycle detection.
- Topological sorting.
- Finding paths.
- Bridges and articulation points.
- Strongly connected components.
- Backtracking.

**Important:** DFS traversal order does not guarantee the shortest path.

### Multi-source BFS

Instead of inserting one starting vertex into the queue, insert all starting vertices initially.

Applications:
- Rotten Oranges.
- Distance from nearest 1.
- Nearest hospital.
- Fire spreading.
- Multiple simultaneous starting points.

---

# 3. Cycle Detection

One of the most frequently tested graph concepts.

| Graph | Algorithm | Complexity |
|---|---|---|
| Undirected | DFS + parent tracking | O(V + E) |
| Undirected | BFS + parent tracking | O(V + E) |
| Undirected | DSU | O(E α(V)) |
| Directed | DFS + recursion stack / colours | O(V + E) |
| Directed | Kahn's algorithm | O(V + E) |

### Undirected graph

When performing DFS:

If a neighbour is already visited and is not the parent, a cycle exists.

Remember:
```cpp
if (vis[v] && v != parent)
    return true;
```

### Directed graph

Two common approaches:

**Approach 1: DFS + recursion stack**

Maintain:
- `vis[]`
- `pathVis[]`

If a vertex is already in the current recursion path, a cycle exists.

**Approach 2: Kahn's algorithm**

Perform topological sorting.

If the number of processed vertices is less than V, the graph contains a cycle.

---

# 4. Topological Sorting

Applicable only to Directed Acyclic Graphs (DAGs).

Two important approaches:

| Algorithm | Approach | Complexity |
|---|---|---|
| DFS Topological Sort | Push vertex after processing neighbours | O(V + E) |
| Kahn's Algorithm | BFS using indegree | O(V + E) |

### DFS approach

1. Perform DFS.
2. Visit all unvisited neighbours.
3. Push the current vertex into a stack after processing neighbours.
4. Reverse the resulting order.

### Kahn's algorithm

1. Calculate indegree of every vertex.
2. Insert all vertices having indegree 0 into a queue.
3. Remove a vertex and process its neighbours.
4. Decrease their indegrees.
5. Insert newly available zero-indegree vertices.

**Important applications:**
- Course Schedule I and II.
- Task scheduling.
- Dependency resolution.
- Build systems.
- Detecting directed cycles.
- Alien Dictionary.

**Advanced:** Topological sorting using DFS and Kahn's algorithm should both be comfortable for you.

---

# 5. Shortest Path Algorithms

This is probably the most important category to master.

| Algorithm | Applicable graph | Time complexity |
|---|---|---|
| BFS | Unweighted | O(V + E) |
| 0-1 BFS | Weights 0 and 1 | O(V + E) |
| DAG Shortest Path | Directed acyclic graph | O(V + E) |
| Dijkstra | Non-negative weights | O((V + E) log V) |
| Bellman-Ford | Negative weights allowed | O(VE) |
| Floyd-Warshall | All-pairs shortest paths | O(V³) |

### 5.1 BFS shortest path

Use when all edges have equal weights.

### 5.2 0-1 BFS

Use when edge weights are exclusively 0 or 1.

Uses a deque:
- Weight 0 → push_front.
- Weight 1 → push_back.

### 5.3 Dijkstra

Use when all edge weights are non-negative.

Typically implemented using:
- Adjacency list.
- Min priority queue.
- Distance array.

C++:
```cpp
priority_queue<
    pair<int,int>,
    vector<pair<int,int>>,
    greater<pair<int,int>>
> pq;
```

Important concepts:
- Relaxation.
- Greedy selection.
- Stale priority queue entries.
- Distance initialization.
- Why negative weights break Dijkstra.

### 5.4 Bellman-Ford

Use when negative edge weights are present.

Algorithm:
1. Relax every edge V-1 times.
2. Perform one additional iteration.
3. If any distance can still be reduced, a reachable negative cycle exists.

### 5.5 Floyd-Warshall

Finds shortest paths between every pair of vertices.

```cpp
for(int k = 0; k < n; k++)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            dist[i][j] = min(
                dist[i][j],
                dist[i][k] + dist[k][j]
            );
        }
    }
}
```

Time: O(V³)  
Space: O(V²)

### 5.6 DAG shortest path

Topologically sort the graph and relax edges in topological order.

Can handle negative edge weights because there are no cycles.

**Important interview distinction:**

| Scenario | Algorithm |
|---|---|
| Unweighted graph | BFS |
| Binary weights | 0-1 BFS |
| Positive/non-negative weights | Dijkstra |
| Negative weights | Bellman-Ford |
| DAG | Topological sort + relaxation |
| All pairs shortest path | Floyd-Warshall |

---

# 6. Minimum Spanning Tree (MST)

Two essential algorithms.

### 6.1 Prim's Algorithm

- Greedy algorithm.
- Starts from any vertex.
- Continuously selects the minimum-weight edge connecting the current tree to an unvisited vertex.
- Usually implemented using a min heap.

Complexity: O(E log V) with an adjacency-list implementation and binary heap.

### 6.2 Kruskal's Algorithm

- Sort all edges by weight.
- Process edges in increasing order.
- Include an edge only if it doesn't create a cycle.
- Uses Disjoint Set Union (DSU).

Complexity: O(E log E).

### Prim vs Kruskal

| Prim | Kruskal |
|---|---|
| Grows one tree | Builds components and merges them |
| Uses priority queue | Uses sorting |
| Uses visited array | Uses DSU |
| Works naturally with adjacency list | Works naturally with edge list |
| Selects minimum outgoing edge | Selects minimum edge globally |

**Important:** MST is not the same as shortest path.

---

# 7. Disjoint Set Union (DSU)

Also called Union-Find.

This is an important algorithm that you should not skip.

Two operations:

1. `findParent(x)`
2. `union(x, y)`

Optimizations:
- Path compression.
- Union by rank.
- Union by size.

Complexity: Almost O(1) amortized per operation, formally O(α(V)).

Applications:
- Kruskal's algorithm.
- Cycle detection in undirected graphs.
- Number of connected components.
- Dynamic connectivity.
- Accounts Merge.
- Number of Islands II.
- Redundant Connection.

**Advanced DSU topics:**
- DSU with component sizes.
- DSU with extra information.
- DSU on grids.
- Offline connectivity queries.

---

# 8. Strongly Connected Components (SCC)

Applicable to directed graphs.

Two major algorithms:

### 8.1 Kosaraju's Algorithm

Three steps:

1. DFS on the original graph and store vertices according to finishing time.
2. Reverse all graph edges (transpose graph).
3. Process vertices in reverse finishing order using DFS.

Each DFS in the second pass discovers one SCC.

Complexity: O(V + E).

### 8.2 Tarjan's Algorithm

Uses:
- Discovery time (`tin[]`).
- Lowest reachable discovery time (`low[]`).
- Stack.
- On-stack tracking.

It identifies SCCs using a single DFS traversal.

Complexity: O(V + E).

| Kosaraju | Tarjan |
|---|---|
| Two DFS passes | One DFS pass |
| Requires transpose graph | No transpose required |
| Easier to understand | More intricate implementation |
| O(V + E) | O(V + E) |

---

# 9. Bridges and Articulation Points

These are important advanced DFS algorithms.

### 9.1 Bridges

An edge whose removal increases the number of connected components.

Uses:
- `tin[]`
- `low[]`

For DFS tree edge (u, v):

A bridge exists when:

`low[v] > tin[u]`

Complexity: O(V + E).

### 9.2 Articulation Points

A vertex whose removal increases the number of connected components.

For a non-root vertex u, it is an articulation point if a child v satisfies:

`low[v] >= tin[u]`

Special condition:
- DFS root is an articulation point if it has more than one DFS child.

Complexity: O(V + E).

These two algorithms are closely related. Learn them together.

---

# 10. Bipartite Graph

A graph is bipartite if its vertices can be divided into two sets such that no edge connects vertices belonging to the same set.

Two approaches:

1. BFS + 2-colouring.
2. DFS + 2-colouring.

Complexity: O(V + E).

Applications:
- Possible two-team assignment.
- Graph colouring with two colours.
- Detecting odd-length cycles.
- Matching problems.

**Important property:** A graph is bipartite if and only if it contains no odd-length cycle.

---

# 11. Other Important Graph Algorithms

These are commonly missed when preparing only the standard graph syllabus.

| Algorithm | Purpose | Complexity |
|---|---|---|
| Flood Fill | Explore connected regions | O(V + E) |
| Hierholzer's Algorithm | Eulerian path/circuit | O(V + E) |
| Tarjan's Bridge Algorithm | Find bridges | O(V + E) |
| Tarjan's SCC | Find strongly connected components | O(V + E) |
| A* Search | Heuristic shortest path | Depends on graph and heuristic |
| Edmonds-Karp | Maximum flow | O(VE²) |
| Dinic's Algorithm | Maximum flow | O(V²E) general bound |
| Hopcroft-Karp | Maximum bipartite matching | O(E√V) |
| Transitive Closure | Reachability between all pairs | O(V³) using Floyd-style DP |
| Johnson's Algorithm | All-pairs shortest paths for sparse graphs | O(VE log V) with suitable heap implementation |

A few deserve particular attention:

**Eulerian Path/Circuit — Hierholzer's Algorithm**

Finds a path that uses every edge exactly once.

**Maximum Flow — Ford-Fulkerson / Edmonds-Karp / Dinic**

Used for:
- Network flow.
- Resource allocation.
- Bipartite matching.
- Capacity constraints.

**A* Search**

Uses:
- Actual distance travelled: `g(n)`
- Estimated distance to destination: `h(n)`

Evaluation:

`f(n) = g(n) + h(n)`

Useful for pathfinding and navigation.

---

# 12. Graph Problems on Grids

Don't overlook these. Many interview problems disguise graph problems as matrix problems.

| Problem | Typical approach |
|---|---|
| Number of Islands | DFS/BFS |
| Rotten Oranges | Multi-source BFS |
| Flood Fill | DFS/BFS |
| Surrounded Regions | Boundary DFS/BFS |
| Number of Enclaves | Boundary DFS/BFS |
| Shortest Path in Binary Matrix | BFS |
| Word Ladder | BFS |
| Minimum Multiplications | BFS |
| Minimum Effort Path | Dijkstra |
| Swim in Rising Water | Dijkstra / Binary Search + BFS |
| Making a Large Island | DFS + DSU |
| Number of Islands II | DSU |

---

# 13. Complete Revision Checklist

Here is the checklist I would use to prepare for graph interviews.

| Priority | Algorithm | Revision |
|---|---|---|
| Essential | BFS | ☐ |
| Essential | DFS | ☐ |
| Essential | Connected Components | ☐ |
| Essential | Cycle Detection (Undirected) | ☐ |
| Essential | Cycle Detection (Directed) | ☐ |
| Essential | Bipartite Graph | ☐ |
| Essential | Topological Sort (DFS) | ☐ |
| Essential | Kahn's Algorithm | ☐ |
| Essential | Dijkstra | ☐ |
| Essential | Bellman-Ford | ☐ |
| Essential | Prim | ☐ |
| Essential | Kruskal | ☐ |
| Essential | DSU | ☐ |
| Essential | Kosaraju | ☐ |
| Important | 0-1 BFS | ☐ |
| Important | DAG Shortest Path | ☐ |
| Important | Floyd-Warshall | ☐ |
| Important | Bridges | ☐ |
| Important | Articulation Points | ☐ |
| Important | Tarjan SCC | ☐ |
| Important | Multi-source BFS | ☐ |
| Important | Grid BFS/DFS | ☐ |
| Advanced | Eulerian Path | ☐ |
| Advanced | A* Search | ☐ |
| Advanced | Maximum Flow | ☐ |
| Advanced | Bipartite Matching | ☐ |
| Advanced | Johnson's Algorithm | ☐ |

---

# 14. Recommended Revision Order

I would revise in this sequence:

**Phase 1 — Fundamentals**
1. BFS
2. DFS
3. Connected Components
4. Cycle Detection
5. Bipartite Graph

**Phase 2 — Ordering and Connectivity**
6. Topological Sort
7. Kahn's Algorithm
8. DSU
9. Kruskal
10. Prim

**Phase 3 — Shortest Paths**
11. BFS Shortest Path
12. 0-1 BFS
13. Dijkstra
14. Bellman-Ford
15. Floyd-Warshall
16. DAG Shortest Path

**Phase 4 — Advanced DFS**
17. Kosaraju
18. Tarjan SCC
19. Bridges
20. Articulation Points

**Phase 5 — Advanced Applications**
21. Eulerian Path
22. Maximum Flow
23. Bipartite Matching
24. A* Search

### My recommendation

Don't just memorize implementations. For each algorithm, make sure you can answer these five questions:

1. What problem does it solve?
2. Under what graph conditions does it work?
3. Why does it work?
4. What is its time and space complexity?
5. What breaks if we modify one of its assumptions?

For example, **why does Dijkstra fail with negative edge weights?** Why does BFS fail to find the shortest weighted path? Why does Kruskal need DSU?

These questions distinguish someone who knows the implementation from someone who actually understands graph algorithms.

---







**I'd start with BFS and DFS, then move to cycle detection.** Once those are solid, the remaining algorithms become considerably easier to understand.
