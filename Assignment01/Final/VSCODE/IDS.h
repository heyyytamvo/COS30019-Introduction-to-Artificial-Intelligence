#ifndef IDS_H
#define IDS_H
#include <iostream>
#include "Map.h"
#include "Position.h"
#include "DLS.h"
#include <vector>
#include <queue>
using namespace std;

class IDS{
    private:

    //intialize the path to the target
    vector< vector< pair<int, int> > > path;

    //fucntion that check the valid move of the cell
    bool validMove(int newX, int newY, int width, int height){
        return (newX >= 0 && newX < height && newY >= 0 && newY < width);
    }

    public:
    /// Constructor
    IDS(){

    }

    void printPath(Map myMap, int iteration){
        DLS DLS_Agent;
        int depthOfTheGoal = -1;

        /// find the depth of the destination
        for (int i = 0; i < iteration; i++){
            int temp = DLS_Agent.LimitDepth(myMap, i);
            if (temp != -1){
                depthOfTheGoal = i;
                break;
            }
        }
        
        /// the iteration is not enough to find out the goal
        if (depthOfTheGoal == -1){
            cout << "Cannot find the solution within " << iteration << " iterations, please increase the number" << endl;
            return;
        }else{
            //getting necessary information
            int width = myMap.getWidth();
            int height = myMap.getHeight();
            Position source = myMap.getSource();
            Position destination = myMap.getDestination();

            //initialize the visited cell list 2D Array
            vector< vector<bool> > visited = vector< vector<bool> >(height, vector<bool>(width, false));

            //initialize the path list 2D Array
            path = vector< vector< pair<int, int> > >(height, vector< pair<int, int> >(width, make_pair(-1, -1)));
            
            //initialize the frontier
            stack<Position> frontier;
            
            //intialize the root
            Position root;
            root.row = source.row;
            root.col = source.col;
            root.level = 0;
            frontier.push(root);

            //processing the DLS algorithm
            while (frontier.empty() == false){
                Position currentCell = frontier.top();
                visited[currentCell.row][currentCell.col] = true;
                frontier.pop();

                /// found out the goal, then return the depth of that goal
                if (currentCell.row == destination.row && currentCell.col == destination.col){
                    break;
                }

                //visiting all neighbour cell
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
                                newCell.level = currentCell.level + 1;
                                /// make sure the next cell's depth is still less than the limitation 
                                if (newCell.level <= depthOfTheGoal){
                                    path[newCellX][newCellY] = make_pair(currentCell.row, currentCell.col);
                                    frontier.push(newCell);
                                }
                            }
                        }
                    }
                }
            }

            /// Print the path
            if (source.row == destination.row && source.col == destination.col){
                cout << "Source and Goal are the same" << endl;
                return;
            }

            /// if could not find out the path
            if (path[destination.row][destination.col].first == -1){
                cout << "There are no path" << endl;
            }else{
                vector<Position> solution;
                int tempX = destination.row;
                int tempY = destination.col;
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

                cout << "IDS Algorithm" << endl;
                for (int i = solution.size() - 1; i >= 0; i--){
                    cout << "(" << solution[i].row << ", " << solution[i].col << ") ";
                }
            }

        }
    }
};
#endif