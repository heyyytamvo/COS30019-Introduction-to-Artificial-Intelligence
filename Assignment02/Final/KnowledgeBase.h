#ifndef KnowledgeBase_H
#define KnowledgeBase_H

#include <iostream>
#include <vector>
#include "Clause.h"

class KnowledgeBase{
    private:
        vector<Clause> clauses;
    public:
       /// CONSTRUCTION
        KnowledgeBase(vector<Clause> _clauses){
            clauses = _clauses;
        }

        /// Function returns the list of ALL clauses
        vector<Clause> getAllClauses(){
            return clauses;
        }

        /// Function returns the list of all symbols that are contained in the KB
        vector<string> getSymbols(){
            vector<string> output;

            /// Checking every clause in the knowledge base
            for (int i = 0; i < clauses.size(); i++){
                
                Clause currentClause = clauses[i];
            
                /// if that clause contains premise, else, ignore the premise
                if (currentClause.containPremise()){
                    vector<string> listOfSymbolsInPremise = currentClause.getPremise();
                
                    for (int j = 0; j < listOfSymbolsInPremise.size(); j++){
                        string currentSymbol = listOfSymbolsInPremise[j];

                        ///checking the current symbo is contained in the output or not
                        if (count(output.begin(), output.end(), currentSymbol) == 0){
                            output.push_back(currentSymbol);
                        }
                    }
                }

                ///checking the current conclusion is contained in the output or not
                string conclusion = currentClause.getConclusion();
        
                if (count(output.begin(), output.end(), conclusion) == 0){
                    output.push_back(conclusion);
                }
            }

            return output;
        }


        // Function returns fact from KB
        vector<string> getFact(){
            vector<string> result;
            
            for (int i = 0; i < clauses.size(); i++){
                Clause currentClause = clauses[i];
                if (currentClause.containPremise() == false){
                    result.push_back(currentClause.getConclusion());
                }
            }
            
            return result;
        }
};
#endif