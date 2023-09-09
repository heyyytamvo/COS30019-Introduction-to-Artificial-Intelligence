//
//  Map.cpp
//  Assignment1
//
//  Created by Tam Vo on 15/06/2023.
//
#ifndef DFS_H
#define DFS_H

#include <iostream>
#include "Position.h"
#include "Map.h"
#include <vector>
#include <stack>
using namespace std;

class DFS{
    private:
    //declare the path to the target 2D Array
    vector< vector< pair<int, int> > > path;

    //fucntion that check the valid move of the cell
    bool validMove(int newX, int newY, int width, int height){
        return (newX >= 0 && newX < height && newY >= 0 && newY < width);
    }

    public:
    //construction
    DFS(){

    }

    void DepthFirstSearch(Map myMap){
        //getting necessary information
        int width = myMap.getWidth();
        int height = myMap.getHeight();
        Position source = myMap.getSource();



        //initialize the visited cell list
        vector< vector<bool> > visited = vector< vector<bool> >(height, vector<bool>(width, false));
        
        /// intialize the path list 2D Array
        path = vector< vector< pair<int, int> > >(height, vector< pair<int, int> >(width, make_pair(-1, -1)));

        //initialize the frontier, using stack
        stack<Position> frontier;
        frontier.push(source);

        //processing the DFS algorithm
        while (frontier.empty() == false){
            Position currentCell = frontier.top();
            visited[currentCell.row][currentCell.col] = true;
            frontier.pop();

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
        /// if source and destination are the same
        if (source.row == goal.row && source.col == goal.col){
            cout << "Source and Goal are the same" << endl;
            return;
        }

        /// in case the path could not be found
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

            cout << "DFS Algorithm" << endl;
            for (int i = solution.size() - 1; i >= 0; i--){
                cout << "(" << solution[i].row << ", " << solution[i].col << ") ";
            }
        }
    }
};

#endif