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
        v.d = INT_MAX; // Distance from start vertex
        v.pi = K(); // Parent
        //vertices.push_back(v);

        adjList[v] = edges[i]; //intiallize adjacency list
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
    // Iterate through the adjList to find the vertex with key k
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        if (it->first.key == k) {
            return &(it->first); // Return pointer to the found vertex
        }
    }
    return nullptr; // Return nullptr if vertex with key k not found
}
/*
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
    // Finding the vertices with keys u and v
    Vertex* startVertex = get(u);
    Vertex* targetVertex = get(v);
    
    // If either startVertex or targetVertex is not found, return false
    if (startVertex == nullptr || targetVertex == nullptr) {
        return false;
    }

    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = 1;
        vertices[i].d = -1;
        vertices[i].pi = nullptr;
    }
    startVertex->color = 1;
    startVertex->d = 0;
    startVertex->pi = nullptr;

    queue<K> Q;
    Q.push(startVertex->key);
    
    while(!Q.empty()){
        Vertex* x = get(Q.front());
        Q.pop();
        for(auto it = adjList.begin(); it != adjList.end(); ++it){ 
            Vertex* y = get(it->first);
            if (y->key == targetVertex->key)
                return true;
            if (y->color == 1){
                y->color = 2;
                y->d = x->d + 1;
                y->pi = x->key;
                Q.push(y->key);
            }
        }
    }
    return false;
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
        Vertex* x = Q.front();
        Q.pop();
        for(int i = 0; i < (x->adjList).size(); i++){ 
            Vertex* v = get(adjList[i]);
            if (v->color == 1){
                v->color = 2;
                v->d = x->d + 1;
                v->pi = x->key;
                Q.push(v);
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
void Graph<D, K>::print_path(K s, K v)
{
    Vertex* x = get(s);
    Vertex* y = get(v);

    if (y->key == x->key)
        cout << x->key << endl;
    else if ( y->pi == K()){
        return; 
    }
    else{
        print_path(s, y->pi);
        cout << y->key << "->"; 
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
*/