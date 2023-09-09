#include <iostream>
#include <vector>

using namespace std;

vector<int> minHeap;

void buildMinHeap(int index){
    int smallest = index;
    int childLeftIndex = index * 2 + 1;
    int childRightIndex = index * 2 + 2;

    if (childLeftIndex < minHeap.size() && minHeap[childLeftIndex] < minHeap[smallest]){
        smallest = childLeftIndex;
    }

    if (childRightIndex < minHeap.size() && minHeap[childRightIndex] < minHeap[smallest]){
        smallest = childRightIndex;
    }

    /*DEBUG
    for (int i = 0; i < minHeap.size(); i++){
        cout << minHeap[i] << " ";
    }*/

    //cout << endl;

    if (smallest != index){
        swap(minHeap[index], minHeap[smallest]);
        buildMinHeap(smallest);
    }
}

void buildMaxHeap(int index){
    int largest = index;
    int childLeftIndex = index * 2 + 1;
    int childRightIndex = index * 2 + 2;

    if (childLeftIndex < minHeap.size() && minHeap[childLeftIndex] > minHeap[largest]){
        largest = childLeftIndex;
    }

    if (childRightIndex < minHeap.size() && minHeap[childRightIndex] > minHeap[largest]){
        largest = childRightIndex;
    }

    /*DEBUG
    for (int i = 0; i < minHeap.size(); i++){
        cout << minHeap[i] << " ";
    }*/

    //cout << endl;

    if (largest != index){
        swap(minHeap[index], minHeap[largest]);
        buildMaxHeap(largest);
    }
}

int main(){
    minHeap.push_back(7);
    minHeap.push_back(12);
    minHeap.push_back(6);
    minHeap.push_back(10);
    minHeap.push_back(17);
    minHeap.push_back(15);
    minHeap.push_back(2);
    minHeap.push_back(4);

    cout << "Current array:" << endl;
    for (int i = 0; i < minHeap.size(); i++){
        cout << minHeap[i] << " ";
    }
    cout << endl;

    for (int i = minHeap.size()/2 - 1; i >= 0; i--){
        buildMinHeap(i);
    }


    cout << "Final is: " << endl;
    for (int i = 0; i < minHeap.size(); i++){
        cout << minHeap[i] << " ";
    }

    return 0;
}