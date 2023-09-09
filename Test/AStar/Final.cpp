#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <thread>   
#include <chrono>
#include <map>
using namespace std;

const int CorrectPosition[3][3] = { {1, 2, 3}, 
                                    {4, 5, 6}, 
                                    {7, 8, 0}};
map< int, pair<int, int> > manhattanList;
const int vectorX[4] = {-1, 0, 1, 0};
const int vectorY[4] = {0, 1, 0, -1};

unordered_map<string, string> StateExist;
struct Position
{
    /* data */
    int XPosi;
    int YPosi;
};


class State {
public:
    int Puzzle2D[3][3];
    bool isGoal;
    Position blank_space;
    int missingTiles;
    int manhattanNum;
    string key;

    State(int _puzzle[3][3]) {
        missingTiles = 0;
        manhattanNum = 0;
        key = "";

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                Puzzle2D[i][j] = _puzzle[i][j];
                if (Puzzle2D[i][j] == 0){
                    blank_space.XPosi = i;
                    blank_space.YPosi = j;
                }


                //calculate missing tiles
                if (_puzzle[i][j] != CorrectPosition[i][j]){
                    missingTiles += 1;
                }

                //calculate manhattan
                manhattanNum += abs(i - manhattanList[Puzzle2D[i][j]].first) + abs(j - manhattanList[Puzzle2D[i][j]].second);

                key += to_string(_puzzle[i][j]);
            }
        }

        
        if (missingTiles == 0){
            isGoal = true;
        }else{
            isGoal = false;
        }
    }
};


/// Building priority queue ///
struct optionMissingTiles {
    bool operator()(
        State const& a,
        State const& b)
        const 
    {
        return a.missingTiles > b.missingTiles;
    }
};

struct optionManhattan {
    bool operator()(
        State const& a,
        State const& b)
        const 
    {
        return a.manhattanNum > b.manhattanNum;
    }
};

priority_queue< State, vector<State>, optionManhattan > pq; 


//---------------AGENT FUNCTION
State input(){
    int source[3][3];
    int index = 1;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cin >> source[i][j];
            if (index == 9){
                manhattanList.insert(make_pair(0, make_pair(i, j)));
            }else{
                manhattanList.insert(make_pair(index, make_pair(i, j)));
            }
            index++;
        }
    }

    State result(source);

    return result;
}

///////NEED TO BE MODIFIED
bool validMove(int newX, int newY){
    return ((0 <= newX) && (newX < 3) && (0 <= newY) && (newY < 3));
}

string newState(State _currentState, int newX, int NewY){
    int temp[3][3];

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            temp[i][j] = _currentState.Puzzle2D[i][j];
        }
    }

    //Swap
    int targetValue = temp[newX][NewY];
    temp[newX][NewY] = 0;
    temp[_currentState.blank_space.XPosi][_currentState.blank_space.YPosi] = targetValue;

    string key = "";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            key += to_string(temp[i][j]);
        }
    }

    return key;
}

string AStarPuzzle(State orginalState){
    pq.push(orginalState);
    int indexState = 1;

    StateExist[orginalState.key] = "DONE";
    while (pq.empty() == false){
        State current = pq.top();
        pq.pop();

        //current.printPuzzle();
        //cout << "----------" << endl;
        
        //cout << "Current X posi (" << current.blank_space.XPosi << ", " << current.blank_space.YPosi << ")" << endl;

        if (current.isGoal){
            return current.key;
        }

       // std::cout << "Memory used by Exist State vector: " << sizeof(StateExist) + StateExist.size() * sizeof(std::string) << " bytes" << std::endl;

        //neighbour
        for (int i = 0; i < 4; i++){
            int newXPosi = current.blank_space.XPosi + vectorX[i];
            int newYPosi = current.blank_space.YPosi + vectorY[i];

            if (validMove(newXPosi, newYPosi)){
                string newKey = newState(current, newXPosi, newYPosi);
                //cout << "New key generated: " << newKey << endl;
                if (StateExist.count(newKey) == 0){
                    //cout << "New key generated: " << newKey << endl;
                    StateExist[newKey] = current.key;
                    int newPuzzle2D[3][3];
                    int index = 0;
                    for (int j = 0; j < 3; j++){
                        for (int k = 0; k < 3; k++){
                            newPuzzle2D[j][k] = newKey[index] - '0';
                            index++;
                        }
                    }

                    State nextState(newPuzzle2D);
                    pq.push(nextState);
                    indexState++;
                }
            }
        }
        if (indexState > 181440){
            break;
        }
    }
    
    return "Not found";
}

void Agent(){
    State originalState = input();
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    string result = AStarPuzzle(originalState);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    // Calculate the elapsed time in microseconds
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "The Agent need " << duration.count() << "ms to findout the solution\n";

    if (result != "Not found"){
        cout << "Here is the solution:" << endl;
        vector<string> finalSolution;
        
        while (result != "DONE"){
            string step = "";
            for (int i = 0; i < 9; i++){
                char currentChar = result[i];
                if (currentChar == '0'){
                    step += 'x';
                }else{
                    step += currentChar;
                }
            }
            finalSolution.push_back(step);
            result = StateExist[result];
        }

        cout << "There are " << finalSolution.size() << " steps in total" << endl;
        for (int i = finalSolution.size() - 1; i >= 0; i--){
            string current = finalSolution[i];

            for (int j = 0; j < 9; j++){
                cout << current[j] << " ";
                if (j % 3 == 2){
                    cout << endl;
                }
            }
            cout << "-------------------------" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }else{
        cout << "There are no solution" << endl;
    }
    
}

int main(){
    Agent();
    //std::cout << "Memory used by Exist State vector: " << sizeof(StateExist) + StateExist.size() * sizeof(std::string) << " bytes" << std::endl;
    return 0;
}
