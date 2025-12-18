#include <bits/stdc++.h>
#include <random>
using namespace std;

struct Edge {
    int u, v;
};

void contract(vector<Edge>& edges, int u, int v) {
    for (auto &e : edges) {
        if (e.u == v) e.u = u;
        if (e.v == v) e.v = u;
    }

    vector<Edge> newEdges;
    for (auto &e : edges) {
        if (e.u != e.v)
            newEdges.push_back(e);
    }
    edges = newEdges;
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    int V, E;
    infile >> V >> E;

    vector<Edge> originalEdges(E);
    for (int i = 0; i < E; i++) {
        int u, v;
        infile >> u >> v;
        originalEdges[i] = {u, v};
    }

    random_device rd;
    mt19937 gen(rd());

    int iterations = max(1, V*V);
    int minCut = INT_MAX;
    vector<Edge> bestCut;

    for (int it = 0; it < iterations; it++) {
        vector<Edge> edges = originalEdges;

        vector<int> vertices(V);
        for (int i = 0; i < V; i++) vertices[i] = i+1;

        while (vertices.size() > 2) {
            uniform_int_distribution<> dis(0, edges.size() - 1);
            int idx = dis(gen); 
            int u = edges[idx].u;
            int v = edges[idx].v;

            contract(edges, u, v);
            vertices.erase(remove(vertices.begin(), vertices.end(), v), vertices.end());
        }

        if ((int)edges.size() < minCut) {
            minCut = edges.size();
            bestCut = edges;
        }
    }

    outfile << "Mincut = " << minCut << endl;
    outfile << "Edges in Min Cut:" << endl;
    for(auto &e : bestCut) {
        outfile << e.u << " - " << e.v << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}
