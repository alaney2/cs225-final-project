#include "Graph.cpp"

int main(){
    Graph g = Graph("test.txt");
    string root = g.getRoot();
    cout << "root " << root << endl;
    vector<string> n = g.getNeighbor(root);
    for(auto i : n){
        cout << i<< " || ";
    }
    cout << endl;
    string search;
    
    cout << "Enter new url: "<<endl;
    while (true){
        cin >> search;
        vector<string> n2 = g.getNeighbor(search);
        for(auto i : n2){
            cout << i<< " || ";
        }
        cout << endl;
        cout << "Enter new url or enter 'done'"<<endl;
    }
    return 1;

}