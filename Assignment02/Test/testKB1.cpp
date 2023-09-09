#include <iostream>

using namespace std;

bool conjunctionOperation(bool p, bool q){
    return (p * q);
}

int main(){
    for (int a = 0; a < 2; a++){
        for (int b = 0; b < 2; b++){
            for (int c = 0; c < 2; c++){
                bool statement1 = a;
                bool statement2 = conjunctionOperation(b, c);

                if (statement1 && statement2){
                    if (!b){
                        cout << "NO";
                        return 0;
                    }
                }
            }
        }
    }

    cout << "Yes" << endl;
    return 0;
}