#include <iostream>

using namespace std;


// Define the struct
struct Clause
{
    /* data */
    string mainOperator;
    string originalExpression;
    Clause left;
    Clause right;
};
