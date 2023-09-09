#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Position.h"

using namespace std;

class Input{
    private:
    string fileName;
    public:
    /// Constructor
    Input(string _filename){
        fileName = _filename;
    }

    /// Function read width and height 
    void readWidthHeight(int &width, int &height){
        ifstream infile(fileName);
        string line;
        // get the first line
        getline(infile, line);
        // create a stringstream from the line
        stringstream ss(line);
        ss >> height >> width;
        infile.close();
    }

    /// Function read source
    void readSource(Position &source){
        ifstream infile(fileName);
        string line;
        // get the second line
        for (int i = 0; i < 2; i++){
            getline(infile, line);
        }
        // create a stringstream from the line
        stringstream ss(line);
        ss >> source.row >> source.col;
        infile.close();
    }

    /// Function read destination
    void readDestination(Position &destination){
        ifstream infile(fileName);
        string line;
        // get the third line
        for (int i = 0; i < 3; i++){
            getline(infile, line);
        }
        // create a stringstream from the line
        stringstream ss(line);
        ss >> destination.row >> destination.col;
        infile.close();
    }

    /// Function read walls
    void readWalls(vector<Position> &wallsList){
        ifstream infile(fileName);
        string line;
        // ignore the first 3 lines
        for (int i = 0; i < 3; i++){
            getline(infile, line);
        }

        // read from the third line
        while (getline(infile, line)) {
            stringstream ss(line);
            int leftX, leftY, width, height;
            ss >> leftX >> leftY >> height >> width;
            int numberOfCells = width * height;
            for (int i = 0; i < numberOfCells; i++){

                for (int j = leftX; j < height + leftX; j++){
                    for (int k = leftY; k < width + leftY; k++){
                        Position wall;
                        wall.row = j; 
                        wall.col = k;
                        wallsList.push_back(wall);
                    }
                }
            }
        }
        infile.close();
    }
};
#endif