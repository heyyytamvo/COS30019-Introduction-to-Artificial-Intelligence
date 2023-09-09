#include <iostream>
#include <map>

#include "logicalExpression.h"

using namespace std;


void printAll(logicalExpression original){
    vector<logicalExpression> listChild = original.getChildren();
    cout << "Current expression is: ";
     cout << original.getOriginalExpression() << endl;

    for (int i = 0; i < listChild.size(); i++){
        if (listChild[i].containOnlySymbol()){
            cout << listChild[i].getOriginalExpression() << endl;
        }

        printAll(listChild[i]);
    }
}

// function returns all symbols in the logical expression
vector<string> getSymbols(logicalExpression _logicalExpression){
    vector<string> output;
    if (_logicalExpression.containOnlySymbol()){
        output.push_back(_logicalExpression.getOriginalExpression());
        return output;
    }

    for (int i = 0; i < _logicalExpression.getChildren().size(); i++){
        logicalExpression currentChild = _logicalExpression.getChildren()[i];
        vector<string> temp = getSymbols(currentChild);

        for (int j = 0; j < temp.size(); j++){
            
            // ensure the result is already in the output
            if (count(output.begin(), output.end(), temp[j]) == 0){
                output.push_back(temp[j]);
            }
        }
    }

    return output;
}

int main(){
    logicalExpression a = logicalExpression("(a <=> (c => ~d)) & b & (b => a)");
    a.getOriginalExpression();
    // printAll(a);

    // vector<logicalExpression> childList = a.getChildren();
    vector<string> symbols = getSymbols(a);
    for (int i = 0; i < symbols.size(); i++){
        cout << symbols[i] << " ";
    }


    return 0;
    
}