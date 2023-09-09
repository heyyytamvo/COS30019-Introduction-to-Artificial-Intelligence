#ifndef TruthTableHornClause_H
#define TruthTableHornClause_H

#include <iostream>
#include <map>
#include <vector>
#include "Clause.h"
#include "KnowledgeBase.h"

using namespace std;

class TruthTableHornClause{
    private:
        int kbCount;
        /// PL_TrueAlpha returns the value of alpha in the current model

        bool PL_TrueAlpha(string _query, map<string, bool> model){
            
            ///DEBUG
            // cout << "PL_TrueAlpha called, current query is: " << _query << endl;
            // cout << "For this model, alpha value is: " << model[_query] << endl;

            return model[_query];
        }


        /// PL_TrueKB returns true in case that: with this model, our KB is TRUE

        bool PL_TrueKB(KnowledgeBase kb, map<string, bool> model){
            // getting clauses list
            vector<Clause> listOfClause = kb.getAllClauses();
            bool output = true;

           
            // Traverse and access the keys using a range-based for loop
            
            // DEBUG print out the model
            // cout << "current model is: " << endl;
            // for (const auto& pair : model) {
            //     const string& key = pair.first;
            //     cout << key << ": " << model[key] << endl;
            // }
            // DEBUG print out the model

        
            // traverse every clause
            for (int i = 0; i < listOfClause.size(); i++){
                
                Clause currentClause = listOfClause[i];
                bool valueOfCurrentClauseWithThisModel = true; 

                /// DEBUG print out the current clause
        
                // if the clause only has the conclusion, 
                if (currentClause.containPremise() == false){
                    valueOfCurrentClauseWithThisModel = model[currentClause.getConclusion()];
                } 
                // if the clause has the premise and conclusion
                else{
                    vector<string> listOfSymbolsInPremise = currentClause.getPremise();
                    string conclusionOfThisClause = currentClause.getConclusion();

                    // a => b equivalent to !a or b
                    // if the conclusion is true, then this clause is true

                    if (model[conclusionOfThisClause]){
                        valueOfCurrentClauseWithThisModel = true;
                    }
                    /// if the conjunction of every symbol in the premise is false, then this clause is True
                    else{
                        
                        /// traverse every symbols in the premise symbols list
                        bool _conjunction = true;
                        for (int j = 0; j < listOfSymbolsInPremise.size(); j++){
                            string symbol = listOfSymbolsInPremise[j];
                            _conjunction = _conjunction && model[symbol];
                        }

                        valueOfCurrentClauseWithThisModel = valueOfCurrentClauseWithThisModel && !_conjunction;
                    }
                }

                output = output && valueOfCurrentClauseWithThisModel;
            }

            // DEBUG print out the output of this model
            // cout << "With this model, our KB value is " << output << endl;
            // DEBUG print out the output of this model
            if (output){
                kbCount++;
            }
            return output;
        }

        
        map<string, bool> extendModel(string key, bool value, map<string, bool> model){
            // Adding a new key-value pair using the insert() method
            map<string, bool> result;
            result.insert(model.begin(), model.end());
            result.insert(make_pair(key, value));

            return result;
        }
    
        bool TTCheckAll(KnowledgeBase kb, string alp, vector<string> symbols, map<string, bool> model){

            /// if list of symbols is empty
            if (symbols.empty()){
                if (PL_TrueKB(kb, model)){
                    return PL_TrueAlpha(alp, model);
                }
                return true;
            }
            ///else, list of symbols is not empty
            
            vector<string> listOfSymbolCopy;
            listOfSymbolCopy.assign(symbols.begin(), symbols.end());
            string P = listOfSymbolCopy[0];
            listOfSymbolCopy.erase(listOfSymbolCopy.begin());


            // Generating new model where P is true
            map<string, bool> restUnionWithPTrue = extendModel(P, true, model);
            
            // Generating new model where P is false
            map<string, bool> restUnionWithPFalse = extendModel(P, false, model);
        
            return (TTCheckAll(kb, alp, listOfSymbolCopy, restUnionWithPTrue)) && (TTCheckAll(kb, alp, listOfSymbolCopy, restUnionWithPFalse));
            
        }

        bool TT_Entails(KnowledgeBase kb, string alpha){
            /// a list of propositional symbols in KB and alpha
            vector<string> symbols = kb.getSymbols();

            // checking that alpha is contained in the symbols list or not, if 
            // not, add it to the symbols list
            auto it = find(symbols.begin(), symbols.end(), alpha);
            if (it == symbols.end()){
                symbols.push_back(alpha);
            }
        
            map<string, bool> model;
            bool result = TTCheckAll(kb, alpha, symbols, model);
            return result;
        }
    
    public:
        TruthTableHornClause(){
            kbCount = 0;
        }

        void solve(KnowledgeBase kb, string query){
            bool result = TT_Entails(kb, query);

            if (result){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }

            cout << kbCount << endl;
            
        }

        
    //
};
#endif