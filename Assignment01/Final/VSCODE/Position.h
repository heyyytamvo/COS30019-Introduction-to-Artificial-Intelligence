#ifndef POSITION_H
#define POSITION_H

#include <cmath>
const int vectorX[4] = {-1, 0, 1, 0};
const int vectorY[4] = {0, 1, 0, -1};

struct Position{
    int row;
    int col;

    /// These attributes are used for informed search
    int manhattanDistanceToGoal;        /// The manhattan distance from this position to the destination
    int actualDistanceToThisPosition;   /// The actual distance from the source to this position


    /// This attribute is used for Iterative deepening depth-first search
    int level;
};

int getManhattan(Position x, Position y){
    return (abs(x.row - y.row) + abs(x.col - y.col));
}

#endif