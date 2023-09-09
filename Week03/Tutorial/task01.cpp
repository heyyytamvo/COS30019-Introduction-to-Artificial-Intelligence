#include <iostream>

using namespace std;


//An appropriate data structure for representing a state
class State{
    public:
    int jug3;
    int jug5;
    State(int _jug3, int _jug5){
        jug3 = _jug3;
        jug5 = _jug5;
    }
};

// initial state
State initialState = State(0,0);

//Goal State
State Goal0 = State(1,0);
State Goal1 = State(0,1);

int main(){
    cout << initialState.jug3;
    return 0;
}

