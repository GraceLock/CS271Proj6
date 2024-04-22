//
//  test_graph.cpp
//  CS 271 Graph Project: Test File
//
//  Created by Daniel Ziabicki, Grace Lock, William Nguyen
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

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
        
}

/*
Edge Cases:
- empty graph
- one vertex doesn't exist
- the other vertex doesn't exist
- neither exist
- source vertex == target vertex
*/
void test_edge_class(){
}

/*
Edge Cases:
- empty graph
- all vertices are 1 away from source
- only one vertex
- source vertex not in graph
- include isolated vertices
*/
void test_bfs_tree(){

}

int main(){
    test_get();
    test_reachable();

    cout << "Testing Completed" << endl;
    return 0;
}