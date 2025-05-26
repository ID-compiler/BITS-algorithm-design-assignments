// 2023EBCS125

#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define MAX_NODES 100

struct Edge {   // Structure to represent an edge
    int u, v, weight;
};

struct Graph {  // Structure to represent a graph
    int numNodes, numEdges;
    struct Edge edges[MAX_EDGES];
};

struct Subset {   // Structure to represent a subset for union-find
    int parent, rank;
};

int find(struct Subset subsets[], int i);  // Function prototypes
void unionSets(struct Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void KruskalMST(struct Graph* graph, FILE* outputFile);

int find(struct Subset subsets[], int i) {    // Find function for union-find
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSets(struct Subset subsets[], int x, int y) {   // Union function for union-find
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {        // Union by rank
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compareEdges(const void* a, const void* b) {     // Comparison function for qsort (sorts edges by weight)
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

void KruskalMST(struct Graph* graph, FILE* outputFile) {       // Function to run Kruskal's algorithm and find the MST
    int numNodes = graph->numNodes;
    struct Edge result[MAX_NODES];          // Store the resulting MST edges
    int resultCount = 0;                    // Number of edges in MST
    int totalCost = 0;                      // Total cost of MST

    qsort(graph->edges, graph->numEdges, sizeof(graph->edges[0]), compareEdges);      // Step 1: Sort all edges by weight

    struct Subset* subsets = (struct Subset*)malloc(numNodes * sizeof(struct Subset));       // Allocate memory for union-find subsets

    for (int v = 0; v < numNodes; ++v) {          // Initialize each node as its own parent (union-find)
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    for (int i = 0; i < graph->numEdges; ++i) {         // Step 2: Iterate through all sorted edges
        struct Edge nextEdge = graph->edges[i];

        int u = nextEdge.u;
        int v = nextEdge.v;

        int setU = find(subsets, u);
        int setV = find(subsets, v);

        if (setU != setV) {                // If u and v belong to different sets, include this edge in the MST
            result[resultCount++] = nextEdge;
            totalCost += nextEdge.weight;
            unionSets(subsets, setU, setV);
        }

        if (resultCount == numNodes - 1) {        // Stop when we have found n-1 edges for the MST
            break;
        }
    }

    // Output the final MST and total cost to the output file
    fprintf(outputFile, "Minimum cost: %d\n", totalCost);
    fprintf(outputFile, "Connections to establish:\n");
    for (int i = 0; i < resultCount; ++i) {
        fprintf(outputFile, "%d-%d\n", result[i].u, result[i].v);
    }

    free(subsets);          // Free allocated memory
}

int main() {
    FILE *inputFile, *outputFile;

    inputFile = fopen("input.txt", "r");      // Open the input file
    if (inputFile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    outputFile = fopen("output.txt", "w");    // Open the output file
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        fclose(inputFile);
        return 1;
    }

    struct Graph graph;
    fscanf(inputFile, "%d %d", &graph.numNodes, &graph.numEdges);   // Read number of nodes and edges

    for (int i = 0; i < graph.numEdges; ++i) {
        fscanf(inputFile, "%d %d %d", &graph.edges[i].u, &graph.edges[i].v, &graph.edges[i].weight);  // Read each edge
    }

    KruskalMST(&graph, outputFile);    // Run Kruskal's algorithm and output the result to the file

    fclose(inputFile);   // Close input file
    fclose(outputFile);  // Close output file

    return 0;
}
