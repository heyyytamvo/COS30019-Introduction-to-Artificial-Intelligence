#include <iostream>
#include "dog.cpp"

using namespace std;

int main(){
    Dog myDog = Dog("KIKI");
    cout << "His name is: " << myDog.getName() << endl;

    return 0;
}