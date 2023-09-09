#ifndef Input_H
#define Input_H

#include <iostream>
#include <fstream>
#include <string>

#include "KnowledgeBase.h"
#include "GetKnowledgeBase.h"
#include "Clause.h"
#include "logicalExpression.h"
#include "GetAdvancedKnowledgeBase.h"
#include "AdvancedKB.h"


using namespace std;

class GetInput{
    private:
        /* data */
        string fileName;
    public:
        GetInput(string _fileName){
            fileName = _fileName;
        }


        // Function returns the Horn Clause KB
        KnowledgeBase getKB(){
            // get the second line
            ifstream file(fileName);
            string line;
            int lineCount = 0;

            while (std::getline(file, line)) {
                lineCount++;
                if (lineCount == 2) {
                    break;
                }
            }
            
            GetKnowledgeBase getKBAgent = GetKnowledgeBase();
            cout << line << endl;
            KnowledgeBase output = getKBAgent.getKB(line);

            return output;
        }

        // Function returns the query
        string getQuery(){
            // get the fourth line
            ifstream file(fileName);
            string line;
            int lineCount = 0;

            while (std::getline(file, line)) {
                lineCount++;
                if (lineCount == 4) {
                    break;
                }
            }

            return line;
        }

        // Function return generic KB
        AdvancedKB getAdvancedKB(){
            // get the second line
            ifstream file(fileName);
            string line;
            int lineCount = 0;

            while (std::getline(file, line)) {
                lineCount++;
                if (lineCount == 2) {
                    break;
                }
            }
            
            GetAdvancedKnowledgeBase getAdvancedKBAgent = GetAdvancedKnowledgeBase();
            cout << line << endl;
            AdvancedKB output = getAdvancedKBAgent.getAdvancedKB(line);

            return output;
        }
    };

#endif