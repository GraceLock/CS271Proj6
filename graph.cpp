#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
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
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K> > edges)
{
    // Initialize vertices
    for (int i = 0; i < keys.size(); ++i) {
        Vertex v;
        v.key = keys[i];
        v.data = data[i];
        v.color = 0; // 0 for white
        v.distance = -1; // Distance from start vertex
        v.pi = K(); // Parent
        vertices.push_back(v);

        adjList[keys[i]] = edges[i]; //intiallize adjacency list
    }
}

//=========================================================================
// get

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
typename Graph<D, K>::Vertex* Graph<D, K>::get(const K k)
{
    // Iterate through the vertices to find the vertex with key k
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].key == k) {
            return &vertices[i]; // Return pointer to the found vertex
        }
    }
    return nullptr; // Return nullptr if vertex with key k not found
}

//=========================================================================
// reachable

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================

template <class D, class K>
bool Graph<D, K>::reachable(K u, K v)
{
    bfs(u);

    // Finding the vertices with keys u and v
    Vertex* startVertex = get(u);
    Vertex* targetVertex = get(v);
    
    // If either startVertex or targetVertex is not found, return false
    if (startVertex == nullptr || targetVertex == nullptr) {
        return false;
    }

    return targetVertex->color == 2; // Return true if v is black (reachable), false otherwise 
}

//=========================================================================
// bfs

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================

template <class D, class K>
void Graph<D, K>::bfs(K k)
{
    Vertex* s = get(k);

    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = 0;
        vertices[i].distance = -1;
        vertices[i].pi = K();
    }
    
    s->color = 1;
    s->distance = 0;
    s->pi = K();
    
    queue<K> Q;
    Q.push(s->key);
    while(!Q.empty()){
        K a = Q.front();
        Vertex* u = get(a);
        Q.pop();
        for(int i = 0; i < adjList[u->key].size(); i++){ 
            Vertex* v = get(adjList[u->key][i]);
            if (v->color == 0){
                v->color = 1; // 1 for gray 
                v->distance = u->distance + 1;
                v->pi = u->key;
                Q.push(v->key);
            }
        }
        u->color = 2; // 2 for black 
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
void Graph<D, K>::print_path(K s, K v)
{
    Vertex* x = get(s);
    Vertex* y = get(v);

    if (y->key == x->key)
        cout << x->key;
    else if ( y->pi == K() ){
        return; 
    }
    else{
        print_path(s, y->pi);
        cout << " -> " << y->key; 
    }
}
/*
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
*/