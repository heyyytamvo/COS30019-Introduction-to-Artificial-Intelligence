#ifndef GBFS_H
#define GBFS_H
#include <iostream>
#include "Map.h"
#include "Position.h"
#include <vector>
#include <queue>
using namespace std;


class GBFS{
    private:
    // Initialize the path to the target
    vector< vector< pair<int, int> > > path;
    
    /// Building priority queue option based on the idea of Heap data structure ///
    struct optionManhattan {
        bool operator()(const Position& a, const Position& b) const {
            return a.manhattanDistanceToGoal > b.manhattanDistanceToGoal;
        }
    };
    
    //fucntion that check the valid move of the cell
    bool validMove(int newX, int newY, int width, int height){
        return (newX >= 0 && newX < height && newY >= 0 && newY < width);
    }

    public:
    //construction
    GBFS(){

    }

    void GreedyBestFirstSearch(Map myMap){

        /// declare the built-in priority queue
        priority_queue< Position, vector<Position>, optionManhattan > frontier;

        /// getting necessary information
        int width = myMap.getWidth();
        int height = myMap.getHeight();
        Position source = myMap.getSource();
        Position destination = myMap.getDestination();

        //initialize the visited list 2D Array
        vector< vector<bool> > visited = vector< vector<bool> >(height, vector<bool>(width, false));

        // initialize the path list 2D Array
        path = vector< vector< pair<int, int> > >(height, vector< pair<int, int> >(width, make_pair(-1, -1)));

        /// Processing the GBFS algorithm
        frontier.push(source);

        while (frontier.empty() == false){
            Position currentCell = frontier.top();
            frontier.pop();
            visited[currentCell.row][currentCell.col] = true;
            /// find the target, then quit the loop
            if (currentCell.col == destination.col && currentCell.row == destination.row){
                break;
            };

            /// visiting all neighbour cell
            for (int i = 0; i < 4; i++){
                int newCellX = currentCell.row + vectorX[i];
                int newCellY = currentCell.col + vectorY[i];

                //if that is a valid move, then continue checking
                if (validMove(newCellX, newCellY, width, height)){
                    // make sure that the cell is not the wall
                    if (myMap.isWall(newCellX, newCellY) == false){
                        //if that have not visited, then push it to the frontier
                        if (!visited[newCellX][newCellY]){
                            Position newCell;
                            newCell.row = newCellX;
                            newCell.col = newCellY;
                            /// calculate the manhattan distance from this cell to the goal
                            newCell.manhattanDistanceToGoal = getManhattan(newCell, destination);
                            path[newCellX][newCellY] = make_pair(currentCell.row, currentCell.col);
                            frontier.push(newCell);
                        }
                    }
                }
            }
        }
    }

    //print path
    void printPath(Position source, Position goal){
        /// Case source and goal are the same
        if (source.row == goal.row && source.col == goal.col){
            cout << "Source and Goal are the same" << endl;
            return;
        }

        /// Case can not find the path
        if (path[goal.row][goal.col].first == -1){
            cout << "There are no path" << endl;
        }else{
            vector<Position> solution;
            int tempX = goal.row;
            int tempY = goal.col;
            int temp_x;
            int temp_y;
            while (tempX != -1 && tempY != -1){
                Position currentCell;
                currentCell.row = tempX;
                currentCell.col = tempY;

                solution.push_back(currentCell);
                temp_x = path[tempX][tempY].first;
                temp_y = path[tempX][tempY].second;
                tempX = temp_x;
                tempY = temp_y;
            }   

            cout << "GBFS Algorithm" << endl;
            for (int i = solution.size() - 1; i >= 0; i--){
                cout << "(" << solution[i].row << ", " << solution[i].col << ") ";
            }
        }
    }  
};
#endif