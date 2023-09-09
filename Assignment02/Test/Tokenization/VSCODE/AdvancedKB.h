#ifndef AdvancedKB_H
#define AdvancedKB_H

#include <iostream>
#include <vector>

#include "logicalExpression.h"

using namespace std;


class AdvancedKB{
    private:
        /* data */
        vector<logicalExpression> logicalExpressions;
    
        // function returns all symbols in A logical expression
        vector<string> getSymbolsInEachLE(logicalExpression _logicalExpression){
            vector<string> output;
            if (_logicalExpression.containOnlySymbol()){
                output.push_back(_logicalExpression.getOriginalExpression());
                return output;
            }

            for (int i = 0; i < _logicalExpression.getChildren().size(); i++){
                logicalExpression currentChild = _logicalExpression.getChildren()[i];
                vector<string> temp = getSymbolsInEachLE(currentChild);

                for (int j = 0; j < temp.size(); j++){
            
                    // ensure the result is already in the output
                    if (count(output.begin(), output.end(), temp[j]) == 0){
                        output.push_back(temp[j]);
                    }
                }
            }

            return output;
        }

    public:
        AdvancedKB(vector<logicalExpression> _logicalExpressions){
            logicalExpressions = _logicalExpressions;
        }

        /// Function returns the list of ALL logical Expression
        vector<logicalExpression> getAllLogicalExpression(){
            return logicalExpressions;
        }
        
        /// Function returns the list of all symbols that are contained in the KB
        vector<string> getSymbolsOfAdvancedKB(){
            vector<string> output;

            //traverse every logical expression
            for (int i = 0; i < logicalExpressions.size(); i++){
                logicalExpression currentLE = logicalExpressions[i];
                vector<string> listOfSymbolsInCurrentLE = getSymbolsInEachLE(currentLE);

                for (int j = 0; j < listOfSymbolsInCurrentLE.size(); j++){
                    // ensure current symbol is not in the output
                    if (count(output.begin(), output.end(), listOfSymbolsInCurrentLE[j]) == 0){
                        output.push_back(listOfSymbolsInCurrentLE[j]);
                    }
                }
            }

            return output;
        }



};

#endif