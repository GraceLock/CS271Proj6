//=========================================================================
//  graph.h
//  CS 271 Graph Project: Header File
//  Created by Daniel Ziabicki, Grace Lock, William Nguyen
//=========================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

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
        int distance;
        K pi;
        bool color;
        int f;
    };

    vector<Vertex> vertices;
    unordered_map<K, vector<K> > adjList;

    public:
        Graph(vector<K> keys, vector<D> data, vector<vector<K> > edges);

        typename Graph<D, K>::Vertex* get(const K k);
        bool reachable(K u, K v);
        void bfs(K k);
        void print_path(K s, K v);
        string edge_class(K u, K v);
        void bfs_tree(K k);
        void dfs();
        void dfs_visit(Vertex* v, int &t);
};

#endif