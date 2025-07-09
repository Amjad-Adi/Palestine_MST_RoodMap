# Palestine_MST_RoadMap(10/10)

![image](https://github.com/user-attachments/assets/20db223d-30b3-42f1-ae9f-a04fba9c66f0)

This C program builds a graph of cities and roads from a file and applies Prim’s and Kruskal’s algorithms to compute the Minimum Spanning Tree (MST)
 The goal is to help visualize and compare the performance and cost of both algorithms in terms of execution time and total distance.

---

## 🚦 Features

- 📁 **Load City Network**: Parses a `Cities.txt` file where each line contains two cities and the distance between them.
- 🌉 **Graph Representation**: Uses an adjacency list with hashing to efficiently store and access city connections.
- ⚙️ **Prim’s Algorithm**: Builds the MST starting from a user-selected city using a custom min-heap.
- 🧩 **Kruskal’s Algorithm**: Builds the MST globally using edge sorting and a union-find data structure.
- ⏱️ **Performance Timing**: Measures and displays the execution time of both algorithms.
- 📊 **Comparison Mode**: Automatically runs both algorithms and displays their costs and runtimes side by side.

---

## 📘 File Format

The input file `Cities.txt` must contain lines in the format:

```
CityA#CityB#Distance
```

Example:

```
Ramallah#Nablus#35
Nablus#Jenin#42
Ramallah#Jericho#28
```

---

## 🧠 Algorithms Used

### Prim’s Algorithm
- Starts from a specified city
- Builds MST incrementally by selecting the minimum-weight edge that expands the tree
- Custom min-heap used for priority queue
- Time complexity: **O((E + V) log V)**

### Kruskal’s Algorithm
- Considers all edges globally and sorts them
- Builds MST by picking smallest edges without forming cycles
- Uses **union-find** for cycle detection
- Time complexity: **O((E + V) log E)**

---

## 📂 Data Structures

- **Adjacency List**: Represents graph using linked lists of `CityNode`s.
- **Hash Table**: Maps city names to indices using double hashing.
- **Min-Heap**: Custom implementation for edge selection in both algorithms.
- **Union-Find**: Helps Kruskal’s algorithm avoid cycles efficiently.

---

## 🧪 Sample Operations

- Load cities: `Cities.txt` ➜ in-memory graph
- Run Prim’s algorithm: choose a source city
- Run Kruskal’s algorithm: automatic
- Compare: cost and runtime of both MSTs

---
