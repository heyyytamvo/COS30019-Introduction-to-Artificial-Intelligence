#ifndef GetKnowledgeBase_H
#define GetKnowledgeBase_H

#include <iostream>
#include <vector>
#include <sstream>
#include "Clause.h"
#include "KnowledgeBase.h"

using namespace std;

class GetKnowledgeBase{
    private:
        vector<string> getEveryExpression(string _input){
            // Split the string using ';' as the delimiter
            vector<string> output;
            istringstream iss(_input);
            string temp;
            while (getline(iss, temp, ';')) {
                output.push_back(temp);
            }

            /// DEBUG NOTE: these lines of code fix the reading problem
            /// counting the ";"
            int count = 0;
            for (int i = 0; i < _input.size(); i++){
                if (_input[i] == ';'){
                    count++;
                }
            }

            if (output.size() == count + 1){
                /// removing the "\n"
                output.pop_back();
            }
            /// DEBUG NOTE: these lines of code fix the reading problem


            return output;
        }

        // Function to remove whitespaces from a string
        string removeWhiteSpace(string inputString) {
            size_t firstNonSpace = inputString.find_first_not_of(" \t\n\r");
            size_t lastNonSpace = inputString.find_last_not_of(" \t\n\r");

            if (firstNonSpace == string::npos || lastNonSpace == string::npos) {
                // The string contains only whitespaces or is empty
                return "";
            }

            return inputString.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        }

        // Function to get every clause in the KB
        vector<Clause> gettingListOfClause(string inputKnowledgeBase){
            vector<Clause> result;
            vector<string> listOfEveryExpression = getEveryExpression(inputKnowledgeBase); ////
            for (int i = 0; i < listOfEveryExpression.size(); i++) {
                string currentClause = removeWhiteSpace(listOfEveryExpression[i]);
                string premise;
                string conclusion;

                // cout << "Current clause: " << currentClause << endl;

                // ONLY READ Horn clause
                // If a clause contains "=>", its length must be greater than 3
                if (currentClause.length() > 3) {

                    vector<string> listOfSymbolsInPremise;
                    // Get the index of '=' in "=>"
                    int indexOfEqualSign = -1;
                    for (int j = 0; j < currentClause.size(); j++) {
                        char current = currentClause[j];
                        if (current == '=') {
                            indexOfEqualSign = j;
                            break;
                        }
                    }

                    // Ensure '=' is found, and it's not the first or last character
                    if (indexOfEqualSign > 0 && indexOfEqualSign < currentClause.size() - 1) {
                        // Getting the list of all symbol in premise 
                        premise = removeWhiteSpace(currentClause.substr(0, indexOfEqualSign));
                
                        istringstream iss(premise);

                        string symbol;
                        while (getline(iss, symbol, '&')) {
                            symbol = removeWhiteSpace(symbol);
                            listOfSymbolsInPremise.push_back(symbol);
                        }
                        // Determine the conclusion of the Horn Clause
                        conclusion = removeWhiteSpace(currentClause.substr(indexOfEqualSign + 2));

                        Clause newClause = Clause(listOfSymbolsInPremise, conclusion);
                        result.push_back(newClause);

                    } else {
                        // // Invalid Horn clause format
                        continue;
                    }
                } else { // else, the clause contains only one symbol
                    // Determine the conclusion of the Horn Clause
                    conclusion = currentClause;
                    vector<string> listOfSymbolsInPremise;
                    Clause newClause = Clause(listOfSymbolsInPremise, conclusion);
                    result.push_back(newClause);
                }
            }

            return result;
        }
    public:
        GetKnowledgeBase(){

        }

        KnowledgeBase getKB(string text){
            vector<Clause> listOfClause = gettingListOfClause(text);
            KnowledgeBase output = KnowledgeBase(listOfClause);

            return output;
        }

};
#endif

