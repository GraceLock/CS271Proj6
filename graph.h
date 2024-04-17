#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

template <class D, class K>
class Graph
{
    private:
        struct Vertex
    {
        K key;
        D data;
        int d;
        K pi;
        int color;
        vector<K> adjList;
    };

    vector<Vertex> vertices;

    public:
        Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);

        Vertex<D, K>* get(const k);
        bool reachable(K u, K v);
        void bfs(K k);
        void print_path(K s, K v);
        string edge_class(K u, K v);
        void bfs_tree(K k);
};

#endif