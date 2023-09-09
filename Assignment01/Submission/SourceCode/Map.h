//
//  Map.cpp
//  Assignment1
//
//  Created by Tam Vo on 15/06/2023.
//

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Position.h"
#include <vector>
using namespace std;


class Map{
    private:
    vector< vector<char> > map;
    int width;
    int height;
    Position source;
    Position destination;
    vector<Position> ObstacleList;
    
    public:
    //construction
    Map(int _height, int _width, Position _source, Position _destination, vector<Position> _obstacleList){
        map = vector< vector<char> >(_height, vector<char>(_width, '_'));
        width = _width;
        height = _height;

        /// Setting source position
        source.row = _source.row;
        source.col = _source.col;
        source.manhattanDistanceToGoal = getManhattan(source, destination);
        source.actualDistanceToThisPosition = 0;

        /// Setting destination, ignore the actual distance from the source to the destination
        destination.row = _destination.row;
        destination.col = _destination.col;
        destination.manhattanDistanceToGoal = 0;

        /// setting obstacle Position, cell that can be visited is '_', cell that is an obstacle/wall is 'X'
        for (int i = 0; i < _obstacleList.size(); i++){
            Position Cell = _obstacleList[i];
            map[Cell.row][Cell.col] = 'X';
        }
    }
    
    //Method get width
    int getWidth(){
        return width;
    }
    
    //Method get height
    int getHeight(){
        return height;
    }
    
    //Method get Source
    Position getSource(){
        return source;
    }

    //Method get Destination
    Position getDestination(){
        return destination;
    }

    //Method get Map
    vector< vector<char> > getMap(){
        return map;
    }  

    //Method return true if the current cell is the wall
    bool isWall(int x, int y){
        return (map[x][y] == 'X');
    }

    //Method print the whole map
    void printMap(){
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }
};
#endif
