#ifndef DLS_H
#define DLS_H
#include <iostream>
#include "Map.h"
#include "Position.h"
#include <vector>
#include <stack>
using namespace std;

class DLS{

    //fucntion that check the valid move of the cell
    bool validMove(int newX, int newY, int width, int height){
        return (newX >= 0 && newX < height && newY >= 0 && newY < width);
    }

    public:
    //construction
    DLS(){

    }

    int LimitDepth(Map myMap, int limit){
        //getting necessary information
        int width = myMap.getWidth();
        int height = myMap.getHeight();
        Position source = myMap.getSource();
        Position destination = myMap.getDestination();


        //initialize the visited cell list
        vector< vector<bool> > visited = vector< vector<bool> >(height, vector<bool>(width, false));

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
                return limit;
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
                            /// make sure the current depth is still less than the limitation
                            if (newCell.level <= limit){
                                frontier.push(newCell);
                            }
                        }
                    }
                }
            }
        }

        return -1;
    }
};
#endif