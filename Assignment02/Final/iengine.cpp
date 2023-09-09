#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "GetInput.h"
#include "KnowledgeBase.h"
#include "Clause.h"
#include "AdvancedKB.h"
#include "FC.h"
#include "BC.h"
#include "TruthTableHornClause.h"
#include "TruthTableGenericKB.h"
using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Invalid Command Line" << endl;
        cout << "Make sure the command line is valid as below: " << endl;
        cout << "./iengine TT/FC/BC hornClause.txt" << endl;
        cout << "./iengine TTGenericKB genericKB.txt" << endl;
        return 1;
    }

    string choice = argv[1];
    GetInput getInputAgent = GetInput(argv[2]);
    string query = getInputAgent.getQuery();
    if (choice == "FC"){
        cout << "KB: ";
        KnowledgeBase kb = getInputAgent.getKB();
        cout << "Query: " << query << endl;
        FC FCAgent = FC();
        FCAgent.solve(kb, query);
    }else if (choice == "BC"){
        cout << "KB: ";
        KnowledgeBase kb = getInputAgent.getKB();
        cout << "Query: " << query << endl;
        BC BCAgent = BC();
        BCAgent.solve(kb, query);
    }else if (choice == "TT"){
        cout << "KB: ";
        KnowledgeBase kb = getInputAgent.getKB();
        cout << "Query: " << query << endl;
        TruthTableHornClause TTAgent = TruthTableHornClause();
        TTAgent.solve(kb, query);
    }else if (choice == "TTGeneric"){
        cout << "KB: ";
        AdvancedKB kb = getInputAgent.getAdvancedKB();
        cout << "Query: " << query << endl;
        TruthTableGenericKB GenericKBAgent = TruthTableGenericKB();
        GenericKBAgent.solve(kb, query);
    }else{
        cout << "Invalid method, here is the list of method" << endl;
        cout << "FC: Forward Chaining for Horn Clause" << endl;
        cout << "BC: Backward Chaining for Horn Clause" << endl;
        cout << "TT: Truth Table for Horn Clause" << endl;
        cout << "TTGeneric: Truth Table for generic knowledge base" << endl;
    }

    return 0;
}