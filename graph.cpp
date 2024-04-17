#include <iostream>
#include <string>
#include <queue>
#include "graph.h"

using namespace std;

//=========================================================================
// Constructor

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================

template <class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges)
{
    // Initialize vertices
    for (size_t i = 0; i < keys.size(); ++i) {
        Vertex v;
        v.key = keys[i];
        v.data = data[i];
        v.color = 0; // 0 for white (unvisited)
        v.d = INT_MAX; // Distance from start vertex
        v.pi = -1; // Parent
        vertices.push_back(v);
    }

    //initialize adjacency list

}

//=========================================================================
// get

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================

template <class D, class K>
typename Graph<D, K>::Vertex* get(K k)
{
    this.bfs();

    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].key == k) {
            return &vertices[i];
        }
    }
    return nullptr; // Vertex with key k not found
}

//=========================================================================
// reachable

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>

//=========================================================================
// bfs

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
void bfs(K k)
{
    s = this.get(k);

    for(int i = 0; i < len(vertices); i++){
        vertices[i]->color = 1;
        vertices[i]->d = -1;
        vertices[i]->pi = nullptr;
    }
    s->color = 1;
    s->d = 0;
    s->pi = nullptr;

    queue<K> Q;
    Q.push(s);
    while(!Q.empty()){
        x = Q.front();
        Q.pop();
        for(int i = 0; i < len(x->adjList); i++){ 
            Vertex<D, K> v = get(adjList[i]);
            if (v->color == 1){
                v->color = 2;
                v->d = x->d + 1;
                v->pi = x->key;
                Q.push(v)
            }
        }
    }
}

//=========================================================================
// print_path

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
void print_path(K s, K v)
{
    if v == s
        cout << s->key << endl;
    else if ( v->pi == nullptr){
        return; 
    }
    else{
        print_path(s, v->pi);
        cout << v->key << "->"; 
    }
}

//=========================================================================
// edge_class

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>

//=========================================================================
// bfs_tree

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
