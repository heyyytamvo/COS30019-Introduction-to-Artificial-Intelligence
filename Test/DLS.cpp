#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#define NUMBER_VERTCES 11
#define NUMBER_EDGES 10
using namespace std;


class Node{
    private:
    int level;
    int vertex;
    
    public:
    Node(int _level, int _vertex){
        level = _level;
        vertex = _vertex;
    }
    int getLevel(){
        return level;
    }
    int getVertex(){
        return vertex;
    }
};

int graph[NUMBER_VERTCES][NUMBER_VERTCES];
int visited[NUMBER_VERTCES];
int path[NUMBER_VERTCES];
int sourceVertex, targetVertex;

void getInput(){
    cout << "\t\t\tGraphs\n";
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    memset(path, -1, sizeof(path));

    cout << "Please input all vertices, the format is x1 x2:" << endl;
    for (int i = 0; i < NUMBER_EDGES; i++){
        int x1, x2;
        cin >> x1 >> x2;
        graph[x1][x2] = 1;
        graph[x2][x1] = 1;
    }

    cout << "Please input the source vertex: ";
    cin >> sourceVertex;
    cout << endl << "Please input the target vertex: ";
    cin >> targetVertex;
    cout << endl;
}

void DLS(int limit, int source, int target){
    stack<Node> frontier;
    Node StartNode = Node(0, source);
    frontier.push(StartNode);

    while (!frontier.empty()){
        Node currentNode = frontier.top();
        frontier.pop();
        int currentVertex = currentNode.getVertex();
        int currentLevel = currentNode.getLevel();
        visited[currentVertex] = true;
        for (int j = 0; j < NUMBER_VERTCES; j++){
            if (graph[currentVertex][j] == 1 && visited[j] == false){
                if (currentLevel + 1 < limit){
                    Node newNode = Node(currentLevel + 1, j);
                    path[j] = currentVertex;
                    frontier.push(newNode);
                }
            }
        }
    }
}

void printPath(){
    if (path[targetVertex] == -1){
        cout << "No path" << endl;
        return;
    }else{
        vector<int> solution;
        int &temp = targetVertex; 
        while (temp != sourceVertex){
            solution.push_back(temp);
            temp = path[temp];
        }
        solution.push_back(temp);

        for (int i = solution.size() - 1; i >= 0; i--){
            cout << solution[i] << " ";
        }
        cout << endl;
    }
}

int main(){
    getInput();
    DLS(7, sourceVertex, targetVertex);
    printPath();

    return 0;
}



