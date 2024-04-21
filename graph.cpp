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
        v.f = 0;
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

//=========================================================================
// edge_class

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
string Graph<D, K>::edge_class(K u, K v)
{
    dfs();

    Vertex* v1 = get(u);
    Vertex* v2 = get(v);

    if (v1->color == 0 || v2->color == 0) {                                                 // If one of the vertices is not in the graph.
        return "no edge"; 
    }
    if (v1->distance < v2->distance && v2->distance < v2->f && v2->f < v1->f) {             // u discovered before v and v finishes before u.
        return "tree edge"; 
    } else if (v2->distance <= v1->distance && v1->distance < v1->f && v1->f <= v2->f) {    // v is an ancestor of u.
        return "back edge"; 
    } else if (v1->distance < v2->distance && v2->f < v1->f) {                              // u is an ancestor of v but not a direct parent.
        return "forward edge";
    } else if (v2->f < v1->distance || v1->f < v2->distance) {                              // u and v are in different subtrees.
        return "cross edge";
    }
    return "unknown";                                                                       // Catch-all for any unclassified edges.
}

//=========================================================================
// bfs_tree

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
void Graph<D, K>::bfs_tree(K k)
{
    bfs(k);

}

//=========================================================================
// dfs

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
void Graph<D, K>::dfs()
{
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = 0;
        vertices[i].pi = K();
    }
    int time = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].color == 0){
            dfs_visit(get(vertices[i].key), time);
        }
    }
}

//=========================================================================
// dfs_visit

// Parameters: 
// Return:	
// Preconditions: 
// Postconditions: 
//=========================================================================
template <class D, class K>
void Graph<D, K>::dfs_visit(Vertex* v, int t)
{
    t++;
    v->distance = time;
    v->color = 1;
    for(int j = 0; j < (adjList[v->key][j]).size(); j++){
        Vertex* x = get(adjList[v->key][j].key);
        if (x->color == 0){
            x->pi = v->key;
            dfs_visit(x, t);
        }
    }
    t++;
    v->f = t;
    v->color = 2;
}