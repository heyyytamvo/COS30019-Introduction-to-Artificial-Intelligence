#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std; 


int vertices,edges;
vector<int> adj[1000];
bool visited[1000];
int path[1000];

void input(){
    memset(visited, false, sizeof(visited));
    memset(path, -1, sizeof(path));

    cin >> vertices >> edges;

    for (int i = 0; i < edges; i++){
        int n, m;
        cin >> n >> m;

        adj[n].push_back(m);
        adj[m].push_back(n);
    }
}

void DFS(int startingPoint){
    stack<int> waitingStack;
    waitingStack.push(startingPoint);
    visited[startingPoint] = true;
    
    cout << "Checked order: ";
    while (!waitingStack.empty()){
        int value = waitingStack.top();
        waitingStack.pop();
        cout << value << " ";
        for (int vertex : adj[value]){
            if (visited[vertex] == false){
                waitingStack.push(vertex);
                visited[vertex] = true;
                path[vertex] = value;
            }
            
        }
    }

    cout << endl;
}

void printPath(int start, int end){
    int result[100];
    int index = 0;

    
    if (start == end){
        cout << start;
        return;
    }

    if (path[end] == -1){
        cout << "No path";
        return;
    }

    while (true){
        result[index] = end;
        end = path[end];
        index++;
        
        if (end == start){
            result[index] = end;
            break;
        } 
    }

    cout << "Path is :";
    for (int i = index; i >= 0; i--){
        cout << result[i] << " ";
    }
}


int main(){
    input();
    DFS(0);
    printPath(0, 5);
}