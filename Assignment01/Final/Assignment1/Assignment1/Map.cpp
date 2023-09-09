//
//  Map.cpp
//  Assignment1
//
//  Created by Tam Vo on 15/06/2023.
//

#include <stdio.h>
#include <iostream>
#include "Position.cpp"
#include <vector>
using namespace std;

class Map{
    private:
    vector< vector<char> > map;
    int width;
    int height;
    Position source;
    vector<Position> DestinationList;
    
    public:
    //construction
    Map(int _row, int _col, int _sourceX, int _sourceY, vector<Position> _destinationList){
        map = vector< vector<char> >(_row, vector<char>(_col, '_'));
        width = _col;
        height = _row;
        source.row = _sourceX;
        source.col = _sourceY;
        
        for (int i = 0; i < _destinationList.size(); i++){
            DestinationList.push_back(_destinationList[i]);
        }
    }
    
    //Method get width
    int getWidth() const{
        return width;
    }
    
    //Method get height
    int getHeight() const{
        return height;
    }
    
    //Method get DestinationList
    vector<Position> getDestinationList() const{
        return DestinationList;
    }
    
    
        
};
