#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Graph{
    public:
    Graph(string filename){
        string line;
        ifstream file(filename);
        string url = "";
        bool flag = 1;
        if (file.is_open()){
            while ( getline (file,line) ){
                int counter = 1;
                
                string vertex = "";
                vector<string> neighbors;
                neighbors.clear();
                for(char &c : line){
                    if(c == ' ' && counter == 1){   //vertex url
                        url.pop_back();
                        vertex = url;
                        nodes[vertex] = neighbors;
                        url = "";
                        counter --;
                        if(flag){
                            root = vertex;
                            flag = false;
                        }
                    }
                    else if( c == ' '){ //neighbors url
                        url.pop_back();
                        nodes[vertex].push_back(url);
                        url = "";   
                    }
                    else{
                        url += c;
                    }
                }
            }
            file.close();
        }
        else{
            cout << "Could not open file."<<endl;
        }
    }
    string getRoot(){ return root; }
    vector<string> getNeighbor(string vertex){ return nodes[vertex]; }
    
    private:
        // struct Node{
        //     string url_;
        //     vector<Node*> neighbors_;
        // };
        // Node* basenode_;
        // vector<Node*> vertices_;
        map<string, vector<string>> nodes;
        string root;
        
};