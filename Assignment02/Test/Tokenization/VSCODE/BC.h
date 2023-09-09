#ifndef BC_H
#define BC_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>


#include "KnowledgeBase.h"
#include "Clause.h"
using namespace std;


class BC{
    private:
        /* data */
        queue<string> propositionalEntailed;
        unordered_map<string, bool> fact;

        bool BC_Entail(KnowledgeBase kb, string query){
            
            /// Base case, query exists in fact list
            if (fact.count(query) > 0){
                propositionalEntailed.push(query);
                return true;
            }

            vector<Clause> listOfClauses = kb.getAllClauses();
            /// getting the clause in KB where the query is in the conclusion
            bool output = true;
            for (int i = 0; i < listOfClauses.size(); i++){
                Clause currentClause = listOfClauses[i];
                if (currentClause.getConclusion() == query){
                    
                    // traverse all symbols in the premise
                    vector<string> premiseList = currentClause.getPremise();
                    for (int j = 0; j < premiseList.size(); j++){
                        output = output && BC_Entail(kb, premiseList[j]);   
                        if (output){
                            fact.insert(make_pair(query, true));
                            propositionalEntailed.push(query);
                        }
                    }
                }
            }

            return fact[query];
        }    


          
        
    public:
        BC(){

        };
    
    void solve(KnowledgeBase kb, string query){
        vector<string> factList = kb.getFact();
        
        for (int i = 0; i < factList.size(); i++){
            fact.insert(make_pair(factList[i], true));
        }
        bool result = BC_Entail(kb, query);
        if (result){
            cout << "YES: ";

            while (propositionalEntailed.empty() == false){
                cout << propositionalEntailed.front() << " ";
                propositionalEntailed.pop();
            }
            cout << endl;
        }else{
            cout << "NO" << endl;
        }

        // cout << fact.size() << endl;
        // Iterate over the keys and values and print them
        // for (auto it = fact.begin(); it != fact.end(); ++it) {
        //     std::cout << it->first << ": " << it->second << std::endl;
        // }
    }
};


#endif