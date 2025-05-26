# Kruskal’s Algorithm for Minimum Spanning Tree (MST)

This program implements **Kruskal's Algorithm** to find the Minimum Spanning Tree (MST) of a connected, undirected graph. It uses the **union-find** data structure to avoid cycles and greedily selects edges with minimum weights.

---

## Description

- **Goal:** Find the MST of a given connected, undirected graph.
- **Method:** Sort edges by weight and add them one by one if they don't form a cycle (checked using union-find).
- **Result:** The MST with minimum total edge weight.

---

## Files

- `Source_code.c`  
  Implementation of Kruskal’s algorithm using union-find.

- `input.txt`  
  Input file format:  
  - First line: number of nodes and edges  
  - Next lines: edges in the format `u v weight` (where `u` and `v` are node indices)

- `output.txt`  
  Output file shows:  
  - The minimum total cost of the MST  
  - The edges included in the MST

---

## Example

### input.txt
