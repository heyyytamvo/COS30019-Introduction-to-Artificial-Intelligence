#include <iostream>
using namespace std;

bool biconditionalOperation(bool p, bool q){
    return (p * q) || (!p * !q);
}