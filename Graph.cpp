#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Graph{
    public:
    Graph(string filename){
        string line;
        ifstream file(filename);
        string url = "";
        if (file.is_open()){
            while ( getline (file,line) ){
                Node* node = new Node;
                int counter = 1;
                bool flag = 1;
                for(char &c : line){
                    if(c == ' ' && counter == 1){   //base url
                        url.pop_back();
                        node->url_ = url;
                        url = "";
                        counter --;
                        if(flag){
                            basenode = node;
                        }
                    }
                    else if( c == ' '){
                        url.pop_back();
                        node->neighbors_.push_back(url);
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
    void printGraph(){
        queue<Node*> nei;

    }
    
    private:
        struct Node{
            string url_;
            vector<Node*> neighbors_;
        };
        Node* basenode;
};