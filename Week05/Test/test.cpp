#include <iostream>
#include <vector>
#define MAX 9

using namespace std;
char player = 'O';
char computer = 'X';

class Board{
    private:
    char board[3][3];
    public:
    Board(vector< vector<char> > _board){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                board[i][j] = _board[i][j];
            }
        }
    }

    bool isABlank(int i, int j){
        if (board[i][j] == '_')
            return true;
        return false;
    }

    void playerFill(int i, int j){
        board[i][j] = player;
    }

    void playerRedo(int i, int j){
        board[i][j] = '_';
    }

    void computerFill(int i, int j){
        board[i][j] = computer;
    }

    void computerRedo(int i, int j){
        board[i][j] = '_';
    }

    //return -1 if computer win, 1 if player win
    int utility(){
        // check row
        for (int row = 0; row < 3; row++){
            if (board[row][0] == board[row][1] && board[row][0] == board[row][2]){
                if (board[row][0] == player)
                    return -1;
                else if (board[row][0] == computer)
                    return 1;
            }
        }

        // check collumn
        for (int col = 0; col < 3; col++){
            if (board[0][col] == board[1][col] && board[0][col] == board[2][col]){
                if (board[0][col] == player)
                    return -1;
                else if (board[0][col] == computer)
                    return 1;
            }
        }

        //checking diagonal
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){
            if (board[0][0] == player)
                return -1;
            else if (board[0][0] == computer)
                return 1;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
            if (board[0][2] == player)
                return -1;
            else if (board[0][2] == computer)
                return 1;
        }

        //if no one wins, return 0;
        return 0;
    }


    //checking move left
    bool noMoreMove(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[i][j] == '_')
                    return false;
            }
        }

        return true;
    }

    int endGame(){
        int result = utility();
        if (result == 1)
            return 1;
        else if (result == -1)
            return -1;

        return 0;
    }

    void printPuzzle(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
    }

};

/////////////////////////////////////////////////

vector< vector<char> > to2DVector(string state){
    vector< vector<char> > matrix(3, vector<char>(3,'_'));
    int index = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matrix[i][j] = state[index];
            index++;
        }
    }
    return matrix;
}

string ToString(vector< vector<char> > state){
    string result = "";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            result += state[i][j];
        }
    }
    return result;
}

//////////////////////////////////////////
struct Node {
    string current;
    vector<Node*> listOfChild;
    int num;
};

Node* newNode(string stringState) {
    Node* node = new Node();
    node->current = stringState;

    for (int i = 0; i < 9; i++){
        node->listOfChild.push_back(NULL);
    }
    return node;
}


int main(){
    return 0;
}
