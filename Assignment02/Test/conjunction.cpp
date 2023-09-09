#include <iostream>
using namespace std;

bool conjunctionOperation(bool p, bool q){
    return (p * q);
}

int main(){
    cout << conjunctionOperation(true, false);
    return 0;
}