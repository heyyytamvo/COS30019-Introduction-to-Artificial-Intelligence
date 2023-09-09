#include <iostream>
#include <vector>
using namespace std;

class Map{
    private:
    vector< vector<char> > map;
    int width;
    int height;

    public:
    Map(int _row, int _col){
        map = vector< _row, vector<char> >(_col, vector<char>(_row, '_'));
        width = col;
        height = row;
    }

    void printMap(){
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                cout << map[i][j] << ' ';
            }
            cout << endl;
        }

    }
};

int main(){
    Map myMap = Map(3, 5);
    myMap.printMap();

    return 0;
}