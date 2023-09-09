#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#define MAX 4
#define INF 1e3

using namespace std;

struct Posi{
    int coorX;
    int coorY;
};

bool visited[MAX][MAX];
Posi path[MAX][MAX];
int cost[MAX][MAX];
Posi start, goal;
char graph[MAX][MAX];

int newX[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int newY[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

// Evaluation function 1
double EuclideanDistanceFunction(Posi start, Posi goal){
    return sqrt((goal.coorX - start.coorX) * (goal.coorX - start.coorX) + (goal.coorY - start.coorY) * (goal.coorY - start.coorY));
}
//priorityQueue option 1
struct option1 {
    bool operator()(
        Posi const& a,
        Posi const& b)
        const 
    {
        return EuclideanDistanceFunction(a, goal) + cost[a.coorX][a.coorY] > EuclideanDistanceFunction(b, goal) + cost[b.coorX][b.coorY];
    }
};

//valid move checking
bool validMove(Posi newPosi){
    return (newPosi.coorX >= 0 && newPosi.coorX < MAX) && (newPosi.coorY >= 0 && newPosi.coorY < MAX);
}

//init function
void init(){
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            visited[i][j] = false;
            Posi newPosi;
            newPosi.coorX = -1;
            newPosi.coorY = -1;
            path[i][j] = newPosi;
            cost[i][j] = INF;
        }
    }
}

//AstarSearch function 1
void AStarSearch1(){
    priority_queue< Posi, vector<Posi>, option1> pq;
    pq.push(start);
    cost[start.coorX][start.coorY] = 0;

    while (pq.empty() == false){
        Posi currentPoint = pq.top();
        visited[currentPoint.coorX][currentPoint.coorY] = true;
        cout << '(' << currentPoint.coorX << ", " << currentPoint.coorY << ") " << endl;
        pq.pop();

        for (int i = 0; i < 8; i++){
            int newXCoor = currentPoint.coorX + newX[i];
            int newYCoor = currentPoint.coorY + newY[i];

            //reach goal
            if ((newXCoor == goal.coorX) && (newYCoor == goal.coorY)){
                path[newXCoor][newYCoor] = currentPoint;
                cost[newXCoor][newYCoor] = cost[currentPoint.coorX][currentPoint.coorY] + 1;
                return;
            }

            Posi newPosi;
            newPosi.coorX = newXCoor;
            newPosi.coorY = newYCoor;
            if (validMove(newPosi)){
                if (visited[newXCoor][newYCoor] == false && graph[newXCoor][newYCoor] == '.'){
                    path[newXCoor][newYCoor] = currentPoint;
                    cost[newXCoor][newYCoor] = cost[currentPoint.coorX][currentPoint.coorY] + 1;
                    pq.push(newPosi);
                }
            }
        }
    }
    return;
}

void input(){
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            char character;
            cin >> character;

            graph[i][j] = character;
        }
    }

    
    cout << "Please input the coordinate for source: ";
    cin >> start.coorX >> start.coorY;
    cout << endl << "Please input the coordinate for destination: ";
    cin >> goal.coorX >> goal.coorY;
}

void printPath(){
    if (path[goal.coorX][goal.coorY].coorX == -1 && path[goal.coorX][goal.coorY].coorY == -1){
        cout << "No Solution" << endl;
        return;
    }else{
        vector<Posi> Solution;
        Solution.push_back(goal);
        Posi& temp = path[goal.coorX][goal.coorY];

        while (temp.coorX != -1 && temp.coorY != -1){
            Solution.push_back(temp);
            temp = path[temp.coorX][temp.coorY];
        }

        for (int i = Solution.size() - 1; i >= 0; i--){
            Posi current = Solution[i];
            cout << '(' << current.coorX << ", " << current.coorY << ") ";
            
        }
    }
}

void debugPath(){
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            Posi current = path[i][j];
            cout << '(' << current.coorX << ", " << current.coorY << ") ";
        }
        cout << endl;
    }

}

int main(){
    init();
    input();
    AStarSearch1();
    printPath();

    return 0;
}







