#include <iostream>
using namespace std;

char player = 'O';
char computer = 'X';

struct NextMove{
    int row, col;
};

class Board{
    private:
    char board[3][3];
    public:
    Board(){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                board[i][j] = '_';
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


int minimax(Board board, int depth, bool compTurn){
    int score = board.utility();

    //computer win
    if (score == 1)
        return 1;

    //player win
    if (score == -1)
        return -1;

    //tie case
    if (board.noMoreMove())
        return 0;

    //computer's turn
    if (compTurn){
        int bestValue = -1e6;

        //generate next move
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board.isABlank(i, j)){

                    board.computerFill(i, j);
                    bestValue = max(bestValue, minimax(board, depth+1, !compTurn));
                    board.computerRedo(i, j);
                }

            }
        }

        return bestValue;
    }else{
        int bestValue = 1e6;

        //generate next move
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board.isABlank(i, j)){

                    board.playerFill(i, j);
                    bestValue = min(bestValue, minimax(board, depth+1, !compTurn));
                    board.playerRedo(i, j);
                }
            }
        }
        return bestValue;
    }
}


NextMove bestMove(Board board){
    NextMove result;
    result.col = -1;
    result.row = -1;
    int bestValue = -1e6;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board.isABlank(i, j)){
                board.computerFill(i, j);

                int moveEvalu = minimax(board, 0, false);

                board.computerRedo(i, j); 

                if (moveEvalu > bestValue){
                    bestValue = moveEvalu;
                    result.row = i;
                    result.col = j;
                }
            }
        }
    }

    return result;
}

void GameOrganizer(){
    Board tictac = Board();

    int x, y;
    int result = tictac.endGame();
    // tictac.computerFill(0, 1);
    // tictac.playerFill(1, 1);
    // tictac.computerFill(0, 0);
    // tictac.playerFill(0, 2);
    // tictac.printPuzzle();
    // cout << "-----------" << endl;
    // NextMove next = bestMove(tictac);
    // tictac.computerFill(next.row, next.col);
    tictac.printPuzzle();
    while (!result && !tictac.noMoreMove())
    {
        /* code */
        
        cout << "Your turn: ";
        cin >> x >> y;
        tictac.playerFill(x, y);
        if (tictac.endGame())
            break;
        if (tictac.noMoreMove()){
            cout << "Tie";
            return;
        }
        NextMove next = bestMove(tictac);
        tictac.computerFill(next.row, next.col);
        tictac.printPuzzle();
        
        result = tictac.endGame();
    }

    result = tictac.endGame();
    //cout << result << endl;
    if (result == -1){
        cout << "You Win" << endl;
        return;
    }
        
    if (result == 1){
        cout << "You Lose" << endl;
        return;
    }
        
}




int main(){
    GameOrganizer();
    return 0;
}