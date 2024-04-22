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
        cout << data[i] << endl;
        v.color = false; // false for white
        v.distance = -1; // Distance from start vertex
        v.pi = K(); // Parent
        v.f = 0;
        vertices.push_back(v);

        adjList[keys[i]] = edges[i]; //intialize adjacency list
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

    return targetVertex->color == true; // Return true if v is black (reachable), false otherwise 
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
        vertices[i].color = false;
        vertices[i].distance = -1;
        vertices[i].pi = K();
    }
    
    s->color = true;
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
            if (v->color == false){
                v->color = true; // 1 for gray 
                v->distance = u->distance + 1;
                v->pi = u->key;
                Q.push(v->key);
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

    if (v2->pi == v1->key) { //tree edge, v2 is a direct descendant of v1
        return "tree edge";
    } else if (v1->distance < v2->distance && v2->distance < v2->f && v2->f < v1->f) { //forward edge, v2 is a descendant of v1
        return "forward edge";
    } else if (v2->distance <= v1->distance && v1->distance < v1->f && v1->f <= v2->f) { //back edge, v2 is an anscestor of v1
        return "back edge";
    } else if (v2->distance < v2->f && v2->f < v1->distance && v1->distance < v1->f) { //cross edge, neither node is an ancestor or descendant to the other
        return "cross edge";
    }
    return "no edge";
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
    vector<Vertex*> A;
    Vertex* s = get(k);
    A.push_back(s);

    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = false;
        vertices[i].distance = -1;
        vertices[i].pi = K();
    }
    
    s->color = true;
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
            if (v->color == false){
                v->color = true; // 1 for gray 
                v->distance = u->distance + 1;
                v->pi = u->key;
                Q.push(v->key);
                A.push_back(v);
            }
        }
    }

    for(int i = 0; i < A.size()-1; i++){
        if(A[i]->distance != A[i+1]->distance){
            cout << A[i]->key << endl;
        }else{
            cout << A[i]->key << " ";
        }
    }
    cout << A[A.size()-1]->key;

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
        vertices[i].color = false;
        vertices[i].pi = K();
    }
    int time = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].color == false){
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
void Graph<D, K>::dfs_visit(Vertex* v, int &t)
{
    t++;
    v->distance = t;
    v->color = true;
    for(int j = 0; j < (adjList[v->key]).size(); j++){
        Vertex* x = get(adjList[v->key][j]);
        if (x->color == false){
            x->pi = v->key;
            dfs_visit(x, t);
        }
    }
    t++;
    v->f = t;
}