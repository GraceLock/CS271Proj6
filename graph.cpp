//=========================================================================
//  graph.cpp
//  CS 271 Graph Project: Implementation File
//  Created by Daniel Ziabicki, Grace Lock, William Nguyen
//=========================================================================

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include "graph.h"

using namespace std;

//=========================================================================
// Constructor
// Parameters: 
//  keys - vector of keys of the vertices for the graph (of any type)
//  data - vector of data items for the vertices of the graph (of any type), 
//          must be the same number as keys and must be in the same order as keys
//  edges - vector of vectors (same type as keys), representing the adjacency 
//          lists of the vertices in matching order
// Return:	none 
// Preconditions: Keys, data, and edges should be the same length and in matching order
// Postconditions: A graph structure is created with the keys, data, and edges provided
//=========================================================================

template <class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K> > edges)
{

    for (int i = 0; i < keys.size(); ++i) {                                     // Initialize vertices
        Vertex v;
        v.key = keys[i];
        v.data = data[i];
        v.color = false;                                                        // false for white
        v.distance = -1;                                                        // Distance from start vertex
        v.pi = K();                                                             // Parent
        v.f = 0;
        vertices.push_back(v);

        adjList[keys[i]] = edges[i];                                            //intialize adjacency list
    }
}

//=========================================================================
// get
// Parameters: 
//  k - key of the vertex to return a pointer to 
// Return:	
//  a pointer to a vertex in the graph 
// Preconditions: the graph to call get() on exists and k is in the graph 
// Postconditions: if k is in the graph a pointer is returned to the appropriate 
//      vertex, if k is not in the graph nullptr is returned 
//=========================================================================
template <class D, class K>
typename Graph<D, K>::Vertex* Graph<D, K>::get(const K k)
{
    
    for (int i = 0; i < vertices.size(); i++) {                             // Iterate through the vertices to find the vertex with key k
        if (vertices[i].key == k) {
            return &vertices[i];                                            // Return pointer to the found vertex
        }
    }
    return nullptr;                                                         // Return nullptr if vertex with key k not found
}

//=========================================================================
// reachable
// Parameters: 
//  u - key of the vertex to start at 
//  v - key of the vertex to ideally end at 
// Return:	
//  true - if v is reachable from u 
//  false - if v is not reachable from u 
// Preconditions: u and v are in the graph for a meaningful return value 
// Postconditions: true or false is accurately returned based on if 
//  v is reachable in the graph from u 
//=========================================================================

template <class D, class K>
bool Graph<D, K>::reachable(K u, K v)
{
    bfs(u);
    
    Vertex* startVertex = get(u);                                           // Finding the vertices with keys u and v
    Vertex* targetVertex = get(v);

    
    if (startVertex == nullptr || targetVertex == nullptr) {                // If either startVertex or targetVertex is not found, return false
        return false;
    }

    return targetVertex->color == true;                                     // Return true if v is black (reachable), false otherwise 
}

//=========================================================================
// bfs
// Parameters: 
//  k - key of the source vertex to begin the algorithm at 
// Return:	none 
// Preconditions: The key k exists in the graph 
// Postconditions: The algorithm accurately updates the attributes of the vertices
//  in the graph: color, distance, pi
//=========================================================================

template <class D, class K>
void Graph<D, K>::bfs(K k)
{
    Vertex* s = get(k);
    if(s == nullptr){return;}

    // Initialize all vertices' properties
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = false;
        vertices[i].distance = -1;
        vertices[i].pi = K();
    }
    
    s->color = true;                                                        // mark the source vertex as gray (true)
    s->distance = 0;
    s->pi = K();

    queue<K> Q;                                                             // managing the BFS frontier with Queue
    Q.push(s->key);                                                         // enqueue the source vertex
    while(!Q.empty()){
        K a = Q.front();                                                    // get key of queue's front vertex
        Vertex* u = get(a);                                                 // get the vertex with its key from graph
        Q.pop();                                                            // remove the vertex key from the queue
        for(int i = 0; i < adjList[u->key].size(); i++){                    // iterate through all adjacent vertices
            Vertex* v = get(adjList[u->key][i]);                            // get adjacent vertex
            if (v->color == false){                                         // check if the vertex is undiscovered
                v->color = true;                                            // set vertex to gray (discovered)
                v->distance = u->distance + 1;                              // set distance as one more than the predecessor's distance
                v->pi = u->key;                                             // set predecessor to the current vertex key
                Q.push(v->key);                                             // enqueue the adjacent vertex key
            }
        }
    }
}

//=========================================================================
// print_path
// Parameters: 
//  s - key of the start vertex
//  v - key of the end vertex
// Return:	none 
// Preconditions: s and v are existing keys in the graph 
// Postconditions: prints the shortest path in G corresponding
//  to the key u to the vertex in G corresponding to the key v
//=========================================================================

template <class D, class K>
void Graph<D, K>::print_path(K s, K v)
{
    bfs(s);                                                                 // execute BFS from the start vertex to set up paths and distances

    Vertex* x = get(s);                                                     // get start vertex
    Vertex* y = get(v);                                                     // get the end vertex

    if (y->key == x->key)                                                   // check if start and end are the same
        cout << x->key;                                                     // Print start vertex's key
    else if (y->pi == K()){                                                 // check if there's no path to the end vertex
        return;
    }
    else{
        print_path(s, y->pi);                                               // print path from start to the predecessor of the end vertex recursively
        cout << " -> " << y->key;                                           // print the current vertex key forming a path segment
    }
}

//=========================================================================
// edge_class
// Parameters: 
//  u - key of a vertex in the graph 
//  v - key of a vertex in the graph
// Return:	
//  string - the string representation of the edge classification:
//  tree edge, back edge, forward edge, cross edge, or no edge 
// Preconditions: u and v are existing keys in the graph 
// Postconditions: the string representation of the edge classification
//  (tree edge, back edge, forward edge, cross edge, or no edge) of 
//  the edge from vertex u to v
//=========================================================================
template <class D, class K>
string Graph<D, K>::edge_class(K u, K v)
{
    dfs();                                                                                  //constructs a dfs to get edge type of an edge

    Vertex* v1 = get(u);                                                                    //vertices to check the input's edge type
    Vertex* v2 = get(v);

    if((v1 == nullptr || v2 == nullptr) || (v1 == v2)){return "no edge";}

    if (v2->pi == v1->key) {                                                                //tree edge, v2 is a direct descendant of v1
        return "tree edge";
    } else if (v1->distance < v2->distance && v2->distance < v2->f && v2->f < v1->f) {      //forward edge, v2 is a descendant of v1
        return "forward edge";
    } else if (v2->distance <= v1->distance && v1->distance < v1->f && v1->f <= v2->f) {    //back edge, v2 is an anscestor of v1
        return "back edge";
    } else if (v2->distance < v2->f && v2->f < v1->distance && v1->distance < v1->f) {      //cross edge, neither node is an ancestor or descendant to the other
        return "cross edge";
    }
    return "no edge";                                                                       //no such edge exists
}

//=========================================================================
// bfs_tree
// Parameters:
//  k - key of source vertex to begin bfs 
// Return: none
// Preconditions: key k exists in the graph 
// Postconditions: The bfs tree is printed for the source vertex corresponding 
//  to the key s. Vertices in the bfs tree should be represented by their keys. 
//  Each depth level of the tree should be printed on a separate line with each 
//  vertex at the same depth being separated by a single space
//=========================================================================
template <class D, class K>
void Graph<D, K>::bfs_tree(K k)
{
    vector<Vertex*> A;
    Vertex* s = get(k);
    if(s == nullptr){ return; }
    A.push_back(s);


    for(int i = 0; i < vertices.size(); i++){                               // set default values for vertices' attribute
        vertices[i].color = false;
        vertices[i].distance = -1;
        vertices[i].pi = K();
    }
    
    s->color = true;                                                        // mark the source vertex as visited (gray)
    s->distance = 0;
    s->pi = K();

    queue<K> Q;                                                             // manage the BFS frontier with Queue
    Q.push(s->key);
    while(!Q.empty()){
        K a = Q.front();                                                    // get the key of the vertex at the front of the queue
        Vertex* u = get(a);                                                 // retrieve the vertex with its key from graph
        Q.pop();                                                            // remove the vertex key from the queue
        for(int i = 0; i < adjList[u->key].size(); i++){                    // explore all adjacent vertices
            Vertex* v = get(adjList[u->key][i]);                            // get adjacent vertex
            if (v->color == false){
                v->color = true;
                v->distance = u->distance + 1;                              // set distance as one more than the predecessor's distance
                v->pi = u->key;                                             // set predecessor to the current vertex key
                Q.push(v->key);                                             // enqueue the vertex
                A.push_back(v);                                             // add this vertex to the BFS tree array
            }
        }
    }

    for(int i = 0; i < A.size()-1; i++){
        if(A[i]->distance != A[i+1]->distance){
            cout << A[i]->key << endl;                                      // newline represents new distance level
        }else{
            cout << A[i]->key << " ";                                       // print on the same line as on same distance level
        }
    }
    cout << A[A.size()-1]->key;                                             // print the last vertex's key
}

//=========================================================================
// dfs
// Parameters: none 
// Return:	none 
// Preconditions: the graph object exists 
// Postconditions: the attributes of the vertices are appropriately updated 
//  according to the depth first search algorithm
//=========================================================================
template <class D, class K>
void Graph<D, K>::dfs()
{
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = false;
        vertices[i].pi = K();
    }
    int time = 0;                                                           // time variable for tracking discovery and finish times
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].color == false){                                     // check if vertex is undiscovered
            dfs_visit(get(vertices[i].key), time);                          // DFS visit starting from this vertex
        }
    }
}

//=========================================================================
// dfs_visit
// Parameters: 
//  v - pointer to a vertex in the graph 
//  t - time variable 
// Return:	none 
// Preconditions: the vertex at v has not yet been discovered 
// Postconditions: all of the attributes of the vertex v are properly updated
//=========================================================================
template <class D, class K>
void Graph<D, K>::dfs_visit(Vertex* v, int &t)
{
    t++;                                                                    // increment time for discovery
    v->distance = t;                                                        // set discovery time
    v->color = true;
    for(int j = 0; j < (adjList[v->key]).size(); j++){                      // explore all adjacent vertices
        Vertex* x = get(adjList[v->key][j]);
        if (x->color == false){                                             // if the adjacent vertex is unvisited
            x->pi = v->key;                                                 // set predecessor to the current vertex key
            dfs_visit(x, t);                                                // visit the unvisited adjacent vertex recursively
        }
    }
    t++;                                                                    // increment time for finish
    v->f = t;
}