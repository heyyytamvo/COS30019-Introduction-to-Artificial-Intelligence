#include <iostream>
#include <vector>
#include <thread>   
#include <chrono>
#include "Position.h"
#include "Map.h"
#include "DFS.h"
#include "BFS.h"
#include "GBFS.h"
#include "AStar.h"
#include "IDS.h"
#include "Input.h"
#include "Clock.h"
using namespace std;


Position Source;
Position Destination;
int width, height;
vector<Position> listOfWalls;


int main(int argc, char* argv[]){

    if (argc < 3) {
        cout << "Invalid command line" << endl;
        cout << "Make sure the options are valid as below:" << endl;
        cout << "./search input.txt BFS/DFS/GBFS/ASTAR" << endl;
        cout << "./search input.txt IDS 8" << endl;
        return 1;
    }

    /// Get input
    Input Input_Agent = Input(argv[1]);
    Input_Agent.readWidthHeight(width, height);
    Input_Agent.readSource(Source);
    Input_Agent.readDestination(Destination);
    Input_Agent.readWalls(listOfWalls);

    /// initialize the map
    Map myMap = Map(height, width, Source, Destination, listOfWalls);
    cout << "Here is the map" << endl;
    myMap.printMap();
    cout << "The Source is (" << myMap.getSource().row << " " << myMap.getSource().col << ")" << endl;
    cout << "The Destination is (" << myMap.getDestination().row << " " << myMap.getDestination().col << ")" << endl;
    
    /// Search choice
    string searchChoice = argv[2];

    if (searchChoice == "BFS" && argc == 3){
        BFS BFS_Agent;
        Clock clock;
        BFS_Agent.BreadthFirstSearch(myMap);
        clock.endClock();
        BFS_Agent.printPath(Source, Destination);
        clock.ExecutingTime();
    }else if (searchChoice == "DFS" && argc == 3){
        DFS DFS_Agent;
        Clock clock;
        DFS_Agent.DepthFirstSearch(myMap);
        clock.endClock();
        DFS_Agent.printPath(Source, Destination);
        clock.ExecutingTime();
    }else if (searchChoice == "GBFS" && argc == 3){
        GBFS GBFS_Agent;
        Clock clock;
        GBFS_Agent.GreedyBestFirstSearch(myMap);
        clock.endClock();
        GBFS_Agent.printPath(Source, Destination);
        clock.ExecutingTime();
    }else if (searchChoice == "ASTAR" && argc == 3){
        ASTAR ASTAR_Agent;
        Clock clock;
        ASTAR_Agent.AStarSearch(myMap);
        clock.endClock();
        ASTAR_Agent.printPath(Source, Destination);
        clock.ExecutingTime();
    }else if (searchChoice == "IDS" && argc == 4){
        int iteration = stoi(argv[3]);
        IDS IDS_Agent;
        Clock clock;
        IDS_Agent.printPath(myMap, iteration);
        clock.endClock();
        clock.ExecutingTime();
    }else{
        cout << "Invalid command" << endl;
        cout << "Make sure the options are valid as below:" << endl;
        cout << "./search input.txt BFS/DFS/GBFS/ASTAR" << endl;
        cout << "./search input.txt IDS 8" << endl;
    }


    return 0;
}