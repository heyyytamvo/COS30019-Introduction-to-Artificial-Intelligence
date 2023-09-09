#include <iostream>
#include <vector>
using namespace std;


class Dog{
    private:
    string name;
    vector<int> haha;

    public:
    Dog(string _name){
        name = _name;
        haha = vector<int>(3, 10);
    }

    //get Name Method
    string getName(){
        return name;
    }

    void print(){
        for (int i = 0; i < 3; i++){
            cout << haha[i] << ' ';
        }
    }
};


int main(){
    Dog myDog("kev");
    myDog.print();
}
