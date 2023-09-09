#ifndef GetAdvancedKB_H
#define GetAdvancedKB_H

#include <iostream>
#include <vector>
#include "logicalExpression.h"
#include "AdvancedKB.h"


using namespace std;

class GetAdvancedKnowledgeBase{
    private:
    /* data */

        vector<string> getEveryExpression(string _input){
            // Split the string using ';' as the delimiter
            vector<string> output;
            istringstream iss(_input);
            string temp;
            while (getline(iss, temp, ';')) {
                output.push_back(temp);
            }

            /// removing the "\n"
            output.pop_back();
            return output;
        }


        // function returns a list of logical expression
        vector<logicalExpression> gettingListOfLE(string inputString){
            vector<logicalExpression> output;
            vector<string> listOfEveryExpression = getEveryExpression(inputString);

            for (int i = 0; i < listOfEveryExpression.size(); i++){
                logicalExpression temp = logicalExpression(listOfEveryExpression[i]);
                output.push_back(temp);
            }

            return output;
        }
   
    public:
        GetAdvancedKnowledgeBase(){

        }

        // Function returns advanced KB
        AdvancedKB getAdvancedKB(string text){
            vector<logicalExpression> listOfLogicalExpressions = gettingListOfLE(text);
            AdvancedKB output = AdvancedKB(listOfLogicalExpressions);

            return output;
        }  
};

#endif