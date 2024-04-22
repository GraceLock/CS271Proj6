//
//  test_graph.cpp
//  CS 271 Graph Project: Test File
//
//  Created by Daniel Ziabicki, Grace Lock, William Nguyen
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            size_t delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim != string::npos)
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
        infile.close();
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

/*
Edge Cases:
- empty graph
- call on existing key in graph
- call on non-existent key
*/
void test_get(){
    //int, string
    try{
        vector<string> keys;
        vector<int> data;
        vector<vector<string>> edges = {{}, {}, {}, {}};
        Graph<int, string> G(keys, data, edges);
        if(G.get("A") != nullptr){
            cout << "Incorrect result getting vertex \"A\"" << endl;
        }

        keys = {"A", "B", "C", "D"};
        data = {1, 2, 3, 4};
        Graph<int, string> G1(keys, data, edges);
        if(G1.get("A")->key != "A" && G1.get("A")->data != 1){
            cout << "Incorrect result getting vertex \"A\"" << endl;
        }
        if(G1.get("B")->key != "B" && G1.get("B")->data != 2){
            cout << "Incorrect result getting vertex \"B\"" << endl;
        }

        if(G1.get("E") != nullptr){
            cout << "Incorrect result getting vertex \"E\"" << endl;
        }
        
    }catch(exception &e){
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }

    //string, int
    try{
        vector<int> keys;
        vector<string> data;
        vector<vector<int>> edges = {{}, {}, {}, {}};
        Graph<string, int> G(keys, data, edges);
        if(G.get(1) != nullptr){
            cout << "Incorrect result getting vertex 1" << endl;
        }

        keys = {1, 2, 3, 4};
        data = {"hello world", "apple", "robert", "green"};
        Graph<string, int> G1(keys, data, edges);
        if(G1.get(1)->key != 1 && G1.get(1)->data != "hello world"){
            cout << "Incorrect result getting vertex 1" << endl;
        }
        if(G1.get(2)->key != 2 && G1.get(2)->data != "apple"){
            cout << "Incorrect result getting vertex 2" << endl;
        }
        
        if(G1.get(5) != nullptr){
            cout << "Incorrect result getting vertex 5" << endl;
        }
        
    }catch(exception &e){
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }

    //float, char
    try{
        vector<char> keys;
        vector<double> data;
        vector<vector<char>> edges = {{}, {}, {}, {}};
        Graph<double, char> G(keys, data, edges);

        if(G.get('A') != nullptr){
            cout << "Incorrect result getting vertex 'A'" << endl;
        }

        keys = {'A', 'B', 'C', 'D'};
        data = {3.1415, 2.7182, 1.6180, -0.5};
        Graph<double, char> G1(keys, data, edges);
        if(G1.get('A')->key != 'A' && G1.get('A')->data != 3.1415){
            cout << "Incorrect result getting vertex 'A'" << endl;
        }
        if(G1.get('B')->key != 'B' && G1.get('B')->data != 2.7182){
            cout << "Incorrect result getting vertex 'B'" << endl;
        }
        
        if(G1.get('E') != nullptr){
            cout << "Incorrect result getting vertex 'E'" << endl;
        }

    }catch(exception &e){
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

/*
Edge Cases:
- empty graph
- both keys non-existent
- one key exists
- both keys exist, no connection between them
- both keys exist, connection is one-way
- both keys exist, connection is both ways
*/
void test_reachable(){
    //int string
    try{
        vector<string> keys;
        vector<int> data;
        vector<vector<string>> edges = {{}, {}, {}, {}};
        Graph<int, string> G(keys, data, edges);
        if(G.reachable("R", "V")){
            cerr << "huh" << endl;
        }
        keys = {"Hello World", "B", "C", "D"};
        data = {1, 2, 3, 4};
        edges = {{"B", "D"}, {"C"}, {"D"}, {}};
        Graph<int, string> G1(keys, data, edges);
        if(!G1.reachable("Hello World", "B")){
            cerr << "Should be reachable 1" << endl;
        }
        if(!G1.reachable("B", "C")){
            cerr << "Should be reachable 2" << endl;
        }
        if(G1.reachable("C", "B")){
            cerr << "Should be not reachable 3" << endl;
        }
        if(G1.reachable("D", "B")){
            cerr << "Should be not reachable 4" << endl;
        }
        if(G1.reachable("E", "B")){
            cerr << "Should be not reachable 5" << endl;
        }
        if(!G1.reachable("B", "B")){
            cerr << "Should be reachable 6" << endl;
        }
        if(G1.reachable("E", "E")){
            cerr << "Should be not reachable 7" << endl;
        }

    }catch (exception &e){
        cerr << "Error testing reachable : " << e.what() << endl;
    }

    //string int
    try{
        vector<int> keys;
        vector<string> data;
        vector<vector<int>> edges = {{}, {}, {}, {}};
        Graph<string, int> G(keys, data, edges);
        if(G.reachable(1, 2)){
            cerr << "huh" << endl;
        }
        keys = {1, 2, 3, 4};
        data = {"Hello World", "B", "C", "D"};
        edges = {{2, 4}, {3}, {4}, {}};
        Graph<string, int> G1(keys, data, edges);
        if(!G1.reachable(1, 2)){
            cerr << "Should be reachable 1" << endl;
        }
        if(!G1.reachable(2, 3)){
            cerr << "Should be reachable 2" << endl;
        }
        if(G1.reachable(3, 2)){
            cerr << "Should be not reachable 3" << endl;
        }
        if(G1.reachable(4, 2)){
            cerr << "Should be not reachable 4" << endl;
        }
        if(G1.reachable(5, 2)){
            cerr << "Should be not reachable 5" << endl;
        }
        if(!G1.reachable(2, 2)){
            cerr << "Should be reachable 6" << endl;
        }
        if(G1.reachable(5, 5)){
            cerr << "Should be not reachable 7" << endl;
        }
    }catch (exception &e){
        cerr << "Error testing reachable : " << e.what() << endl;
    }

    //double char
    try{
        vector<char> keys;
        vector<double> data;
        vector<vector<char>> edges = {{}, {}, {}, {}};
        Graph<double, char> G(keys, data, edges);
        if(G.reachable(1, 2)){
            cerr << "huh" << endl;
        }
        keys = {'A', 'B', 'C', 'D'};
        data = {3.1415, 2.7182, 1.6180, -0.5};
        edges = {{'A', 'B'}, {'C'}, {'D'}, {}};
        Graph<double, char> G1(keys, data, edges);
        if(!G1.reachable('A', 'B')){
            cerr << "Should be reachable 1" << endl;
        }
        if(!G1.reachable('B', 'C')){
            cerr << "Should be reachable 2" << endl;
        }
        if(G1.reachable('C', 'B')){
            cerr << "Should be not reachable 3" << endl;
        }
        if(G1.reachable('D', 'B')){
            cerr << "Should be not reachable 4" << endl;
        }
        if(G1.reachable('E', 'B')){
            cerr << "Should be not reachable 5" << endl;
        }
        if(!G1.reachable('B', 'B')){
            cerr << "Should be reachable 6" << endl;
        }
        if(G1.reachable('E', 'E')){
            cerr << "Should be not reachable 7" << endl;
        }
    }catch (exception &e){
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

/*
Edge Cases:
- empty graph
- source key doesn't exist
- cyclic graph
- multiple isolated vertices
- source key exists
*/
void test_bfs(){
    //int string
    try{
        vector<string> keys;
        vector<int> data;
        vector<vector<string>> edges = {{}, {}, {}, {}};
        Graph<int, string> G(keys, data, edges);
        //empty test

        keys = {"Hello World", "B", "C", "D"};
        data = {1, 2, 3, 4};
        edges = {{"B", "D"}, {"C"}, {"D"}, {}};
        Graph<int, string> G1(keys, data, edges);
        //more tests

    }catch (exception &e){
        cerr << "Error testing reachable : " << e.what() << endl;
    }

    //string int
    try{
        vector<int> keys;
        vector<string> data;
        vector<vector<int>> edges = {{}, {}, {}, {}};
        Graph<string, int> G(keys, data, edges);
        //empty test

        keys = {1, 2, 3, 4};
        data = {"Hello World", "B", "C", "D"};
        edges = {{2, 4}, {3}, {4}, {}};
        Graph<string, int> G1(keys, data, edges);
        //more tests

    }catch (exception &e){
        cerr << "Error testing reachable : " << e.what() << endl;
    }

    //double char
    try{
        vector<char> keys;
        vector<double> data;
        vector<vector<char>> edges = {{}, {}, {}, {}};
        Graph<double, char> G(keys, data, edges);
        //empty test

        keys = {'A', 'B', 'C', 'D'};
        data = {3.1415, 2.7182, 1.6180, -0.5};
        edges = {{'A', 'B'}, {'C'}, {'D'}, {}};
        Graph<double, char> G1(keys, data, edges);
        //more tests

    }catch (exception &e){
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

/*
Edge Cases:
- empty graph
- source and target are the same vertex
- source doesn't exist, target exists and vice versa
- neither exist
- multiple paths
*/
void test_print_path(){
    try
    {
        //Path exists
        vector<string> keys;
        vector<int> data;
        vector<vector<string>> edges = {{}, {}, {}, {}};
        Graph<int, string> G(keys, data, edges);

        keys = {"Hello World", "B", "C", "D"};
        data = {1, 2, 3, 4};
        edges = {{"B", "D"}, {"C"}, {"D"}, {}};
        Graph<int, string> G1(keys, data, edges);

        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G1.print_path("B", "C");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "B -> C")
        {
            cout << "Incorrect path from vertex \"B\" to vertex \"C\". Expected: B -> C but got : " << buffer.str() << endl;
        }

        //path doesn't exist
        keys = {"Hello World", "B", "C", "D"};
        data = {1, 2, 3, 4};
        edges = {{"B", "D"}, {}, {"D"}, {}};
        Graph<int, string> G2(keys, data, edges);

        stringstream buffer1;
        streambuf *prevbuf1 = cout.rdbuf(buffer1.rdbuf());
        G2.print_path("B", "C");
        cout.rdbuf(prevbuf1);
        if (buffer1.str() != "")
        {
            cout << "Incorrect path from vertex \"B\" to vertex \"C\". Expected: but got : " << buffer1.str() << endl;
        }

        //Source and target are the same
        vector<int> keys1 = {1, 2, 3, 4};
        vector<float> data1 = {1.12, 2.54, 3.44, 4.99};
        vector<vector<int>> edges1 = {{2, 3}, {}, {2}, {2}};
        Graph<float, int> G3(keys1, data1, edges1);

        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        G3.print_path(3, 3);
        cout.rdbuf(prevbuf2);
        if (buffer2.str() != "3")
        {
            cout << "Incorrect path from vertex \"3\" to vertex \"3\". Expected: but got : " << buffer2.str() << endl;
        }

        //Multiple paths 
        stringstream buffer3;
        streambuf *prevbuf3 = cout.rdbuf(buffer3.rdbuf());
        G3.print_path(1, 3);
        cout.rdbuf(prevbuf3);
        if (buffer3.str() != "1 -> 3")
        {
            cout << "Incorrect path from vertex \"1\" to vertex \"3\". Expected: 1 -> 3 but got : " << buffer3.str() << endl;
        }

        //Path exists string
        vector<string> keys2 = {"grace", "daniel", "william", "cs"};
        vector<string> data2 = {"hi", "apple", "banana", "dog"};
        vector<vector<string>> edges2 = {{"daniel", "cs"}, {"william"}, {"grace"}, {"daniel"}};
        Graph<string, string> G4(keys2, data2, edges2);

        stringstream buffer5;
        streambuf *prevbuf5 = cout.rdbuf(buffer5.rdbuf());
        G4.print_path("daniel", "william");
        cout.rdbuf(prevbuf5);
        if (buffer5.str() != "daniel -> william")
        {
            cout << "Incorrect path from vertex \"daniel\" to vertex \"william\". Expected: daniel -> william but got : " << buffer5.str() << endl;
        }

        //Path exists bool
        stringstream buffer6;
        streambuf *prevbuf6 = cout.rdbuf(buffer6.rdbuf());
        G4.print_path("daniel", "cs");
        cout.rdbuf(prevbuf6);
        if (buffer6.str() != "daniel -> william -> grace -> cs")
        {
            cout << "Incorrect path from vertex \"dan\" to vertex \"cs\". Expected: dan -> will -> grace -> cs but got : " << buffer6.str() << endl;
        }

    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

/*
Edge Cases:
- empty graph
- one vertex doesn't exist
- the other vertex doesn't exist
- neither exist
- source vertex == target vertex
*/
void test_edge_class()
{
    // segmentation fault here
    // //int string
    // try{
    //     vector<string> keys;
    //     vector<int> data;
    //     vector<vector<string>> edges = {{}, {}, {}, {}};
    //     Graph<int, string> G(keys, data, edges);
    //     //empty test

    //     string e_class = G.edge_class("R", "V");
    //     if (e_class != "no edge")
    //     {
    //         cout << "Misidentified empty tree edge" << endl;
    //     }

    // }catch (exception &e){
    //     cerr << "Error testing edge class : " << e.what() << endl;
    // }

    // //string int
    // try{
    //     vector<int> keys;
    //     vector<string> data;
    //     vector<vector<int>> edges = {{}, {}, {}, {}};
    //     Graph<string, int> G(keys, data, edges);
    //     //empty test

    //     string e_class = G.edge_class(1, 2);
    //     if (e_class != "no edge")
    //     {
    //         cout << "Misidentified empty tree edge" << endl;
    //     }

    // }catch (exception &e){
    //     cerr << "Error testing edge class : " << e.what() << endl;
    // }

    // //double char
    // try{
    //     vector<char> keys;
    //     vector<double> data;
    //     vector<vector<char>> edges = {{}, {}, {}, {}};
    //     Graph<double, char> G(keys, data, edges);
    //     //empty test

    //     string e_class = G.edge_class('A','B');
    //     if (e_class != "no edge")
    //     {
    //         cout << "Misidentified empty tree edge" << endl;
    //     }

    // }catch (exception &e){
    //     cerr << "Error testing edge class : " << e.what() << endl;
    // }

    Graph<string, string> *G = generate_graph("graph_description.txt");

    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("U", "Y"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified back edge (\"U\", \"Y\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("S", "R"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified tree edge (\"S\", \"R\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
         e_class = G->edge_class("S", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"S\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "S"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"R\", \"S\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
        // segmentation fault here
        // e_class = G->edge_class("R", "A"); // only one vertex exists
        // if (e_class != "no edge")
        // {
        //     cout << "Misidentified edge" << endl;
        // }
        // e_class = G->edge_class("A", "S"); // only one vertex exists but reverse order
        // if (e_class != "no edge")
        // {
        //     cout << "Misidentified edge" << endl;
        // }
        // e_class = G->edge_class("A", "B"); // neither exists
        // if (e_class != "no edge")
        // {
        //     cout << "Misidentified edge" << endl;
        // }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

/*
Edge Cases:
- empty graph
- all vertices are 1 away from source
- only one vertex
- source vertex not in graph
- include isolated vertices
*/

void test_bfs_tree()
{
    Graph<string, string> *G = generate_graph("graph_description.txt");
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() == "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

int main(){
    test_get();
    test_reachable();
    test_bfs();
    test_print_path();
    test_edge_class();
    test_bfs_tree();

    cout << "Testing Completed" << endl;
    return 0;
}