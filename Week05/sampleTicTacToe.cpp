#include <iostream>

using namespace std;
char PLAYER = 'X';
char COMP = 'O';

struct Move{
    int row, col;
};

int State = 1;
// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char _board[3][3]){
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (_board[i][j]=='_')
                return true;
    return false;
}


int evaluate(char _board[3][3]){
    
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++){
        if (_board[row][0]==_board[row][1] && _board[row][1]==_board[row][2]){
            if (_board[row][0] == PLAYER){
                return 10;
            }else if (_board[row][0] == COMP){
                return -10;
            }
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++){
        if (_board[0][col]==_board[1][col] && _board[1][col]==_board[2][col]){
            if (_board[0][col] == PLAYER)
                return 10;
            else if (_board[0][col] == COMP)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if ((_board[0][0] == _board[1][1]) && (_board[2][2] == _board[1][1])){
        if (_board[0][0] == PLAYER)
                return 10;
            else if (_board[0][0] == COMP)
                return -10;
    }

    // Checking for Diagonals for X or O victory.
    if ((_board[0][2] == _board[1][1]) && (_board[2][0] == _board[1][1])){
        if (_board[0][2] == PLAYER)
                return 10;
            else if (_board[0][2] == COMP)
                return -10;
    }

    //return 0 if no one wins
    return 0;
}

int minimax(char _currentState[3][3], int depth, bool MaxTurn){
    int score = evaluate(_currentState);

    // If Maximizer/Player has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer/Comp has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(_currentState)==false)
        return 0;

    // If this maximizer's move
    if (MaxTurn){
        int best = -1e6;

        // travel all cell
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                
                if (_currentState[i][j] == '_'){
                    _currentState[i][j] = PLAYER;
                    //call the minimax recursively
                    best = max(best, minimax(_currentState, depth+1, !MaxTurn));

                    //undo the move
                    _currentState[i][j] = '_';
                }
            }
        }
        return best;
    }else{
        int best = 1e6;
        // travel all cell
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                
                if (_currentState[i][j] == '_'){
                    _currentState[i][j] = COMP;
                    //call the minimax recursively
                    best = min(best, minimax(_currentState, depth+1, !MaxTurn));

                    //undo the move
                    _currentState[i][j] = '_';
                }
            }
        }
        return best;
    }
}


Move findBestMove(char _currentState[3][3]){
    int bestVal = -1e6;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (_currentState[i][j] == '_'){
                // Move 
                _currentState[i][j] = PLAYER;
                //compute the evaluation function for this move
                int moveEvalu = minimax(_currentState, 0, false); 

                //undo
                _currentState[i][j] = '_';


                if (moveEvalu > bestVal){
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveEvalu;
                }
            }
        }
    }

    return bestMove;
}

void printPuzzle(char puzzle[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    char currentState[3][3] = { {'X', 'X', 'O'},
                                {'_', 'O', '_'},
                                {'_', '_', '_'} };

    Move bestMove;
    
    bestMove = findBestMove(currentState);
    currentState[bestMove.row][bestMove.col] = PLAYER;
    printPuzzle(currentState);
        
        
        
        
    

    return 0;    
}