# cpp_ds_and_algos

A library of data structures and algorithms in C++

# Maze Generator and Solver

## A binary that demonstrates the use of these data structs + algorithm libraries

# Data structures

- [x] Doubly Linked List
- [x] Stack
- [x] Queue
- [x] Dynamic Array
- [x] Union Find
- [x] PriorityQueue / MinHeap
- [x] Hashmap<K, V>
- [x] Graph (using adjencey sparse matrix)

# Algorithms

- [x] Depth First Search
- [x] Breadth First Search
- [x] Dijkstra
- [x] A\*

## Notes

For M1 MacOs use `leak` for memory leaks

# Core DS & Algorithms for Maze Generation & Solving

```text
Data Structures

    Vector<T> (your dynamic array)

    Disjoint‑Set Union (Union‑Find)

        Union by rank + path compression

    HashMap<Key,Value>

        O(1) visited‑set and predecessor mapping

    PriorityQueue<T,Compare> (binary heap)

        For Prim’s generator & A* solver

    Graph Representation

        Adjacency list or CSR sparse‑matrix (choose per perf needs)

Maze Generation Algorithms

    Recursive Backtracker (DFS + Stack<T>)

    Kruskal’s Algorithm (shuffle walls + DSU)

    Prim’s Algorithm (min‑heap of frontier edges + PriorityQueue)

Maze Solving Algorithms

    Breadth‑First Search (shortest unweighted path + Queue<T>)

    Depth‑First Search (exploration + Stack<T>)

    A* Search (PriorityQueue keyed by g+h heuristic)

    Path Reconstruction via your HashMap<Cell,Cell> predecessor map
```
