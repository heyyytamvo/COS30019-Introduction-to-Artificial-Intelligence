#ifndef Clause_H
#define Clause_H

#include <iostream>
#include <vector>
using namespace std;

class Clause{
    private:
        vector<string> premise;
        string conclusion;
    public:
        ///CONSTRUCTION
        Clause(vector<string> _premise, string _conclusion){
            premise = _premise;
            conclusion = _conclusion;
        }

        /// Function returns true if the clause contains premise
        bool containPremise(){
            return (premise.size() > 0);
        }
    
        /// Function returns the list of symbol in premise
        vector<string> getPremise(){
            return premise;
        }

        /// Function returns the conclusion
        string getConclusion(){
            return conclusion;
        }

        /// Function returns the entire clause as a string
        string getClauseAsString(){
            string output = "";
            if (premise.size() > 0){
                for (int i = 0; i < premise.size(); i++){
                    string currentSymbol = premise[i];
                    output += currentSymbol;
                
                    if (i < premise.size() - 1){
                        output += " & ";
                    }
                }

                output += " => ";
                output += conclusion;
            }
            else{
                output += conclusion;
            }
            return output;
        }


        // function checking the symbols is contained in the premise
        bool containedInPremise(string symbol){
            for (int i = 0; i < premise.size(); i++){
                if (symbol == premise[i]){
                    return true;
                }
            }

            return false;
        }

};
#endif